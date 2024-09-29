#define PHOTO_SENSOR_DOWN A0
#define PHOTO_SENSOR_RIGHT A4
#define PHOTO_SENSOR_UP A2
#define PHOTO_SENSOR_LEFT A3
//#define LED_DOWN 7
//#define LED_UP 2
#define LED_RIGHT 4
#define LED_LEFT 8
#define BLINK_INTERVAL 600
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
int state=0;
void update_states(){
  if (state==1){
    if (millis()%BLINK_INTERVAL>300){
      digitalWrite(LED_RIGHT,HIGH);
    }else{
      digitalWrite(LED_RIGHT,LOW);
    }
    digitalWrite(LED_LEFT,HIGH);
  }else if (state==2){
    if (millis()%BLINK_INTERVAL>300){
      digitalWrite(LED_LEFT,HIGH);
    }else{
      digitalWrite(LED_LEFT,LOW);
    }
    digitalWrite(LED_RIGHT,HIGH);
  }else{
    digitalWrite(LED_RIGHT,HIGH);
    digitalWrite(LED_LEFT,HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //int down_val=analogRead(PHOTO_SENSOR_DOWN);
  //int up_val=analogRead(PHOTO_SENSOR_UP);

  int right_val=analogRead(PHOTO_SENSOR_RIGHT);
  int left_val=analogRead(PHOTO_SENSOR_LEFT);
  //int max_val=max(max(down_val,up_val),max(right_val,left_val));
  int diff_val=abs(right_val-left_val);
  //if (down_val==max_val){
  //  digitalWrite(LED_DOWN,HIGH);
  //  digitalWrite(LED_UP,LOW);
  //  digitalWrite(LED_RIGHT,LOW);
  //  digitalWrite(LED_LEFT,LOW);
  //}else if (up_val==max_val){
  //  digitalWrite(LED_DOWN,LOW);
  //  digitalWrite(LED_UP,HIGH);
  //  digitalWrite(LED_RIGHT,LOW);
  //  digitalWrite(LED_LEFT,LOW);
  //}else
  if (diff_val>100){
    if (right_val>left_val){
      //digitalWrite(LED_DOWN,LOW);
      //digitalWrite(LED_UP,LOW);
      state=1;
    }else{
      //digitalWrite(LED_DOWN,LOW);
      //digitalWrite(LED_UP,LOW);
      state=2;
    }
  }else{
    state=0;
  }
  update_states();
  //Serial.print("down: ");
  //Serial.println(down_val);
  //Serial.print("up: ");
  //Serial.println(up_val);
  //Serial.print("right: ");
  //Serial.println(right_val);
  //Serial.print("left: ");
  //Serial.println(left_val);
  //delay(300);
}


