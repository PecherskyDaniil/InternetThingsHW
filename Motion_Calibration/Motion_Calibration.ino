#include <SoftwareSerial.h>

SoftwareSerial BTSerial(8,13);
#define WHEEL1 7
#define SPEED1 6
#define WHEEL2 4
#define SPEED2 5
void setup() {
  for (int i=4;i<8; i++){
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600);
  BTSerial.begin(9600);
  BTSerial.println("Hello computer!");
}

int wheels[][2] = {
  {1,1},
  {0,1},
  {1,0},
  {0,0},
  };

void move(int dir_left,int dir_right){
  digitalWrite(WHEEL1,dir_left);
  analogWrite(SPEED1,200);
  digitalWrite(WHEEL2,dir_right);
  analogWrite(SPEED2,200);
}
void stop(){
  digitalWrite(WHEEL1,0);
  analogWrite(SPEED1,0);
  digitalWrite(WHEEL2,0);
  analogWrite(SPEED2,0);
}
int speed=200;
int state=0;
int save_parameters=false;
int ind = 0;
void loop() {
  if (BTSerial.available()){
    int sig = BTSerial.read();
    if (sig==48){//Стоп
      state=0;
    }
    if (sig==70){//Вперед
      state=1;
    }
    if (sig==82){//Направо
      state=2;
    }
    if (sig==76){//Налево
      state=3;
    }
    if (sig==66){//Назад
      state=4;
    }
    if (sig == 83 && !save_parameters){//Изменить параметры колёс
      ind+=1;
      if (ind>3){
        ind=0;
      }
    }
    if (sig == 84){//Сохранить параметры и остановить калибровку
      save_parameters=true;
    }
    if (sig == 88){//Начать калибровку снова
      save_parameters=false;
    }
    Serial.println(sig);
  }
  switch(state){
    case 0:
      stop();
      break;
    case 1:
      move(wheels[ind][0], wheels[ind][1]);
      break;
    case 2:
      move(wheels[ind][0], !wheels[ind][1]);
      break;
    case 3:
      move(!wheels[ind][0], wheels[ind][1]);
      break;
    case 4:
      move(!wheels[ind][0], !wheels[ind][1]);
      break;
  }
}

