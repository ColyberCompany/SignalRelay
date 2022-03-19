/**
 * @file Relay.cpp
 * @author Jan Wielgus
 * @date 2021-02-12
 *
 */

#include "Relay.h"

using namespace PacketComm;

Relay::Relay(ITransceiver &transceiver1, ITransceiver &transceiver2)
	: transc1(transceiver1), transc2(transceiver2)
{
}

void Relay::execute()
{
	relayData(transc1, transc2);
	relayData(transc2, transc1);
}

void Relay::relayData(ITransceiver &source, ITransceiver &dest)
{
	while (source.receive())
	{
		DataBuffer nextData = source.getReceived();
		dest.send(nextData);
	}
}
