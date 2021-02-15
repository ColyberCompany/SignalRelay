/**
 * @file Relay.cpp
 * @author Jan Wielgus
 * @date 2021-02-12
 * 
 */

#include "Relay.h"


Relay::Relay(ITransceiver& transceiver1, ITransceiver& transceiver2)
    : transc1(transceiver1), transc2(transceiver2)
{
}


void Relay::execute()
{
    relayData(transc1, transc2);
    relayData(transc2, transc1);
}


void Relay::relayData(ITransceiver& source, ITransceiver& dest)
{
    uint16_t emptyPacketsCounter = 0;

    if (source.available())
    {
        while (source.available())
        {
            DataBuffer nextData = source.receiveNextData();
            
            if (nextData.size > 0)
            {
                dest.send(nextData);
            }
            else
                if (++emptyPacketsCounter > MaxEmptyPacketsInARow)
                    return;
        }
    }
}
