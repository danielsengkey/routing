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
// Simple implementation of Neighbour Discovery protocol
// Node sends Neighbour Discovery, the receiver then will reply with
// Discovery Reply packet. Discovered node will be added to the neighbour table.
// @author Daniel Febrian Sengkey <danielfebrian015@gmail.com>
// @see NodeDiscoveryBase
// @see NodeBase
// @see Discovery

simple NodeSimpleDiscovery extends NodeDiscoveryBase
{
    @class(NodeSimpleDiscovery);
}
