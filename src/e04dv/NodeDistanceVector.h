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

#ifndef __ROUTING_NODEDISTANCEVECTOR_H_
#define __ROUTING_NODEDISTANCEVECTOR_H_

#include <omnetpp.h>
#include <base/NodeDiscoveryBase.h>
#include <base/vector_m.h>

/**
 * This module implements simple distance vector algorithm to form the routing table.
 * Simple neighbour discovery is needed so the node will be able to identify its neighour.
 * Therefore, NodeSimpleDiscovery is inherited here. However, there is no reply message applied.
 * Instead, since the discovery broadcasted on all interfaces by all nodes, the sender will be
 * directly added without sending the reply.
 * @author Daniel Febrian Sengkey <danielfebrian015@gmail.com>
 * @see NodeSimpleDiscovery
 */
class NodeDistanceVector : public NodeDiscoveryBase
{

protected:
    /**
     * A table contains cost(s) to reach the other hosts.
     * First field is the gate and second is the gate.
     * The node ID is the vector element defined right after.
     * see @rib
     */
    typedef std::map<int,int> GateCostTable;

    /**
     * A vector contains the hosts list and the costs.
     * The host ID is the key. Later, each field is HostCostTable instance.
     * Let it called as Routing Information Base (RIB).
     * There will be one RIB for each known host/node.
     */
    std::map<int, GateCostTable> rib;

    /** A variable used later to identify if the fib has changed or not.*/
    bool fib_updated = false;

    /**
     * Handler for received distance vector message.
     */
    virtual void handleDistanceVectorMessage(cMessage *msg);

    /**
     * Self message handler.
     */
    virtual void handleSelfMessage(cMessage *msg);

    /**
     * Override the main handleMessage() to accept the distance vector packet.
     */
    virtual void handleMessage(cMessage *msg);

    /**
     * Override the discovery message handler. This method handles the discovery message.
     * It means the message from directly connected neighbours.
     */
    virtual void handleDiscoveryMessage(cMessage *msg);

    /**
     * Preparing distance vector message.
     */
    DistanceVectorMessage* prepareDistanceVectorMessage();

    /**
     * Find the output gate with lowest cost to reach a node.
     * This method will return an out gate index.
     */
    int findLowestCostGate(int node);

    /**
     *
     */
    virtual void finish();

    /**
     * Print the contents of the rib.
     */
    virtual void printRIB();

    /**
     * Checking FIB when new entries added.
     */
    virtual void checkFIB();
};

#endif /* __ROUTING_NODEDISTANCEVECTOR_H_ */
