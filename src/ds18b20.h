#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 13

float ds_tem;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress inThermometer, outThermometer;
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void ds_setup(void)
{
  Serial.print("Locating devices...");
  sensors.begin();
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

  Serial.print("Parasite power is: "); 
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");

  if (!sensors.getAddress(outThermometer, 0)) Serial.println("Unable to find address for Device 0"); 
  if (!sensors.getAddress(inThermometer, 1)) Serial.println("Unable to find address for Device 1");

  Serial.print("Device 0 Address: ");
  printAddress(outThermometer);
  Serial.println();

  sensors.setResolution(outThermometer, 12);
 
  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(outThermometer), DEC); 
  Serial.println();


  Serial.print("Device 1 Address: ");
  printAddress(inThermometer);
  Serial.println();

  sensors.setResolution(inThermometer, 12);
 
  Serial.print("Device 1 Resolution: ");
  Serial.print(sensors.getResolution(inThermometer), DEC); 
  Serial.println();
}

void getTemperature(DeviceAddress deviceAddress)
{
  ds_tem = sensors.getTempC(deviceAddress);
  // sendUDP(String(ds_tem));
}

void ds_handle(int interval)
{ 

    static unsigned long i;
    static unsigned int in;
    if(i + (in * 1000) > millis() || interval == 0) return; // если не пришло время, или интервал = 0 - выходим из функции
    i = millis();
    in = interval;
    // всё, что ниже будет выполняться через интервалы
    // sendUDP(String(i));

    static bool st = false;
    if(!st){
        st = true;
        ds_setup();
    }
  sensors.requestTemperatures();
  getTemperature(inThermometer); 
  Serial.println("Temperature in: " + String(ds_tem, 2));
  jee.var("in_tem", String(ds_tem,1));

  getTemperature(outThermometer); 
  Serial.println("Temperature out: " + String(ds_tem, 2));
  jee.var("out_tem", String(ds_tem,1));
}

