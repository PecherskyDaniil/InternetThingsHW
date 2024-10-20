#define LED 7
#define UP 'u'
#define DOWN 'd'
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}
int state=0;
void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    char cmd = Serial.read();
    if (cmd==DOWN){
      state=0;
    }else if(cmd==UP){
      state=1;
    }
    update_state();
  }
  
}
void update_state(){
  if (state==1){
    digitalWrite(LED,HIGH);
    Serial.write("Led on");
  }else{
    digitalWrite(LED,LOW);
    Serial.write("Led off");
  }
}
