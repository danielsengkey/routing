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

package routing.simulations.inetBased.static.staticRouting2;

import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.node.ethernet.Eth100M;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;


network StaticRouting2
{
    @display("bgb=926,345");
    submodules:
        client: StandardHost {
            @display("p=69,155");
        }
        RT_A: Router {
            @display("p=225,155");
        }
        RT_B: Router {
            @display("p=370,155");
        }
        server1: StandardHost {
            @display("p=793,37;i=device/server2");
        }
        RT_B1: Router {
            @display("p=563,37");
        }
        RT_B2: Router {
            @display("p=563,130");
        }
        RT_B3: Router {
            @display("p=563,215");
        }
        RT_B4: Router {
            @display("p=563,288");
        }
        server2: StandardHost {
            @display("p=793,130;i=device/server2");
        }
        server3: StandardHost {
            @display("p=793,215;i=device/server2");
        }
        server4: StandardHost {
            @display("p=793,288;i=device/server2");
        }
        configurator: IPv4NetworkConfigurator {
            @display("p=61,29");
        }
    connections:
        RT_A.pppg++ <--> Eth100M <--> RT_B.pppg++;
        client.ethg++ <--> Eth100M <--> RT_A.ethg++;

        RT_B1.ethg++ <--> Eth100M <--> RT_B.ethg++;
        RT_B2.ethg++ <--> Eth100M <--> RT_B.ethg++;
        RT_B3.ethg++ <--> Eth100M <--> RT_B.ethg++;
        RT_B4.ethg++ <--> Eth100M <--> RT_B.ethg++;

        server1.ethg++ <--> Eth100M <--> RT_B1.ethg++;
        server2.ethg++ <--> Eth100M <--> RT_B2.ethg++;
        server3.ethg++ <--> Eth100M <--> RT_B3.ethg++;
        server4.ethg++ <--> Eth100M <--> RT_B4.ethg++;
}
