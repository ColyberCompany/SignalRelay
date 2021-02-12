#include "Relay.h"
#include "config.h"
#include <SimpleTasker.h>
#include <ESP8266WiFiComm/ESP8266WiFiComm.cpp>
#include <StreamComm.h>


SimpleTasker tasker(10);

StreamComm uartComm(&Serial, Config::CommMaxPacketSize);
ESP8266WiFiComm wifiComm(Config::WiFiSSID, Config::WiFiPassword, Config::WiFiPort, Config::CommMaxPacketSize);
Relay signalRelay(uartComm, wifiComm);


void setup()
{
    Serial.begin(115200);

    uartComm.begin();

    wifiComm.begin();
    wifiComm.setTargetIPAddressAlwaysToSender();

    tasker.addTask(&signalRelay, 250);
}


void loop()
{
    tasker.runLoop();
}