#include <SPI.h>
#include <AIR430BoostETSI.h>

// Data to read from radio RX FIFO (60 bytes MAX.)
unsigned char rxData;
//const char cmp[6] = { 'H', 'I', 'G', 'H', '\0', '\0' };

void printRxData()
{
  Serial.print("RX (DATA, RSSI, LQI, CRCBIT): ");
  Serial.print("(");
  Serial.print((char*)rxData);
  Serial.print(", ");
  Serial.print(Radio.getRssi());
  Serial.print(", ");
  Serial.print(Radio.getLqi());
  Serial.println(")");
}

void setup()
{
  Radio.begin(0x11, CHANNEL_1, POWER_MAX);
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(RED_LED, LOW);
}

void loop()
{
  while (Radio.busy());

  if (Radio.receiverOn((unsigned char*)rxData, sizeof(rxData), 1000) > 0)
  {
   Serial.print(rxData);
   //Serial.print(rxData[1]);
  }
  digitalWrite(RED_LED, LOW);
 // delay(500);
}
