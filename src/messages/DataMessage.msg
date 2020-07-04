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

cplusplus {{
#include <vector>
#include <Coord.h>

typedef struct {
        int sender_id;
        
        double utility;

        //cMessage* cleanUpTimer;
    } neighbor_rec;
typedef std::vector<neighbor_rec> neighbors_rec;
}}

class noncobject neighbors_rec;
class noncobject Coord;



packet DataMessage {  
              
    //Coord messageOriginPosition;
    //double messageROI;
    //simtime_t messageOriginTime; 
    
    //int hops;    
    
    //bool sentSCFState = false;  
    int message_id;//  id du message
    int sender_id;
    Coord messageOriginPosition;
    
    //int sender_origine_address;
    
	
   simtime_t messageTTL;
   simtime_t messageOriginTime;
   int messageLength;
   
	//Coord messageOriginPosition;
	double vecX;
	double vecY;
	double vecZ;
	
	simtime_t timestamp;
	
	//cMessage* broadcastTimer;//self message for broadcast suppression
	
	neighbors_rec liste_priority_trad;
}