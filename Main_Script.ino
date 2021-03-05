const int xInput = A1;
const int yInput = A5;
const int zInput = A3;
const int buttonPin = 2;

const int led = 13;

int last_xRaw = 0;
int last_time = 0;
int timeInterval = 0;

int x_onTime = 0;
int x_offTime = 0;
bool x_on = false;

int y_onTime = 0;
int y_offTime = 0;
bool y_on = false;

int z_onTime = 0;
int z_offTime = 0;
bool z_on = false;



bool brake_light = false;

void setup() {
  
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {

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
