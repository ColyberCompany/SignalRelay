#include "Relay.h"
#include "config.h"
#include <SimpleTasker.h>
#include <ESP8266WiFiComm/ESP8266WiFiComm.cpp>
#include <StreamComm.h>
#include <Task.h>


SimpleTasker tasker(10);

StreamComm uartComm(&Serial, Config::CommMaxPacketSize);
ESP8266WiFiComm wifiComm(Config::WiFiSSID, Config::WiFiPassword, Config::WiFiPort, Config::CommMaxPacketSize);

Relay signalRelay(uartComm, wifiComm);




// Tasker tasks:

class : public Task
{
    void execute() override
    {
        //Serial.println(wifiComm.getLocalIP());
    }
} debugTask;


class : public Task
{
    void execute() override
    {
        if (wifiComm.isConnected())
            digitalWrite(LED_BUILTIN, LOW); // states are for some reason inverted
        else
            digitalWrite(LED_BUILTIN, HIGH);
    }
} wifiStateDiodeTask;





void setup()
{
    Serial.begin(115200);

    uartComm.begin();

    wifiComm.begin();
    wifiComm.setTargetIPAddressAlwaysToSender();

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);


    tasker.addTask(&debugTask, 10);
    tasker.addTask(&signalRelay, 250);
    tasker.addTask(&wifiStateDiodeTask, 5);
}


void loop()
{
    tasker.runLoop();
}