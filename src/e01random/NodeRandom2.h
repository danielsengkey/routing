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

#ifndef NODERANDOM_H_
#define NODERANDOM_H_

#include <NodeBase.h>

/**
 * This node implements random routing.
 * The instance of this class will select random gate <b> EXCEPT </b> the incoming gate.
 * with uniform probability.
 * Therefore this class only override the handleNetworkPacket() method.
 * @author Daniel Febrian Sengkey <danielfebrian015@gmail.com>
 * @see NodeBase
 */

class NodeRandom2: public NodeBase {
    /**
     * A method to handle received network packet.
     * This method overrides handleNetworkPacket()
     * from the superclass (NodeBase).
     */
    virtual void handleNetworkPacket(cMessage *msg);

    virtual void initialize();

};

#endif /* NODERANDOM_H_ */
