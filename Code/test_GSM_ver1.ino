
#include <SoftwareSerial.h> //gia lap TX RX 
SoftwareSerial mySerial(9, 10);
char msg;
char call;

void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)

  delay(100);
}

void loop()
{  
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
     sent_data("trung");
      break;

  }
 
 if (mySerial.available()>0)
 Serial.write(mySerial.read()); // mySerial.read => xoa ky tu vua doc

}
///////////////////////////////

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
//  ss.listen();  //Accept just only 1 uart enable
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
