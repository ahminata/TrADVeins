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
/*#if __cplusplus <= 201103L
  #error This library needs at least a C++11 compliant compiler
#endif
*/
#ifndef __UV_CAST_BASE_TRAD_H_
#define __UV_CAST_TRAD_H_

#include "BaseWaveApplLayer.h"
#include "WaveShortMessage_m.h"
#include "BeaconMessage_m.h"
#include "DataMessage_m.h"
#include "TraCIMobility.h"
#include <algorithm>
#include <limits>

#include "FindModule.h"
#include "Mac1609_4.h"
//TODO: Added for Game theory Solution
#include "DeciderResult80211.h"
#include "PhyToMacControlInfo.h"
#include "PhyControlMessage_m.h"

/**
 *
 */

#include <vector>
#include <map>
#include <algorithm>

using Veins::TraCIMobility;
using Veins::AnnotationManager;
using std::vector;
using std::map;

#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

typedef std::vector<BeaconMessage*> BeaconMessages;
typedef std::vector<DataMessage*> DataMessages;

class BASE_TRAD : public BaseWaveApplLayer {

protected:

    TraCIMobility* mobility;
       Veins::TraCICommandInterface* traci;
       Veins::TraCICommandInterface::Vehicle* traciVehicle;
       Veins::AnnotationManager* annotations;



    double neighborLifetimeThreshold;



    simtime_t lastDroveAt;
    bool sentMessage;


    uint32_t receivedBeacons;
    uint32_t receivedData;
    uint32_t numberOfNodes;





    // BASE_TRAD table used to store neighbor's information
    std::map<int, BeaconMessage*> neighborsTable;

    // UV-CAST table used to store sent and received data messages
    std::map<int, DataMessage*> receivedWarningMessageMap;    // treeId, WSM vector
    //int idMsg;

    std::vector<int> indicesWarnigMsgsApp;
    BeaconMessages neighbors;

    //neighbor_rec liste_clusters;
    std::vector<neighbors_rec> liste_clusters;
    neighbors_rec liste_priority_trad;

    cMessage* cleanUpTimer;

    cMessage* CCHStartTimer;

    cMessage* SCHStartTimer;


    enum TRADMessageKinds {
            ENTRY_TIMEOUT = SEND_BEACON_EVT + 1, // Timer to clean old entries from received beacons
            BROADCAST_TIMEOUT, // Timer used to control the wait time for vehicles. When it fires, then send message
            //SCF_TIMEOUT,
            //BACK_TRAFFIC_ENTRY_TIMEOUT,
            CCH_START,
            SCH_START,
     };
    enum RSUMessageKinds{
        SEND_DATA = SCH_START + 1,
        END_SIMULATION,
    };

    virtual void initialize(int);
    virtual void finish();
    virtual void handleSelfMsg(cMessage* msg);
    virtual void onBeacon(WaveShortMessage* wsm);
    virtual void onData(WaveShortMessage* wsm);
    neighbors_rec classify_clusters();
    double getutility (BeaconMessage* neighbor);
    bool same_cluster(BeaconMessage* neighbor1,BeaconMessage* neighbor2);
    virtual ~BASE_TRAD();


    bool isDuplicateMsg(int idMsg);
    bool hasMobility;


public:
    //TODO: Added for Game theory Solution

    simsignal_t lastTxPower;
    simsignal_t meanSNR;

    simsignal_t sentDownMACInCCH; // Indicate the total number of messages sent down to MAC when the CCH was active
    simsignal_t collisions; // Indicate the total number of collisions
    simsignal_t messagesTransmittedSCF; // Indicate the number of messages transmitted by a vehicle in the SCF state
    simsignal_t messagesReceivedSCF; // Indicate whether the message was received or not using indirect forwarding
    simsignal_t duplicatedMessages; // Indicate the number of duplicate messages received by a vehicle
    simsignal_t messagesTransmitted; // Indicate the number of messages transmitted by a vehicle
    simsignal_t messagesReceived; // Indicate whether the message was received or not
    simsignal_t isInROI; // Indicate whether the vehicle is inside the ROI at the time the dissemination starts


};

#endif
