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

package routing.simulations;
import routing.base.*;
import ned.DelayChannel;


channel C extends DelayChannel
{
        delay = uniform(0.01s, 0.1s);
}

network Grid
{
    parameters:
        double height @prompt("Number of rows") = default(9);
        double width @prompt("Number of columns") = default(7);
        
    submodules:
        node[height*width]: <> like INode;
    connections:
        for i=0..height-1, for j=0..width-1 {
                node[i*width+j].gate++ <--> C <--> node[(i+1)*width+j].gate++ if i!=height-1;
                node[i*width+j].gate++ <--> C <--> node[(i*width+j)+1].gate++ if j!=width-1;
        }
}

network Ring
{
    parameters:
        int n = default(3); //Number of nodes
        
    submodules:
        node[n]: <> like INode;
        
    connections:
        for i=0..n-2{
        	node[i].gate++ <--> C <--> node[i+1].gate++;
        }
        node[n-1].gate++ <--> C <--> node[0].gate++;
}

network StraightLine
{
    parameters:
        int n = default(3); //Number of nodes
        
    submodules:
        node[n]: <> like INode;
        
    connections:
        for i=0..n-2{
        	node[i].gate++ <--> C <--> node[i+1].gate++;
        }
}
