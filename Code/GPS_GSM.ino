
#include <SoftwareSerial.h> //gia lap TX RX 
SoftwareSerial mySerial(9, 10);   //SIM 800A

#include <TinyGPS++.h>
TinyGPSPlus gps;
SoftwareSerial ss(4, 3);  //GPS

boolean sendonce = false;  //cờ ngắt của listen()

const String myphone = "0834234523";

int button = 2;

float flat, flon;
char str[15];
int led = 13;
int led1 = 12;
int temp = 0, i = 0;
int ttLight = 0;
void Gsm_Init();

void sent_data(String datasent)
{

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+84834234523\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print(datasent); //text content_____Ex: mySerial.println("TRUNG_sim800a sms CANH BAO TROM");
  updateSerial();
  mySerial.write(26);  // mySerial.println((char)26);
  ss.listen();  //Accept just only 1 uart enable
}


void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)

  ss.begin(9600);
  mySerial.listen();

  delay(50);
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(button, INPUT);
  Gsm_Init();
}
void loop()
{
  serialEvent();
  check_button();
  /*
   int buttonStatus = digitalRead(button);
  delay(200);
  if (buttonStatus==1)
    {
   //  SendMessage();
   Serial.println(buttonStatus);
   check_button();
   delay(500);
       MakeCall(); 
      }
   */

      
 // serialEvent();
  if (temp == 1)
  {
    check();
    temp = 0;
    i = 0;
    delay(1000);
  }
  mySerial.listen();
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
    //----- Bat led ---------
    digitalWrite(led1, HIGH);
    digitalWrite(led, HIGH);
    Serial.println("ON");

    //------------Doc tin hieu va gui ve dien thoai
    ss.listen();
    while (sendonce == false)
    {
      while (ss.available() > 0)
      {
        gps.encode(ss.read());
        if (gps.location.isUpdated())
        {
          sendonce = true;
          //Lay toa do va chuyen sang dang String
          char Templat[12], TempLon[12];
          dtostrf(gps.location.lat(), 2, 6, Templat); // Lay toa do va luu vao bien lat
          dtostrf(gps.location.lng(), 3, 6, TempLon); // Lay toa do va luu vao bien long

          String tmp = "";
          // Chuyen doi ki tu cua toa do LAT sang String
          for (int i = 0 ; i < 10; i++)
            tmp += (String)(Templat[i]);

          // Ky tu phan biet lat va long
          tmp += ",";

          // Chuyen doi ki tu cua toa do LONG sang String
          for (int i = 0 ; i < 10; i++)
            tmp += (String)(TempLon[i]);

          delay(500);
          mySerial.listen();

          delay(500);
          sent_data(tmp);
          Serial.println("Da gui toa do");
          Serial.println(tmp);
        }
        else {
        }
      }
    }
    sendonce = false;

    //------------

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


void updateSerial()
{
  delay(500);
  while (Serial.available())
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while (mySerial.available())
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
void MakeCall()
{
  mySerial.println("ATD+84834234523;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
  Serial.println("Calling  "); // print response over serial port
  delay(1000);
}

//////////////////////
void check_button()
{ 
  Serial.println("wating...");
  int buttonStatus = digitalRead(button);
  delay(500);
  if (buttonStatus == 1)
  {
    //----- Bat led ---------
    digitalWrite(led1, HIGH);
    digitalWrite(led, HIGH);
    Serial.println("Button_ON");

    //------------Doc tin hieu va gui ve dien thoai
    ss.listen();
    while (sendonce == false)
    {
      while (ss.available() > 0)
      {
        gps.encode(ss.read());
        if (gps.location.isUpdated())
        {
          sendonce = true;
          //Lay toa do va chuyen sang dang String
          char Templat[12], TempLon[12];
          dtostrf(gps.location.lat(), 2, 6, Templat); // Lay toa do va luu vao bien lat
          dtostrf(gps.location.lng(), 3, 6, TempLon); // Lay toa do va luu vao bien long

          String tmp = "";
          // Chuyen doi ki tu cua toa do LAT sang String
          for (int i = 0 ; i < 10; i++)
            tmp += (String)(Templat[i]);

          // Ky tu phan biet lat va long
          tmp += ",";

          // Chuyen doi ki tu cua toa do LONG sang String
          for (int i = 0 ; i < 10; i++)
            tmp += (String)(TempLon[i]);

          delay(500);
          mySerial.listen();

          delay(500);
          sent_data(tmp);
          Serial.println("Da gui toa do");
          Serial.println(tmp);
        }
        else {
        }
      }
    }
    sendonce = false;

    //------------

    delay(200);
  }
}
