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

#ifndef NODEFLOODING_H_
#define NODEFLOODING_H_

#include <NodeBase.h>

/*
 * This class implements flooding routing technique.
 * Received packet will be forwarded on all gates
 * except the incoming gate.
 * A variable  and simsignal_t to record how many times this node
 * has forward network packet is added for post-simulation analysis.
 * The initial network packet also sent using flooding technique.
 * @author Daniel Febrian Sengkey <danielfebrian015@gmail.com>
 * @see NodeBase
 */

class NodeFlooding: public NodeBase {

protected:
    /* How many times this node forward packet? */
    int numForwardedPackets;

    /* Signal to record numForwardedPackets */
    simsignal_t signalNumForwardedPackets;

    /* Override NetworkPacket handler. */
    virtual void handleNetworkPacket(cMessage *msg);

    /* Override selectiveBroadcast method by adding forwarding counter. */
    virtual void selectiveBroadcast(cMessage *msg, int notViaThisGateIndex);

    /**
     * Redefine the specific initialization.
     */
    virtual void specificInitialization();
};

#endif /* NODEFLOODING_H_ */
