#define LED_RED 2
#define LED_GREEN 4
#define LED_BLUE 7
#define SET_LED_RED 'r'
#define SET_LED_BLUE 'b'
#define SET_LED_GREEN 'g'
#define SET_LED_CHANGE 'c'
#define SET_LED_OFF 'o'
#define STATE_LED_RED 1
#define STATE_LED_BLUE 2
#define STATE_LED_GREEN 3
#define STATE_LED_OFF 0
#define STATE_LED_CHANGE 4
#define FLASH_INTERVAL 1800
#define BLINK_INTERVAL 300
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}
int state=2;
long change_start=0;
int led_state=2;
bool changed=0;
void loop() {
  // put your main code here, to run repeatedly:
  update_state();
  set_state();
  flash_led();
}
void update_state(){
   if(Serial.available()>0){
    char cmd = Serial.read();
    if (cmd == SET_LED_RED){
      state=STATE_LED_RED;
    }else if (cmd == SET_LED_BLUE){
      state=STATE_LED_BLUE;
    }else if (cmd == SET_LED_GREEN){
      state=STATE_LED_GREEN;
    }else if (cmd == SET_LED_OFF){
      state=STATE_LED_OFF;
    }else if (cmd == SET_LED_CHANGE){
      state=STATE_LED_CHANGE;
      change_start=millis();
    }
  }
}
void blink_state(){
  if ((millis()-change_start)%FLASH_INTERVAL>FLASH_INTERVAL-FLASH_INTERVAL/3){
    if ((millis()-change_start)%BLINK_INTERVAL>BLINK_INTERVAL/2){
      if (led_state == STATE_LED_RED){
        digitalWrite(LED_RED,HIGH);
      }else if (led_state == STATE_LED_BLUE){
        digitalWrite(LED_BLUE,HIGH);
      }else if (led_state == STATE_LED_GREEN){
        digitalWrite(LED_GREEN,HIGH);
      }
    }else{
      if (led_state == STATE_LED_RED){
        digitalWrite(LED_RED,LOW);
      }else if (led_state == STATE_LED_BLUE){
        digitalWrite(LED_BLUE,HIGH);
      }else if (led_state == STATE_LED_GREEN){
        digitalWrite(LED_GREEN,LOW);
      }
    }
  }else{
    if (led_state == STATE_LED_RED){
        digitalWrite(LED_RED,HIGH);
      }else if (led_state == STATE_LED_BLUE){
        digitalWrite(LED_BLUE,HIGH);
      }else if (led_state == STATE_LED_GREEN){
        digitalWrite(LED_GREEN,HIGH);
      }
  }
}
void flash_led(){
  if (led_state == STATE_LED_RED){
    if (changed){
      blink_state();
    }else{
      digitalWrite(LED_RED,HIGH);
    }
    digitalWrite(LED_BLUE,LOW);
    digitalWrite(LED_GREEN,LOW);
  }else if (led_state == STATE_LED_BLUE){
    digitalWrite(LED_RED,LOW);
    if (changed){
      blink_state();
    }else{
      digitalWrite(LED_BLUE,HIGH);
    }
    digitalWrite(LED_GREEN,LOW);
  }else if (led_state == STATE_LED_GREEN){
    digitalWrite(LED_RED,LOW);
    digitalWrite(LED_BLUE,LOW);
    if (changed){
      blink_state();
    }else{
      digitalWrite(LED_GREEN,HIGH);
    }
  }else if (led_state == STATE_LED_OFF){
      digitalWrite(LED_RED,LOW);
      digitalWrite(LED_BLUE,LOW);
      digitalWrite(LED_GREEN,LOW);
  }
}
void set_state(){
  if (state == STATE_LED_RED){
    if (led_state>1 and led_state!=0){
      led_state-=1;
      delay(100);
    }else{
      led_state=1;
    }
      changed=0;
    }else if (state == STATE_LED_BLUE){
      led_state=2;
      changed=0;
    }else if (state == STATE_LED_GREEN){
      if (led_state<3 and led_state!=0){
      led_state+=1;
      delay(100);
    }else{
      led_state=3;
    }
      changed=0;
    }else if (state == STATE_LED_OFF){
      led_state=0;
      changed=0;
    }else if (state == STATE_LED_CHANGE){
      changed=1;
      if (millis()<= change_start + FLASH_INTERVAL){
        led_state=1;
      }
      if (millis()> change_start + FLASH_INTERVAL and millis()<= change_start + FLASH_INTERVAL*2){
        led_state=2;
      }
      if(millis()> change_start + FLASH_INTERVAL*2 and millis()<=change_start + FLASH_INTERVAL*3){
        led_state=3;
      }
      if(millis()> change_start + FLASH_INTERVAL*3 and millis()<=change_start + FLASH_INTERVAL*4){
        led_state=2;
      }
      if(millis()> change_start + FLASH_INTERVAL*4){
        change_start=millis();
      }
    }
}