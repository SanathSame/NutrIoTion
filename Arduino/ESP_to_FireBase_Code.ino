
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_AUTH "KiGeHghZn3i6K2y7EeaJcjgInV8dWcg6d557jCod" 
#define FIREBASE_HOST "nutriotion-30c8c-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define WIFI_SSID " ashutosh"
#define WIFI_PASSWORD "12345678"

String values,sensor_data;

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
        sensor_data=Serial.readString(); 
        Sr=true;    
        
    }
  
delay(1000);

  if(Sr==true){  
    
  values=sensor_data;
  
  //get comma indexes from values variable
  int fristCommaIndex = values.indexOf(',');
  int secondCommaIndex = values.indexOf(',', fristCommaIndex+1);
  
  //get sensors data from values variable by  spliting by commas and put in to variables  
  String gas_sensor_1_value = values.substring(0, fristCommaIndex);
  String gas_sensor_2_value = values.substring(fristCommaIndex+1, secondCommaIndex);

  //store gas_sensor_1 sensor data as string in firebase 
  Firebase.setString("gas_sensor_1_value",gas_sensor_1_value);
   delay(10);
  //store IR sensor 1 data as string in firebase 
  Firebase.setString("gas_sensor_2_value",gas_sensor_2_value);
   delay(10);

  //store previous sensors data as string in firebase
  
  Firebase.pushString("previous_gas_sensor_1_value",gas_sensor_1_value);
   delay(10);
  Firebase.pushString("previous_gas_sensor_2_value",gas_sensor_2_value);

  
  delay(1000);
  
  if (Firebase.failed()) {  
      return;
  }
  
}   
}
