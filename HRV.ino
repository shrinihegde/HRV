#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,6,5,4,3);

#define  THRASHOLD_VALUE    600
 int data=A1;
 int ECG = A0;
 char mystr[20];
 const int Buzzer =2;
 int count=0;
unsigned long temp=0;
String one = "VEHICLE LOCATION AT:https://www.google.com/maps/?q=12.8812,77.4444";
 
void setup() 
{
Serial.begin(9600);
Serial1.begin(9600);
lcd.begin(16,2);
pinMode(data,INPUT);
pinMode(ECG,INPUT);
pinMode(Buzzer,OUTPUT);
digitalWrite(Buzzer,LOW);
lcd.setCursor(0,0);
lcd.print("HEALTH MONITORING");
lcd.setCursor(4,1);
lcd.print("System");
delay(3000);
lcd.clear();
}
void loop() 
{
 lcd.setCursor(0,0);
lcd.print("HEALTH CONDITION:");
HeartBeat ();
 ECG_condition();
 delay(1000);
 lcd.clear();
}


  void HeartBeat()
{
  count=0;
temp=millis();
      
      while(millis()<(temp+10000))
      {
        if(analogRead(data)<100)
        {
            count=count+1;
//Serial.println(count);
            
            while(analogRead(data)<100);
           
        }
      }
      count=count*6;
       lcd.setCursor(0,1);
      lcd.print("BPM:");
      lcd.setCursor(4,1);
      lcd.print(count);
     if(count<50)
      {
       // Serial.begin(9600);
        Serial.write('H');
        digitalWrite(Buzzer,HIGH);
        delay(2000);
        digitalWrite(Buzzer,LOW);
    //    Serial.end();
        delay(2000);
       // Serial1.begin(9600);
        SendSms("9008873470","LOW BP AND PERSON LOCATION AT:https://www.google.com/maps/?q=12.8999,77.4958");
       // Serial1.end();
        }
//Serial.println(count);
      temp=0;
      count=0;
    delay(1000);
}

  void ECG_condition()
  {
    int ECG_read= analogRead(A1);
//    Serial.print("ECG_read:");
//    Serial.print(ECG_read);
   
      //  lcd.clear();
      lcd.setCursor(7,1);
      lcd.print("ECG:");
      lcd.setCursor(11,1);
      lcd.print(ECG_read);
      delay(1000);
      //lcd.clear();
   if(ECG_read >THRASHOLD_VALUE)
   {
  //  Serial.begin(9600);
            Serial.write('G');
        digitalWrite(Buzzer,HIGH);
        delay(2000);
        digitalWrite(Buzzer,LOW);
      //  Serial.end();
        delay(500);
        //
        SendSms("9008873470","CRITICAL CONDITION AND PERSON LOCATION AT:https://www.google.com/maps/?q=12.8999,77.4958");
        //Serial1.end();
    
    }
       if(ECG_read <10)
   {
  //  Serial.begin(9600);
            Serial.write('I');
        digitalWrite(Buzzer,HIGH);
        delay(2000);
        digitalWrite(Buzzer,LOW);
      //  Serial.end();
        delay(500);
        //
    SendSms("9008873470","CRITICAL CONDITION AND PERSON LOCATION AT:https://www.google.com/maps/?q=12.8999,77.4958");
        //Serial1.end();
    
    }
    delay(2000);
    // lcd.clear();
    }
  void SendSms( char *num1, char * str1 )
{
    char buff[10],i=0;
    Serial1.write('A');
    delay(100);
    Serial1.write('T');
    delay(100);
    Serial1.write('E');
    delay(100);
    Serial1.write('0');
    delay(100);
    Serial1.write('\r');
    
    //*****************************************
    Serial1.write("AT+CMGF=1\n\r"); //Initialize GSM For mobile
    delay(2000);
    Serial1.write("AT+CMGS=\"");
    delay(2000);
    Serial1.write(num1);
    delay(2000);
    Serial1.write("\"\r");
    Serial1.write(str1);
    delay(2000);
    Serial1.write(26);
    delay(2000);
    Serial.print("sms sent");

}
