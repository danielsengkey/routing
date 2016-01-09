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

#include "NodeBase.h"

Define_Module(NodeBase);

void NodeBase::initialize()
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

    // Statistics
    signalPacketHopCount    = registerSignal("HopCount");
    signalNumReceivedPacket = registerSignal("NumReceivedPacket");
    signalDroppedPackets    = registerSignal("DroppedPackets");

    // Initialize number of received packet with 0.
    numReceivedPacket   = 0;
    droppedPackets      = 0;

    // Calling specificInitialization() method.
    specificInitialization();
}

void NodeBase::specificInitialization()
{
    // Do nothing here.
    // Need to be redefined in subclasses.
}

int NodeBase::getNumberOfNodes()
{
    int n;

    cTopology *topo = new cTopology("topo");
    std::vector<std::string> nedTypes;
    nedTypes.push_back(getNedTypeName());
    topo->extractByNedTypeName(nedTypes);
    n = topo->getNumNodes();

    delete topo;
    return n;
}

void NodeBase::handleMessage(cMessage *msg)
{
    switch (msg->getKind()) {
        case NETWORK_PACKET:
            handleNetworkPacket(msg);
            break;
        default:
            EV << "Received unknown message type." << endl;
            break;
    }
}

void NodeBase::handleNetworkPacket(cMessage *msg)
{
    // TODO Function implemented in subclass.
    // In the base node the message just deleted.

    delete msg;
}

NetworkPacket* NodeBase::prepareNetworkPacket(int destinationId)
{
    EV << "Preparing Network Packet for Node " << destinationId << "." << endl;
    NetworkPacket *networkPacket = new NetworkPacket("Network packet", NETWORK_PACKET);
    networkPacket->setSourceID(myId);
    networkPacket->setDestinationID(destinationId);
    networkPacket->setHopsArraySize(numberOfNodes);
    networkPacket->setHopCount(0);
    return networkPacket;
}

void NodeBase::forwardMessage(cMessage *msg, int outGateIndex)
{
    EV << "Forwarding message " << msg->getName() << " via out gate index " << outGateIndex << endl;
    send(msg, outGateName, outGateIndex);
}

void NodeBase::broadcastMessage(cMessage *msg)
{
    // TODO The concatenation requires special attention. Need to check documentation of concatenating const c
    EV << "Broadcasting message " << msg->getName() << endl;
    for (int i=0; i<totalGate; i++) send(i==(totalGate-1)?msg:msg->dup(), outGateName, i);
    if(!msg->isScheduled()) delete msg;
}

void NodeBase::selectiveBroadcast(cMessage *msg, int notViaThisGateIndex)
{
    for (int i=0; i<totalGate; i++)
        {
            if(i==notViaThisGateIndex) continue;
            send(i==(totalGate-1)?msg:msg->dup(), outGateName, i);
        }
    if(!msg->isScheduled()) delete msg;
}

void NodeBase::unicastSending(cMessage *msg, int outGateIndex)
{
    send(msg, outGateName, outGateIndex);
}

void NodeBase::printModuleLog(std::string logMessage)
{
    if(logVerbose) EV << logMessage << endl;
}
