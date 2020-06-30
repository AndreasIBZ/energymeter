/**************************************************************
 *
 *                  Settings - DDS238-TRACER-BALCONY
 *
 **************************************************************/
/*
   Auth Codes & Wifi info go in the following file.
   put this file inside your Arduino sketch folder
*/

// WIFI credentials
#define WIFI_SSID						"YOUR-SSID-HERE"
#define WIFI_PASS						"YOUR-WIFI-PASSWORD-HERE"

/*
  Over The Air Hostname  
*/
#define OTA_HOSTNAME					"DDS238-TRACER-BALCONY"

// Blynk Auth Token
#define AUTH							"YOUR-BLYNK-AUTH-TOKEN-HERE" // paste here your Blynk Auth Token; you'll find it in the Blynk-App under Project Settings - Auth Tokens - Copy All

/*
   Local Server Settings
   Comment out to use Cloud Server
*/
#define USE_LOCAL_SERVER
#define SERVER           				IPAddress(255,255,255,255) // your local Blynk Server IP
#define SERVER_PORT       				8080

/*
   Virtual Pins - Base. (For Blynk)
*/
#define vPIN_PV_POWER                   V1
#define vPIN_PV_CURRENT                 V2
#define vPIN_PV_VOLTAGE                 V3
#define vPIN_LOAD_CURRENT               V4
#define vPIN_LOAD_POWER                 V5
#define vPIN_BATT_TEMP                  V6
#define vPIN_BATT_VOLTAGE               V7
#define vPIN_BATT_REMAIN                V8
#define vPIN_CONTROLLER_TEMP            V9
#define vPIN_BATTERY_CHARGE_CURRENT     V10
#define vPIN_BATTERY_CHARGE_POWER       V11
#define vPIN_BATTERY_OVERALL_CURRENT    V12
#define vPIN_ENERGY_CONS_TODAY          V13
#define vPIN_ENERGY_CONS_MONTH          V14
#define vPIN_ENERGY_CONS_YEAR           V15
#define vPIN_ENERGY_CONS_TOTAL          V16
#define vPIN_ENERGY_GEN_TOTAL           V17
#define vPIN_CO2_REDUCTION              V18
#define vPIN_LOAD_ENABLED               V19
#define vPIN_currenttotalenergy         V20
#define vPIN_currentexportenergy        V21
#define vPIN_currentimportenergy        V22
#define vPIN_voltage                    V23
#define vPIN_current                    V24
#define vPIN_activepower                V25
#define vPIN_reactivepower              V26
#define vPIN_powerfactor                V27
#define vPIN_frequency                  V28
