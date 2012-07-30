#define ANALOG_IN A5

#define THRESH 100
#define ONTIME   3000
#define ONDELAY  0


// state variables
int ledState;
unsigned long lastOn;
unsigned long toTurnOn;

void setup() {
  // setup
  pinMode(13,OUTPUT);
  
  //RGB led
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT); 
  
  // cathodes
  analogWrite(9,255);  
  analogWrite(10,255); 
  analogWrite(11,255); 

  //Serial.begin(19200);
  
  // initial state
  ledState = LOW;
  lastOn = millis();
  toTurnOn = -1;

  // pin stuff
  digitalWrite(13,ledState);
  digitalWrite(12,ledState);
  analogReference(DEFAULT);    // 5V  
  //analogReference(EXTERNAL);   // 
  //analogReference(INTERNAL);    // 1.1V

}


void loop() {
  // read analog in
  int val = analogRead(ANALOG_IN);

  // if off and saw a value and haven't seen other value yet
  //    then set up a time to turn on
  if((ledState == LOW)&&(val < THRESH)&&(toTurnOn == -1)){
    toTurnOn = millis()+ONDELAY;
  }
  // if off and have seen a high value and it's time to turn on
  else if((ledState == LOW)&&(toTurnOn != -1)&&(millis() > toTurnOn)){
    ledState = HIGH;
    toTurnOn = -1;
    digitalWrite(13,ledState);
    rgb(10,11,9);
    lastOn = millis();    
  }
  // if on for more than ONTIME milliseconds
  else if((ledState == HIGH)&&((millis()-lastOn) > ONTIME)){
    ledState = LOW;
    digitalWrite(13,ledState);
    digitalWrite(11,ledState);
    digitalWrite(10,ledState);
    digitalWrite(9,ledState);
  }

  Serial.write( 0xff);
  Serial.write( (val >> 8) & 0xff);
  Serial.write( val & 0xff);
}



void rgb(int r, int g, int b){
  
  int oldRGB[3] = {
  0,0,0};

 int val = analogRead(A0);
  val = constrain(val,600,900);
  if(abs(val - oldRGB[0]) > 12){
    int mval = map(val,600,900,0,255);
    analogWrite(b,mval); 
    oldRGB[0] = val;
    Serial.print("B ");
    Serial.print(mval);
    Serial.print('\n');
  }
  delay(10);

  val = analogRead(A1);
  val = constrain(val,600,900);
  if(abs(val - oldRGB[1]) > 12){
    int mval = map(val,600,900,0,255);
    analogWrite(r,mval); 
    oldRGB[1] = val;
    Serial.print("R ");
    Serial.print(mval);
    Serial.print('\n');
  }
  delay(10);

  val = analogRead(A2);
  val = constrain(val,600,900);
  if(abs(val - oldRGB[2]) > 12){
    int mval = map(val,600,900,0,255);    
    analogWrite(g,mval); 
    oldRGB[2] = val;
    Serial.print("G ");
    Serial.print(mval);
    Serial.print('\n');
  }
  delay(10);

}
