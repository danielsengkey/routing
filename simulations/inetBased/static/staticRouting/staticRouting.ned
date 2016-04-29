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

package routing.simulations.inetBased.static.staticRouting;

import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.node.ethernet.Eth100M;
import inet.node.ethernet.EtherSwitch;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;


network StaticRouting
{
    @display("bgb=380,337");
    submodules:
        hostA: StandardHost {
            @display("p=61,269");
        }
        hostB: StandardHost {
            @display("p=306,269");
        }
        hostC: StandardHost {
            @display("p=306,88");
        }
        hostD: StandardHost {
            @display("p=61,88");
        }
        router: Router {
            @display("p=183,171");
        }
        switch1: EtherSwitch {
            @display("p=183,269");
        }
        switch2: EtherSwitch {
            @display("p=183,88");
        }

        configurator: IPv4NetworkConfigurator {

            @display("p=53,22");
        }
    connections:
        router.ethg++ <--> Eth100M <--> switch1.ethg++;
        router.ethg++ <--> Eth100M <--> switch2.ethg++;
        hostA.ethg++ <--> Eth100M <--> switch1.ethg++;
        hostB.ethg++ <--> Eth100M <--> switch1.ethg++;
        hostC.ethg++ <--> Eth100M <--> switch2.ethg++;
        hostD.ethg++ <--> Eth100M <--> switch2.ethg++;

}
