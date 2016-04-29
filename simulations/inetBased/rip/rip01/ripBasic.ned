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

package routing.simulations.inetBased.rip.rip01;
import inet.common.lifecycle.LifecycleController;
import inet.common.scenario.ScenarioManager;
import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.networklayer.ipv4.RoutingTableRecorder;
import inet.node.ethernet.Eth100M;
import inet.node.ethernet.Eth1G;
import inet.node.inet.StandardHost;
import inet.node.rip.RIPRouter;

network ripBasic
{
    @display("bgb=940,362");
    submodules:
        cli: StandardHost {
            @display("p=27,202");
            gates:
                ethg[1];
        }
        srv: StandardHost {
            @display("p=895,202;i=device/server");
            gates:
                ethg[1];
        }

        configurator: IPv4NetworkConfigurator {
            @display("p=51,22");
            config = xml(
            	"<config>"
            		+"<interface hosts='*' address='192.168.0.x' netmask='255.255.255.x'/>"
            		+"<route hosts='cli' destination='*' netmask='*' gateway='primaryRouter1'/>"
            		+"<route hosts='srv' destination='*' netmask='*' gateway='primaryRouter2'/>"
            	+"</config>");
        }

        scenarioManager: ScenarioManager {
            @display("p=167,22");
        }
        altRouter1: RIPRouter {
            @display("p=472,83");
            gates:
                ethg[2];
        }
        altRouter2: RIPRouter {
            @display("p=472,321");
            gates:
                ethg[2];
        }
        primaryRouter1: RIPRouter {
            @display("p=204,202");
            gates:
                ethg[4];
        }
        primaryRouter2: RIPRouter {
            @display("p=736,202");
            gates:
                ethg[4];
        }
        rtr: RoutingTableRecorder {
            @display("p=258,22");
        }
    connections:
        cli.ethg[0] <--> Eth100M <--> primaryRouter1.ethg[3];
        srv.ethg[0] <--> Eth100M <--> primaryRouter2.ethg[3];

        primaryRouter1.ethg[0] <--> Eth1G <--> primaryRouter2.ethg[0];

        primaryRouter1.ethg[1] <--> Eth100M <--> altRouter1.ethg[0];
        primaryRouter1.ethg[2] <--> Eth100M <--> altRouter2.ethg[0];

        altRouter2.ethg[1] <--> Eth100M <--> primaryRouter2.ethg[1];
        altRouter1.ethg[1] <--> Eth100M <--> primaryRouter2.ethg[2];
}
