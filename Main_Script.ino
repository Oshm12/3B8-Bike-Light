bool indicator_left = false;
bool indicator_right = false;
bool brake_light = false;
int indicator_pin_left = 2;
int main_light_pin = 3;
int indicator_pin_right = 4;
int left_start_t;
int right_start_t;
int main_start_t = 0 ;

void setup() {
  
  //Light Control signal outputs
  pinMode(indicator_pin_left, OUTPUT);
  pinMode(main_light_pin, OUTPUT);
  pinMode(indicator_pin_right, OUTPUT);

  //LED Test light
  pinMode(13, OUTPUT);
}

void loop() {

if(millis() > 10000){
  indicator_left = true;
}

if(millis() > 20000){
  indicator_left = false;
}


  //************Light Control Code***************

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

    //digitalWrite(main_light_pin, HIGH);


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

    
  }



}
