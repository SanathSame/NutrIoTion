#define gas_sensor1Pin A1
#define gas_sensor2Pin A2

int trigger_pin = 2;
int echo_pin = 3;
 
int gas_sensor1_Value;
int gas_sensor2_Value;
int time;
int distance; 
String values;

 void setup() { 
  
 pinMode (trigger_pin, OUTPUT); 
 
 pinMode (echo_pin, INPUT);
 
 //Initializes the serial connection at 9600 to sent sensor data to ESP8266.
 Serial.begin(9600); 
 
delay(2000);  
  
 }

 
void loop() {

  // get sensors data and put in to values variables as a string.
   values= (get_gas_sensor1_Value()+','+get_gas_sensor2_Value());
       delay(1000);
       // removed any buffered previous serial data.
       Serial.flush();
       delay(1000);
       // sent sensors data to serial (sent sensors data to ESP8266)
       Serial.print(values);
       delay(2000);
 

}


// get Gas sensor 1 data
String get_gas_sensor1_Value(){ 
   
gas_sensor1_Value =analogRead(get_sensor1Pin);
    delay(1000);
    return String(gas_sensor1_Value);  
    
}

// get IR sensor 2 data
String get_gas_sensor2_Value(){ 
   
gas_sensor2_Value =analogRead(gas_sensor2Pin);
delay(1000);
    return String(gas_sensor2_Value);  
}
 
  
