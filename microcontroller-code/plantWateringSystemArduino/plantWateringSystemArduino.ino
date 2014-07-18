#include <EEPROM.h>

int const plantCount = 2; //tell me how many plants you have
int thresholds[] = {500,300}; //threshold of water per plant 
// dry is: 0,540 // 1,383
int addr = 0; //eeprom address
int minutes_to_eeprom = 10; //every N minutes, write to eeprom
int counter = 0; 
byte value;
int eeprom_read_wait = 50;

void setup() {
   Serial.begin(9600);  
   //when boot reads the whole EEPROM to serial (hopefully a computer is listening)
  while (addr < 512){
    value = EEPROM.read(addr);   // read a byte from the current address of the EEPROM
    Serial.print(addr);
    Serial.print("\t");
    Serial.print(value, DEC);
    Serial.println();
    addr = addr++;     // advance to the next address of the EEPROM
    delay(eeprom_read_wait);
  }    
  addr = 0;
}

void loop() {
  for (int i=0; i<=(plantCount-1);i++) {
     int sensorValue = analogRead(i);
     if (sensorValue > thresholds[i])
     {
        activateWater(i);
     } 
     //write to serial (if computer listens, great)
     Serial.print(i);
     Serial.print(",");  
     Serial.println(sensorValue);  

     counter++;      
     //write to eeprom //only happens every n minutes (a minute is 600 times 100 milliseconds), so n x 600
     if (minutes_to_eeprom * 600 == counter){
       int val = sensorValue / 4;
       EEPROM.write(addr, val);
       addr = addr + 1;
       if (addr == 512)
        addr = 0;
     }
     else counter = 0;
   }  
  delay(100);            
}


void activateWater(int i){
  //do something later
}
