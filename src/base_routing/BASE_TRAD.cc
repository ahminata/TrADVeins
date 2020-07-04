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
#include "BASE_TRAD.h"
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

Define_Module(BASE_TRAD);

//const simsignalwrap_t BASE_TRAD::mobilityStateChangedSignal = simsignalwrap_t(MIXIM_SIGNAL_MOBILITY_CHANGE_NAME);

void BASE_TRAD::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);
    hasMobility=true;
    if (stage == 0) {
        //traci = Veins::TraCIMobilityAccess().get(getParentModule());
        mobility = 0;



        //messagesReceived = registerSignal("messagesReceived");

        // configuration variables found in omnetpp.ini
        neighborLifetimeThreshold =
                par("beaconEntryTTL").doubleValue();


        sentMessage = false;
        lastDroveAt = simTime();

        receivedBeacons = 0;
        receivedData = 0;

        // Timer to clean neighbor entries  after time=beaconEntryTTL
        cleanUpTimer = new cMessage("entry timeout", ENTRY_TIMEOUT);

        CCHStartTimer = new cMessage("CCH start", CCH_START);
        SCHStartTimer = new cMessage("SCH start", SCH_START);

        uint64_t currenTime = simTime().raw();
        uint64_t switchingTime = SWITCHING_INTERVAL_11P.raw();
        double timeToNextSwitch = (double)(switchingTime - (currenTime % switchingTime)) / simTime().getScale();

        // Control Channel is active
        if ((currenTime / switchingTime) % 2 == 0) {
            scheduleAt(simTime() + timeToNextSwitch + SWITCHING_INTERVAL_11P, CCHStartTimer);
            scheduleAt(simTime() + timeToNextSwitch, SCHStartTimer);
        }
        // Service Channel is active
        else {
            scheduleAt(simTime() + timeToNextSwitch, CCHStartTimer);
            scheduleAt(simTime() + timeToNextSwitch + SWITCHING_INTERVAL_11P, SCHStartTimer);
        }



        double offSet = dblrand() * (par("beaconEntryTTL").doubleValue()/2);
        offSet = offSet + floor(offSet/0.050)*0.050;
        scheduleAt(simTime() + offSet, cleanUpTimer);
    }
}

void BASE_TRAD::finish() {
    BaseWaveApplLayer::finish();
    if (cleanUpTimer->isScheduled()) {
            cancelAndDelete(cleanUpTimer);
        }
        else {
            delete cleanUpTimer;
        }

       // findHost()->unsubscribe(mobilityStateChangedSignal, this);


   }


void BASE_TRAD::handleSelfMsg(cMessage* msg) {
    switch (msg->getKind()) {
// Nettoyage de la liste des voisins à l'emission au niveau de la classe mère
    case ENTRY_TIMEOUT: {

        //Nettoyage de la liste des voisins
        //neighborLifetimeThreshold=2, si la durée de vie d'un voisin d'un voisin dépasse les 2 seconde
        //(ceci veut dire que le voisin s'est éloigné), ce voisin est supprimé

          vector<int> indices;

         for (int i = 0; i < neighbors.size(); ++i) {
             BeaconMessage* neighbor = neighbors[i];
             if  (simTime() - neighbor->getArrivalTime() > neighborLifetimeThreshold)
                  indices.push_back(i);
          }

                  // remove the old neighbors
                     BeaconMessages newNeighborList;
                     for (int i = 0; i < neighbors.size(); ++i) {
                         bool keepNeighbor = true;
                         for (int j = 0; j < indices.size(); ++j) {
                             if (i == indices[j])
                                 keepNeighbor = false;
                         }
                         if (keepNeighbor)
                             newNeighborList.push_back(neighbors[i]);
                     }
                     neighbors = newNeighborList;

            scheduleAt(simTime() + par("beaconEntryTTL").doubleValue(),cleanUpTimer);

             break;
             }


    }

}
// Vérification à la reception si le voisin est connu du véhicule ou pas
void BASE_TRAD::onBeacon(WaveShortMessage* wsm1) {
    //EV <<"onBeacon"<<endl;
    BeaconMessage* wsm = dynamic_cast<BeaconMessage*>(wsm1->decapsulate());
    ASSERT(wsm);
  //  EV << "onBeacon" << wsm->getCarId() << endl;

    urgent_message_rec indices_message_urgence = wsm->getListe_message_urgence();

    bool bEqual = false;

    //EV  << "<=====les identifiants des différents messages attaché au beacon====>"
             // << indices_message_urgence.size() << endl;
    for (int i = 0; i < indices_message_urgence.size(); ++i) {

        int id_msg = indices_message_urgence[i];
        //EV << "Identifiants trouvés dans la balise====" << id_msg << endl;

        if (std::find(indicesWarnigMsgsApp.begin(), indicesWarnigMsgsApp.end(),
                id_msg) != indicesWarnigMsgsApp.end()) {
            bEqual = true;
            break;
        }
        /* else{
         bEqual=false;
         break;
         }*/

    }

   // EV << "<=====La balise contient des identifiants avec des messages que le véhicule connaît?====>"
             // << bEqual << endl;
    // handle stats
    receivedBeacons++;
    //emit(beaconMsgCounterSignalRx,receivedBeacons);


    //Si le beacon recu a déja été reçu par le même véhicule alors il supprime ce voisin
    //et ce voisin se fait ajouté de nouveau dans la liste avec un nouveau remps d'arrivage


    for (int i = 0; i < neighbors.size(); ++i) {
        BeaconMessage* neighbor = neighbors[i];
        if (neighbor->getCarId() == wsm->getCarId()) {
            // isNewNeighbor = false;
            neighbors.erase(neighbors.begin() + i);
        }
    }

    // if it is a new neighbor
    // cette méthode sera utilisé pour le SCF
    // Si le message qu'on veut disseminer n'est pas connu des voisins du véhicule: si oui on le rebroadcast aprés quelques condition
   /* if (!bEqual) {
        for (map<int, DataMessages>::iterator i =
                receivedWarningMessageMap.begin();
                i != receivedWarningMessageMap.end(); ++i) {
            DataMessage* msg = i->second[0];
            ASSERT(msg);
            findHost()->getDisplayString().updateWith("r=16,purple");
            // disseminate warning message
            //
            //
            //
            //if (timeoutEvent2->isScheduled())
            //cancelEvent(timeoutEvent2);
            //else
            //scheduleAt(simTime()+timeout2 ,timeoutEvent2);
        }

    }*/

    // Ajout de ce voisin
    neighbors.push_back(wsm->dup());
    //neighborsTable[wsm->getCarId()]= wsm->dup();



    //extract id vehicles from Neigbors Table Extraire id véhicle des neighborspour construire le messageData
    /*vector<int> idVehicles;
    //EV << "******************Neighbors Table**********************"  << neighbors.size() << endl;
    for (std::vector<BeaconMessage*>::const_iterator i = neighbors.begin();
            i != neighbors.end(); ++i) {
        BeaconMessage* msg = *i;
        idVehicles.push_back(msg->getCarId());
    }*/


}

/*bool BASE_TRAD::isDuplicateMsg(long idMsg) {
 return receivedWarningMessageMap.find(idMsg) != receivedWarningMessageMap.end();
 }*/

double BASE_TRAD::getutility (BeaconMessage* neighbor){

    //calcul de N, D, WCBR
           double N=std::min(double(neighbor->getNbr_neighbor())/(par("max_neighbor").doubleValue()),1.0);
          //distance
           //Coord Neighbor_position=Coord(neighbor->getVecX(),neighbor->getVecY(),neighbor->getVecZ());
           double distance=0.0;
           if (hasMobility) {
               distance =mobility->getCurrentPosition().distance(neighbor->getPosition());
           }else {
               Coord rsuPosition = Coord(par("eventOriginX").doubleValue(), par("eventOriginY").doubleValue(), par("eventOriginZ").doubleValue());
               distance =rsuPosition.distance(neighbor->getPosition());
           }

           double D=std::min(distance/par("maximum_radio_range").doubleValue(),1.0);



            double WCBR=1.0;
            double my_cbr=neighbor->getCbr();
             if(my_cbr>0.8) WCBR=0.001;
             else if(my_cbr>=0.6) WCBR=1-my_cbr;

              double utility= WCBR*(N+D)/2;
              return utility;

}

bool BASE_TRAD::same_cluster(BeaconMessage* neighbor1, BeaconMessage* neighbor2){


     if (neighbors.empty())
     return true;

     double x = (neighbor1->getPosition().x - curPosition.x);
     double y = (neighbor1->getPosition().y - curPosition.y);



     double a = (neighbor2->getPosition().x - curPosition.x);
     double b = (neighbor2->getPosition().y - curPosition.y);

     double numerator = (x * a) + (y * b);
     double denominator = sqrt((x*x) + (y*y)) * sqrt((a*a) + (b*b));
     double angle = acos(numerator / denominator);



     return (angle < M_PI/4.0);


}

neighbors_rec BASE_TRAD::classify_clusters(){

   // int key_i_suivant=0;
    //vider la table
    for (int i=0;i<int(liste_clusters.size());i++){
         liste_clusters[i].clear();
    }
    liste_clusters.clear();
    EV << "******************Classify cluster **********************" << endl;
    EV << "******************Neighbors Table du véhicule **********************"  << neighbors.size() << endl;
     for (int i = 0; i < neighbors.size(); ++i) {

             BeaconMessage* neighbor = neighbors[i];
             EV << "****************** voisin"<<i<<"**********************"<< neighbor->getCarId() << endl;
             EV << "****************** Utility voisin"<<i<<"**********************"<< getutility(neighbor) << endl;

         }




    std::map<int, BeaconMessage*> neighbors_map;
    std::transform(neighbors.begin(), neighbors.end(), std::inserter(neighbors_map, neighbors_map.end()),
                   [](BeaconMessage* s) { return std::make_pair(s->getCarId(),s); });

    std::map<int, BeaconMessage*> copy_neighbors_map(neighbors_map);

    EV << "******************Neighbors Table du véhicule Copiée **********************"  << neighbors.size() << endl;
    for (std::map<int, BeaconMessage*>::iterator i = copy_neighbors_map.begin(); i != copy_neighbors_map.end(); i++) {
        BeaconMessage* neighbor = i->second;
        EV << "****************** voisin :"<< neighbor->getCarId() ;
        EV << "** Utility voisin :"<< getutility(neighbor) << endl;

    }

       //scruter neighbors
    while (!copy_neighbors_map.empty()){
        std::map<int,BeaconMessage*>::iterator first_neigbbor = copy_neighbors_map.begin();
        BeaconMessage* a_neighbor = first_neigbbor->second;
        std::vector<neighbor_rec> a_cluster;
        neighbor_rec aneighbor_rec;
        aneighbor_rec.sender_id=a_neighbor->getCarId();
        aneighbor_rec.utility=getutility(a_neighbor);
        a_cluster.push_back(aneighbor_rec);

        copy_neighbors_map.erase(first_neigbbor);
        for (std::map<int,BeaconMessage*>::iterator i_neigbbor = copy_neighbors_map.begin(); i_neigbbor != copy_neighbors_map.end();)
            {
            BeaconMessage* other_neighbor = i_neigbbor->second;

            if (same_cluster(a_neighbor, other_neighbor) ){
                neighbor_rec other_neighbor_rec;
                other_neighbor_rec.sender_id=other_neighbor->getCarId();
                other_neighbor_rec.utility=getutility(other_neighbor);
                a_cluster.push_back(other_neighbor_rec);
                copy_neighbors_map.erase(i_neigbbor++);
            }
            else{
                ++i_neigbbor;
            }

        }// end for

        // il faut classifier le cluster
        std::vector<neighbor_rec> a_sorted_cluster;
        while (!(a_cluster.empty())){
            double utility_sup = a_cluster[0].utility;
            uint64 id_sup = a_cluster[0].sender_id;
            int i_sup=0;
            for (int i=1; (i< int(a_cluster.size()));i++ ) {
                if (a_cluster[i].utility>utility_sup){
                    utility_sup= a_cluster[i].utility;
                    id_sup = a_cluster[i].sender_id;
                     i_sup=i;
                }
            }

            neighbor_rec aneighbor_rec;
            aneighbor_rec.sender_id=id_sup;
            aneighbor_rec.utility=utility_sup;
            a_sorted_cluster.push_back(aneighbor_rec);
            std::vector<neighbor_rec>::iterator it;
            it=a_cluster.begin()+i_sup;
            a_cluster.erase(it);
         }
       liste_clusters.push_back(a_sorted_cluster);
       EV << "******************Le nombre de neighbor dans le cluster Nr°"<< liste_clusters.size() <<" est de *************"  << a_sorted_cluster.size() << endl;

       for (int i = 0; i < a_sorted_cluster.size(); ++i) {

           neighbor_rec neighbor_record = a_sorted_cluster[i];
           EV << "******* neighbors_record = "<< neighbor_record.sender_id ;
           EV << " and Utility = "<< neighbor_record.utility << endl;

           }


    }//end while
    // Maintenant il faut créer une liste de neighbours triée par priorité

  //vider liste_priority_trad;
    liste_priority_trad.clear();
    bool all_clusters_done=false;
    int j=0;
    //scruter les cluster avec un round robin
    while (!all_clusters_done){
      all_clusters_done=true;
      for (int i=0;i<int(liste_clusters.size());i++){
        if (int(liste_clusters[i].size())>j) {
          liste_priority_trad.push_back(liste_clusters[i][j]);
          all_clusters_done=false;
        }
      }
      j++;
    }

    EV <<endl<< "******************Liste des neighbors triée *************"  <<  endl;

    for (int i = 0; i < liste_priority_trad.size(); ++i) {

        neighbor_rec neighbor_record = liste_priority_trad[i];
            EV << "******* neighbors_record = "<< neighbor_record.sender_id ;
            EV << " and Utility = "<< neighbor_record.utility << endl;

        }
    return liste_priority_trad;
}


void BASE_TRAD::onData(WaveShortMessage* wsm) {


}

BASE_TRAD::~BASE_TRAD() {}
