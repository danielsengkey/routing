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

#ifndef __ROUTING_NODESIMPLEDISCOVERY2EXT_H_
#define __ROUTING_NODESIMPLEDISCOVERY2EXT_H_

#include <omnetpp.h>
#include <NodeSimpleDiscovery2.h>

/**
 * Give extended capability to NodeSimpleDiscovery2.
 * The main goal to avoid/reduce dropped discovery reply
 * due to destination unreachable.
 * Now, upon receiving a discovery message, node will insert the sender and gate
 * to fib, then reply the message. Since this is a minor alteration,
 * only the handleDiscoveryMessage() that changed.
 * @author Daniel Febrian Sengkey <danielfebrian015@gmail.com>
 * @see NodeSimpleDiscovery2
 */
class NodeSimpleDiscovery2ext : public NodeSimpleDiscovery2
{
  protected:
    virtual void handleDiscoveryMessage(cMessage *msg);
};

#endif
