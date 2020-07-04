//
// This program is free software: you can redistribute it and/or modify

// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

// TODO
// Calcul d'utilité
    // Utility=(Nbr_Neighbors,Distance _emmiteur recepteur,CBR occupation du canal)

// Calcul Des clusters
#include "TRAD.h"
#include <WaveShortMessage_m.h>
#include <BeaconMessage_m.h>
#include <iostream>

using Veins::TraCIMobility;
using Veins::TraCIMobilityAccess;
using Veins::AnnotationManagerAccess;

using std::map;
using std::vector;
using std::string;
const double timeSlot = 0.000013;

Define_Module(TRAD);

const simsignalwrap_t TRAD::mobilityStateChangedSignal = simsignalwrap_t(MIXIM_SIGNAL_MOBILITY_CHANGE_NAME);

void TRAD::initialize(int stage) {
    BASE_TRAD::initialize(stage);

    if (stage == 0) {


         //TODO: Added for Game Theory Solution
         lastTxPower = registerSignal("lastTxPower");
         meanSNR = registerSignal("meanSNR");

         sentDownMACInCCH = registerSignal("sentDownMACInCCH");
         collisions = registerSignal("collisions");
         messagesTransmittedSCF = registerSignal("messagesTransmittedSCF");
         messagesReceivedSCF = registerSignal("messagesReceivedSCF");
         duplicatedMessages = registerSignal("duplicatedMessages");
         messagesTransmitted = registerSignal("messagesTransmitted");
         messagesReceived = registerSignal("messagesReceived");
         isInROI = registerSignal("isInROI");

         //wasInROI = false;
         disseminationStarted = false;

         simulation.getSystemModule()->subscribe("disseminationStartTime", this);

         mac = FindModule<Mac1609_4*>::findSubModule(getParentModule());
         assert(mac);

         //TODO: Added for Game Theory Solution
         curTxPower = mac->par("txPower");
         powerLevel = 3;
         myUtilityValue = 0;

         lastNumCollisions = 0;
         totalCollisions = 0;
         receivedData=0;

        mobility = TraCIMobilityAccess().get(getParentModule());
        traci = mobility->getCommandInterface();
        traciVehicle = mobility->getVehicleCommandInterface();
        annotations = AnnotationManagerAccess().getIfExists();
        ASSERT(annotations);

        broadcastTimer = new cMessage("broadcast timeOut", BROADCAST_TIMEOUT);

    }
}

void TRAD::finish() {
    BASE_TRAD::finish();

    /* if (wasInROI) {
     emit(isInROI, 1);
     } else {
     emit(isInROI, 0);
     }

     //TODO: Added for Game Theory Solution
     emit(lastTxPower, curTxPower);

     emit(collisions, totalCollisions);

     if (!messagesRcvd.empty()) {
     std::ofstream log;
     std::ostringstream o;

     o << "./results/" << par("log_traffic").longValue() << "-" << par("log_replication").longValue() << "-receiver-" << myId;
     log.open(o.str().c_str());

     for (std::map<int, MessageInfoEntry*>::iterator i = messagesRcvd.begin(); i != messagesRcvd.end(); i++) {
     MessageInfoEntry* videoInfo = i->second;

     log << videoInfo->receptionTime << " " << "id " << videoInfo->messageID << " " << "udp " << videoInfo->messageLength << " " << videoInfo->distanceToOrigin << endl;
     }
     log.close();
     }*/
    //TODO: Added for Game Theory Solution

     emit(lastTxPower, curTxPower);
     emit(collisions, totalCollisions);

     simulation.getSystemModule()->unsubscribe("disseminationStartTime", this);
}

WaveShortMessage* TRAD::createDataMsg(DataMessage* data) {
 WaveShortMessage* wsm = prepareWSM("data", dataLengthBits, type_SCH, dataPriority, 0, data->getMessage_id());

 //TODO: Added for Game Theory Solution
 PhyControlMessage *controlInfo = new PhyControlMessage();
 controlInfo->setTxPower_mW(curTxPower);
 wsm->setControlInfo(dynamic_cast<cObject *>(controlInfo));

 DataMessage* msg = new DataMessage("data");

 msg->setSender_id(getParentModule()->getIndex());
 msg->setMessageOriginPosition(data->getMessageOriginPosition());
 //msg->setMessageROI(info->messageROI);
 msg->setMessageOriginTime(data->getMessageOriginTime());
 msg->setMessageTTL(data->getMessageTTL());
 msg->setListe_priority_trad(classify_clusters());
 msg->setMessage_id(data->getMessage_id());
 //msg->setHops(info->hops);

 /*if (info->SCF) {
 msg->setSentSCFState(true);
 }*/

 wsm->setByteLength(data->getMessageLength());

 wsm->encapsulate(msg);

 return wsm;
 }

void TRAD::handleSelfMsg(cMessage* msg) {
    BASE_TRAD::handleSelfMsg(msg);//Nettoyage de la liste des voisins
    switch (msg->getKind()) {

    case SEND_BEACON_EVT: {
        WaveShortMessage* wsm = prepareWSM("beacon", beaconLengthBits, type_CCH,
                beaconPriority, 0, -1);
        BeaconMessage* beaconMsg = new BeaconMessage("beacon");

        beaconMsg->setSpeed(mobility->getSpeed());

        beaconMsg->setCarId(wsm->getSenderAddress());
        beaconMsg->setPosition(wsm->getSenderPos());

        beaconMsg->setAngleRad(mobility->getAngleRad());

        //x,y,z ne sont pas vrai
        beaconMsg->setVecX(wsm->getSenderPos().x);

        beaconMsg->setVecY(wsm->getSenderPos().y);

        beaconMsg->setVecZ(wsm->getSenderPos().z);


        //temps d'occupation du canal
         Mac1609_4* myMacp = FindModule<Mac1609_4*>::findSubModule(getParentModule());
        simtime_t tbt=myMacp->statsTotalBusyTime;
        double tI=(simTime()-tbt)/simTime();

        beaconMsg->setCbr(tI);
        beaconMsg->setNbr_neighbor(neighbors.size());
        beaconMsg->setListe_message_urgence(indicesWarnigMsgsApp);


        wsm->encapsulate(beaconMsg);
        sendWSM(wsm);
        scheduleAt(simTime() + par("beaconInterval").doubleValue(),sendBeaconEvt);


        break;
    }

        /* unsigned int j = 0;
         for (std::map<int, MessageInfoEntry*>::iterator i = messagesRcvd.begin(); i != messagesRcvd.end(); i++) {
         int messageID = i->first;

         beaconMsg->setReceivedMessages(j, messageID);
         j++;
         }

         wsm->encapsulate(beaconMsg);

         Coord rsuPosition = Coord(par("eventOriginX").doubleValue(), par("eventOriginY").doubleValue(), par("eventOriginZ").doubleValue());
         if (simTime() > par("startDataProductionTime").doubleValue() - 3 &&
         curPosition.distance(rsuPosition) <= par("dataROI").doubleValue() + 300) {

         sendWSM(wsm);
         } else {
         delete wsm;
         }

         scheduleAt(simTime() + par("beaconInterval").doubleValue(), sendBeaconEvt);
         break;
         }*/

        case BROADCAST_TIMEOUT: {
         DataMessage* data = (DataMessage*) msg->getContextPointer();


         if (isMessageAlive(data)) {
            EV << "******************Rebroadcast le message id:**********************"  << data->getMessage_id() << endl;
            WaveShortMessage* wsm = createDataMsg(data);

             sendWSM(wsm);


             emit(messagesTransmitted, 1);

             if (isCCHActive()) {
             emit(sentDownMACInCCH, 1);
             }
         }

         delete broadcastTimer;
         broadcastTimer = NULL;

         break;
         }

         /*case SCF_TIMEOUT: {
         MessageInfoEntry* info = (MessageInfoEntry*) msg->getContextPointer();

         if (isInsideROI(info) && isMessageAlive(info)) {
         WaveShortMessage* wsm = createDataMsg(info);
         sendWSM(wsm);

         emit(messagesTransmittedSCF, 1);
         emit(messagesTransmitted, 1);

         if (isCCHActive()) {
         emit(sentDownMACInCCH, 1);
         }
         }

         delete info->broadcastTimer;
         info->broadcastTimer = NULL;

         break;
         }



         case BACK_TRAFFIC_ENTRY_TIMEOUT: {
         TRADNeighborEntry* entry = (TRADNeighborEntry*) msg->getContextPointer();
         int address = entry->senderAddress;
         cancelAndDelete(entry->cleanUpTimer);
         entry->cleanUpTimer = NULL;
         lastRequesters.erase(address);

         break;
         }*/

         case CCH_START: {
         totalCollisions = totalCollisions + mac->statsTXRXLostPackets - lastNumCollisions;
         scheduleAt(simTime() + SWITCHING_INTERVAL_11P + SWITCHING_INTERVAL_11P, CCHStartTimer);
         break;
         }
// Indique le début du SCH et le nombre de packets perdu entre sch et cch est calculé
         //par mac->statsTXRXLostPackets - lastNumCollisions; et qui va etre ajouté au total collision
         case SCH_START: {
         lastNumCollisions = mac->statsTXRXLostPackets;
         scheduleAt(simTime() + SWITCHING_INTERVAL_11P + SWITCHING_INTERVAL_11P, SCHStartTimer);
         break;
         }

         default: {
         if (msg)
         EV << "TRAD - Error: Got Self Message of unknown kind! Name: " << msg->getName() << endl;
         break;
         }
    }
}

void TRAD::onBeacon(WaveShortMessage* wsm1) {
    BASE_TRAD::onBeacon(wsm1);
}

bool TRAD::isDuplicateMsg(int idMsg) {

    return receivedWarningMessageMap.find(idMsg) != receivedWarningMessageMap.end();

 }

double DeferTime(int ordre){

    double Delay=0.0;
    double trad_st=0.005;

    Delay= double(ordre+1)*trad_st;
    return Delay;

  }


void TRAD::onData(WaveShortMessage* wsm) {
    BASE_TRAD::onData(wsm);


    if (par("adaptTxPower").boolValue())
       adjustTxPower(wsm);

       DataMessage* dataMsg = dynamic_cast<DataMessage*>(wsm->decapsulate());
        EV << "******************Message reçuuuuuuuuuuu dont le Id est***********"<< dataMsg->getMessage_id() << endl;


     if (!isDuplicateMsg(dataMsg->getMessage_id())) {

     //scheduleRebroadcast(info, wsm->getSenderPos(), BROADCAST_TIMEOUT);

         EV << "******************Message reçu dont le Id est**********************"<< dataMsg->getMessage_id() << endl;
     // Store message
         receivedWarningMessageMap[dataMsg->getMessage_id()] = dataMsg;

         //receivedData++;
         //emit(messagesReceived, receivedData);

         emit(messagesReceived, 1);

         neighbors_rec myliste_priority_trad=dataMsg->getListe_priority_trad();

         int order=-1;
         int myId= getParentModule()->getIndex();

         for(int i=0; i<int(myliste_priority_trad.size()); ++i){
             if(myId==myliste_priority_trad[i].sender_id)
              order=i;
         }

         if (order!=-1){
             double myDeferTime =0.0;
             myDeferTime=DeferTime(order);



// Adjust dataRateTimer to send message down to MAC only when the Service Channel is active.
 //  If current time is Control Channel, then
  //schedule time to the next Service Channel cycle

             if (par("desynchronize").boolValue()) {
                 myDeferTime = desynchronize(myDeferTime);
             }

             broadcastTimer->setContextPointer((DataMessage*) dataMsg);
             scheduleAt(simTime() + myDeferTime, broadcastTimer);


         }
     }else {
     // If vehicle is in broadcast suppression, then leave it
     //if (info->broadcastTimer && info->broadcastTimer->isScheduled()){
     //cancelAndDelete(info->broadcastTimer);
     //info->broadcastTimer = NULL;
         if (broadcastTimer && broadcastTimer->isScheduled()) {
              cancelAndDelete(broadcastTimer);
              broadcastTimer = NULL;
         }
               emit(duplicatedMessages, 1);
        }
}


/*void TRAD::scfPolicyMissingPackets(WaveShortMessage* wsm) {
 BeaconMessage* beaconMsg = dynamic_cast<BeaconMessage*>(wsm->decapsulate());

 for (std::map<int, MessageInfoEntry*>::iterator i = messagesRcvd.begin(); i != messagesRcvd.end(); i++) {
 MessageInfoEntry* info = i->second;
 bool received = false;
 int numMsgsRcvd = beaconMsg->getReceivedMessagesArraySize();

 for (int j = 0; j < numMsgsRcvd; j++) {
 int msgRcvdID = beaconMsg->getReceivedMessages(j);
 if (msgRcvdID == info->messageID) {
 received = true;
 break;
 }
 }

 if (!received && info->SCF && !info->broadcastTimer) {
 scheduleRebroadcast(info, wsm->getSenderPos(), SCF_TIMEOUT);
 }
 received = false;
 }

 delete beaconMsg;
 }*/

double TRAD::desynchronize(double delay) {
 // Adjust dataRateTimer to send message down to MAC only when the
 // Service Channel is active. If current time is Control Channel, then
 // schedule time to the next Service Channel cycle
 uint64_t currenTime = simTime().raw();
 uint64_t switchingTime = SWITCHING_INTERVAL_11P.raw();
 double timeToNextSwitch = (double)(switchingTime - (currenTime % switchingTime)) / simTime().getScale();
 // Control Channel is active
 if ((currenTime / switchingTime) % 2 == 0) {
 int rounds = floor(delay / 0.05);
 delay = timeToNextSwitch + delay + (rounds * 0.05) + 0.000000000001;

 // Service Channel is active
 } else {
 double delay_tmp = delay - timeToNextSwitch;
 if (delay_tmp > 0) {
 int rounds = ceil(delay_tmp / 0.05);
 delay = delay + (rounds * 0.05);
 }
 }

 return delay;
 }

 bool TRAD::isCCHActive() {
 uint64_t currenTime = simTime().raw();
 uint64_t switchingTime = SWITCHING_INTERVAL_11P.raw();

 return ((currenTime / switchingTime) % 2 == 0);
 }





/*bool TRAD::isInsideROI(MessageInfoEntry* info) {
 return info->messageOriginPosition.distance(curPosition) < info->messageROI;
 }*/

 bool TRAD::isMessageAlive(DataMessage* msg) {
 return simTime() < msg->getMessageOriginTime() + msg->getMessageTTL();
 }



 /*void TRAD::insertEntry(int senderAddr, Coord senderPos) {
 if (neighbors.find(senderAddr) == neighbors.end()) {
 TRADNeighborEntry* entry = new TRADNeighborEntry;

 entry->senderAddress = senderAddr;
 entry->position = senderPos;

 entry->cleanUpTimer = new cMessage("entry timeout", ENTRY_TIMEOUT);
 entry->cleanUpTimer->setContextPointer((TRADNeighborEntry*) entry);
 scheduleAt(simTime() + par("beaconEntryTTL").doubleValue(), entry->cleanUpTimer);

 neighbors[senderAddr] = entry;
 } else {
 TRADNeighborEntry* entry = neighbors[senderAddr];
 entry->position = senderPos;
 cancelEvent(entry->cleanUpTimer);
 scheduleAt(simTime() + par("beaconEntryTTL").doubleValue(), entry->cleanUpTimer);
 }
 }

 void TRAD::processBackTraffic(int senderAddr) {
 if (lastRequesters.find(senderAddr) == lastRequesters.end()) {
 // Send 60 packets of 1000 bytes on the Service Channel
 for (int i = 0; i < 60; i++) {
 WaveShortMessage* wsm = prepareWSM("back traffic", dataLengthBits, type_SCH, dataPriority, 0, i);
 wsm->setByteLength(1000);

 sendWSM(wsm);
 }

 TRADNeighborEntry* entry = new TRADNeighborEntry;

 entry->cleanUpTimer = new cMessage("beacon entry timeout", BACK_TRAFFIC_ENTRY_TIMEOUT);
 entry->cleanUpTimer->setContextPointer((TRADNeighborEntry*) entry);
 scheduleAt(simTime() + 3, entry->cleanUpTimer);

 lastRequesters[senderAddr] = entry;
 }
 }

 void TRAD::addGPSError() {
 cRNG *rng = getRNG(9);
 double randomNumber, error;

 randomNumber = rng->doubleRand(); // Generate value in [0, 1)
 error = randomNumber * par("maxGPSError").doubleValue();

 if (randomNumber > 0.5) {
 curPosition.x += error;
 curPosition.y += error;
 } else {
 curPosition.x -= error;
 curPosition.y -= error;
 }
 }

 void TRAD::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details) {
 Enter_Method_Silent();
 BaseWaveApplLayer::receiveSignal(source, signalID, obj, details);

 if (signalID == mobilityStateChangedSignal) {
 Coord rsuPosition = Coord(par("eventOriginX").doubleValue(), par("eventOriginY").doubleValue(), par("eventOriginZ").doubleValue());

 if (disseminationStarted && curPosition.distance(rsuPosition) <= par("dataROI").doubleValue() &&
 ((simTime() >= disseminationStartTime) && (simTime() <= (disseminationStartTime + par("dataTTL").doubleValue())))) {
 wasInROI = true;
 }

 if (par("maxGPSError").doubleValue() > 0) {
 addGPSError();
 }
 }
 }

 void TRAD::receiveSignal(cComponent *source, simsignal_t signalID, const SimTime& t) {
 Enter_Method_Silent();

 if (!strcmp(getSignalName(signalID), "disseminationStartTime")) {
 disseminationStarted = true;
 disseminationStartTime = simTime();
 Coord rsuPosition = Coord(par("eventOriginX").doubleValue(), par("eventOriginY").doubleValue(), par("eventOriginZ").doubleValue());

 if (curPosition.distance(rsuPosition) <= par("dataROI").doubleValue())
 wasInROI = true;
 }
 }*/

 //TODO: Added for Game Theory Solution
 void TRAD::adjustTxPower(WaveShortMessage* wsm) {
 double rcvTxPower, rcvSNR, utility;

 rcvTxPower = ((DeciderResult80211*)((PhyToMacControlInfo*)wsm->getControlInfo())->getDeciderResult())->getRecvPower_dBm();
 // Convert dBm to mW
 rcvTxPower = pow(10.0, rcvTxPower / 10.0);
 rcvSNR = ((DeciderResult80211*)((PhyToMacControlInfo*)wsm->getControlInfo())->getDeciderResult())->getSnr();

 utility = (1 * log(1 + rcvSNR) - (0.009 * curTxPower));

 //if (rcvTxPower >= curTxPower) {
 if (myUtilityValue > utility) {
 myUtilityValue = utility;
 //increaseTxPower();
 } else {
 decreaseTxPower();
 }
 //}

 emit(meanSNR, rcvSNR);
 }

 //TODO: Added for Game Theory Solution
 void TRAD::decreaseTxPower() {
 const double txPowerVals[] = {0.61, 0.98, 1.6, 2.2};

 if (powerLevel > 0) {
 powerLevel--;
 curTxPower = txPowerVals[powerLevel];
 }
 }

 //TODO: Added for Game Theory Solution
 void TRAD::increaseTxPower() {
 const double txPowerVals[] = {0.61, 0.98, 1.6, 2.2};

 if (powerLevel < 3) {
 powerLevel++;
 curTxPower = txPowerVals[powerLevel];
 }

 }

TRAD::~TRAD() {

     cancelAndDelete(broadcastTimer);

     cancelAndDelete(cleanUpTimer);

     cancelAndDelete(CCHStartTimer);
     cancelAndDelete(SCHStartTimer);
}
