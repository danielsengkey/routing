//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003-2010 Andras Varga, Rudolf Hornig
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

package routing.simulations;
import routing.base.*;
import ned.DelayChannel;

//
// Copied from TicToc Example with some modifications
//
network Tictoc16
{
    types:
        channel C extends DelayChannel
		{
        	delay = uniform(0.01s, 0.1s);
		}
    submodules:
        tic[6]: <> like INode;
    connections:
        tic[0].gate++ <--> C <--> tic[1].gate++;
        tic[1].gate++ <--> C <--> tic[2].gate++;
        tic[1].gate++ <--> C <--> tic[4].gate++;
        tic[3].gate++ <--> C <--> tic[4].gate++;
        tic[4].gate++ <--> C <--> tic[5].gate++;
}

