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
  MotorControl(0,10);
}