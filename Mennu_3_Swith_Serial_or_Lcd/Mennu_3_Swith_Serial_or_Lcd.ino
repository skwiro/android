#include <LiquidCrystal.h>
LiquidCrystal lcd(8,9,4,5,6,7);
char *k0="Akt.Temp. = ";
char *k1=" <> Temp. = ";
char *k2=" C";
char *k3=" Ustawiono!";
int temp=20;
// --------------------------------------------------------------------------------
void setup()
{
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(11,INPUT_PULLUP);
  Serial.begin(9600);
  lcd.begin(16,2);
}
// ---------------------------------------------------------------------------------
int getButton(int bG, int bD, int oK)
{
  if(digitalRead(bG)==LOW){delay(30);if(digitalRead(bG)==LOW)return 2;}
  if(digitalRead(bD)==LOW){delay(30);if(digitalRead(bD)==LOW)return 8;}
  if(digitalRead(oK)==LOW){delay(30);if(digitalRead(oK)==LOW)return 5;}
  return -1;
}
// ---------------------------------------------------------------------------------
void ekran(char *kL, int v ,char *kP="",int wiersz=1)
{
  if(wiersz>=0)
    {
    lcd.setCursor(0,wiersz);lcd.print(" ");
    lcd.setCursor(0,wiersz);lcd.print(kL);lcd.print(v);lcd.print(kP);
    }
    else {Serial.print(kL);Serial.print(v);Serial.println(kP);}
}
// ---------------------------------------------------------------------------------
void ekran(char *kK,int wiersz=1)
{
  if(wiersz>=0)
    {
    lcd.setCursor(0,wiersz);lcd.print(" ");
    lcd.setCursor(0,wiersz);lcd.print(kK);
    }
    else Serial.print(kK);
}    
// ---------------------------------------------------------------------------------
int nastawy(int v, int vmin, int vmax)
{
  ekran(k0,v,k2);
  int zm=-1;
  int x=-1;
  while(x!=5)
    {
    x=getButton(2,3,11);
    if(x!=zm)
      {
      switch(x)
        {
        case 2: v++;if(v>vmax)v=vmax;ekran(k1,v,k2);break;
        case 8: v--;if(v<vmin)v=vmin;ekran(k1,v,k2);break;
        case 5: ekran(k3);delay(2000);ekran("");return v;break;
        }
      }
     zm=x; 
    }
}
// ---------------------------------------------------------------------------------
void loop()
{
lcd.setCursor(0,0);lcd.print("< USTAWIENIA >");
temp=nastawy(temp,0,40);
//delay(2000);
}
