
#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);
char msg;
char call;

int button = 2;

void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  //GSM
  Serial.println("GSM SIM800A BEGIN");
  Serial.println("Enter character for control option:");
  Serial.println("h : to disconnect a call");
  Serial.println("i : to receive a call");
  Serial.println("s : to send message");
  Serial.println("r : to receive message");
  Serial.println("c : to make a call");  
  Serial.println("e : to redial");
  Serial.println();
 //SR04
  pinMode(button, INPUT);
  //pinMode(trig,OUTPUT);
  //pinMode(echo,INPUT);
  delay(100);
}

void loop()
{  
//  SR04=Distance();
int buttonStatus = digitalRead(button);
delay(200);
  // delay(1000);  //Note: feedback signal
    if (buttonStatus==1)
    {
   //  SendMessage();
       MakeCall(); 
      }
    //  else
   //   {
   //    HangupCall();
   //     }
    
}

/*
 int Distance()
{
  unsigned long duration;
  int distance;
  digitalWrite(trig,0);
  delayMicroseconds(2);
  digitalWrite(trig,1);
  delayMicroseconds(5);
  digitalWrite(trig,0);
  duration=pulseIn(echo,HIGH);
  distance=int(duration/2/29.412);
  if (distance>10) {
           return 1; 
          }
   else { 
          return 0; 
    }
}
 */

void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+84834234523\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("TRUNG_sim800a sms CANH BAO TROM");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void MakeCall()
{
  mySerial.println("ATD+84834234523;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
  Serial.println("Calling  "); // print response over serial port
  delay(1000);
}

void HangupCall()
{
  mySerial.println("ATH");
  Serial.println("Hangup Call");
  delay(1000);
}
