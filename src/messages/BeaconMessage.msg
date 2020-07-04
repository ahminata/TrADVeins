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
#include <Coord.h>
typedef std::vector<int> urgent_message_rec;
}}


class noncobject Coord;
class noncobject urgent_message_rec;



packet BeaconMessage {        
	//int beacon_id;// Id  du beacon 
	

	int carId; //Id du vehicle emetteur du beacon
	
	int nbr_neighbor;// le nombre de voisin
	//int ttl;
	Coord position;
	double speed;
	//double accel;
	double angleRad;
	double vecX;
	double vecY;
	double vecZ;
	
	double  cbr;// temps d'occupation du canal
	//cMessage* cleanUpTimer;
	
	urgent_message_rec liste_message_urgence;
	
	//int liste_messages_reçus[];
}