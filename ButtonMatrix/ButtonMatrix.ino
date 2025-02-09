#define ROW1 2
#define ROW2 3
#define ROW3 4

#define COL1 5
#define COL2 6
#define COL3 7

#define NROWS 3
#define NCOLS 3

const int row_pins[NROWS] = {2, 3, 4};
const int col_pins[NCOLS] = {5, 6, 7};
long btns_time[9]={0,0,0,0,0,0,0,0,0};
byte btn_pressed = B00000000;
int btns=0;
int lastbtns=0;
int irow=0;
const long N = 1;
void setup()
{
  DDRD=B00011100;
  for(int i = 0;i < NCOLS; i++) {
    pinMode(col_pins[i], INPUT_PULLUP);
  }
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = (16000000 / 256 / 1000) * N - 1;
  TCCR1B |= (1 << WGM12);
  TCCR1B = TCCR1B | (1 << CS12);
  TIMSK1 |= (1 << OCIE1A);
  sei();
  Serial.begin(9600);
}

void loop()
{

}

void update_button_state() {
   irow=(irow+1)-3*(irow>1);
   PORTD=B00011100;
   digitalWrite(row_pins[irow], LOW);
   btn_pressed=~(PIND&B11100000);
   btn_pressed/=32;
   report_row_states(irow);
}
ISR(TIMER1_COMPA_vect) {
  update_button_state();
}
void report_row_states(int row_number) {
  if (row_number==0){
    start_time(btns);
    if (lastbtns!=btns){
      //Serial.println(btns);
      printbtns(btns);
      print_time(lastbtns, btns);
    }
    lastbtns=btns;
    btns=0;
  }
  for(int icol = 0; icol < NCOLS; icol++) {
    if(btn_pressed % 2 ==1) {
           
      //Serial.print("Button ");
      //Serial.print(1+icol + NCOLS * row_number);
      btns+=stepen2(icol + NCOLS * row_number);
      //Serial.println(" pressed");
    }
    btn_pressed/=2; 
  }
  
}
void printbtns(int btnse){
  String info = String("Pressed buttons ");
  bool nopress=true;
  int btnsa=btnse;
  for(int i = 0; i < 9; i++){
    //Serial.println(btnsa);
    if (btnsa%2==1){
      nopress=false;
      info=info+String(i+1)+String(", ");
    }
    btnsa/=2;
  }
  if (nopress){
    Serial.println("Pressed no buttons");
  }else{
    Serial.println(info);
  }
}
void start_time(int btns){
  int btnsa=btns;
  for(int i = 0; i < 9; i++){
    if (btnsa%2==1 && btns_time[i]==0){
      btns_time[i]=millis();
    }
    btnsa/=2;
  }
}

void print_time(int prev, int now){
  int btns1=prev;
  int btns2=now;
  String info=String("");
  for(int i = 0; i < 9; i++){
    if (btns1%2==1 && btns2%2==0){
      info = String(String("Press duration of button ")
                    +String(i+1)
                    +String(" - ")
                    +String(millis()-btns_time[i])
                    +String(" ms, Press start - ")
                    +String(btns_time[i])
                    +String(" ms"));
      Serial.println(info);
      btns_time[i]=0;
    }
    btns1/=2;
    btns2/=2;
  }

}
int stepen2(int n){
  int ans=1;
  for(int i = 0; i < n; i++){
    ans*=2;
  }
  return ans;
}