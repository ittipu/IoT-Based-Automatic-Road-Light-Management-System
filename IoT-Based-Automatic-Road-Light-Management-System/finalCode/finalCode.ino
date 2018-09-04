#define led D0
#define sensorPin A0
int sensorValue, actualValue;
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
char ssid[] = "ICE_Innovation_lab";
char wifiPassword[] = "bolajabena15";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "eecd27e0-1c3f-11e8-b6d4-35a0ad51f849";
char password[] = "ad1efb65d66fc1830a8915ce2df57662397bb3d2";
char clientID[] = "4cf5d720-33e4-11e8-a21e-7395420787ce";

void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  pinMode(led, OUTPUT);
  pinMode(sensorPin, INPUT);
}

void loop() {
  Cayenne.loop();
  sensorValue=analogRead(sensorPin);
  actualValue=1024-sensorValue;
  Serial.print("Sensor Value: ");
  Serial.println(actualValue);
  if(actualValue<10)
  {
    digitalWrite(led, HIGH);
  }
  else if(actualValue>=10&&actualValue<=800)
  {
    digitalWrite(led,LOW);
  }
  delay(1000);
  
}

CAYENNE_OUT_DEFAULT()
{
  // Write data to Cayenne here. This example just sends the current uptime in milliseconds on virtual channel 0.
  Cayenne.virtualWrite(0, actualValue);
}
CAYENNE_IN(1)  // button
{   
  if(actualValue>800)
  {
    int currentValue=getValue.asInt();
    if(currentValue==1)
    {
      digitalWrite(led,HIGH);
    }
    else
    {
      digitalWrite(led,LOW); 
    }
  }
}

