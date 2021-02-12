/**
 * @file Relay.h
 * @author Jan Wielgus
 * @brief Class used to receive signal from one source and retransmit it to the second one
 * (and vice versa).
 * @date 2021-02-12
 * 
 */



#ifndef RELAY_H
#define RELAY_H

#ifdef ARDUINO
    #include <Arduino.h>
#endif

#include <ITransceiver.h>
#include <Task.h>


class Relay : public Task
{
    ITransceiver& transc1;
    ITransceiver& transc2;

    static const uint16_t MaxEmptyPacketsInARow = 3;

public:
    Relay(ITransceiver& transceiver1, ITransceiver& transceiver2);

private:
    void execute() override;

    static void relayData(ITransceiver& source, ITransceiver& dest);
};


#endif
