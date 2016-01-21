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

//
// Vector message definition.
// This message is used in distance vector routing.
// It contains list of nodes and the metric to reach it
// From the point of view of the message sender.
// Although the name "vector", this message keeps
// the pair of nodes and vectors in a std::map.
// @author Daniel Febrian Sengkey <danielfebrian015@gmail.com>
//

cplusplus{{
    #include <map>
    
    typedef
    std::map<int,int> NodeVector;
}}

class noncobject NodeVector;

message DistanceVectorMessage{
    int sourceID;
    NodeVector neighbourList;
}