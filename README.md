# Оглавление
[Первый Семестр 3 курса](#Первый_Семестр_3_курса)
1. [Описание](#Описание)
2. [Задание про светофор](#Светофор)
3. [Задание про фоторезистор и направление](#Детектор-источника-света)
4. [Задание про фоторезистор и светодиод на разных микроконтроллерах](#LedPhotoDistributedSerial)
5. [Задание про использование MQTT](#MQTT)
6. [Задание про esp8266, фоторезистор и светодиод](#espLedPhoto)
7. [Задание про espLamp](#espLamp)
8. [Задание про светодиодную матрицу 2x2](#MatrixLed4)
9. [Задание про светодиодную матрицу 8x8](#led_matrix8x8)
10. [Задание про светодиодную матрицу 8x8 с применением регистров](#led_matrix8x8_registers)
11. [Задание про shield и Азубуку Морзе](#MorseShield)

[Второй Семестр 3 курса](#Второй_Семестр_3_курса)
1. [Дребезг кнопки](#DREBEZG)
2. [Матрица кнопок](#ButtonMatrix)
3. [Калибровка инфрокрасного датчика](#RangeCalibration)
4. [H-мост](#Hbridge)
# Первый Семестр 3 курса

# Описание
Данный репозиторий содержит скетчи из моей домашней работы. В Readme.md будут описываться суть работы, схема подключения и другая информация, относящаяся к домашним работам.

# Светофор
### Суть работы
> Подключить три светодиода, красный, зеленый и желтый. Если нет желтого светодиода, синий выполняет роль желтого сигнала светофора.
> Запрограммировать автоматический режим работы светофора: зеленый (10 с) - мигающий зеленый (2 с) - желтый (1с) - красный (7 с) - желтый (1с) - зеленый (10 с).
>  Добавить возможность перевода на ручное управление через команду с ПК: запрос на перевод (одна команда) и режим в котором светофор будет работать зеленый или красный (вторая команда).
> Если текущий режим не соответствует запрошенному, сделать перевод в него через желтый (3с).
>  Ограничить ручной режим на 60 секунд - далее происходит возврат к автоматическому режиму даже если запроса на возврат не было.
> В коде не должно быть задержек (delay).
### Схема подключения
![image](https://github.com/user-attachments/assets/d7476739-acb2-488b-917d-2ab8034936c7)

### Скетч
Скетч для прошивки микроконтроллера Arduino лежит в папке traffic_light репозитория. Для запуска ручного управления нужно написать 'm' в Serial. Для переключения между красным и зеленым нужно отправлять сообщения 'r' и 'g' соответственно.

### Видео демонстрация
Видео демонстрации доступно по ссылке ниже:\
[https://disk.yandex.ru/i/X6cswIxhiJo6qw](https://disk.yandex.ru/i/X6cswIxhiJo6qw)
# Детектор источника света
### Суть работы
>Детектор направления источника освещенности, например окна.
>Создайте схему  на макетной плате с одним или несколькими датчиками освещенности (два резистора) и двумя индикаторами (светодиод и резистор).
>Датчики и индикаторы  подключены независимо - изъятие любого из них не ведет к изменению работы остальных.
>Индикаторы показывают направление в которым нужно повернуть макетную плату вокруг своей оси.
>Должен мигать тот светодиод, при повороте в его сторону источник света должен стать ближе к направлению в котором мы смотрим, если смотреть вперед.
>При нахождении оптимального направления светодиоды, должны светиться без мигания. Не использовать delay.
### Схема подключения
![image](https://github.com/user-attachments/assets/f5395619-4365-495f-a964-689674c60e8f)

### Скетч
Скетч для прошивки микроконтроллера Arduino лежит в папке light_detector репозитория

### Видео демонстрация
Видео демонстрации работы скетча и схемы доступно по ссылке:\
https://disk.yandex.ru/i/MjievQNJMNe0FA
# LedPhotoDistributedSerial
### Суть работы
>Создать программу управляющую светодиодом (освещением) на основе показаний датчика освещенности.
>Датчик и светодиод подключены к разным микроконтроллерам.
>Микроконтроллеры не связаны между собой напрямую, только с помощью USB через ПК.
>Микроконтроллеры просто отрабатывают команды присланные с ПК, решение принимается на ПК.
### Схема подключения
![image](https://github.com/user-attachments/assets/ce04e46d-e61f-4297-8a39-5ae488f52545)
### Скетч
Скетч для прошивки микроконтроллера отвечающего за мигание светодиода лежит в папке LedPhotoDistributedSerial/led_change.
Скетч для прошивки микроконтроллера отвечающего за передачу данных с фоторезистора лежит в папке LedPhotoDistributedSerial/photo_val.
Скетч для отправки команд в Serial лежит в папке LedPhotoDistributedSerial.

### Видео демонстрация
Видео демонстрации работы скетча и схемы доступно по ссылке:\
[https://disk.yandex.ru/i/bKdXRWkYG_4Ryg](https://disk.yandex.ru/i/bKdXRWkYG_4Ryg)

# MQTT
### Суть работы
>Подключить плату с фоторезистором к одному компьютеру, а плату со светодиодом - к другому.
>Написать скрипт на Python который берёт значения фоторезистора используя библиотеку Serial и обрабатывает их и отправляет на топики с помощью библиотеки paho-mqtt. 
>Написать скрипт на Python который, слушая топики MQTT, получает значения фоторезистора и отправляет команды по включению/выключению светодиода с помощбю библиотеки Serial.
>Светодиод должен светиться только на участках убывающей яркости.


Список топиков:
* lab/UNIQUE_ID/photo/instant - значения фоторезистора в диапазоне от 0 да 100
* lab/UNIQUE_ID/photo/averge - бегущее среднее по 100 значениям фоторезистора
* lab/UNIQUE_ID/photo/stream - сырые значения фоторезистора
* lab/UNIQUE_ID/photo/activate_stream - запуск/выключение отправки значений в поток по командам "on"/"off"
* lab/UNIQUE_ID/photo/min - обновляющееся минимальное значение фоторезистора
* lab/UNIQUE_ID/photo/max - обновляющееся максимальное значение фоторезистора
### Схема подключения
![image](https://github.com/user-attachments/assets/ce04e46d-e61f-4297-8a39-5ae488f52545)
### Скетч
Скетч для прошивки микроконтроллера отвечающего за мигание светодиода лежит в папке LedPhotoDistributedSerial/led_change.
Скетч для прошивки микроконтроллера отвечающего за передачу данных с фоторезистора лежит в папке LedPhotoDistributedSerial/photo_val.
Скетч на стороне фоторезистора для отправки значений по MQTT лежит в папке MQTT_led_photo/photoside.py.
Скетч на стороне светодиода для обработки значений фоторезистора лежит в папке MQTT_led_photo/ledside.py.

### Видео демонстрация
Видео демонстрации работы скетча и схемы доступно по ссылке:\
[https://disk.yandex.ru/i/mg7Io_f2WVdvkQ](https://disk.yandex.ru/i/mg7Io_f2WVdvkQ)

# espLedPhoto
### Суть работы
>Создайте программу управляющую светодиодом (освещением) на основе показаний датчика освещенности. Датчик и светодиод подключены к двум разным микроконтроллерам. Используйте esp8266. Микроконтроллеры не связаны между собой напрямую,
только с помощью MQTT. Воспользуйтесь кодом с проекта https://github.com/vesninam/esp_network_mqtt чтобы настроить коммуникацию. Можете использовать для отладки, настройки или вывода сообщений как http сервер так и serial порт. ВАЖНО1: данные должны ходить только по MQTT. ВАЖНО2: топики на subscriber хардкодить нельзя.
### Скетч
Скетч для прошивки esp8266 с фоторезистором лежит в папке espPhoto.
Скетч для прошивки esp8266 со светодиодом лежит в папке espLed.
В обоих скетчах поменяйте в Config.h данные о сети, к которой подключается esp, в перемнных ssidCLI и passwordCLI.
При запуске скетча укажите в Serial топик, куда отправляются данные с фоторезистора. (по умолчанию pech/esp8266/com)
### Видео демонстрация
Видео демонстрации работы скетча и схемы доступно по ссылке:\
[https://disk.yandex.ru/i/BKAiWwv8_NrFKg](https://disk.yandex.ru/i/BKAiWwv8_NrFKg)

# espLamp
### Суть работы
>Возьмите за основу написанный в аудитории код, который включает работу с WiFi (режим AP и Client), WebServer, MQTT. Если что-то пропустили, код можно посмотреть в репозитории https://github.com/vesninam/esp_network_mqtt . Реализуйте программы, которые обеспечит работу устройства (назовем его wifi лампочкой) по следующему сценарию:
>
>0. Пользователь получает Ваше устройство, на "коробке" написано какую WiFi это устройство поднимает и пароль к ней и IP адрес.
>
>1. Пользователь включает ESP и подключается к WiFi указанному на коробке. (Светодиод мигает равномерно медленно - не подключен к интернету)
>
>2. Пользователь открывает браузер и вбивает IP адрес указанный на коробке.
>
>3. Открывается web-интерфейс, в который пользователь должен вбить название и пароль к своей "домашней" (раздайте с телефона) сети WiFi. Для работы с аргументами приходящими по HTTP смотрите статью https://techtutorialsx.com/2016/10/22/esp8266-webserver-getting-query-parameters/
>
>4. После того как данные внесены ESP совершает попытку подключиться к WiFi. При успешной попытке и если существует доступ в Интернет ESP отключает свою точку доступа (к которому подключается пользователь в пункте 1). Подключение не должно теряться при перезагрузке микроконтроллера, для этого можно использовать энергонезависимую память микроконтроллера EEPROM . (Светодиод мигает кратко два раза и затем пауза - подключен к интернету, пока не получал команд, после перезагрузки должен снова мигать кратко, до получения команд)
>
>4.5 При потере подключения к интернету ESP должна снова поднять свою точку доступа. (Светодиод мигает равномерно - не подключен к интернету)
>
>5. Происходит подключение к MQTT брокеру (топик так же указан на коробке). (При неудачном подключении светодиод мигает быстро, при удачном светодиод мигает кратко два раза и затем пауза, как было раньше)
>
>6. Для управления лампочкой реализуйте клиента на python, который имитирует автоматический сценарий управления по времени суток: лампочка светиться с 20 по 40 секунду каждой минуты. Каждую слудующую минут происходит уменьшение времени свечения на 1 секунду, например с 20 по 39 секунду и так далее. Минимальное время свечения 10 секунд  (c 25 по 35 секунду). Дальше время работы лампочки сбрасывается снова на 20 секунд и идет повторение сценария.
>
>7. Клиент принимает ID лампочки (topic) в качестве аргумента. Можно использовать любую библиотеку для взаимодействия в командной строке, например https://pypi.org/project/questionary/
>
>
>
>Индикация:
>
>* светодиод мигает равномерно медленно - поднята своя точка доступ, нет подключения к интернету
>* светодиод мигает кратко два раза - есть подключение к интернету и брокеру
>* светодиод мигает равномерно быстро - есть подключение к интернету и но не к брокеру
### Скетч
Скетч для прошивки esp8266 лежит в папке espLamp.
Клиент на питоне это файл client.py\
При запуске клиента укажите id лампы как 1\
При запуске лампы название её сети это PECH_ESP_WIFI, а пароль 123456789
### Видео демонстрация
Видео демонстрации работы скетча и схемы доступно по ссылке:\
[https://disk.yandex.ru/i/BKAiWwv8_NrFKg](https://disk.yandex.ru/i/E2bRhscnr4oUpA)

# MatrixLed4
### Суть работы
>Собрать светодиодную матрицу 2x2

>Реализовать таблицу состояний и переключение между ними

### Схема подключения
![image](https://github.com/user-attachments/assets/678316f9-fc02-4864-b04e-feb8639be652)

### Скетч
Скетч с таблицей состояний находится в папке MatrixLed4

### Видео демонстрация
Видео демонстрации работы скетча и схемы доступно по ссылке:
[https://disk.yandex.ru/i/IsGPbSsqf3Nz1A](https://disk.yandex.ru/i/IsGPbSsqf3Nz1A)

# led_matrix8x8
### Суть работы
>Подключить светодиодную матрицу 8x8

>Написать программу для управления светодиодами матрицы

### Скетч
Скетч для управления матрицей находится в папке led_matrix8x8

### Видео демонстрация
Видео демонстрации работы скетча и схемы доступно по ссылке:
[https://disk.yandex.ru/i/ZZB8zIuABicP0Q](https://disk.yandex.ru/i/ZZB8zIuABicP0Q)

# led_matrix8x8_registers
### Суть работы
>Подключить светодиодную матрицу 8x8

>Написать программу для управления светодиодами матрицы при помощи регистров таймера и регистров портов Arduino UNO

### Схема подключения
![image](https://github.com/user-attachments/assets/8ce8d8eb-b547-41fc-b377-1aaa199ebae2)


### Скетч
Скетч для управления матрицей при помощи регистров находится в папке led_matrix8x8_registers

### Видео демонстрация
Видео демонстрации работы скетча и схемы доступно по ссылке:
[https://disk.yandex.ru/i/YF3G_6FNn7pL_g](https://disk.yandex.ru/i/YF3G_6FNn7pL_g)

# MorseShield
### Суть работы
>Спаять shield для платы arduino uno, со сдвиговым регистром, семисегментным дисплеем, лампочкой, потенциометром.

>Написать программу для принятия и отображения сигнала в формате Азбуки Морзе

### Скетч
Скетчи для для передатчика и приемника находятся в папке MorseShield

# Второй Семестр 3 курса
# DREBEZG
### Суть работы
>Допишите код, чтобы правильно обрабатывать дребезг - код дает только реальные нажатия. А так же время удержания кнопки.
### Схема подключения
![image](https://github.com/user-attachments/assets/545c5724-cc6b-47b2-9b32-cb099efe566f)


### Скетч
Скетч для прошивки микроконтроллера Arduino лежит в папке BounceProcessing репозитория.

# ButtonMatrix
### Суть работы
>0) (3 балла)Реализуйте работу с кнопками используя регистры PIN# и PORT#, что позволит избавиться от внутренних циклов в update_button_state(). Внешний цикл ( for(int irow = 0; irow < NROWS; irow++) ) >реализовать с помощью таймеров - для этого настройте таймеры на прерывания каждые N миллисекунд (задается константой) и на каждом прерывании сдвигайте на одну строку ниже, по достижению последней строки, >переходим обратно на первую.
>
>1) (2 балла) В serial monitor нужно выводить информацию, только при смене события - нажатие кнопки, которая не была нажата или отпускание кнопки, которая была нажата. Например, если пользователь нажал и держит >кнопки 1, 3, 5 и ничего больше  не делает, то выведено будет один раз, что нажаты кнопки 1, 3, 5. Если пользователь нажал и держит кнопки 1, 3, 5 и потом нажал еще кнопку 7, и спустя время отпустил кнопку 3, то >выведено будет три сообщения, "нажаты кнопки 1, 3, 5", "нажаты кнопки 1, 3, 5, 7", "нажаты кнопки 1, 5, 7".
>
>2) (2 балла) Нужно вести учет длительности и начала нажатия нажатия каждой из кнопок. Выводите его после того как кнопка была отпущена. Если пользователь нажал и держит кнопки 1, 3, 5 и потом нажал еще кнопку >7, и спустя время отпустил кнопку 3, то выведено будет дополнительное сообщение к предыдущим - "нажаты кнопки 1, 3, 5", "нажаты кнопки 1, 3, 5, 7", "нажаты кнопки 1, 5, 7", "длительность нажатия кнопки 3 - 4123 >мс, начало в 12987 мс". Длительность и начало нажатия могут быть полезны в разных сценариях - попробуйте нажать на клавиатуре клавишу и посмотрите, посмотрите что сначала появилась одна буква, а затем уже >началось дублирование (после удержания клавиши определенное время).  Время начала нажатия важно, так как старые нажатия можно "забыть" - например при использовании брелка сигнализации машины вам не нужно >учитывать какие кнопки Вы нажимали до этого, даже если команда не была завершена.
### Схема подключения
![Super Inari-Gogo](https://github.com/user-attachments/assets/2932088f-3288-4450-a3ca-f3197074a01c)

### Скетч
Скетч для прошивки микроконтроллера Arduino лежит в папке ButtonMatrix репозитория.

# RangeCalibration
### Суть работы
>Используя данные с ультразвукового сенсора. Разработать метод и код для калибровки инфракрасного дальномера. Т.е. код который позволит получить данные что бы воспроизвести данные с графика ниже. График может не соответствовать вашему датчику - посмотрите маркировку и найдите график в сети.
>На стороне микроконтроллера можно оставить только сбор данных и передачу их на ПК по UART (Serial). Осноновные расчеты и визуализация происходят в программе на python. Программа должна осуществить сбор данных, как описано выше, построить по этим точкам модель (найти коэффициенты полинома). Построить график с точками-измерениями и сверху наложить кривую полученную по модели. Учтите что в зависимости от порядка модели будет получаться более или менее точный результат - на картинке ниже слева линейная модель (полином первой степени), справа полином третьей степени. Вы можете вывести несколько графиков на одном рисунке для разных степеней.


### Схема подключения
![image](https://github.com/user-attachments/assets/ee0fd7f1-0751-472f-9c2d-58034a383b51)

# Hbridge
### Суть работы
>Создать схему подключение мотора так чтобы можно было управлять как скоростью так и направлением вращения. Написать функцию для управления мотором. В функцию должно передаваться направление и скорость. Используйте эту функцию в loop чтобы продемонстрировать разные режимы работы мотора.
>Задание можно выполнить в симуляторе tinkercad. В репозитории должна быть ссылка на вашу симуляцию. Код нужно продублировать в репозитории.


### Схема подключения
![image](https://github.com/user-attachments/assets/9cacc18a-ab14-40ba-a368-19ea9b482439)



### Скетч
Скетч для прошивки микроконтроллера Arduino и код питона лежат в папке Hbridge репозитория.

### Схема в Tinkercad
Демонстрации работы скетча и схемы в Tinkercad доступно по ссылке:
[https://www.tinkercad.com/things/cGq73s1uTVA-h-bridge?sharecode=krwKtOFoHliGyfQ3akJvIMGMAOZaS6Lw3utMukpRzBc](https://www.tinkercad.com/things/cGq73s1uTVA-h-bridge?sharecode=krwKtOFoHliGyfQ3akJvIMGMAOZaS6Lw3utMukpRzBc)
