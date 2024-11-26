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
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 1; // Value to compare with
  TCCR1B |= (1 << WGM12);
  // for 256 prescaler
  TCCR1B = TCCR1B | (1 << CS12); //bitSet(TCCR1B, CS12);  
  // for 1024 prescaler
  //TCCR1B = TCCR1B | ((1 << CS12) | (1 << CS10)); 
  // timer overflow interrupt
  TIMSK1 |= (1 << OCIE1A);
  PORTB = PORTB & B000000;
  PORTD = PORTD & B00000000;
  PORTC = PORTC & B00000;
  sei();
  DDRD=B11111111;
  DDRB=B111111;
  DDRC=B11111;
  curstate=1;
  changetime=millis();
  cadr=millis();
}
int pins[8]={R1,R2,R3,R4,R5,R6,R7,R8};
byte states[8]= {
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111
};
void PWMstates(byte* bstates){
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
    if (curstate==8){
      curstate=0;
    }
    curstate+=1;
}
ISR(TIMER1_COMPA_vect) {
  PWMstates(states);
}
void loop() {
  // put your main code here, to run repeatedly:
  //PWMstates(states);
  
}
