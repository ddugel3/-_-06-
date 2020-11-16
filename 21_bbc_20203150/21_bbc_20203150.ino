#include <SharpIR.h>
#include <Servo.h>

#define PIN_IR A0
#define PIN_SERVO 10
#define PIN_LED 9

#define _DUTY_NEU 1490 // servo neutral position (90 degree)

Servo myservo;

int a, b; // unit: mm

void setup() {
  pinMode(PIN_LED,OUTPUT);
  digitalWrite(PIN_LED, 1);
  Serial.begin(57600);
  a = 95;
  b = 370;
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);
  delay(1000);
}
float ir_distance(void){ // return value unit: mm
  float val;
  float volt = float(analogRead(PIN_IR));
  val = ((6762.0/(volt-9.0))-4.0) * 10.0;
  return val;
}
void loop() {
  float raw_dist = ir_distance();
  float dist_cali = 100 + 300.0 / (b - a) * (raw_dist - a);
  Serial.print("min:0,max:500,dist:");
  Serial.print(raw_dist);
  Serial.print(",dist_cali:");
  Serial.println(dist_cali);
  //myservo.writeMicroseconds(_DUTY_NEU);
  if(dist_cali > 185){ 
    digitalWrite(PIN_LED, 0);
    myservo.writeMicroseconds(_DUTY_NEU-50);
  }
  else{
    digitalWrite(PIN_LED, 255);
    myservo.writeMicroseconds(_DUTY_NEU+50);
  }
  
  delay(20);
}
