/*
 * i2C digital pot test script
 * Connor Denney on 10/30/2022
 * 
 * Hardware setup:
 * Setup the Analog Technologies AD5272 1024 position potentiometer as shown in the data sheet with SDA/SCL conneted to the arduino.
 * 
 * The write commands are formated as follows:
 * BYTE 1: 0  0  C3 C2 C1 C0 D9 D8
 * BYTE 2: D7 D6 D5 D4 D3 D2 D1 D0
 * 
 * For the Colorado School of Mines Quantum Engineering Research Group
 * 
 */
 
#define XADDR 0b00101100
#define YADDR 0b00101111
#define ZADDR 0b00101110


#include <Wire.h>

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
  delay(50); //allow time for setup.
  
  Wire.beginTransmission(XADDR); // transmit to device
  Wire.write(0b00011100);
  Wire.write(0b00000010);    // Sets the control register to allow writing of the wiper position.
  Wire.endTransmission();    // stop transmitting

  Wire.beginTransmission(YADDR); // transmit to device
  Wire.write(0b00011100);
  Wire.write(0b00000010);    // Sets the control register to allow writing of the wiper position.
  Wire.endTransmission();    // stop transmitting

  Wire.beginTransmission(ZADDR); // transmit to device
  Wire.write(0b00011100);
  Wire.write(0b00000010);    // Sets the control register to allow writing of the wiper position.
  Wire.endTransmission();    // stop transmitting

}

float input;

void loop() {
  if (Serial.available()){
    
    switch (Serial.read()) {
      case 'H':
      
        char axis = Serial.read();
        input = Serial.parseFloat();

        uint16_t writePos = int( input * 1023 / 200 ); //scale the value given in k-ohms to readable counts.
        writeHH(axis, writePos);
        Serial.print("A");
        Serial.print(axis);
        Serial.println(input);
      break;
    }  
  }
  delay(200);
}

void writeHH(char axis, uint16_t wiperPos) {
  uint8_t MSB;
  uint8_t LSB;
  uint8_t ADDR;

  switch(axis) {
    case 'X':
      ADDR = XADDR;
    break;
    case 'Y':
      ADDR = YADDR;
    break;
    case 'Z':
      ADDR = ZADDR;
    break;
    
  }
  
  MSB = highByte(wiperPos); //Split the incoming byte into two 8 bit values for transmission
  LSB = lowByte(wiperPos);
  MSB |= 0b00000100; // Only the least 2 siginifcant bits are part of the data, so we must set the command word to 0001 to write the wiper position.
  
  Wire.beginTransmission(ADDR);
  Wire.write(MSB);
  Wire.write(LSB);
  Wire.endTransmission(ADDR);
}
