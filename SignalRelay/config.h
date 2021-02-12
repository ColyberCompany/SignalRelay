/**
 * @file config.h
 * @author Jan Wielgus
 * @brief Configuration file.
 * @date 2020-12-01
 * 
 */


#ifndef CONFIG_H
#define CONFIG_H

#ifdef ARDUINO
    #include <Arduino.h>
#endif


namespace Config
{
    const uint16_t CommMaxPacketSize = 70;

    const char* const WiFiSSID = "HUAWEI_P_smart";
	const char* const WiFiPassword = "22222222";
    const uint16_t WiFiPort = 8888;
}


#endif
