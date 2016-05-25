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

package routing.simulations.inetBased.ospf.ospf02;

import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.node.ethernet.Eth10G;
import inet.node.ethernet.Eth40G;
import inet.node.ethernet.EtherSwitch;
import inet.node.inet.StandardHost;
import inet.node.inet.Router;

import inet.node.ethernet.Eth10M;
import inet.node.ethernet.Eth100M;
import inet.node.ethernet.Eth1G;

//
// Eventhough the routers are named after cities/regions,
// this network is not a representation of a real implementation.
//

module LAN
{
    parameters:
        int n = default(1); // number of clients
        @display("is=n;i=misc/town");

    gates:
        inout ethg;

    submodules:
        cli[n]: StandardHost {
            gates:
                ethg[1];
        }
        sw: EtherSwitch;
    connections:
        for i=0..n-1 {
            cli[i].ethg[0] <--> Eth10M <--> sw.ethg++;
        }
        sw.ethg++ <--> ethg;
}

module MetroManado
{
    parameters:
        int n = default(1); // number of clients
        int s = default(1); // number of clients
        @display("is=l;i=misc/city");

    gates:
        inout ethg;

    submodules:
        cli[n]: StandardHost {
            gates:
                ethg[1];
        }
        srv[s]: StandardHost {
            @display("i=device/server");
            gates:
                ethg[1];
        }
        sw: EtherSwitch;
    connections:
        for i=0..n-1 {
            cli[i].ethg[0] <--> Eth10M <--> sw.ethg++;
        }
        for i=0..s-1 {
            srv[i].ethg[0] <--> Eth1G <--> sw.ethg++;
        }
        sw.ethg++ <--> ethg;
}

network Sulutgo
{
    @display("bgb=1366,768");
    submodules:
        configurator: IPv4NetworkConfigurator {
            @display("p=30,21");
        }
        RT_Bintauna: Router {
            @display("p=61,253");
            gates:
                ethg[2];
        }
        RT_Kwandang: Router {
            @display("p=100,389");
            gates:
                ethg[2];
        }
        RT_Popayato: Router {
            @display("p=260,191");
            gates:
                ethg[2];
        }
        metro_gto: EtherSwitch {
            @display("p=180,308");
        }
        RT_Gorontalo: Router {
            @display("p=310,337;i=abstract/router2");
            gates:
                ethg[6];
        }
        RT_Tondano: Router {
            @display("p=499,121;i=abstract/router2");
            gates:
                ethg[5];
        }
        RT_Tomohon: Router {
            @display("p=809,121;i=abstract/router2");
            gates:
                ethg[5];
        }
        RT_Manado: Router {
            @display("p=980,354;i=abstract/opticalrouter");
            gates:
                ethg[7];
        }
        RT_Amurang: Router {
            @display("p=460,496;i=abstract/router2");
            gates:
                ethg[6];
        }
        RT_Bitung: Router {
            @display("p=825,512;i=abstract/router2");
            gates:
                ethg[7];
        }
        metro_amg: EtherSwitch {
            @display("p=444,624");
        }
        RT_Tanawangko: Router {
            @display("p=293,622");
            gates:
                ethg[1];
        }
        RT_Tumpaan: Router {
            @display("p=592,622");
            gates:
                ethg[1];
        }
        RT_Pondang: Router {
            @display("p=438,724");
            gates:
                ethg[1];
        }
        RT_Sagerat: Router {
            @display("p=786,679");
            gates:
                ethg[1];
        }
        RT_Manembo2: Router {
            @display("p=948,659");
            gates:
                ethg[1];
        }
        RT_Bolmong: Router {
            @display("p=1104,253");
            gates:
                ethg[2];
        }
        RT_Bolangitang: Router {
            @display("p=1237,241");
            gates:
                ethg[1];
        }
        RT_Bolanguki: Router {
            @display("p=1297,333");
            gates:
                ethg[1];
        }
        RT_Kotamobagu: Router {
            @display("p=1104,461");
            gates:
                ethg[3];
        }
        RT_Inobonto: Router {
            @display("p=1210,547");
            gates:
                ethg[3];
        }
        RT_Ilongkou: Router {
            @display("p=1088,625");
            gates:
                ethg[2];
        }
        RT_Ibolian: Router {
            @display("p=1321,625");
            gates:
                ethg[2];
        }

        Manado_Net: MetroManado {
            parameters:
                @display("p=985,180;t=708 Hosts");
        }

        Kwandang_Net: LAN {
            parameters:
                @display("t=81 Clients;p=92,506");
        }
        Bintauna_Net: LAN {
            parameters:
                @display("t=180 Clients;p=67,134");
        }
        Popayato_Net: LAN {
            parameters:
                @display("t=54 Clients;p=292,88");
        }
        Ilongkou_Net: LAN {
            parameters:
                @display("t=13 Clients;p=1088,720");
        }
        Ibolian_Net: LAN {
            parameters:
                @display("t=9 Clients;p=1321,724");
        }
        Inobonto_Net: LAN {
            parameters:
                @display("t=33 Clients;p=1305,475");
        }
        Kotamobagu_Net: LAN {
            parameters:
                @display("t=311 Clients;p=985,515");
        }
        rmj_bolaang2: EtherSwitch {
            @display("p=1210,624");
        }
        metro_bolmong: EtherSwitch {
            @display("p=1171,360");
        }
    connections:
        // Backbone
        RT_Manado.ethg[0] <--> Eth10G <--> RT_Tomohon.ethg[0];
        RT_Manado.ethg[1] <--> Eth100M <--> RT_Tondano.ethg[0];
        RT_Manado.ethg[2] <--> Eth100M <--> RT_Gorontalo.ethg[0];
        RT_Manado.ethg[3] <--> Eth100M <--> RT_Amurang.ethg[0];
        RT_Manado.ethg[4] <--> Eth1G <--> RT_Bitung.ethg[0];
        RT_Manado.ethg[5] <--> Eth1G <--> RT_Bolmong.ethg[0];
        RT_Manado.ethg[6] <--> Eth10G <--> Manado_Net.ethg;

        RT_Tomohon.ethg[1] <--> Eth10G <--> RT_Tondano.ethg[1];
        RT_Tomohon.ethg[2] <--> Eth100M <--> RT_Gorontalo.ethg[1];
        RT_Tomohon.ethg[3] <--> Eth100M <--> RT_Amurang.ethg[1];
        RT_Tomohon.ethg[4] <--> Eth100M <--> RT_Bitung.ethg[1];

        RT_Tondano.ethg[2] <--> Eth10G <--> RT_Gorontalo.ethg[2];
        RT_Tondano.ethg[3] <--> Eth100M <--> RT_Amurang.ethg[4];
        RT_Tondano.ethg[4] <--> Eth100M <--> RT_Bitung.ethg[6];

        RT_Gorontalo.ethg[3] <--> Eth1G <--> RT_Amurang.ethg[2];
        RT_Gorontalo.ethg[4] <--> Eth100M <--> RT_Bitung.ethg[2];

        RT_Amurang.ethg[3] <--> Eth1G <--> RT_Bitung.ethg[3];

        // Gorontalo Network
        RT_Gorontalo.ethg[5] <--> Eth1G <--> metro_gto.ethg++;
        RT_Popayato.ethg[0] <--> Eth100M <--> metro_gto.ethg++;
        RT_Bintauna.ethg[0] <--> Eth100M <--> metro_gto.ethg++;
        RT_Kwandang.ethg[0] <--> Eth100M <--> metro_gto.ethg++;

        RT_Popayato.ethg[1] <--> Eth100M <--> Popayato_Net.ethg;
        RT_Bintauna.ethg[1] <--> Eth100M <--> Bintauna_Net.ethg;
        RT_Kwandang.ethg[1] <--> Eth100M <--> Kwandang_Net.ethg;

        // Urban Bolmong
        metro_bolmong.ethg++ <--> Eth1G <--> RT_Bolmong.ethg[1];
        metro_bolmong.ethg++ <--> Eth1G <--> RT_Kotamobagu.ethg[0];
        metro_bolmong.ethg++ <--> Eth100M <--> RT_Bolangitang.ethg[0];
        metro_bolmong.ethg++ <--> Eth100M <--> RT_Bolanguki.ethg[0];

        RT_Inobonto.ethg[0] <--> Eth1G <--> RT_Kotamobagu.ethg[1];
        Kotamobagu_Net.ethg <--> Eth100M <--> RT_Kotamobagu.ethg[2];

        // Rural Bolmong
        rmj_bolaang2.ethg++ <--> Eth100M <--> RT_Inobonto.ethg[1];
        rmj_bolaang2.ethg++ <--> Eth100M <--> RT_Ibolian.ethg[0];
        rmj_bolaang2.ethg++ <--> Eth100M <--> RT_Ilongkou.ethg[0];

        RT_Ilongkou.ethg[1] <--> Eth100M <--> Ilongkou_Net.ethg;
        RT_Ibolian.ethg[1] <--> Eth100M <--> Ibolian_Net.ethg;
        RT_Inobonto.ethg[2] <--> Eth100M <--> Inobonto_Net.ethg;

		// Bitung Metro
        RT_Sagerat.ethg[0] <--> Eth100M <--> RT_Bitung.ethg[4];
        RT_Manembo2.ethg[0] <--> Eth100M <--> RT_Bitung.ethg[5];

        // Minsel
        metro_amg.ethg++ <--> Eth100M <--> RT_Amurang.ethg[5];
        metro_amg.ethg++ <--> Eth100M <--> RT_Tanawangko.ethg[0];
        metro_amg.ethg++ <--> Eth100M <--> RT_Pondang.ethg[0];
        metro_amg.ethg++ <--> Eth100M <--> RT_Tumpaan.ethg[0];
}
