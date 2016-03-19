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
#include <Packet_m.h>

/**
 * NodeBase class.
 * Provides basic functionalities.
 * @author Daniel Febrian Sengkey <danielfebrian015@gmail.com>
 */
class NodeBase : public cSimpleModule
{
  protected:
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
     * Is this node the sender for network packet?
     */
    int senderNodeID;

    /**
     * Destination ID of the network packet.
     */
    int destinationNodeID;

    /**
     * The NED implementation should hold the choice
     * of what value will be used as identifier.
     * This variable stores the choice.
     */
    const char *identityValue;

    // Collecting stats using signals.

    /**
     * Signal for packet hop count.
     * The information source is the hop count field
     * of the received packet.
     */
    simsignal_t signalPacketHopCount;

    /**
     * If a node receive a packet not destined for it then it will forward the packet.
     * This variable stores how much packet is received by a node,
     * either it will be forwarded or this node is the receiver,
     * which means this variable value is 1.
     */
    int numReceivedPacket;

    /**
     * Signal for recording number of received packet.
     */
    simsignal_t signalNumReceivedPacket;

    /**
     * Dropped packets counter.
     */
    int droppedPackets;

    /**
     * Signal for dropped packets counter.
     */
    simsignal_t signalDroppedPackets;

    /**
     * This method will print verbose messages if the logVerbose is true.
     * @see logVerbose
     */
    void printModuleLog(std::string logMessage);

    /**
     * Number of nodes in the network, also used as maximum hop count.
     * Instead of ttl field in the message, this routing example uses
     * hop count limitation in similar fashion with a firewall e.g. Linux iptables.
     */
    int numberOfNodes;

    /** Enumerated message kind for easier identification. */
    enum messageKind{
        DISCOVERY_MESSAGE,
        DISCOVERY_REPLY,
        NETWORK_PACKET,
        LINK_STATE_PACKET
    };

    /** Prepare network packet */
    NetworkPacket *prepareNetworkPacket(int destinationId);

    /** Module initialization. */
    virtual void initialize();

    /**
     * Pure virtual method for specific implementation of routing technique.
     * This method should be implemented in subclasses initialize() method.
     * The existence of this method is to avoid redundant lines of initialization
     * in subclasses since all subclasses containing specific routing technique
     * implementation have very similar module initialization.
     */
    virtual void specificInitialization();

    /**
      * Basic message handler.
      * The implementation only contains decision based on the message kind
      * to determine what should be done next with the message.
      */
     virtual void handleMessage(cMessage *msg);

    /**
     * A method to handle received network packet.
     */
    virtual void handleNetworkPacket(cMessage *msg);

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
     * Get the number of nodes in the network.
     */
    virtual int getNumberOfNodes();
};

#endif
