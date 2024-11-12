#define R6 11 
#define R2 A1 
#define R8 4 
#define R3 5 
#define R7 7 
#define R5 3 
#define R4 8 
#define R1 9 
#define C8 10
#define C5 2
#define C3 A3
#define C7 13
#define C2 A0
#define C4 12
#define C6 A2
#define C1 6
int curstate;
int changetime;
int cadr;
void setup() {
  // put your setup code here, to run once:
  pinMode(R1,OUTPUT);
  pinMode(R2,OUTPUT);
  pinMode(R3,OUTPUT);
  pinMode(R4,OUTPUT);
  pinMode(R5,OUTPUT);
  pinMode(R6,OUTPUT);
  pinMode(R7,OUTPUT);
  pinMode(R8,OUTPUT);
  pinMode(C1,OUTPUT);
  pinMode(C2,OUTPUT);
  pinMode(C3,OUTPUT);
  pinMode(C4,OUTPUT);
  pinMode(C5,OUTPUT);
  pinMode(C6,OUTPUT);
  pinMode(C7,OUTPUT);
  pinMode(C8,OUTPUT);
  curstate=1;
  changetime=millis();
  cadr=millis();
}
int pins[8]={R1,R2,R3,R4,R5,R6,R7,R8};
byte states[8]= {
  0b00000000,
  0b00111000,
  0b01111100,
  0b11111110,
  0b11111110,
  0b01111100,
  0b00111000,
  0b00000000
};
void PWMstates(byte* bstates){
  if (millis()-changetime>1){
    digitalWrite(pins[curstate-1], bstates[curstate-1]>0);
    for (int i = 0; i <= 7; i++) { 
        if (i!=curstate-1){
          digitalWrite(pins[i], LOW);
        }
    } 
    digitalWrite(C1, abs(1-bitRead(bstates[curstate-1],7)));
    digitalWrite(C2, abs(1-bitRead(bstates[curstate-1],6)));
    digitalWrite(C3, abs(1-bitRead(bstates[curstate-1],5)));
    digitalWrite(C4, abs(1-bitRead(bstates[curstate-1],4)));
    digitalWrite(C5, abs(1-bitRead(bstates[curstate-1],3)));
    digitalWrite(C6, abs(1-bitRead(bstates[curstate-1],2)));
    digitalWrite(C7, abs(1-bitRead(bstates[curstate-1],1)));
    digitalWrite(C8, abs(1-bitRead(bstates[curstate-1],0)));
    changetime=millis();
    if (curstate==8){
      curstate=0;
    }
    curstate+=1;
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  PWMstates(states);
  if (millis()-cadr>100){
    for (int i = 0; i <= 7; i++) { 
      if (states[i]>=128){
        states[i]=((states[i]-128)*2)+1;
      }else{
        states[i]=states[i]*2;
      }
    }
    cadr=millis();
  }
}
