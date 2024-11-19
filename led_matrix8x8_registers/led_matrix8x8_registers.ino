#define R6 7 
#define R2 3 
#define R8 9 
#define R3 4 
#define R7 8 
#define R5 6 
#define R4 5 
#define R1 2 
#define C8 A3
#define C5 A0
#define C3 12
#define C7 A2
#define C2 11
#define C4 13
#define C6 A1
#define C1 10

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
  0b00011000,
  0b00111100,
  0b01111110,
  0b11111111,
  0b11111111,
  0b01111110,
  0b00111100,
  0b00011000
};
void PWMstates(byte* bstates){
  if (millis()-changetime>1){
    int dstate=(pow(2,1+curstate)+1)*(curstate<7)*(bstates[curstate-1]>0);
    int bstate=(pow(2,curstate-7))*(curstate>6)*(bstates[curstate-1]>0);
    int addb=B00111100-(bstates[curstate-1] & B00001111)*4;
    bstate+=addb;
    int cstate=15-(bstates[curstate-1] & B11110000)/16;
    PORTD=PORTD & B00000001;
    PORTB=PORTB & B00000000;
    PORTC=PORTC & B00000000;
    PORTD=PORTD | dstate;
    PORTB=PORTB | bstate;
    PORTC=PORTC | cstate;
    
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
  
}
