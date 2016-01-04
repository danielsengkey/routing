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

package routing.base;

//
// Covers basic functionalities of a node.
// Behaviours on routing method should be covered in subclasses.
// @author Daniel Febrian Sengkey <danielfebrian015@gmail.com>
//
simple NodeBase like INode
{
    parameters:
        string identity = default("id");
        bool logVerbose = default(false);
        int senderNodeID;
        int destinationNodeID;
        
        // Signals from C++ module
        @signal[HopCount](type="long");
        @signal[NumReceivedPacket](type="long");
        
        // Statistics recording
        @statistic[hopCount](title="Packet Hop Count"; record=last; source="HopCount";);
        @statistic[receivedPacket](title="Number of Received Packet"; record=last; source="NumReceivedPacket";);
        
        @display("i=misc/node2");
        
    gates:
        inout gate[];
}
