

// глобальные переменные для работы с ними в программе
int ds_int; // интервал замера ds18b20 в секундах 
int mqtt_int; // интервал отправки данных по MQTT в секундах 
float tem; // тут храним температуру
float in_tem; // температура включения реле
float out_tem; // гистерезис
float hum;

void parameters(){
// создаем параметры для нашего проекта
  jee.var("wifi", "STA"); // режим работы WiFi по умолчанию ("STA" или "AP")  (параметр в энергонезависимой памяти)
  jee.var("ssid", "gw-rage"); // имя точки доступа к которой подключаемся (параметр в энергонезависимой памяти)
  jee.var("pass", "1111111111111"); // пароль точки доступа к которой подключаемся (параметр в энергонезависимой памяти)

  jee.var("ds_int", "10"); // это будет интервал замеров DH22 в секундах
}

void update(){ // функция выполняется после ввода данных в веб интерфейсе. получение параметров из веб интерфейса в переменные
  // получаем данные в переменную в ОЗУ для дальнейшей работы
  ds_int = jee.param("ds_int").toInt(); // читаем параметр в переменную с переобразованием в нужный тип данных
	// p_tem = jee.param("p_tem").toFloat(); // читаем параметр в переменную с переобразованием в нужный тип данных
  // h_tem = jee.param("h_tem").toFloat(); // читаем параметр в переменную с переобразованием в нужный тип данных
  // mode = jee.param("mode"); // читаем параметр в переменную как String

}

void interface(){ // функция в которой мы формируем веб интерфейс и интерфейс в приложении JeeUI2

  jee.app("Температура в гараже"); // название программы (отображается в веб интерфейсе)

  // создаем меню
  jee.menu("Устройство");
  jee.menu("Настройки MQTT");
  jee.menu("Настройки Wi-Fi");
  // создаем контент для каждого пункта меню

  jee.page(); // разделитель между страницами
  // Страница "Датчики"

  // эта суперфункция покажет в веб интерфейсе температуру 
  // и она же обепечит автоматическую отправку по mqtt по 
  // одноименному топику при обновлении параметра (первый аргумент)
  // как только вы запишите в "tem" значение - туту же 
  // отправится сообщение на топик ID/tem с заданным значением вот так: jee.var("tem", "значение")
  jee.pub("tem", "Температура в гараже", "°C", "#4ad491", "#f5f5f5"); 
  jee.pub("hum", "Влажность в гараже", "%", "#4ac2d4", "#f5f5f5"); 
  jee.pub("in_tem", "Температура на входе бокса", "°C", "#6060ff", "#f5f5f5"); 
  jee.pub("out_tem", "Температура на выходе бокса", "°C", "#CC0000", "#f5f5f5"); 

  jee.number("ds_int", "Интервал опроса датчика сек.");
  

  jee.page(); // разделитель между страницами
  // Страница "Настройки MQTT"
  jee.formMqtt(); // готовая форма настроек MQTT

  jee.page(); // разделитель между страницами
  // Страница "Настройки WiFi"
  jee.formWifi(); // готовая форма настроек Wi-Fi
  jee.page(); // разделитель между страницами

}