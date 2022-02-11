
#include <SoftwareSerial.h> //gia lap TX RX 
SoftwareSerial mySerial(9, 10);   //SIM 800A

#include <TinyGPS.h>
TinyGPS gps;
SoftwareSerial ss(6, 5);  //GPS //4,3

const String myphone = "0834234523";

float flat, flon;
char str[15];
int led = 13; 
int led1 = 12;
int temp = 0, i = 0;
int ttLight = 0;
void Gsm_Init();
void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  ss.begin(9600);

  delay(50);
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  Gsm_Init();
}
void loop()
{
  serialEvent();
  if (temp == 1)
  {
    check();
    temp = 0;
    i = 0;
    delay(1000);
  }
}

void serialEvent()
{
  while (mySerial.available())
  {
    if (mySerial.find("#A."))
    {
      digitalWrite(led, HIGH);
      delay(1000);
      digitalWrite(led, LOW);
      while (mySerial.available())
      {
        char inChar = mySerial.read();
        str[i++] = inChar;
        if (inChar == '*')
        {
          temp = 1;
          return;
        }
      }
    }
  }
}

void check()
{
  if (!(strncmp(str, "led on", 6)))
  {
    digitalWrite(led1, HIGH);
    Serial.println("ON");
    delay(200);
  }
  else if (!(strncmp(str, "led off", 7)))
  {
    digitalWrite(led1, LOW);
    Serial.println("OFF");
    delay(200);
  }
}

 void Gsm_Init()
{
  mySerial.println("ATE0");   // Tat che do phan hoi (Echo mode)
  delay(2000);
  mySerial.println("AT+IPR=9600");   // Dat toc do truyen nhan du lieu 9600 bps
  delay(2000);
  mySerial.println("AT+CMGF=1");  // Chon che do TEXT Mode
  delay(2000);
  mySerial.println("AT+CLIP=1"); // Hien thi thong tin nguoi goi den
  delay(2000);
  mySerial.println("AT+CNMT=2,2,0,0,0");  // Hien thi truc tiep noi dung tin nhan
  delay(2000);
}
