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

#ifndef __ROUTING_NODEBASE_H_
#define __ROUTING_NODEBASE_H_

#include <omnetpp.h>
#include <discovery_m.h>

/**
 * NodeBase class.
 * Provides basic functionalities.
 * @author Daniel Febrian Sengkey <danielfebrian015@gmail.com>
 */
class NodeBase : public cSimpleModule
{
  private:
    /** A variable storing in gate name */
    const char *inGateName;

    /** A variable storing out gate name */
    const char *outGateName;

    /** Total gate owned by this node. */
    int totalGate;

    /**
     * This node's identity.
     * It is encouraged to use the index number when the node implemented in network using vector.
     */
    int myId;

    /**
     * If set to true, the module log will display more messages.
     */
    bool logVerbose;

    /**
     * This method will print verbose messages if the logVerbose is true.
     * @see logVerbose
     */
    void printModuleLog(std::string logMessage);

    /** Neighbour Discovery message that will be sent by this node. */
    DiscoveryMessage myDiscoveryMessage;

    /** Received Discovery Message. */
    DiscoveryMessage receivedDiscovery;

  protected:
    // Class members

    /** Enumerated message kind for easier identification. */
    enum messageKind{
        DISCOVERY_MESSAGE,
        DISCOVERY_REPLY
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

    /** Module initialization. */
    virtual void initialize();

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
     * A method to forward message through specified out gate.
     * Routing decision should be made earlier.
     * Do not use this method with message that should be broadcasted.
     * To achieve such action, use broadcastMessage() or selectiveBroadcast() instead.
     * see @broadcastMessage()
     * see @selectiveBroadcast()
     */
    virtual void forwardMessage(cMessage *msg, int outGateIndex);

    /**
     * A method to broadcast message to all connected gates.
     */
    virtual void broadcastMessage(cMessage *msg);

    /**
     * Similar with broadcastMessage(), except this method will not send through specified gate.
     * This method can be use to forwarding by rebroadcast a received discovery message.
     */
    virtual void selectiveBroadcast(cMessage *msg, int notViaThisGateIndex);

    /**
     * Send message with specific destination ID.
     * Should be invoked only by the source.
     * Intermediate nodes should use forwardMessage().
     * @see forwardMessage()
     */
    virtual void unicastSending(cMessage *msg, int outGateIndex);

    /**
     * Find the output gate with lowest cost to reach a node.
     * This method will return an out gate index.
     */
    int findLowestCostGate(int node);
};

#endif
