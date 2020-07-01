
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "";
char ssid[] = "MyWifi";
char pass[] = "12345678";

int sensor2 = 4;
int sensor1 = 13;
int Status= 12;
int count=0;
int result=0;
int con=0;
int final=0;
int saved1;
int saved2;

BlynkTimer timer;

void myTimerEvent()
{
    con=con+5;
    Blynk.virtualWrite(V5, result);
    Blynk.virtualWrite(V6, (float)result*con*0.12);
    Blynk.virtualWrite(V7, count); 
    //con=con+5;
}

void setup() {
  Serial.begin(115200);
  pinMode(sensor1, INPUT); // declare sensor as input
  pinMode(sensor2, INPUT);
  pinMode(Status, OUTPUT);  // declare LED as output
  digitalWrite(Status, LOW);
  digitalWrite(sensor1,LOW);
  digitalWrite(sensor2,LOW);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(5000L, myTimerEvent);
  while (! Serial);
  Serial.println("Calibrating Sensor  ....");
  delay(30000);
  Serial.println("Calibrating ENDED ....");
}

void loop(){
  Blynk.run();
  if (Serial.available())
  {
    char ch = Serial.read();
    if (ch == 'z')
    {
      count=0;
      con=0;
    }
  }
  //delay(150);

  saved1=digitalRead(sensor1);
  saved2=digitalRead(sensor2);

    if(digitalRead(sensor1) != saved1 && digitalRead(sensor2) == saved2){
      count++;
      //digitalWrite(Status, LOW);
      Serial.println("Motion detected! through 1");
      delay(1000);
    }


     else if(digitalRead(sensor2) != saved2 && digitalRead(sensor1) == saved1){
     count--;
     //digitalWrite(Status, HIGH);
     Serial.println("Motion detected! through 2");
     delay(1000);
    }
    
    Serial.print(count);
    delay(150);
    if(count>0)
    {
      digitalWrite(Status, HIGH);
      result=1;
      timer.run();
    }
    else
    {
      digitalWrite(Status, LOW);
      result=0;
      con=-5;
    }
    
    Serial.print(con);
}
