int const plantCount = 2; //tell me how many plants you have
int thresholds[] = {500,300}; //threshold of water per plant 
// dry is: 0,540 // 1,383


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
