
#include <SoftwareSerial.h>
byte incoming;
SoftwareSerial BTSerial(3, 4); // RX | TX


//Declaring Variables
//Flags for lights and modes
bool indicator_left = false;
bool indicator_right = false;
bool brake_light = false;
bool hazard_light = false;

//pin declarations
int indicator_pin_left = 3;
int main_light_pin = 5;
int indicator_pin_right = 6;

//light timing variables
double left_start_t;
double right_start_t;
double main_start_t;
double hazard_start_t;
double swap_t;
int brake_pulse = 400;

//accelerometer 
int x_onTime = 0;
int x_offTime = 0;
bool x_on = false;

int y_onTime = 0;
int y_offTime = 0;
bool y_on = false;

int z_onTime = 0;
int z_offTime = 0;
bool z_on = false;



void setup() {
  //BLUETOOTH SERIAL SETUP
  Serial.begin(9600);

  Serial.println("Bluetooth is ready");//Prints sentence to serial port 
  
  pinMode(3, INPUT); //Sets the RX pin as an INPUT, sampling
  
  pinMode(4, OUTPUT); // Sets TX pin an OUTPUT, can provide current
  
  BTSerial.begin(9600); //Setting the baud rate for the HC-05 Module
  
  pinMode(LED_BUILTIN, OUTPUT);// Setting the built-in LED as an OUTPUT

  
  //Light Control signal outputs
  pinMode(indicator_pin_left, OUTPUT);
  pinMode(main_light_pin, OUTPUT);
  pinMode(indicator_pin_right, OUTPUT);

  //LED Test light
  pinMode(13, OUTPUT);
}

void loop() {

//test timing for indicators
//turn on
/*
if(millis() > 10000){
  indicator_left = true;
  indicator_right = true;
}
//turn off
if(millis() > 20000){
  indicator_left = false;
  indicator_right = false;
}
*/
  //randomising brake flashing timing
  if(millis() % 2500 < 50){
    //random length of pulse between 150 and 750 ms
    brake_pulse = random(150,750);
  }


  //************Light Control Code***************

  if(!hazard_light){
  //Standard not braking flashing main light
     if(!brake_light){
      
          if(millis() < main_start_t + brake_pulse){
            digitalWrite(main_light_pin, HIGH);
          }
          else {
            digitalWrite(main_light_pin, LOW);
          }
    
          if(millis() > main_start_t + (brake_pulse*2)){
            main_start_t = millis();
          }
  
        
     }
  
    
    if(brake_light){
      //turn on brake light
  
      digitalWrite(main_light_pin, HIGH);
  
  
    }
  
    
  
    if(indicator_left){
      
      //begin flashing left indicator
      
        if(millis() < left_start_t + 200){
            digitalWrite(indicator_pin_left, HIGH);
          }
        else {
          digitalWrite(indicator_pin_left, LOW);
        }
    
        if(millis() > left_start_t + 400){
          left_start_t = millis();
        }
    }
  
  
  
    if(indicator_right){
      //begin flashing right indicator
  
        if(millis() < right_start_t + 200){
              digitalWrite(indicator_pin_right, HIGH);
            }
        else {
          digitalWrite(indicator_pin_right, LOW);
        }
      
        if(millis() > right_start_t + 400){
          right_start_t = millis();
        }  
    }
  }

  if(hazard_light){
  //special hazard light pattern
  
      if(millis() - swap_t <= 1000){
        digitalWrite(indicator_pin_right, HIGH);
        digitalWrite(indicator_pin_left, HIGH);
        digitalWrite(main_light_pin, HIGH);
      }
      
      if(millis() - swap_t > 1000){
        digitalWrite(indicator_pin_right, LOW);
        digitalWrite(indicator_pin_left, LOW);
        digitalWrite(main_light_pin, LOW);
      }

      if(hazard_start_t > millis() + 60000){
        hazard_light = false;
      }

      if(millis() - swap_t > 1500){
        swap_t = millis();
      }
  }


  if(BTSerial.available() > 0) { 
    // If data is available
    char incoming = BTSerial.read();//Read byte from the master
  
    Serial.println("Incoming =");
    
    Serial.println(incoming);

    //**I THINK THIS SHOULD WORK - NOT TESTED
    //Should ocnvert incoming achii to char so the rest of the code below will work
    //if not, send me a message and ill convert to work with ascii
    char command;
    command = incoming;

    if(command == 'l'){
    //turn indicators on
    indicator_left = true;
    
    //make sure both indicators aren't on
    indicator_right = false;
    return;
    
    }
    
    if(command == 'L'){
      //turn indicators off
      indicator_left = false;
      digitalWrite(indicator_pin_left, LOW);
      return;
       
    }
  
    if(command == 'r'){
      //turn right indicators on
      indicator_right = true;
      
      //make sure both indicators aren't on
      indicator_left = false;
      return;
      
    }
  
    if(command == 'R'){
      //turn indicators off
      indicator_right = false;
      digitalWrite(indicator_pin_right, LOW);
      return;
       
    }
  
    if(command == 'h'){
      //turn hazards on
      hazard_light = true;
      hazard_start_t = millis();
      swap_t = millis();
  
      //make sure both indicators aren't on
      digitalWrite(indicator_pin_left, LOW);
      digitalWrite(indicator_pin_right, LOW);
      
      return;
  
    }
  
    if(command == 'H'){
      //turn hazards off
      hazard_light = false;
      return;
      
    }
  
      
    }
  
  else {

    //no data in Serial Buffer
    Serial.println("No data available");
  }

  //Braking Accelorometer code

  //y = a5, x = a1
  int xRaw = analogRead(xInput);
  int yRaw = analogRead(yInput);
  int zRaw = analogRead(zInput);


  Serial.print("\nX Axis: ");
  Serial.print(xRaw);
  Serial.print("\nY Axis: ");
  Serial.print(yRaw);
  Serial.print("\nZ Axis: ");
  Serial.print(zRaw);



  if(xRaw > 700){
    // deceleration detected
    if(!x_on){
      x_onTime = millis();
      x_on = true;
    }

    if(x_on && (millis() - x_onTime > 200)){

      brake_light = true;
      
    }
    
  }

  if(xRaw < 700){

    if(x_on){
      x_offTime = millis();
    }
    
    if(x_on && (millis() - x_offTime  > 1000)){

       brake_light = false;
       x_on = false;      
    }  
  }

  if(yRaw > 700){
    // deceleration detected
    if(!y_on){
      y_onTime = millis();
      y_on = true;
    }

    if(y_on && (millis() - y_onTime > 200)){

      brake_light = true;
      
    }
    
  }

  if(yRaw < 700){

    if(y_on){
      y_offTime = millis();
    }
    
    if(y_on && (millis() - y_offTime  > 1000)){

       brake_light = false;
       y_on = false;      
    }  
  }

  if(zRaw > 700){
    // deceleration detected
    if(!z_on){
      z_onTime = millis();
      z_on = true;
    }

    if(z_on && (millis() - z_onTime > 200)){

      brake_light = true;
      
    }
    
  }

  if(zRaw < 700){

    if(z_on){
      z_offTime = millis();
    }
    
    if(z_on && (millis() - z_offTime  > 1000)){

       brake_light = false;
       z_on = false;      
    }  
  }
  
}
