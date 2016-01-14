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

#include "NodeSimpleDiscovery2ext.h"

Define_Module(NodeSimpleDiscovery2ext);

void NodeSimpleDiscovery2ext::handleDiscoveryMessage(cMessage *msg)
{
    // Check and cast received message.
    DiscoveryMessage *receivedND = check_and_cast<DiscoveryMessage *>(msg);

    if(logVerbose) EV << "[" << myId << "] Received " << receivedND->getName() << " from " << receivedND->getSourceID() << "." << endl;

    // Check the source of this message.
    // If in fact the message is sent from this node
    // and get forwarded by the other nodes, drop it!
    if(receivedND->getSourceID()!=myId)
    {
        // Increase received network discovery counter
        rcvdND++;

        // Check if the sender already in my fib or not, if yes go to else, deleted the message.
        if(fib.find(receivedND->getSourceID())==fib.end())
        {

        // Reply with discovery reply
        unicastSending(prepareMessage(DISCOVERY_REPLY, receivedND->getSourceID(), receivedND->getTtl()), receivedND->getArrivalGate()->getIndex());

        // Add sender into fib
        fib[receivedND->getSourceID()] = receivedND->getArrivalGate()->getIndex();
        }

        // Selective broadcast if ttl > 0, otherwise delete it
        if(receivedND->getTtl()>0)
        {
            // Decrease ttl
            receivedND->setTtl(receivedND->getTtl()-1);

            //Selective broadcast
            selectiveBroadcast(receivedND, receivedND->getArrivalGate()->getIndex());
        } else {
            // If ttl equal to 0 then delete the message.
            delete receivedND;

            droppedNDtimeOut++;
        }
    } else {
        // receivedND->getSourceID() == myId;
        rcvdSelfND++;
        delete receivedND;
    }
}
