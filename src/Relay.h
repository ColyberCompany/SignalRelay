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
#include <IExecutable.h>


class Relay : public IExecutable
{
    PacketComm::ITransceiver& transc1;
    PacketComm::ITransceiver& transc2;

public:
    Relay(PacketComm::ITransceiver& transceiver1, PacketComm::ITransceiver& transceiver2);

private:
    void execute() override;

    static void relayData(PacketComm::ITransceiver& source, PacketComm::ITransceiver& dest);
};


#endif
