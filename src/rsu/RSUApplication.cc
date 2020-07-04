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

#include "RSUApplication.h"



Define_Module(RSUApplication);

const simsignalwrap_t RSUApplication::mobilityStateChangedSignal = simsignalwrap_t(MIXIM_SIGNAL_MOBILITY_CHANGE_NAME);

void RSUApplication::initialize(int stage) {
    BASE_TRAD::initialize(stage);
    hasMobility=false;
    if (stage == 0) {
        if (par("sendData").boolValue()) {
            datarate = par("datarate").doubleValue();
            disseminationStarted = false;
            packet_send= false;
            disseminationStartTime = registerSignal("disseminationStartTime");


            // Schedule end simulation
            cMessage* m = new cMessage("end simulation", END_SIMULATION);
            scheduleAt(par("startDataProductionTime").doubleValue() + par("dataTTL").doubleValue(), m);

            //TODO: Changed for Game Theory project
            emit(disseminationStartTime, par("startDataProductionTime").doubleValue());
            disseminationStarted = true;

            readDataFromFile();
            sendDataTimer = new cMessage("Send data", SEND_DATA);
            scheduleAt(par("startDataProductionTime").doubleValue(), sendDataTimer);
        }
    }
}

void RSUApplication::finish() {
    BASE_TRAD::finish();

    std::ofstream log;
    std::ostringstream o;

    o << "./results/" << par("log_traffic").longValue() << "-" << par("log_replication").longValue() << "-sender";
    log.open(o.str().c_str());

    for (std::map<simtime_t, MessageEntryInfo*>::iterator i = loggingInfo.begin(); i != loggingInfo.end(); i++) {
        simtime_t time = i->first;
        MessageEntryInfo* videoInfo = i->second;

        //tempo \t id n�mero \t udp tamanho
        log << time << " " << "id " << videoInfo->ID << " " << "udp " << videoInfo->length << endl;
    }
    log.close();
}

RSUApplication::~RSUApplication() {}

void RSUApplication::handleSelfMsg(cMessage* msg) {
    BASE_TRAD::handleSelfMsg(msg);//Nettoyage de la liste des voisins
    switch (msg->getKind()) {
        case SEND_DATA: {
            sendData();

            break;
        }

        case END_SIMULATION: {
            delete msg;
            endSimulation();
            break;
        }

        default: {
            if (msg)
                EV << "Error: Got Self Message of unknown kind! Name: " << msg->getName() << endl;
            break;
        }
    }
}

void RSUApplication::onBeacon(WaveShortMessage* wsm) {

    BASE_TRAD::onBeacon(wsm);

    if (!disseminationStarted && simTime() >= par("startDataProductionTime")) {
        emit(disseminationStartTime, simTime());
        disseminationStarted = true;
        readDataFromFile();
        sendDataTimer = new cMessage("Send data", SEND_DATA);
        scheduleAt(simTime(), sendDataTimer);
    }
}

void RSUApplication::onData(WaveShortMessage* wsm) {
    BASE_TRAD::onData(wsm);
}



void RSUApplication::sendData() {
    if (!packet_send) {
        MessageEntryInfo* videoInfo = outputQueue.front();
        //outputQueue.pop_front();
        packet_send = true;

        WaveShortMessage* wsm = prepareWSM("data", dataLengthBits, type_SCH, dataPriority, 0, videoInfo->ID);

        // Send first message
        DataMessage* dataMsg = new DataMessage("data");

        dataMsg->setMessage_id(wsm->getSerial());

        dataMsg->setSender_id(getParentModule()->getIndex());

        dataMsg->setMessageTTL(par("dataTTL"));
        dataMsg->setMessageOriginTime(simTime());
       // classify_clusters();
        dataMsg->setListe_priority_trad(classify_clusters());

        //dataMsg->setVecX(mobility->getCurrentPosition().x);

        //dataMsg->setVecY(mobility->getCurrentPosition().y);

        //dataMsg->setVecZ(mobility->getCurrentPosition().z);

        //dataMsg->setMessageROI(par("dataROI").doubleValue());
        //dataMsg->setTimestamp(simTime());

        wsm->setBitLength(videoInfo->length);
        //indicesWarnigMsgsApp.push_back (wsm->getSerial());

        wsm->encapsulate(dataMsg);
        EV << "Id du message : " << videoInfo->ID << endl;
        sendWSM(wsm);



        loggingInfo[simTime()] = videoInfo;

        double nextPktTime = wsm->getBitLength() / datarate;
       // scheduleAt(simTime() , sendDataTimer);
        //scheduleAt(simTime() + nextPktTime, sendDataTimer);


    } else {
        cancelAndDelete(sendDataTimer);
    }

    /*or (int ID = 1; ID <= par("numberPackets").longValue(); ID++) {
            MessageEntryInfo* videoInfo = new MessageEntryInfo;
            EV << "Id du message : " << videoInfo->ID << endl;
            //videoInfo->ID = ID;
            //videoInfo->length = par("packetSize").longValue();

            //outputQueue.push_back(videoInfo);
        }*/
}

void RSUApplication::readDataFromFile() {
    /*std::ifstream sender_trace_file("sender_trace_packets");
    std::string line;

    int ID;
    char type;
    double time;
    int length;
    int unknown1;
    int unknown2;

    while (sender_trace_file >> ID >> type >> time >> length >> unknown1 >> unknown2) {
        MessageEntryInfo* videoInfo = new MessageEntryInfo;
        videoInfo->ID = ID;
        videoInfo->length = length;

        outputQueue.push_back(videoInfo);
    }*/

    for (int ID = 1; ID <= par("numberPackets").longValue(); ID++) {
        MessageEntryInfo* videoInfo = new MessageEntryInfo;
        videoInfo->ID = ID;
        videoInfo->length = par("packetSize").longValue();

        outputQueue.push_back(videoInfo);
    }
}


void RSUApplication::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details) {
    Enter_Method_Silent();
    BaseWaveApplLayer::receiveSignal(source, signalID, obj, details);
}
