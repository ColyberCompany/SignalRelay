#include "config.h"
#include "Relay.h"
#include <Tasker.h>
#include <ESP8266WiFiComm/ESP8266WiFiComm.cpp>
#include <StreamComm.h>
#include <Arduino.h>

Tasker tasker(10);

PacketComm::StreamComm<Config::CommMaxPacketSize> uartComm(&Serial);
PacketComm::ESP8266WiFiComm wifiComm(Config::WiFiPort, Config::CommMaxPacketSize);

Relay signalRelay(uartComm, wifiComm);

// Tasker tasks:

class : public IExecutable
{
	void execute() override
	{
		Serial.println(wifiComm.getLocalIP());

		if (wifiComm.receive())
		{
			auto data = wifiComm.getReceived();
			Serial.println(data.size);
		}
	}
} debugTask;

class : public IExecutable
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

	WiFi.mode(WIFI_STA);
    WiFi.begin(Config::WiFiSSID, Config::WiFiPassword);
    wifiComm.setTargetIPAddressAlwaysToSender();

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);


	// tasker.addTask_Hz(&debugTask, 10);
	tasker.addTask_Hz(&signalRelay, 250);
	tasker.addTask_Hz(&wifiStateDiodeTask, 5);
}

void loop()
{
	tasker.loop();
}