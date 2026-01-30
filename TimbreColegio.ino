#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27,16,2); // LCD 16x2
RTC_DS1307 RTC;                   // RTC
const int ledTimbre = 7;          // LED que funciona como timbre
int segundo;
int minuto;
int hora;


const int botonHorasPin = 2; // botón de horas
const int botonMinutosPin = 3; // botón de minutos



// Horario 1
int h1 = 7;   int m1 = 0;    int s1 = 0;
int h2 = 8;   int m2 = 10;  
int h3 = 9;   int m3 = 50;  
int h4 = 10;  
int h5 = 11;  
int h6 = 13;
int h7 = 14;
int h8 = 15;  
int h9 = 16;
int h10 = 17;
int h11 = 18;

void setup () {

 pinMode(ledTimbre, OUTPUT);                  
 Wire.begin();                              
 RTC.begin();       


 // ajustar manualmente la fecha y hora (año, mes, día, hora, minuto, segundo)
 //RTC.adjust(DateTime(2024, 10, 31, 15, 3, 0));  // borrar el comentario en caso de que se quiera configurar el RTC
 
 Serial.begin(9600);                         
 lcd.init();
 lcd.backlight();                            
 lcd.clear();                                
pinMode(botonHorasPin, INPUT_PULLUP); // 
pinMode(botonMinutosPin, INPUT_PULLUP); // 
}


void loop(){
 DateTime now = RTC.now();


 Serial.print(now.year(), DEC);  // año
 Serial.print('/');
 Serial.print(now.month(), DEC); // mes
 Serial.print('/');
 Serial.print(now.day(), DEC);   // día
 Serial.print(' ');
 Serial.print(now.hour(), DEC);  // horas
 Serial.print(':');
 Serial.print(now.minute(), DEC); // minutos
 Serial.print(':');
 Serial.print(now.second(), DEC); // segundos
 Serial.println();
 lcd.setCursor(0,0);
 lcd.print("D:");
 lcd.print(now.year(), DEC);
 lcd.print("/");
 lcd.print(now.month(), DEC);
 lcd.print("/");
 lcd.print(now.day(), DEC);
 lcd.print(" ");
 lcd.setCursor(0,1);
 lcd.print("T: ");
 lcd.print(now.hour(), DEC);
 lcd.print(":");
 lcd.print(now.minute(), DEC);
 lcd.print(":");
 lcd.print(now.second(), DEC);
 segundo=now.second();
 minuto=now.minute();
 hora=now.hour();


 int r_diaSemana = dia_de_semana();
 
 horario_2();


 digitalWrite(ledTimbre, LOW);    
 delay(500);                       
 lcd.setCursor(9,0);      
 lcd.print("        ");
 lcd.setCursor(8,1);
 lcd.print("        ");
   if (digitalRead(botonHorasPin) == LOW) {
    now = RTC.now();  
    DateTime newTime(now.unixtime() + 3600);
    RTC.adjust(newTime);
    }


if (digitalRead(botonMinutosPin) == LOW) {
      now = RTC.now();
    DateTime newTime(now.unixtime() + 60);
    RTC.adjust(newTime);
}


}


// activa el LED (timbre)
void activar_timbre(){
    digitalWrite(ledTimbre, HIGH);
    lcd.setCursor(0,0);
    lcd.print("Timbre ON  ");
    Serial.println("Timbre Activo");
    delay(3000);
}


// calcular el día de la Semana
int dia_de_semana(){
 int n_dia;
 int r_dia;
 int n_mes;
 int t_mes;
 int n_anno;
 int d_anno;
 int t_siglo = 6;


 DateTime now = RTC.now();
 lcd.setCursor(13,1);


 n_anno = (now.year() - 2000);
 d_anno = n_anno / 4;
 n_dia = now.day();
 n_mes = now.month();


 switch (n_mes) {
    case 1:
      t_mes = 0;
      break;
    case 2:
      t_mes = 3;
      break;
    case 3:
      t_mes = 3;
      break;
    case 4:
      t_mes = 6;
      break;
    case 5:
      t_mes = 1;
      break;
    case 6:
      t_mes = 4;
      break;
    case 7:
      t_mes = 6;
      break;
    case 8:
      t_mes = 2;
      break;
    case 9:
      t_mes = 5;
      break;
    case 10:
      t_mes = 0;
      break;
    case 11:
      t_mes = 3;
      break;
    case 12:
      t_mes = 5;
      break;
    default:
      t_mes = t_mes;
    break;
 }


 r_dia = n_dia + t_mes + n_anno + d_anno + t_siglo;
 r_dia = r_dia % 7;


 switch (r_dia) {
    case 1:
       lcd.print("Lun");
        Serial.print(" Lun ");
      break;
      case 2:
       lcd.print("Mar");
       Serial.println(" Mar ");
      break;
      case 3:
       lcd.print("Mie");
       Serial.print(" Mie ");
      break;
      case 4:
       lcd.print("Jue");
       Serial.print(" Jue ");
      break;
      case 5:
       lcd.print("Vie");
       Serial.print(" Vie ");
      break;
      case 6:
       lcd.print("Sab");
       Serial.print(" Sab ");
      break;
      case 0:
       lcd.print("Dom");
       Serial.print(" Dom ");
      break;
      default:
       lcd.print("---");
       Serial.print(" ---");
      break;
 }
 return r_dia;
}


void horario_2(){
   lcd.setCursor(14,0);
   lcd.print("");
   Serial.print("Horario");
   if ((hora==h1) && (minuto==m1) && (segundo==s1))  activar_timbre();
   if ((hora==h1) && (minuto==m3) && (segundo==s1))  activar_timbre();
   if ((hora==h2) && (minuto==m1) && (segundo==s1))  activar_timbre();
   if ((hora==h2) && (minuto==m3) && (segundo==s1))  activar_timbre();
   if ((hora==h3) && (minuto==m1) && (segundo==s1))  activar_timbre();
   if ((hora==h3) && (minuto==m3) && (segundo==s1))  activar_timbre();
   if ((hora==h4) && (minuto==m1) && (segundo==s1))  activar_timbre();
   if ((hora==h5) && (minuto==m1) && (segundo==s1))  activar_timbre();
   if ((hora==h5) && (minuto==m2) && (segundo==s1))  activar_timbre();
   if ((hora==h5) && (minuto==m3) && (segundo==s1))  activar_timbre();
   
   if ((hora==h6) && (minuto==m1) && (segundo==s1))  activar_timbre();
   if ((hora==h6) && (minuto==m3) && (segundo==s1))  activar_timbre();
   if ((hora==h7) && (minuto==m1) && (segundo==s1))  activar_timbre();
   if ((hora==h7) && (minuto==m3) && (segundo==s1))  activar_timbre();
   if ((hora==h8) && (minuto==m1) && (segundo==s1))  activar_timbre();
   if ((hora==h8) && (minuto==m3) && (segundo==s1))  activar_timbre();
   if ((hora==h9) && (minuto==m1) && (segundo==s1))  activar_timbre();
   if ((hora==h10) && (minuto==m1) && (segundo==s1))  activar_timbre();
   if ((hora==h10) && (minuto==m2) && (segundo==s1))  activar_timbre();
   if ((hora==h11) && (minuto==m1) && (segundo==s1))  activar_timbre();
}
