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

#ifndef __ROUTING_NODEDISCOVERYBASE_H_
#define __ROUTING_NODEDISCOVERYBASE_H_

#include <omnetpp.h>
#include <NodeBase.h>
#include <discovery_m.h>

/**
 * This node contains basic functions for node that uses network discovery.
 * Further specific functions should be implemented in subclasses.
 * @author Daniel Febrian Sengkey <danielfebrian015@gmail.com>
 * @see NodeBase
 */
class NodeDiscoveryBase : public NodeBase
{
  protected:

    /** Neighbour Discovery message that will be sent by this node. */
    DiscoveryMessage myDiscoveryMessage;

    /** Received Discovery Message. */
    DiscoveryMessage receivedDiscovery;

    /** Redefine the messageKind with network discovery messages */
    enum messageKind{
            DISCOVERY_MESSAGE,
            DISCOVERY_REPLY,
            NETWORK_PACKET
        };

    /** A simple routing table. */
    typedef std::map<int,int> RoutingTable;

    /** The forwarding information base, instance of the routing table. */
    RoutingTable fib;

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
    std::vector<GateCostTable> rib;

    /** A method for message preparation. If a broadcast message then the destination id is -1. */
    DiscoveryMessage *prepareMessage(int messageKind, int destinationId);

    /** Override to declare specific initilaization related with this node/ */
    virtual void specificInitialization();

    /**
      * Basic message handler.
      * The implementation only contains decision based on the message kind
      * to determine what should be done next with the message.
      */
     virtual void handleMessage(cMessage *msg);

     /**
      * Specific method to handle discovery message.
      * Should be invoked from the main handleMessage().
      * @see handleMessage()
      * @see handleDiscoveryReply()
      */
     virtual void handleDiscoveryMessage(cMessage *msg);

     /**
      * Specific method to handle discovery reply message.
      * Should be invoked from the main handleMessage().
      * @see handleMessage()
      * * @see handleDiscoveryMessage()
      */
     virtual void handleDiscoveryReply(cMessage *msg);

     /**
      * Find the output gate with lowest cost to reach a node.
      * This method will return an out gate index.
      */
     int findLowestCostGate(int node);
};

#endif
