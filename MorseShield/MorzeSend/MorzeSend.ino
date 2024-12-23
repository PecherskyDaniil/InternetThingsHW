#define WRITEPIN 4
int state=0;
int message[]={0,1,0,1,0,1,0,1,0};
String morse="";
int index=0;
int TU=10;
bool istranslated=false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(WRITEPIN,OUTPUT);
  digitalWrite(WRITEPIN,1);
  delay(2000);
}
int a=1;
int i=0;
int n=9;
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
  if (gotmessage){
    if (i<=n){
      send_message(message);
    }else if (i>n){
      a=1;
      digitalWrite(WRITEPIN,a);
      istranslated=true;
      gotmessage=false;
    }
  }
}

