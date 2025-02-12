#define PIN_TRIG 12
#define PIN_ECHO 11
#define INFRO 0
#define GET_INFRO 'i'
#define GET_ULTRA 'u'
long duration, cm;

void setup() {

  // Инициализируем взаимодействие по последовательному порту

  Serial.begin (9600);
  //Определяем вводы и выводы
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
}

void loop() {

  // Сначала генерируем короткий импульс длительностью 2-5 микросекунд.

  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);

  // Выставив высокий уровень сигнала, ждем около 10 микросекунд. В этот момент датчик будет посылать сигналы с частотой 40 КГц.
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  //  Время задержки акустического сигнала на эхолокаторе.
  duration = pulseIn(PIN_ECHO, HIGH);

  // Теперь осталось преобразовать время в расстояние
  cm = (duration / 2);

  //Serial.print("Ультразвук: ");
  //Serial.println(cm);
  float distance = analogRead(INFRO);
  //Serial.print("Инфракрасный: ");
  //Serial.println(distance);   // print the distance

  if (Serial.available() > 0) {  //если есть доступные данные
    int command = Serial.read();
    if (command==GET_INFRO){
      Serial.write(int(distance)/4);
    }
    if (command==GET_ULTRA){
      Serial.write(cm/4);
    }
  }
}

