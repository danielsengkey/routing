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

#include "NodeDiscoveryBase.h"

Define_Module(NodeDiscoveryBase);

void NodeDiscoveryBase::specificInitialization()
{
    rcvdND      = 0;
    rcvdNDdup   = 0;

    signalRcvdND    = registerSignal("receivedND");
    signalRcvdNDdup = registerSignal("receivedNDdup");

    ttlNeighbourDiscovery = par("discoveryTTL").longValue();

    broadcastMessage(prepareMessage(DISCOVERY_MESSAGE, -1, ttlNeighbourDiscovery));
}

void NodeDiscoveryBase::handleMessage(cMessage *msg)
{
    switch (msg->getKind()) {
        case DISCOVERY_MESSAGE:
            handleDiscoveryMessage(msg);
            break;
        case DISCOVERY_REPLY:
            handleDiscoveryReply(msg);
            break;
        case NETWORK_PACKET:
            handleNetworkPacket(msg);
            break;
        default:
            EV << "Received unknown message type." << endl;
            break;
    }
}

void NodeDiscoveryBase::handleDiscoveryMessage(cMessage *msg)
{
    // TODO Function implemented in subclass.
    // In the base node the message just deleted.

    delete msg;
}

void NodeDiscoveryBase::handleDiscoveryReply(cMessage *msg)
{
    // TODO Function implemented in subclass.
    // In the base node the message just deleted.

    delete msg;
}


DiscoveryMessage* NodeDiscoveryBase::prepareMessage(int messageKind, int destinationId, int ttl)
{
    DiscoveryMessage *discoveryMsg = NULL;

    switch (messageKind) {
        case DISCOVERY_MESSAGE:
            discoveryMsg = new DiscoveryMessage("Discovery Message", DISCOVERY_MESSAGE);
            break;
        case DISCOVERY_REPLY:
            discoveryMsg = new DiscoveryMessage("Discovery Reply", DISCOVERY_REPLY);
            break;
        default:
            EV << "Unknown message kind." << endl;
            break;
    }
    discoveryMsg->setSourceID(myId);
    discoveryMsg->setDestinationID(destinationId);
    discoveryMsg->setTtl(ttl);
    return discoveryMsg;
}

int NodeDiscoveryBase::findLowestCostGate(int node)
{
    int gateWithLowestCost;
    int lowestCost = 999999; // A very huge number that likely this model won't have cost that much.

    for(auto it: rib[node])
    {
        if(it.second < lowestCost) gateWithLowestCost = it.first;
    }
    return gateWithLowestCost;
}

int NodeDiscoveryBase::getOutGate(int node)
{
    int outGate;
    if(fib.find(node)==fib.end())
    {
        outGate = -1;
    } else {
        outGate = fib[node];
    }
    return outGate;
}

void NodeDiscoveryBase::printFIB()
{
    for(auto it : fib)
    {
        EV << "[" << myId << "] Node " << it.first << " is reachable via gate " << it.second << "." << endl;
    }
}

void NodeDiscoveryBase::finish()
{
    // Emit signals for stats recording.
    emit(signalRcvdND, rcvdND);
    emit(signalRcvdNDdup, rcvdNDdup);

    // Print the fib
    if(logVerbose) printFIB();
}
