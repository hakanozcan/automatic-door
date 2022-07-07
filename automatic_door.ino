#include<Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,20,4);

char keys[4][3]={
 {'1','2','3'},
 {'4','5','6'},
 {'7','8','9'},
 {'*','0','#'}};
 
byte rowPin[4]={6,7,8,9};
byte colPin[3]={3,4,5};

String password = "123";  // Pin kodumuz
int position = 0;

int wrong = 0; // Hatalı giriş sayısını tutan değişkenimiz

int redPin = 10;
int greenPin = 11;
int buzzer = 12;
 
Keypad keypad=Keypad(makeKeymap(keys),rowPin,colPin,4,3);

int total = 0; // Hatalı giriş sayılarını konrol eden operatörümüz

void setup()
{
  
 pinMode(redPin,OUTPUT);
 pinMode(greenPin,OUTPUT);
 pinMode(buzzer, OUTPUT);
 
lcd.init(); //Lcd ekranı başlatma komutu
lcd.init();
lcd.backlight();
lcd.print("   HAKAN OZCAN   ");
lcd.setCursor(0,1);
lcd.print("   OTOMATIK   ");
lcd.setCursor(0,2);
lcd.print("     KAPI     ");
lcd.setCursor(0,3);
lcd.print("   SISTEMI   ");
delay(3000);
lcd.clear();
setLocked(true);
delay(20);
}

void loop()
{
  
  lcd.clear();
  lcd.print(" SIFRE GIRINIZ ");
  delay(100);
  
 char pressed=keypad.getKey();
 String key[3];
  
 if(pressed)
 {
  lcd.clear();
  lcd.print(" SIFRE GIRINIZ ");
  lcd.setCursor(position,2);
  lcd.print(pressed);
  delay(500);
    if(pressed == '*' || pressed == '#')
      {
          position = 0;
          setLocked(true);
          lcd.clear();
      }

    else if(pressed == password[position])
      {
          key[position]=pressed;
          position++;
      }
 
    else if (pressed != password[position] )
      {
          wrong++;
          position ++;
      }

    if(position == 3){
          if( wrong >0)
            {
                total++;
                wrong = 0;
                position = 0;
                lcd.clear();
                lcd.setCursor(0,2);
                lcd.print(" HATALI SIFRE ");
                delay(1000);
                setLocked(true);
            }

          else if(position == 3 && wrong == 0)
            {
                position = 0;
                wrong = 0;
                lcd.clear();
                lcd.setCursor(0,1);
                lcd.print("   KAPI ACILDI   ");
                lcd.setCursor(5,2);
                lcd.print("   HOSGELDINIZ   ");
                setLocked(false);
                delay(2000);
                lcd.clear();
                lcd.print(" KAPI 5 SANIYE ");
                lcd.setCursor(0,1);
                lcd.print(" SONRA KAPANACAK ");
                lcd.setCursor(0,2);
                delay(1000);
                lcd.clear();
                lcd.print(" KAPI 4 SANIYE ");
                lcd.setCursor(0,1);
                lcd.print(" SONRA KAPANACAK ");
                lcd.setCursor(0,2);
                delay(1000);
                lcd.clear();
                lcd.print(" KAPI 3 SANIYE ");
                lcd.setCursor(0,1);
                lcd.print(" SONRA KAPANACAK ");
                lcd.setCursor(0,2);
                delay(1000);
                lcd.clear();
                lcd.print(" KAPI 2 SANIYE ");
                lcd.setCursor(0,1);
                lcd.print(" SONRA KAPANACAK ");
                lcd.setCursor(0,2);
                delay(1000);
                lcd.clear();
                lcd.print(" KAPI 1 SANIYE ");
                lcd.setCursor(0,1);
                lcd.print(" SONRA KAPANACAK ");
                lcd.setCursor(0,2);
                delay(1000);
                lcd.clear();
                lcd.print(" KAPI KAPANDI ");
                setLocked(true);
                
            }

             if(total ==3)
            {
                total=0;
                buzzer_beep();
                delay(500);
            }

        }

   }

   
}

void setLocked(int locked)
  {
    if (locked)
      {
          digitalWrite(redPin, HIGH);
          digitalWrite(greenPin, LOW);
          delay(1000);
      }
    else
      {
          digitalWrite(redPin, LOW);
          digitalWrite(greenPin, HIGH);
          delay(1000);
      }
  }
void buzzer_beep()
{
   lcd.clear();
   lcd.setCursor(0,1);
   lcd.print(" HATALI SIFRE!!! ");
   lcd.setCursor(0,2);
   lcd.print(" ERISIM ENGELLENDI ");
    while(1)
   {
   digitalWrite(buzzer,HIGH);
   delay(1000);
   digitalWrite(buzzer,LOW);
   delay(1000);
   }
}
