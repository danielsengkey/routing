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

#ifndef __ROUTING_NODESIMPLEDISCOVERY2_H_
#define __ROUTING_NODESIMPLEDISCOVERY2_H_

#include <omnetpp.h>
#include <base/NodeDiscoveryBase.h>

/**
 * This implementation of neighbour discovery covers multihop neighbours.
 * It means a node could identify all nodes in the network.
 * @author Daniel Febrian Sengkey <danielfebrian015@gmail.com>
 * @see NodeDiscoveryBase
 * @see NodeBase
 */
class NodeSimpleDiscovery2 : public NodeDiscoveryBase
{
  protected:

    /**
     * Since this module also forwarding received neighbour discovery message,
     * there is chance to receive its own neighbour discovery message.
     * This variable counts the received neighbour discovery message which sent by this node.
     */
    int rcvdSelfND;

    /**
     * Signal for rcvdSelfND
     */
    simsignal_t signalRcvdSelfND;

    /**
     * Tracking received discovery reply from indexed node.
     */
    int rcvdDRdup;

    /**
     * Signal for rcvdDRdup;
     */
    simsignal_t signalRcvdDRdup;

    /**
     * Number of dropped neighbour discovery reply due to address unreachable.
     */
    int droppedDRunreachable;

    /**
     * Signal for droppedDRunreachable;
     */
    simsignal_t signalDroppedDRunreachable;

    /**
     * Number of dropped neighbour discovery due to hop limit reached.
     */
    int droppedNDtimeOut;

    /**
     * Signal for droppedNDtimeOut
     */
    simsignal_t signalDroppedNDtimeOut;

    /**
     * Number of dropped discovery reply due to hop limit reached.
     */
    int droppedDRtimeOut;

    /**
     * Signal for droppedDRtimeOut;
     */
    simsignal_t signalDroppedDRtimeOut;

    virtual void handleDiscoveryMessage(cMessage * msg);

    virtual void handleDiscoveryReply(cMessage *msg);

    virtual void specificInitialization();

    virtual void finish();
};

#endif
