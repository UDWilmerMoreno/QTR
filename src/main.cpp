#include <Arduino.h>
#include <QTRSensors.h>

QTRSensors qtr;
const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

void setup()
{
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){10, 9, 14, 15, 16, 17, 18, 19}, SensorCount);
  qtr.setEmitterPin(6);
  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }

  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);

  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(' ');
  }

  Serial.println();

  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.print(' ');
  }

  Serial.println();
  Serial.println();
  delay(1000);
}

void loop()
{
  uint16_t position = qtr.readLineBlack(sensorValues);

  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }

  Serial.println(position);
  delay(250);
}