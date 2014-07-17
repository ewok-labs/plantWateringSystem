int const plantCount = 2; //tell me how many plants you have
int thresholds[] = {700,800}; //threshold of water per plant 

void setup() {
   Serial.begin(9600);  
}

void loop() {
  for (int i=0; i<=(plantCount-1);i++) {
     int sensorValue = analogRead(i);
     if (sensorValue > thresholds[i])
     {
        activateWater(i);
     } 
     Serial.print(i);
     Serial.print(",");  
     Serial.println(sensorValue);  
   }  
  delay(100);            
}


void activateWater(int i){
  //do something later
}
