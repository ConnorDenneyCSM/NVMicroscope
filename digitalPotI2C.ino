/*
 * i2C digital pot test script
 * Connor Denney on 10/30/2022
 * 
 * Hardware setup:
 * Setup the Analog Technologies AD5272 1024 position potentiometer as shown in the data sheet with SDA/SCL conneted to the arduino.
 * The address bits are setup to reflect the ADDR line being connected to ground.
 * 
 * UPDATED 11/9/22 to include testing for hall effect sensor AD1318LUA
 * Connect sensor to 
 * 
 * The write commands are formated as follows:
 * BYTE 1: 0  0  C3 C2 C1 C0 D9 D8
 * BYTE 2: D7 D6 D5 D4 D3 D2 D1 D0
 * 
 * For the Colorado School of Mines Quantum Engineering Research Group
 * 
 */

#define ADDR 0b00101111


#include <Wire.h>

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
  delay(50); //allow time for setup.
  
  Wire.beginTransmission(ADDR); // transmit to device
  Wire.write(0b00011100);
  Wire.write(0b00000010);    // Sets the control register to allow writing of the wiper position.
  Wire.endTransmission();    // stop transmitting

  pinMode(A0, INPUT);
  analogReference(EXTERNAL);
}

float input;
uint16_t wiperPos = 0;

uint8_t MSB;
uint8_t LSB;

void loop() {
  if (Serial.available()){
    input = Serial.parseFloat();

    wiperPos = int( input * 1023 / 20 ); //scale the value given in ohms to readable counts.
    MSB = highByte(wiperPos); //Split the incoming byte into two 8 bit values for transmission
    LSB = lowByte(wiperPos);
    MSB |= 0b00000100; // Only the least 2 siginifcant bits are part of the data, so we must set the command word to 0001 to write the wiper position.
  
  
    Serial.print("Writing the following value to the POT:\r\n");
    Serial.println(wiperPos);
    
    Wire.beginTransmission(ADDR);
    Wire.write(MSB);
    Wire.write(LSB);
    Wire.endTransmission(ADDR);
  }

  Serial.print("B-FIELD INTESNSITY: ");
  Serial.println(analogRead(A0));

  delay(200);
  
  
}
