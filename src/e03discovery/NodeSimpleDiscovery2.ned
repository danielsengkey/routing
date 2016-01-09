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

package routing.e03discovery;
import routing.base.*;

//
// This module implements multihop neighbour discovery.
// It means the discovery message can be forwarded until it ttl reaches 0.
// The ttl is equal to the number of nodes in the network.
// It is set by the C++ code of this module.
// @author Daniel Febrian Sengkey <danielfebrian015@gmail.com>
// @see NodeSimpleDiscovery
// @see NodeDiscoveryBase
// @see NodeBase
// @see DiscoveryMessage
//
simple NodeSimpleDiscovery2 extends NodeDiscoveryBase
{
    @class(NodeSimpleDiscovery2);
    
    @signal[receivedSelfND](type="long");
    @signal[receivedDRdup](type="long");
    
    @signal[DroppedDRtimeOut](type="long");
    @signal[DroppedDRunreachable](type="long");
    @signal[DroppedNDtimeOut](type="long");
    
    @statistic[receivedSelfND](title="Received Own Neighbour Discovery";record=last);
    @statistic[receivedDRdup](title="Received Duplicated Discovery Reply";record=last);
    @statistic[DroppedDRtimeOut](title="Dropped Discovery Reply due to Time Out";record=last);
    @statistic[DroppedDRunreachable](title="Dropped Discovery Reply due to Destination Unreachable";record=last);
    @statistic[DroppedNDtimeOut](title="Dropped Neighbour Discovery due to Time Out";record=last);
}
