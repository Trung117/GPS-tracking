#include <Wire.h> //Thư viện giao tiếp I2C
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
TinyGPSPlus gps;
SoftwareSerial ss(3, 4); // RX,TX --- Ard's RX to GPS's TX
SoftwareSerial mySerial(5, 6); //SIM800L Tx & Rx is connected to Arduino #3 & #2

int solangoitinnhan=1000;
boolean sendonce = false;
const int MPU_addr=0x68;  //Địa chỉ I2C của MPU6050
int16_t AcX,AcY,AcZ,Ms,GyX,GyY,GyZ; //Các 

void sent_data(String datasent)
{
  
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+84918258213\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print(datasent); //text content
  updateSerial();
  mySerial.write(26);
  ss.listen();
}
void setup()
{
  Wire.begin();
  Wire.beginTransmission(MPU_addr); //Gửi tín hiệu đến địa chỉ MPU
  Wire.write(0x6B);  
  Wire.write(0);     //Đưa về 0 để bật MPU
  Wire.endTransmission(true); 
  Serial.begin(9600);
    mySerial.begin(9600);
    ss.begin(9600);
    ss.listen();
    solangoitinnhan=3;
}

void loop()
{
  Wire.beginTransmission(MPU_addr); //Gửi tín hiệu đến địa chỉ MPU
  Wire.write(0x3B);                 //Gửi giá trị lên MPU
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  //Đề nghị thanh ghi của MPU
  //Đọc dữ liệu
  AcZ=Wire.read()<<8|Wire.read();  //Gia tốc trục z
  if(AcZ < 0 )
  {
    Serial.println("Dang trang thai nga");
  if(solangoitinnhan>0)
  {

    while(sendonce == false)
    {
      while (ss.available() > 0){
      gps.encode(ss.read());
    if (gps.location.isUpdated()){
       sendonce = true;
       // Lay toa do va chuyen sang dang String
       char Templat[12],TempLon[12];
       dtostrf(gps.location.lat(),2,6,Templat); // Lay toa do va luu vao bien lat
       dtostrf(gps.location.lng(),3,6,TempLon); // Lay toa do va luu vao bien long

       String tmp ="";
        // Chuyen doi ki tu cua toa do LAT sang String
       for(int i = 0 ; i<10;i++)
        tmp += (String)(Templat[i]);

        // Ky tu phan biet lat va long
        tmp +=",";

        // Chuyen doi ki tu cua toa do LONG sang String
        for(int i = 0 ; i<10;i++)
        tmp += (String)(TempLon[i]);

        delay(500);
        mySerial.listen();

        delay(500);
        sent_data(tmp);
        Serial.println("Da gui toa do");
        Serial.println(tmp);
       //sent_data(tmp)
       //mySerial.listen();
    }
    
  }
    }
    sendonce = false;
    //sent_data("vat the bi nga");

    


    
    delay(5000);
    solangoitinnhan--;
  }
  
  
  }else
  {
    // Serial.println("Dang trang thai binh thuong");
  }
  //delay(333); //Chờ (1/3)s
}
void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
