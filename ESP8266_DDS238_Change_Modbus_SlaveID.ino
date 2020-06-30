// Code for changing of SlaveID and Baudrate of communication with HIKING DDS238 EnergyMeter
// by AndreasIBZ (GitHub), 30/06/2020

#include <ModbusMaster.h>
ModbusMaster node;

// Wiring RS485 UART Module (with automatic flow control 74HC04) to ESP8266
// VCC (Module) - VIN (5V - ESP8266)
// TX (Module) - TX0 (D1 - GPIO1 - ESP8266)
// RX (Module) - RX0 (D3 - GPIO3 - ESP8266)
// GND (Module) - GND (G - GND - ESP8266)
//
// Wiring TTL-to-RS232-Converter (for output of debug console) to ESP8266
// RX (Converter) - TX1 (D4 - GPIO4 - ESP8266)
// GND (Converter) - GND (G - GND - ESP8266)
//
// => Change these values to your needs:
//
uint16_t SerialBaudrate = 57600;              // Baudrate used for serial monitoring
uint8_t curr_SlaveID = 001;                   // current SlaveID (factory setting = "001"
uint8_t curr_Baudrate = 01;                   // current Baudrate-Code
uint8_t new_SlaveID = 002;                    // valid SlaveIDs: 1 ... 247
uint8_t new_Baudrate = 01;                    // valid Baudrate-Codes: 01 - 9600, 02 - 4800, 03 - 2400, 04 - 1200
// 
//
uint16_t HIKING_DDS238_Baudrate;              // Baudrate used to communicate with HIKING via RS485 - will be set according to curr_Baudrate
uint8_t result;                               // variable to store answer of device
uint16_t devSlaveID;                          // variable to store answer of device
uint16_t devBaudrate;                         // variable to store answer of device
uint16_t setword;                             // variable to store new settings
float currenttotalenergy, currentexportenergy, currentimportenergy;
float voltage, current, powerfactor, frequency;
int16_t activepower, reactivepower;

void setup()
{
// Setting up serial communication
switch (curr_Baudrate) {
    case 1: HIKING_DDS238_Baudrate = 9600; break;
    case 2: HIKING_DDS238_Baudrate = 4800; break;
    case 3: HIKING_DDS238_Baudrate = 2400; break;
    case 4: HIKING_DDS238_Baudrate = 1200; break;
    }
  Serial.begin(HIKING_DDS238_Baudrate);        // init Serial communication with RS485-Transceiver
  Serial1.begin(SerialBaudrate, SERIAL_8N1);  // init Serial Monitor on UART1
  Serial1.setDebugOutput(true);               // pipe Debug-Output to Serial1

// Start Modbus-Communication
  node.begin(curr_SlaveID, Serial);

// confirm curr_SlaveID is working by reading its SlaveID and Baudrate-Code
    result = node.readHoldingRegisters(0x0015, 1);
    if (result == node.ku8MBSuccess) {
      devSlaveID = highByte(node.getResponseBuffer(0x00));
      devBaudrate = lowByte(node.getResponseBuffer(0x00));
      Serial1.print("Communication successful. Current SlaveID: ");
      Serial1.print(devSlaveID);
      Serial1.print(" , current Baudrate: ");
      Serial1.print(devBaudrate); 
  
// join new_SlaveID-byte and new_Baudrate-byte to a word - setword 
      setword = new_SlaveID * 256 + new_Baudrate;
      Serial1.print("new setword: 0x");
      Serial1.print(highByte(setword));
      Serial1.println(lowByte(setword));

// set word 0 of TX buffer to setword
      node.setTransmitBuffer(0, setword);

// write setword to register 0x0015
      result = node.writeMultipleRegisters(0x0015, 1);
        if (result == node.ku8MBSuccess) {
          Serial1.print("Successfully changed SlaveID to ");
          Serial1.println(new_SlaveID);
          Serial1.print("Successfully changed Baudrate to ");
          Serial1.println(new_Baudrate);
          } else { 
            Serial1.print("Error changing SlaveID and Baudrate! Using initial values for further communication ...");
            new_Baudrate = curr_Baudrate;
            new_SlaveID = curr_SlaveID;
            }
      } else { // 
      Serial1.print("Error communicating with device! Aborting ...");
      exit(0); // halt processor
      }

// communicate now with new_SlaveID & new_Baudrate 
  switch (new_Baudrate) {
      case 1: HIKING_DDS238_Baudrate = 9600; break;
      case 2: HIKING_DDS238_Baudrate = 4800; break;
      case 3: HIKING_DDS238_Baudrate = 2400; break;
      case 4: HIKING_DDS238_Baudrate = 1200; break;
      }
  node.begin(new_SlaveID, Serial);
  Serial.flush(); // wait for last transmitted data to be sent
  Serial.begin(HIKING_DDS238_Baudrate);
  while(Serial.available()) Serial.read(); 
  delay(1000);
}

void loop()
{
// Read DDS238 Energy Meter with new settings
// read current total energy
  result = node.readHoldingRegisters(0x0000, 2);
    if (result == node.ku8MBSuccess)
    {      
      currenttotalenergy = (node.getResponseBuffer(0x01) | node.getResponseBuffer(0x00) << 16) / 100.0f;
      Serial1.print("Current Total Energy: ");
      Serial1.println(currenttotalenergy);
      } else {
      Serial1.println("Reading HIKING DDS238 failed!");
      }    
      
// read rest of interesting values
  result = node.readHoldingRegisters(0x0008, 10);
    if (result == node.ku8MBSuccess)
    {
      currentexportenergy = (node.getResponseBuffer(0x01) | node.getResponseBuffer(0x00) << 16) / 100.0f;
      currentimportenergy = (node.getResponseBuffer(0x03) | node.getResponseBuffer(0x02) << 16) / 100.0f;     
      voltage = node.getResponseBuffer(0x04) / 10.0f;
      current = node.getResponseBuffer(0x05) / 100.0f;
      activepower = node.getResponseBuffer(0x06);
      reactivepower = node.getResponseBuffer(0x07);
      powerfactor = node.getResponseBuffer(0x08) / 1000.0f;
      frequency = node.getResponseBuffer(0x09) / 100.f;
      Serial1.print("Current Export Energy: ");
      Serial1.println(currentexportenergy);
      Serial1.print("Current Import Energy: ");
      Serial1.println(currentimportenergy);
      Serial1.print("Voltage: ");
      Serial1.println(voltage);
      Serial1.print("Current: ");
      Serial1.println(current);
      Serial1.print("Active Power: ");
      Serial1.println(activepower);
      Serial1.print("Rective Power: ");
      Serial1.println(reactivepower);
      Serial1.print("Powerfactor: ");
      Serial1.println(powerfactor);
      Serial1.print("Frequency: ");
      Serial1.println(frequency);
      } else {
      Serial1.println("Reading HIKING DDS238 failed!");
      }

// read SlaveID and Baudrate-Code
    result = node.readHoldingRegisters(0x0015, 1);
    if (result == node.ku8MBSuccess) {
      devSlaveID = highByte(node.getResponseBuffer(0x00));
      devBaudrate = lowByte(node.getResponseBuffer(0x00));
      Serial1.print("SlaveID: ");
      Serial1.print(devSlaveID);
      Serial1.print(", Baudrate: ");
      Serial1.println(devBaudrate); 
      } else {
      Serial1.println("Reading HIKING DDS238 failed!");
      }
}
