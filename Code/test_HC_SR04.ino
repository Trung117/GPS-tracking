const int trig=8;
const int echo=7;
void setup()
{
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  }

void loop()
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
  Serial.print(distance);
  Serial.println("cm");
  delay(200);
  }
