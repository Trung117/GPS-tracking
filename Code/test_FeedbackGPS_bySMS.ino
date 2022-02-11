#include <SoftwareSerial.h> //gia lap TX RX 
SoftwareSerial mySerial(9, 10);   //SIM 800A

//thuvien_GPS
#include <TinyGPS++.h>
TinyGPSPlus gps;
SoftwareSerial ss(4, 3);  //GPS

boolean sendonce = false;  //important


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
  Serial.begin(9600);
  mySerial.begin(9600);
  ss.begin(9600);
  ss.listen();


}

void loop()
{

  if (Serial.available() > 0)
    switch (Serial.read())
    {
      case 's':
        //
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

        //
        break;
    }
  if (mySerial.available() > 0)
    Serial.write(mySerial.read()); // mySerial.read => xoa ky tu vua doc


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
