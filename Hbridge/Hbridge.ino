#define LEFT 5
#define RIGHT 6
void setup()
{
  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT, OUTPUT);
}
void MotorControl(bool dir,int speed){
  if (dir){
    analogWrite(LEFT,0);
  	analogWrite(RIGHT,speed);
  }else{
    analogWrite(LEFT,speed);
  	analogWrite(RIGHT,0);
  }
}
void loop()
{
  MotorControl(0,50);
  delay(2000);
  MotorControl(1,100);
  delay(2000);
  MotorControl(0,255);
  delay(2000);
  MotorControl(1,50);
  delay(2000);
}