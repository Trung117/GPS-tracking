const String myphone = "0919******"; 
#define Fan 2
#define Light 3
#define TV 4
int temp=0,i=0;
int led=13;
char str[15];
int ttLight=0; 
void Gsm_Init();
void setup()
{
  Serial.begin(9600);
  delay(50);
  pinMode(led, OUTPUT);
  pinMode(Fan, OUTPUT);
  pinMode(Light, OUTPUT);
  pinMode(TV, OUTPUT);
  digitalWrite(Light, HIGH);
  digitalWrite(Fan, HIGH);
  digitalWrite(TV, HIGH);
  Gsm_Init();
}
void loop()
{
  if(temp==1)
  {
    check();
    temp=0;
    i=0;
    delay(1000);
  }
}
void serialEvent() 
{
  while(Serial.available()) 
  {
    if(Serial.find("#A."))
    {
      digitalWrite(led, HIGH);
      delay(1000);
      digitalWrite(led, LOW);
      while (Serial.available()) 
      {
      char inChar=Serial.read();
      str[i++]=inChar;
      if(inChar=='*')
      {
        temp=1;
        return;
      } 
      } 
    }
   }
 }
void check()
{
   if(!(strncmp(str,"tv on",5)))
    {
      digitalWrite(TV, LOW);
      //Serial.println("TV on");
      delay(200);
    }  
   
   else if(!(strncmp(str,"tv off",6)))
    {
      digitalWrite(TV, HIGH);
      //Serial.println("TV off");
      delay(200);
    }
  
    else if(!(strncmp(str,"fan on",6)))
    {
      digitalWrite(Fan, LOW);
      //Serial.println("Fan on");
      delay(200);
    }
 
    else if(!(strncmp(str,"fan off",7)))
    {
      digitalWrite(Fan, HIGH);
      //Serial.println("Fan off");
      delay(200);
    }     
 
    else if(!(strncmp(str,"light on",8)))
    {
      digitalWrite(Light, LOW);
      //Serial.println("Light on");
      ttLight=1;
      delay(200);
    }
 
    else if(!(strncmp(str,"light off",9)))
    {
      digitalWrite(Light, HIGH);
      //Serial.println("Light off");
      ttLight=0;
      delay(200);
    } 
    else if(!(strncmp(str,"all on",6)))
    {
      digitalWrite(Light, LOW);
      digitalWrite(Fan, LOW);
      digitalWrite(TV, LOW);
      delay(200);
    }
 
    else if(!(strncmp(str,"all off",7)))
    {
      digitalWrite(Light, HIGH);
      digitalWrite(Fan, HIGH);
      digitalWrite(TV, HIGH);
      delay(200);
    }    
}
void Gsm_Init()
{
  Serial.println("ATE0");                     // Tat che do phan hoi (Echo mode)
  delay(2000);
  Serial.println("AT+IPR=9600");              // Dat toc do truyen nhan du lieu 9600 bps
  delay(2000);
  Serial.println("AT+CMGF=1");                // Chon che do TEXT Mode
  delay(2000);
  Serial.println("AT+CLIP=1");                // Hien thi thong tin nguoi goi den
  delay(2000);
  Serial.println("AT+CNMI=2,2,0,0,0");        // Hien thi truc tiep noi dung tin nhan
  delay(2000);
}

