#include <EEPROM.h>

int const plantCount = 2; //tell me how many plants you have
int thresholds[] = {500,300}; //threshold of water per plant 
// dry is: 0,540 // 1,383
int addr = 0; //eeprom address
int minutes_to_eeprom = 10; //every N minutes, write to eeprom
int counter = 0; 
byte value;
int eeprom_read_wait = 1;

//booleans for debug, settings, etc
boolean EEPROM_READ = false; 
boolean SERIAL_LOG = true;
boolean EEPROM_WRITE = false;
boolean HELP = true;
boolean DEBUG = false; 
boolean DEBUG_LV2 = false; 
boolean DEBUG_LV3 = false; 

void setup() {
   Serial.begin(9600);  
   if (HELP) Serial.println("Started Watering System");
   if (HELP) Serial.println("Flags are:");
   if (HELP) Serial.println("DEBUG: 1 (obviously)");
   if (HELP) Serial.print("DEBUG_LV2: ");
   if (HELP) Serial.println(DEBUG_LV2);
   if (HELP) Serial.print("DEBUG_LV3: ");
   if (HELP) Serial.println(DEBUG_LV3);
   if (HELP) Serial.print("EEPROM_READ: ");
   if (HELP) Serial.println(EEPROM_READ);
   if (HELP) Serial.print("EEPROM_WRITE: ");
   if (HELP) Serial.println(EEPROM_WRITE);
   if (HELP) Serial.print("SERIAL_LOG: ");
   if (HELP) Serial.println(SERIAL_LOG);
   
   //when boot reads the whole EEPROM to serial (hopefully a computer is listening)
   while (addr < 512 && EEPROM_READ ){
    value = EEPROM.read(addr);   // read a byte from the current address of the EEPROM
    if (EEPROM_READ) Serial.print(addr);
    if (EEPROM_READ) Serial.print("\t");
    if (EEPROM_READ) Serial.print(value, DEC);
    if (EEPROM_READ) Serial.println();
    addr = addr++;     // advance to the next address of the EEPROM
    delay(eeprom_read_wait);
 }    
 addr = 0;
 Serial.println("begin");
}

void loop() {
  counter++;
  for (int i=0; i<=(plantCount-1);i++) {
     int sensorValue = analogRead(i);
     if (sensorValue < thresholds[i])
     {
        if (DEBUG_LV2) Serial.print("Threshold of ");
        if (DEBUG_LV2) Serial.print(thresholds[i]);
        if (DEBUG_LV2) Serial.print(" exceeded for plant ");
        if (DEBUG_LV2) Serial.println(i);        
        activateWater(i);
     } 
     //write to serial (if computer listens, great)
     if (SERIAL_LOG) Serial.print(i);
     if (SERIAL_LOG) Serial.print(",");  
     if (SERIAL_LOG) Serial.println(sensorValue);  

    
     if (DEBUG_LV3) Serial.print("counter: ");
     if (DEBUG_LV3) Serial.println(counter);
     if (DEBUG_LV3) Serial.print("minutes_to_eeprom * 600: ");
     if (DEBUG_LV3) Serial.println(minutes_to_eeprom * 600);
     //write to eeprom //only happens every n minutes (a minute is 600 times 100 milliseconds), so n x 600
     if (minutes_to_eeprom * 600 == counter && EEPROM_WRITE){
       int val = sensorValue / 4;
       if (DEBUG) Serial.print("Writing ");
       if (DEBUG) Serial.print(val);
       if (DEBUG) Serial.println(" to EEPROM");
       EEPROM.write(addr, val);
       addr = addr + 1;
       if (addr == 512) addr = 0;
       if (i==plantCount-1) counter = 0;
     }
   }  
  delay(100);            
}


void activateWater(int i){
  if (DEBUG_LV2) Serial.print("Activating water for plant: ");        
  if (DEBUG_LV2) Serial.println(i);        
}
