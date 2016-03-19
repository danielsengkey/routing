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

#include "NodeLinkState.h"

Define_Module(NodeLinkState);

void NodeLinkState::handleMessage(cMessage *msg)
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
        case LINK_STATE_PACKET:
            handleLinkStatePacket(msg);
            break;
        default:
            if(msg->isSelfMessage()) handleSelfMessage(msg);
            else EV << "Received unknown message type." << endl;
            break;
    }
}

void NodeLinkState::handleSelfMessage(cMessage *msg)
{
    delete msg;
}

void NodeLinkState::handleLinkStatePacket(cMessage *msg)
{
    LinkStatePacket *receivedLSP = check_and_cast<LinkStatePacket *>(msg);

    //EV << "[" << myId << "] Received new link state message from " << receivedLSP->getSourceID() << endl;
    //EV << "Contents are:" << endl;
    //TODO How to handle node that is unknown?
    for(auto it: receivedLSP->getNeighbourList())
    {
        //if(it.first==myId) break;
        int cost = it.second+1;
        EV << "Dst: " << it.first << " cost via " << receivedLSP->getSourceID() << " is " << cost << endl;

        if(it.first!=myId)
        {
            rib[it.first][receivedLSP->getArrivalGate()->getIndex()] = cost;
            if(fib.find(it.first)==fib.end())
            {
                EV << "New node discovered." << endl;
                fib[it.first] = receivedLSP->getArrivalGate()->getIndex();
                fib_updated = true;
            }
        }
    }
    delete receivedLSP;
    checkFIB();
    if(fib_updated) broadcastMessage(prepareLinkStatePacket());

    // Resetting the FIB changes marker.
    fib_updated = false;
}

LinkStatePacket* NodeLinkState::prepareLinkStatePacket()
{
   LinkStatePacket *lsp = new LinkStatePacket("Link State Packet", LINK_STATE_PACKET);
   lsp->setSourceID(myId);

   // A temporary map to store the costs;
   std::map<int,int> nl;

    // Get pair of node and gate from fib, then check the gate cost from rib[node].
    for(auto it: fib)
    {
        // Find the gate and cost from rib[node]
        GateCostTable::iterator t = rib[it.first].find(it.second);
        //EV << t->first << "\t" << t->second << endl;

        //nl[node] = cost
        nl[it.first] = t->second;
    }
    lsp->getNeighbourList() = nl;

    return lsp;
}

void NodeLinkState::handleDiscoveryMessage(cMessage *msg)
{
    // Check and cast received message.
    DiscoveryMessage *receivedND = check_and_cast<DiscoveryMessage *>(msg);

    // Increase received network discovery counter
    rcvdND++;

    if(rib.find(receivedND->getSourceID())==rib.end())
    {
        EV << "Received network discovery message from " << receivedND->getSourceID()
                << " through gate " << receivedND->getArrivalGate()->getIndex() << endl;

        // Pair of cost of gate, a.k.a cost to reach a node through a gate.
        // cost[gate]
        GateCostTable cost;
        cost[receivedND->getArrivalGate()->getIndex()] = 0;

        // Insert the source into rib
        rib[receivedND->getSourceID()] = cost;

        // Directly insert the neighbour into fib.
        fib[receivedND->getSourceID()] = receivedND->getArrivalGate()->getIndex();
    }

    // Send Link State message when all the neighbours already listed in fib.
    // NOTE: Only applicable in point-to-point link!
    if(fib.size()==totalGate) broadcastMessage(prepareLinkStatePacket());

    // Delete the message
    delete receivedND;
}

void NodeLinkState::checkFIB()
{
    for(auto it: fib)
    {
        int currentGate = it.second;
        int newGate = findLowestCostGate(it.first);

        if(currentGate!=newGate)
        {
            EV << "[" << myId << "] FIB has changed." << endl;
            fib[it.first] = newGate;
            fib_updated = true;
        }
    }
}


int NodeLinkState::findLowestCostGate(int node)
{
    RoutingTable::iterator gateIter = fib.find(node);
    int gateWithLowestCost = gateIter->second;

    GateCostTable::iterator costIter=rib[node].find(gateWithLowestCost);
    int currentGateCost = costIter->second;

    for(auto it: rib[node])
    {
        if(it.second < currentGateCost) gateWithLowestCost = it.first;
    }
    return gateWithLowestCost;
}

void NodeLinkState::printRIB()
{
    for(auto it : rib)
    {
        EV << "[" << myId << "] Node " << it.first << " is reachable via gate " << endl;

        for(auto iter: rib[it.first]){
            EV << "\t" << iter.first << "\tcost:\t" << iter.second << endl;
        }
    }
}

void NodeLinkState::finish()
{
    // Emit signals for stats recording.
    emit(signalRcvdND, rcvdND);
    emit(signalRcvdNDdup, rcvdNDdup);

    // Print the fib
    if(logVerbose) printFIB();
    if(logVerbose) printRIB();
}
