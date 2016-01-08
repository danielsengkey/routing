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

#ifndef __ROUTING_NODESIMPLEDISCOVERY_H_
#define __ROUTING_NODESIMPLEDISCOVERY_H_

#include <omnetpp.h>
#include <base/NodeDiscoveryBase.h>

/**
 * Simple implementation of neighbour discovery protocol.
 * Send a neighbour discovery packet then wait for the reply.
 * Upon receiving a reply, then add the replier and the incoming gate
 * to the routing table.
 * @author Daniel Febrian Sengkey <danielfebrian015@gmail.com>
 * @see NodeDiscoveryBase
 * @see NodeBase
 */
class NodeSimpleDiscovery : public NodeDiscoveryBase
{
  protected:
    virtual void handleDiscoveryMessage(cMessage * msg);

    virtual void handleDiscoveryReply(cMessage *msg);
};

#endif
