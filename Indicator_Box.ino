int right_button_pin = 9;
int hazard_button_pin = 10;
int button_interupt_pin = 2;

//Led outputs
int left_LED = 4;
int right_LED = 2; 
int hazard_LED = 3;

//Time set ups
double left_start_t = 0;
double right_start_t = 0;
double hazard_start_t = 0;

//Booleans for Tracking on/off
bool left_indicator = false;
bool right_indicator = false;
bool hazards = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9800);
  //PINMODE OUTPUTS
  
  pinMode(left_LED, OUTPUT);
  pinMode(right_LED, OUTPUT);
  pinMode(hazard_LED, OUTPUT);

  //PINMODE INPUTS

  pinMode(left_button_pin, INPUT);
  pinMode(right_button_pin, INPUT);
  pinMode(hazard_button_pin, INPUT);

  //Set LEDs LOW
  digitalWrite(left_LED, LOW);
  digitalWrite(right_LED, LOW);
  digitalWrite(hazard_LED, LOW);
  
  Serial.println("START");
  
  //Set up the interupt which runs when the common button pin goes from LOW to HIGH eg. when one of them has been pressed. 
  //attachInterrupt(digitalPinToInterrupt(button_interupt_pin), button_interupt, RISING);


}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("Loop");


  //***BUTTON PIN CHECKS***
  //Start
  if(digitalRead(left_button_pin)){
      //LEFT BUTTON pressed
      if(!left_indicator){
        //Turning on the light
        Serial.println('l');
        digitalWrite(left_LED, HIGH);
        left_start_t = millis();
        left_indicator = true;
        
        return;
      }

      if(left_indicator && (millis() - left_start_t) > 750 ){
        //turning off the light
        Serial.println('L');
        digitalWrite(left_LED, LOW);
        left_indicator = false;
        //delay to stop rapid flicking between on off
        delay(400);

        return;
        
       }
  }
  
  if(digitalRead(right_button_pin)){
      //RIGHT BUTTON pressed
      if(!right_indicator){
        //Turning on the light
        Serial.println('r');
        digitalWrite(right_LED, HIGH);
        right_start_t = millis();
        right_indicator = true;
  
        return;
      }

      if(right_indicator && (millis() - right_start_t) > 750 ){
         //Turning off the light
         Serial.println('R');
         digitalWrite(right_LED, LOW);
         right_indicator = false;
         //delay to stop rapid flicking between on off
         delay(400);

         return;
        
      }
  }
  
  if(digitalRead(hazard_button_pin)){
      //HAZARD BUTTON pressed

      if(!hazards){
        //turning Hazards on
        Serial.println('h');
        digitalWrite(hazard_LED, HIGH);
        hazard_start_t = millis();
        hazards = true;
  
        return;
      }
      
      if(hazards && (millis() - hazard_start_t) > 750 ){
         //Turning off the light
         Serial.println('H');
         digitalWrite(hazard_LED, LOW);
         hazards = false;
         //delay to stop rapid flicking between on off
         delay(400);

         return;
        
      }
      
  }

  //end

  //Code for turning LEDS off after a certain length of time

  if(millis() - (left_start_t + 10000) > 0){

    digitalWrite(left_LED, LOW);
  //  Serial.println("LEFT LED OFF");
    
  }

  if(millis() - (right_start_t + 10000) > 0){

    digitalWrite(right_LED, LOW);
  //  Serial.println("right LED OFF");
    
  }
  
  if(millis() - (hazard_start_t + 60000) > 0){

    digitalWrite(hazard_LED, LOW);
   // Serial.println("HAZARD LED OFF");
    
  }
}

