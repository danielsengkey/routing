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

#include <e02flooding/NodeFlooding.h>

Define_Module(NodeFlooding);

void NodeFlooding::specificInitialization()
{
    // Signal to record numForwardedPackets
    signalNumForwardedPackets   = registerSignal("ForwardedPackets");

    // Initialize number of forwarded packet with 0.
    numForwardedPackets = 0;

    numberOfNodes = getNumberOfNodes();

    // Broadcast network packet
    if(senderNodeID==myId) broadcastMessage(prepareNetworkPacket(destinationNodeID));
}

void NodeFlooding::handleNetworkPacket(cMessage *msg)
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
            printModuleLog("Adding hop ID into hops.");
            receivedNP->setHops(receivedNP->getHopCount(), myId);

            printModuleLog("Increasing hopCount.");
            receivedNP->setHopCount(receivedNP->getHopCount()+1);

            // Flooding
            selectiveBroadcast(receivedNP, receivedNP->getArrivalGate()->getIndex());

        } else {
            EV << "Message hop limit reached! Delete message." << endl;
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
            droppedPackets++;
            emit(signalDroppedPackets, droppedPackets);
            delete receivedNP;
        }
    }
}

void NodeFlooding::selectiveBroadcast(cMessage *msg, int notViaThisGateIndex)
{
    for (int i=0; i<totalGate; i++)
        {
            if(i==notViaThisGateIndex) continue;
            send(i==(totalGate-1)?msg:msg->dup(), outGateName, i);

            // Increase number of forwarded packet each time a packet forwarded through each gate.
            numForwardedPackets++;
        }
    if(!msg->isScheduled()) delete msg;
    emit(signalNumForwardedPackets, numForwardedPackets);
}
