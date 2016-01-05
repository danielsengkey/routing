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

package routing.e02flooding;
import routing.base.*;

//
// Implementation of flooding technique.
// @author Daniel Febrian Sengkey <danielfebrian015@gmail.com>
//
simple NodeFlooding extends NodeBase
{
    @class(NodeFlooding);
    
    @signal[ForwardedPackets](type="long");
 	@signal[DroppedPackets](type="long");
 	
    @statistic[hopCount](title="Packet Hop Count"; record=histogram,vector; source="HopCount";);
    @statistic[forwardedPackets](title="Number of Forwarded Packets";record=last;source="ForwardedPackets");
    @statistic[droppedPackets](title="Packets Dropped due to Hop Limit Reached";record=last;source"DroppedPackets");
    @statistic[receivedPacket](title="Number of Received Packet"; record=last; source="NumReceivedPacket";);
    
}
