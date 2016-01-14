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

//
// This module extended the functionality of NodeSimpleDiscovery2.
// The goal is to eliminate dropped messages due to unreachable destination,
// which exists in NodeSimpleDiscovery2 when the network spans more than 7 hops.
// Remember, it is <font color="red"> <b> hops NOT nodes </b></font>. 
// @author Daniel Febrian Sengkey <danielfebrian015@gmail.com>
// @see NodeSimpleDiscovery2
//
simple NodeSimpleDiscovery2ext extends NodeSimpleDiscovery2
{
    @class(NodeSimpleDiscovery2ext);
}
