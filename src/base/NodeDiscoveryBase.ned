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
// Contains basic functionalities of node that uses network discovery.
// Specific functions should be implemented at subclasses.
// @author Daniel Febrian Sengkey <danielfebrian015@gmail.com>
// @see NodeBase
//
simple NodeDiscoveryBase extends NodeBase
{
    
    parameters:
    	@class(NodeDiscoveryBase);
        // TTL or hop limit of the neighbour discovery.
        // This should prevent the network flooded by 
        // unneeded discovery.
        int discoveryTTL = default(1);
        
        @signal[receivedND](type="long");
        @signal[receivedNDdup](type="long");
        
        @statistic[receivedND](title="Number of Received Neighbour Discovery Message";record=last);
        @statistic[receivedNDdup](title="Number of Received Duplicated Neighbour Discovery Message";record=last);
}
