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

package routing.simulations.inetBased.ospf.ospf01;
import inet.common.lifecycle.LifecycleController;
import inet.common.scenario.ScenarioManager;
import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.networklayer.ipv4.RoutingTableRecorder;
import inet.node.inet.StandardHost;
import inet.node.ospfv2.OSPFRouter;
import inet.node.ethernet.Eth100M;
import inet.node.ethernet.Eth1G;

network ospfBasic
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
        }

        scenarioManager: ScenarioManager {
            @display("p=167,22");
        }
        RT_A: OSPFRouter {
            @display("p=472,83");
            gates:
                ethg[2];
        }
        RT_B: OSPFRouter {
            @display("p=472,321");
            gates:
                ethg[2];
        }
        RT_C: OSPFRouter {
            @display("p=204,202");
            gates:
                ethg[4];
        }
        RT_D: OSPFRouter {
            @display("p=736,202");
            gates:
                ethg[4];
        }
        rtr: RoutingTableRecorder {
            @display("p=258,22");
        }
        lifecycleController: LifecycleController {
            @display("p=348,22");
        }
    connections:
        cli.ethg[0] <--> Eth1G <--> RT_C.ethg[3];
        srv.ethg[0] <--> Eth1G <--> RT_D.ethg[3];

        RT_C.ethg[0] <--> Eth100M <--> RT_D.ethg[0];

        RT_C.ethg[1] <--> Eth1G <--> RT_A.ethg[0];
        RT_C.ethg[2] <--> Eth1G <--> RT_B.ethg[0];

        RT_B.ethg[1] <--> Eth1G <--> RT_D.ethg[1];
        RT_A.ethg[1] <--> Eth1G <--> RT_D.ethg[2];
}
