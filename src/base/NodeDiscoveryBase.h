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

    /**
     * Hop limit or time-to-live of a neighbour discovery packet.
     * Should be set within prepareMessage().
     */
    int ttlNeighbourDiscovery;

    /** Counter for the number of received neighbour discovery packet. */
    int rcvdND;

    /** Counter for the number of identically (duplicated) received neighbour discovery packet. */
    int rcvdNDdup;

    /** Signal for rcvdND. */
    simsignal_t signalRcvdND;

    /** Signal for rcvdNDdup. */
    simsignal_t signalRcvdNDdup;

    /** Neighbour Discovery message that will be sent by this node. */
    DiscoveryMessage myDiscoveryMessage;

    /** Received Discovery Message. */
    DiscoveryMessage receivedDiscovery;

    /** A simple routing table. */
    typedef std::map<int,int> RoutingTable;

    /** The forwarding information base, instance of the routing table. */
    RoutingTable fib;

    /** A method for discovery message preparation. If a broadcast message then the destination id is -1. */
    DiscoveryMessage *prepareMessage(int messageKind, int destinationId, int ttl);

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

     /** A method to print fib. @see fib */
     virtual void printFIB();


     /** Check the routing table to find a node and output gate to reach it. */
     virtual int getOutGate(int node);

     /**
      * Finalize
      */
     virtual void finish();
};

#endif
