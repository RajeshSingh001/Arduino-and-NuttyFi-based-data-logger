void setup() 
{
Serial.begin (9600);
}

void loop()
{
//  int TEMP=analogRead(A0);
//  int HUM=analogRead(A1);
//  int PRESS=analogRead(A2);
//  int ALT=analogRead(A3);
int TEMP=25;
int HUM=45;
int PRESS=26668;
int ALT=807;
  Serial.print('\r');
  Serial.print(TEMP);
  Serial.print('|');
  Serial.print(HUM);
  Serial.print('|');
  Serial.print(PRESS);
  Serial.print('|');
  Serial.print(ALT);
  Serial.print('\n');
  delay(3000);
}
