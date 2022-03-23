#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "insert firebasehost" 
#define FIREBASE_AUTH "insert firebase secret" 
#define WIFI_SSID "insert your wifi's ssid" 
#define WIFI_PASSWORD "insert wifi's password" 

String values,Data;//Humidity,Moisture,Temperature;

void setup() {
  //Initializes the serial connection at 9600 get sensor data from arduino.
   Serial.begin(9600);
   
  delay(1000);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    
  }
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
  
}
void loop() {

 bool Sr =false;
 
  while(Serial.available()){
    
        //get sensor data from serial put in sensor_data
        Data=Serial.readString(); 
        Sr=true;    
        
    }
  
delay(50);

  if(Sr==true){  
    
  values=Data;
  
  //get comma indexes from values variable
  int fristCommaIndex = values.indexOf(',');
  int secondCommaIndex = values.indexOf(',',fristCommaIndex+1);
  int thirdCommaIndex = values.indexOf('.',secondCommaIndex+1);
  
  //get sensors data from values variable by  spliting by commas and put in to variables  
  String temperature = values.substring(0, fristCommaIndex);
  String humidity = values.substring(fristCommaIndex+1, secondCommaIndex);
  String moisture = values.substring(secondCommaIndex+1);
  
   //store sensor data as string in firebase 
  Firebase.setString("Temperature",temperature);
  delay(10);
  Firebase.setString("Humidity",humidity);
   delay(10);
  Firebase.setString("Moisture",moisture);
   delay(10);
   
  delay(10);
  
  //store previous sensors data as string in firebase
  
  Firebase.pushString("previous_temperature",temperature);
   delay(10);
  Firebase.pushString("previus_humidity",humidity);
    delay(10);
  Firebase.pushString("previus_moisture",moisture);
    delay(10);
 delay(1000); 
  if (Firebase.failed()) {  
      return;
  }
  
}   
}
