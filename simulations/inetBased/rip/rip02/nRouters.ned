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

package routing.simulations.inetBased.rip.rip02;

import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.node.ethernet.Eth100M;
import inet.node.inet.StandardHost;
import inet.node.rip.RIPRouter;


network NRouters
{
    parameters:
        int n; //Number of routers

    submodules:
        cli: StandardHost {
            @display("p=26,99");
            gates:
                ethg[1];
        }
        router[n]: RIPRouter {
           gates:
                ethg[2];
        }
        srv: StandardHost {
            @display("p=186,99;i=device/server");
            gates:
                ethg[1];
        }

        configurator: IPv4NetworkConfigurator {
            @display("p=101,24");
            config = xml(
            	"<config>"
                    +"<route hosts='srv' destination='*' netmask='0.0.0.0' interface='eth0' />"
					+"<route hosts='cli' destination='*' netmask='0.0.0.0' gateway='router[0]'/>"
            		+"<interface hosts='*' address='192.168.0.x' netmask='255.255.255.x' />"
            	+"</config>");
        }
        
    connections:
        cli.ethg++ <--> Eth100M <--> router[0].ethg++;
        for i=0..n-2{
            router[i].ethg++ <--> Eth100M <--> router[i+1].ethg++;
        }
        router[n-1].ethg[1] <--> Eth100M <--> srv.ethg[0];        
}
