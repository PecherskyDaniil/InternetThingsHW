#define LED_GREEN 2
#define LED_BLUE 4
#define LED_RED 7
#define SET_LED_GREEN 'g'
#define SET_LED_RED 'r'
#define SET_MANUAL_CONTROL 'm'
void setup() {
  Serial.begin(9600);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);

}
int auto_mode = 1;
int current_state=0;
long start=millis();
long previous_switch=millis();
long manual_timer=millis();
int intervalR=7000;
int intervalB=1000;
int intervalG=10000;
long intervalManual = 60000;

void blink(int LED_PIN, long timemillis){
  int led_state=HIGH;
  long blinkstart=millis();
  long prevmillis=millis();
  long curmillis=millis();
  while (curmillis-blinkstart<timemillis){
    curmillis=millis();
    if (curmillis-prevmillis>=300){
      prevmillis=curmillis;
      if (led_state==LOW){
        led_state=HIGH;
      }else{
        led_state=LOW;
      }
    }
    digitalWrite(LED_PIN, led_state);
  }

  previous_switch=millis();
  current_state=2;
}
int command=0;
void loop() {
  long curtime=millis();
  if (curtime-manual_timer>=intervalManual && auto_mode==0){
    auto_mode=1;
    previous_switch=millis();
  }
  if (Serial.available() > 0) {  //если есть доступные данные
    command = Serial.read();
    if (command==SET_MANUAL_CONTROL){
      auto_mode=0;
      manual_timer=millis();
    }
  }
  if (current_state==1){
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_BLUE, LOW);
  }if (current_state==0){
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, LOW);
  }
  if (current_state>1){
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_BLUE, HIGH);
  }
  if (auto_mode==1){
    if (current_state==0 && curtime-previous_switch>=intervalR){
      previous_switch=curtime;
      current_state=3;
    }
    if (current_state>1 && curtime-previous_switch>=intervalB){
      previous_switch=curtime;
      current_state=current_state-2;
    }
    if (current_state==1 && curtime-previous_switch>=intervalG){
      digitalWrite(LED_GREEN, LOW);
      current_state=-1;
      blink(LED_GREEN, 2000);
    }
  }else{
    if (current_state!=1 && command==SET_LED_GREEN){
      previous_switch=curtime;
      current_state=3;
    }
    if (current_state>1 && curtime-previous_switch>=intervalB){
      previous_switch=curtime;
      current_state=current_state-2;
    }
    if (current_state==1 && command==SET_LED_RED){
      digitalWrite(LED_GREEN, LOW);
      current_state=-1;
      blink(LED_GREEN, 2000);
    }
  }
}

