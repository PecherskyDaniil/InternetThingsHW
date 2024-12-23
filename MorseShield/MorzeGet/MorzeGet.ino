#define DATA 7      // connect to pin 14 on the 74HC595
#define LATCH 6     // connect to pin 12 on the 74HC595
#define CLOCK 5    // connect to pin 11 on the 74HC595
#define LAMP 2
#define POTEN A5
#define READPIN 3
#define WRITEPIN 4
int state=0;
long tr=-1;
long tf=-1;
int message[]={0,1,0,0,0,1,1,1,0,0,0,1,0,0,0,1,0,1,0,1,1,1,1,1,1,1,0,1,0,0,0,1,1,1,0,0,0,1,0,0,0,1,0,1,0};
String amorse="";
int TU=10;
bool istranslated=false;
bool lc=false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(LAMP,OUTPUT);
  pinMode(POTEN,INPUT);
  pinMode(READPIN,INPUT_PULLUP);
  pinMode(WRITEPIN,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(READPIN),onChange, CHANGE);
  //Serial.println("");
  digitalWrite(WRITEPIN,1);
}
long changetime=-1;
void onChange() {
  changetime=millis();
  lc=true;
  state=!state;
  if (state){
    tr=millis();
    if (tr==tf){
      tf-=1;
    }
  }else{
    tf=millis();
    if (tr==tf){
      tr-=1;
    }
  }
  
  if (tf>0 && tf<tr){
    
    int space=(tr-tf)/TU;
    if (space==3){
      amorse+=" ";
    }else if (space==7){
      amorse+="   ";
    }
  }
  if (tr>0 && tf>tr){
    int symbol=(tf-tr)/(TU*3);
    if (symbol==0 && (tf-tr)/TU>=1){
      amorse+=".";
      //Serial.println(".");
    }else if (symbol>0){
      amorse+="-";
      
    }
  }
}

void show_message(String morse){
  Serial.println(morse);
  
  int num=0;
  long del=millis();
  bool mig=false;
  int speed=analogRead(POTEN)+100;
  while (num<morse.length()){
    speed=analogRead(POTEN)+100;
    if (!mig && millis()-del>speed){
      if (morse[num]=='.'){
        digitalWrite(LATCH, LOW);
        shiftOut(DATA, CLOCK, LSBFIRST, 253);
        digitalWrite(LATCH, HIGH);
      }else if (morse[num]=='-'){
        digitalWrite(LATCH, LOW);
        shiftOut(DATA, CLOCK, LSBFIRST, 239);
        digitalWrite(LATCH, HIGH);
      }else{
        digitalWrite(LATCH, LOW);
        shiftOut(DATA, CLOCK, LSBFIRST, 255);
        digitalWrite(LATCH, HIGH);
      }
      num+=1;
      mig=true;
      del=millis();
    }else if (mig && millis()-del>speed){
      digitalWrite(LATCH, LOW);
      shiftOut(DATA, CLOCK, LSBFIRST, 255);
      digitalWrite(LATCH, HIGH);
      mig=false;
      del=millis();
    }
  }
  while (millis()-del<speed){
    num=0;
  }
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, 255);
  digitalWrite(LATCH, HIGH);
}
int a=1;
int i=0;
int n=45;
long lasttime=millis();
void send_message(int message[]){
  if (millis()-lasttime>TU){
    a=message[i];
    //Serial.println(a);
    i+=1;
    digitalWrite(WRITEPIN,a);
    lasttime=millis();
  }
}
bool gotmessage=true;
void loop() {
  if (Serial.available()){
    if (Serial.read()=='l'){
      gotmessage=true;
      a=1;
      i=0;
    }
  }
  if (gotmessage){
    if (i<=n){
      send_message(message);
    }else if (i>n){
      a=1;
      digitalWrite(WRITEPIN,a);
      gotmessage=false;
    }
  }
  if (millis()-changetime>TU*12 && lc && changetime!=-1){
    istranslated=true;
  }
  if (istranslated && lc){
    //Serial.println(amorse);
    show_message(amorse);
    istranslated=false;
    lc=false;
    tf=-1;
    tr=-1;
    amorse="";
    state=0;
    changetime=-1;
  }
}