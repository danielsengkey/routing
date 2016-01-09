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

#include "NodeSimpleDiscovery2.h"

Define_Module(NodeSimpleDiscovery2);

void NodeSimpleDiscovery2::specificInitialization()
{
    ttlNeighbourDiscovery = getNumberOfNodes();

    rcvdND      = 0;
    rcvdNDdup   = 0;
    rcvdSelfND  = 0;
    rcvdDRdup   = 0;

    droppedDRtimeOut        = 0;
    droppedDRunreachable    = 0;
    droppedNDtimeOut        = 0;


    signalRcvdND                = registerSignal("receivedND");
    signalRcvdNDdup             = registerSignal("receivedNDdup");
    signalRcvdSelfND            = registerSignal("receivedSelfND");
    signalRcvdDRdup             = registerSignal("receivedDRdup");

    signalDroppedDRtimeOut      = registerSignal("DroppedDRtimeOut");
    signalDroppedDRunreachable  = registerSignal("DroppedDRunreachable");
    signalDroppedNDtimeOut      = registerSignal("DroppedNDtimeOut");

    broadcastMessage(prepareMessage(DISCOVERY_MESSAGE, -1, ttlNeighbourDiscovery));
}

void NodeSimpleDiscovery2::handleDiscoveryMessage(cMessage *msg)
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

            droppedNDtimeOut++;
        }
    } else {
        // receivedND->getSourceID() == myId;
        rcvdSelfND++;
        delete receivedND;
    }
}

void NodeSimpleDiscovery2::handleDiscoveryReply(cMessage *msg)
{
    // Check and cast the message
    DiscoveryMessage *receivedReply = check_and_cast<DiscoveryMessage *>(msg);

    // Check the destination of the message
    // If this node is not the destination, check the routing table.
    // If the destination found, then forward through respective gate.
    // If destination is not in routing table, drop the message.
    if(receivedReply->getDestinationID()==myId)
    {
      if(fib.find(receivedReply->getSourceID())==fib.end()) // If the sender is not in fib yet,
        {
            // insert the sender into fib, reachable via this gate index.
            fib[receivedReply->getSourceID()] = receivedReply->getArrivalGate()->getIndex();
        } else {
            // Introducing a simple duplication tracker.
            // This is a reply message from an indexed node
            EV << "[" << myId << "] Received discovery reply from an indexed node. Ignoring..." << endl;
            rcvdDRdup++;
        }
      delete receivedReply;

    } else if(receivedReply->getTtl()>0) {

        //hop limit is not reached yet
        int outputGateIndex = getOutGate(receivedReply->getDestinationID());

        if(outputGateIndex==-1){
            EV << "[" << myId << "] Destination node " << receivedReply->getDestinationID() << " not in my routing table. Deleting message." << endl;
            delete receivedReply;
            droppedDRunreachable++;
        } else {
            EV << "[" << myId << "] Forwarding " << receivedReply->getName() << " to node " << receivedReply->getDestinationID() << " through gate " << outputGateIndex << endl;
            unicastSending(receivedReply, outputGateIndex);
        }

    } else {

        // This node is not the destination and hop limit reached (ttl = 0)
        delete receivedReply;
        droppedNDtimeOut++;
    }
}

void NodeSimpleDiscovery2::finish()
{
    // Emit signals for stats recording.
    emit(signalRcvdND, rcvdND);
    emit(signalRcvdNDdup, rcvdNDdup);
    emit(signalRcvdSelfND, rcvdSelfND);
    emit(signalRcvdDRdup, rcvdDRdup);

    emit(signalDroppedDRtimeOut, droppedDRtimeOut);
    emit(signalDroppedNDtimeOut, droppedNDtimeOut);
    emit(signalDroppedDRunreachable, droppedDRunreachable);

    // Print the fib
    if(logVerbose) printFIB();

    // Print size of fib
    EV << "[" << myId << "] FIB size " << fib.size() << endl;
}
