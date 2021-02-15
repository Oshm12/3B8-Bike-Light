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
double main_start_t = 0;
double hazard_start_t = 0;

void setup() {
  
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
if(millis() > 10000){
  indicator_left = true;
  indicator_right = true;
}

//turn off
if(millis() > 20000){
  indicator_left = false;
  indicator_right = false;
}


  //************Light Control Code***************

  if(!hazard_light){
  //Standard not braking flashing main light
     if(!brake_light){
      
          if(millis() < main_start_t + 400){
            digitalWrite(main_light_pin, HIGH);
          }
          else {
            digitalWrite(main_light_pin, LOW);
          }
    
          if(millis() > main_start_t + 800){
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
  int t = hazard_start_t/ 500;
      if(-1^hazards_start_t > 0){
        digitalWrite(indicator_pin_right, HIGH);
        digitalWrite(indicator_pin_left, HIGH);
        digitalWrite(main_light_pin, HIGH)
      }
      
      if(-1^hazards_start_t < 0){
        digitalWrite(indicator_pin_right, LOW);
        digitalWrite(indicator_pin_left, LOW);
        digitalWrite(main_light_pin, LOW)
      }

      if(hazard_start_t > millis() + 60000){
        hazard_light = false;
      }
  }
}

void serialEvent(){

  //Function that runs after each loop when the arduino has recieved some serial message
  //Will only run if it has recieved serial packets
  //This will be an instruction from the button box
  //A character with a command will be sent, for hazards, and indicators
  char command;
  
  //readString actually reads in Chars weirdly
  command = Serial.readString();

  //using placeholder chars here which may or may not change

  if(command == 'l'){

    indicator_left = true;
    return;
    
  }

  if(command == 'r'){

    indicator_right = true;
    return;
    
  }

  if(command == 'h'){

    hazard_light = true;
    return;
    hazard_start_t = millis();

  }
}
