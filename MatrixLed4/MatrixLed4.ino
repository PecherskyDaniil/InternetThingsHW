#define D1 3
#define D2 5
#define D3 6
#define D4 9


long changetime=millis();
int curstate=1;
void manageLed(int LED, int state){
  if (state==0){
    digitalWrite(LED,LOW);
  }else{
    digitalWrite(LED,HIGH);
  }
}
void PWMstates(byte bstates){
  if (millis()-changetime>5 && curstate==1){
    digitalWrite(D1, bitRead(bstates,7));
    digitalWrite(D2, bitRead(bstates,6));
    digitalWrite(D3, bitRead(bstates,5));
    digitalWrite(D4, bitRead(bstates,4));
    changetime=millis();
    curstate=2;
  }
  if (millis()-changetime>5 && curstate==2){
    digitalWrite(D1, bitRead(bstates,3));
    digitalWrite(D2, bitRead(bstates,2));
    digitalWrite(D3, bitRead(bstates,1));
    digitalWrite(D4, bitRead(bstates,0));
    changetime=millis();
    curstate=1;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);

}
byte states[12]= {
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111
};
int statenum=0;
long statetime=millis();
void loop() {
  //if (millis()-statetime>2000){
  //  statetime=millis();
  //  statenum++;
  //}
  //if (statenum>11){
  //  statenum=0;
  //}
  PWMstates(states);
  
}
