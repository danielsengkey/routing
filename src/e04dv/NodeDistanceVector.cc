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

#include "NodeDistanceVector.h"

Define_Module(NodeDistanceVector);

void NodeDistanceVector::specificInitialization()
{
    rcvdND      = 0;
    rcvdNDdup   = 0;
    count_fib_updated = 0;

    signalRcvdND    = registerSignal("receivedND");
    signalRcvdNDdup = registerSignal("receivedNDdup");
    signal_count_fib_updated = registerSignal("FIBupdated");

    ttlNeighbourDiscovery = par("discoveryTTL").longValue();

    numberOfNodes = getNumberOfNodes();

    broadcastMessage(prepareMessage(DISCOVERY_MESSAGE, -1, ttlNeighbourDiscovery));
}

void NodeDistanceVector::handleMessage(cMessage *msg)
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
        case DISTANCE_VECTOR_MESSAGE:
            handleDistanceVectorMessage(msg);
            break;
        default:
            if(msg->isSelfMessage()) handleSelfMessage(msg);
            else EV << "Received unknown message type." << endl;
            break;
    }
}

void NodeDistanceVector::handleSelfMessage(cMessage *msg)
{
    delete msg;
}

void NodeDistanceVector::handleDistanceVectorMessage(cMessage *msg)
{
    DistanceVectorMessage *receivedDV = check_and_cast<DistanceVectorMessage *>(msg);

    //EV << "[" << myId << "] Received new distance vector message from " << receivedDV->getSourceID() << endl;
    //EV << "Contents are:" << endl;
    //TODO How to handle node that is unknown?
    for(auto it: receivedDV->getNeighbourList())
    {
        //if(it.first==myId) break;
        int cost = it.second+1;
        EV << "Dst: " << it.first << " cost via " << receivedDV->getSourceID() << " is " << cost << endl;

        if(it.first!=myId)
        {
            rib[it.first][receivedDV->getArrivalGate()->getIndex()] = cost;
            if(fib.find(it.first)==fib.end())
            {
                EV << "New node discovered." << endl;
                fib[it.first] = receivedDV->getArrivalGate()->getIndex();
                fib_updated = true;
            }
        }
    }
    delete receivedDV;
    checkFIB();
    if(fib_updated) {
        broadcastMessage(prepareDistanceVectorMessage());
        count_fib_updated++;
    }

    // Resetting the FIB changes marker.
    fib_updated = false;
}

DistanceVectorMessage* NodeDistanceVector::prepareDistanceVectorMessage()
{
   DistanceVectorMessage *dvm = new DistanceVectorMessage("Distance Vector Message", DISTANCE_VECTOR_MESSAGE);
   dvm->setSourceID(myId);

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
    dvm->getNeighbourList() = nl;

    return dvm;
}

void NodeDistanceVector::handleDiscoveryMessage(cMessage *msg)
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

    // Send distance vector message when all the neighbours already listed in fib.
    // NOTE: Only applicable in point-to-point link!
    if(fib.size()==totalGate) broadcastMessage(prepareDistanceVectorMessage());

    // Delete the message
    delete receivedND;
}

void NodeDistanceVector::checkFIB()
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


int NodeDistanceVector::findLowestCostGate(int node)
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

void NodeDistanceVector::printRIB()
{
    for(auto it : rib)
    {
        EV << "[" << myId << "] Node " << it.first << " is reachable via gate " << endl;

        for(auto iter: rib[it.first]){
            EV << "\t" << iter.first << "\tcost:\t" << iter.second << endl;
        }
    }
}

void NodeDistanceVector::finish()
{
    // Emit signals for stats recording.
    emit(signalRcvdND, rcvdND);
    emit(signalRcvdNDdup, rcvdNDdup);
    emit(signal_count_fib_updated, count_fib_updated);

    // Print the fib
    if(logVerbose) printFIB();
    if(logVerbose) printRIB();
}
