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
#ifndef __UV_CAST_TRAD_H_
#define __UV_CAST_TRAD_H_

#include "BaseWaveApplLayer.h"
#include "BASE_TRAD.h"
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



class TRAD : public BASE_TRAD {

protected:

// UV-CAST table used to store sent and received data messages
   std::map<int, DataMessage*> receivedWarningMessageMap;    // treeId, WSM vector
   int idMsg;



   cMessage* broadcastTimer;


   //TODO: Added for Game theory Solution
   double curTxPower;
   int powerLevel;
   double myUtilityValue;

   uint32_t receivedData;

   Mac1609_4* mac;

   bool wasInROI;

   bool disseminationStarted;

   simtime_t disseminationStartTime;

   long lastNumCollisions;

   long totalCollisions;

   static const simsignalwrap_t mobilityStateChangedSignal;



    virtual void initialize(int);
    virtual void finish();
    virtual void handleSelfMsg(cMessage* msg);
    virtual void onBeacon(WaveShortMessage* wsm);
    virtual void onData(WaveShortMessage* wsm);

    //virtual bool isAssignedSCF(int senderID, Coord senderPos);
    //virtual void scheduleRebroadcast(MessageInfoEntry* info, Coord senderPos, TRADMessageKinds msgType);
    //virtual void scfPolicyMissingPackets(WaveShortMessage* wsm);
    virtual double desynchronize(double delay);
    virtual bool isCCHActive();

    bool isDuplicateMsg(int idMsg);
    //virtual bool isInsideROI(MessageInfoEntry* info);
    virtual bool isMessageAlive(DataMessage* data);
    virtual WaveShortMessage* createDataMsg(DataMessage* data);
    //virtual void insertEntry(int senderAddr, Coord senderPos);
    //virtual void processBackTraffic(int senderAddr);

    //virtual void addGPSError();
    //virtual void receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details);
    //virtual void receiveSignal(cComponent *source, simsignal_t signalID, const SimTime& t);

    //TODO: Added for Game theory Solution
    virtual void adjustTxPower(WaveShortMessage* wsm);
    virtual void decreaseTxPower();
    virtual void increaseTxPower();

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

    virtual ~TRAD();
};

#endif
