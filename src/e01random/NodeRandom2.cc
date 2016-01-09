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

#include <e01random/NodeRandom2.h>

Define_Module(NodeRandom2);

void NodeRandom2::specificInitialization()
{
    numberOfNodes = pow(getNumberOfNodes(),2)<1024?pow(getNumberOfNodes(),2):1024;

    if(senderNodeID==myId)
        unicastSending(prepareNetworkPacket(destinationNodeID), intuniform(0, totalGate-1));
}

void NodeRandom2::handleNetworkPacket(cMessage *msg)
{
    NetworkPacket *receivedNP = check_and_cast<NetworkPacket *>(msg);

    numReceivedPacket++;
    emit(signalNumReceivedPacket, numReceivedPacket);

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

        emit(signalPacketHopCount, receivedNP->getHopCount());

        delete receivedNP;

    } else {
        if(receivedNP->getHopCount()<numberOfNodes) { //Keep forwarding while the hop count still less than number of nodes

            int selectedOutGate;

//            EV << "Received " << receivedNP->getName() << " incoming gate index " << receivedNP->getArrivalGate()->getIndex() << endl;

            printModuleLog("Adding hop ID into hops.");
            receivedNP->setHops(receivedNP->getHopCount(), myId);

            printModuleLog("Increasing hopCount.");
            receivedNP->setHopCount(receivedNP->getHopCount()+1);

            printModuleLog("Selecting random gate for forwarding.");

            // Randomly select output gate, repeat if the input gate is selected.
            do {
                selectedOutGate = intuniform(0, totalGate-1);
            }while (selectedOutGate==receivedNP->getArrivalGate()->getIndex());

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
