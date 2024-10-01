#define PHOTO A2
#define GET_PHOTO_VAL 'p'
void setup() {
  Serial.begin(9600);
  pinMode(PHOTO, INPUT);

}

void loop() {
  if (Serial.available() > 0) {  //если есть доступные данные
    int command = Serial.read();
    if (command==GET_PHOTO_VAL){
      int val = analogRead(PHOTO);
      Serial.write(val/4);
    }
  }
}


