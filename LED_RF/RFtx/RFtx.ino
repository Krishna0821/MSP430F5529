#include <SPI.h>
#include <AIR430BoostETSI.h>

// Data to write to radio TX FIFO (60 bytes MAX.)
unsigned char txData[6] = { 'H', 'I', 'G', 'H', '\0', '\0' };
unsigned char txData1[6] = { 'L', 'O', 'W', '\0', '\0', '\0' };

void printTxData()
{
  Serial.print("TX (DATA): ");
  Serial.println((char*)txData); 
}

void printTxData1()
{
  Serial.print("TX (DATA): ");
  Serial.println((char*)txData1); 
}

void setup()
{
  Radio.begin(0x18, CHANNEL_1, POWER_MAX);
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  pinMode(PUSH2, INPUT_PULLUP);
  digitalWrite(RED_LED, LOW);   // set the LED off
}

void loop()
{
  int buttonState = digitalRead(PUSH2);
  if (buttonState == HIGH) {  
    Radio.transmit(0x20, txData1, 6); 
    digitalWrite(RED_LED, LOW);   // set the LED off
    printTxData1();                   
    } 
  else {
    Radio.transmit(0x20, txData, 6);
    digitalWrite(RED_LED, HIGH);   // set the LED on
    printTxData();                   
  }
 // while (Radio.busy());
  delay(500);
}
