const int xInput = A0;
const int yInput = A1;
const int zInput = A2;
const int buttonPin = 2;

const int led = 13;

int last_xRaw = 0;
int last_time = 0;
int timeInterval = 0;


void setup() {
  
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {


  int xRaw = analogRead(xInput);
  int yRaw = analogRead(yInput);
  int zRaw = analogRead(zInput);


  Serial.print("\nX Axis: ");
  Serial.print(xRaw);
 /* Serial.print("\nY Axis: ");
  Serial.print(yRaw);
  Serial.print("\nZ Axis: ");
  Serial.print(zRaw);
*/

  timeInterval = millis() - last_time;

  if(abs(xRaw - last_xRaw > 200)){
    if(timeInterval > 250){
      
      digitalWrite(led, HIGH);

      last_time = millis();
      delay(400);
    }
    
  }

  if(abs(xRaw - last_xRaw < 200)){

    digitalWrite(led, LOW);
  
  }
  last_xRaw = xRaw;

  

}
