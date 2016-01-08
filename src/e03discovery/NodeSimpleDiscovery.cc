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

#include "NodeSimpleDiscovery.h"

Define_Module(NodeSimpleDiscovery);

void NodeSimpleDiscovery::handleDiscoveryMessage(cMessage *msg)
{
    // Check and cast received message.
    DiscoveryMessage *receivedND = check_and_cast<DiscoveryMessage *>(msg);

    // Increase received network discovery counter
    rcvdND++;

    // Reply with discovery reply
    unicastSending(prepareMessage(DISCOVERY_REPLY, receivedND->getSourceID(), receivedND->getTtl()), receivedND->getArrivalGate()->getIndex());

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
    }
}

void NodeSimpleDiscovery::handleDiscoveryReply(cMessage *msg)
{
    // Check and cast the message
    DiscoveryMessage *receivedReply = check_and_cast<DiscoveryMessage *>(msg);

    // Check the destination of the message
    // Since this is a simple implementation of neighbour discovery,
    // simply delete the packet if not destined for this node.
    if(receivedReply->getDestinationID()==myId)
    {
      if(fib.find(receivedReply->getSourceID())==fib.end()) // If the sender is not in fib yet,
        {
            // insert the sender into fib, reachable via this gate index.
            fib[receivedReply->getSourceID()] = receivedReply->getArrivalGate()->getIndex();
        }
    }
    delete receivedReply;
}
