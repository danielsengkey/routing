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

#include <e01random/NodeRandom.h>

Define_Module(NodeRandom);

void NodeRandom::initialize()
{
    logVerbose  = par("logVerbose").boolValue();

    /** Check if the identity parameter has valid value. */
    identityValue = par("identity").stringValue();

    if (
            !(
                    (strcmp(identityValue,"index")==0)
                    ||
                    (strcmp(identityValue,"id")==0)
            )
    )
        error("Identity must be set as \"index\" or \"id\" (CASE SENSITIVE), instead of " + *identityValue);

    myId                = par("identity").stringValue()=="index"?getIndex():getId();
    senderNodeID        = par("senderNodeID").doubleValue();
    destinationNodeID   = par("destinationNodeID").doubleValue();

    inGateName  = "gate$i";
    outGateName = "gate$o";
    totalGate   = gateSize(inGateName);

    cTopology *topo = new cTopology("topo");
    std::vector<std::string> nedTypes;
    nedTypes.push_back(getNedTypeName());
    topo->extractByNedTypeName(nedTypes);

    numberOfNodes = pow(topo->getNumNodes(),2)<1024?pow(topo->getNumNodes(),2):1024;
    delete topo;

    if(senderNodeID==myId) unicastSending(prepareNetworkPacket(destinationNodeID), intuniform(0, totalGate-1));
}


void NodeRandom::handleNetworkPacket(cMessage *msg)
{
    NetworkPacket *receivedNP = check_and_cast<NetworkPacket *>(msg);

    if(receivedNP->getDestinationID()==myId)
    {
        EV << "Received " << receivedNP->getName() << " from " << receivedNP-> getSourceID() << endl;
        if (receivedNP->getHopCount()>0) EV << "Hops ";
        if(receivedNP->getHopsArraySize()>10) EV << endl;
        for(int i=0; i<receivedNP->getHopsArraySize(); i++)
        {
            if(receivedNP->getHops(i)==0) break;

            EV << receivedNP->getHops(i) << "\t";
            if(i!=0 && i%10==0) EV << endl;
        }
        EV << endl;
        EV << "Hop count\t= " << receivedNP->getHopCount() << endl;
        delete receivedNP;

    } else {
        if(receivedNP->getHopCount()<numberOfNodes) { //Keep forwarding while the hop count still less than number of nodes
            printModuleLog("Adding hop ID into hops.");
            receivedNP->setHops(receivedNP->getHopCount(), myId);

            printModuleLog("Increasing hopCount.");
            receivedNP->setHopCount(receivedNP->getHopCount()+1);

            printModuleLog("Selecting random gate for forwarding.");

            int selectedOutGate = intuniform(0, totalGate-1);
            forwardMessage(receivedNP, selectedOutGate);
        } else {
            EV << "Message hop limit reached! Ending simulation!" << endl;
            if(receivedNP->getHopsArraySize()>10) EV << endl;
            for(int i=0; i<receivedNP->getHopsArraySize(); i++)
            {
                if(receivedNP->getHops(i)==0) break;

                EV << receivedNP->getHops(i) << "\t";
                if(i!=0 && i%10==0) EV << endl;
            }
            EV << endl;
            EV << "Hop count\t= " << receivedNP->getHopCount() << endl;
            EV << "MESSAGE NOT DELIVERED!!!" << endl;
            delete receivedNP;
        }
    }
}


