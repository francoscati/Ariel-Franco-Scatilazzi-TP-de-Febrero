#include <LiquidCrystal.h>

#include <Servo.h>

#define pir 12

#define TRIG 11
#define ECHO 10

Servo serbo;

LiquidCrystal lcd(2,3,5,4,6,7);

int falta=0;
int vuelto=0;
int pago=0;

float duracion;
int distancia;

String text="";

void setup()
{
  pinMode (pir, INPUT);
  pinMode(TRIG , OUTPUT);
  pinMode(ECHO , INPUT);
  lcd.begin(16,2);
  serbo.attach(9);
  serbo.write(90);
  Serial.begin(9600);
}

  	
 
void loop()
{
  
  
  if (digitalRead(pir)==HIGH)
  {
    lcd.setCursor(0,0);
    lcd.print("El monto a pagar");
    lcd.setCursor(5,2);
    lcd.print("Es: 50$");
  
    falta=0;
    vuelto=0;
    pago=0;
    do{
    	Serial.println("Ingrese monto a pagar:");
   		text="";//esto es para que no tenga nada 
    	while(text.length()==0){
          text=Serial.readString();
      	}
    	pago = pago + text.toInt();
      	if(pago<50){
          	lcd.clear();
            falta=50-pago;
            lcd.setCursor(0,0);
      		lcd.print("te falta pagar:");
            lcd.setCursor(5,3);
            lcd.print(falta);
            lcd.print("$");
      	}
      	if(pago>50){
        	lcd.clear();
          	lcd.setCursor(0,0); 
          	lcd.print("su vuelto es: ");
          	lcd.setCursor(5,3);
        	lcd.print((pago-50));
          	lcd.print("$");
      		pago=50;// esto es para que salga del ciclo
          	delay(2000);
      	}
     
    }while(pago!=50);
    
  	Serial.println("Buen viaje");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Buen viaje");
    
    //sensor de distancia dentro del sensor estara lo del servo 
    
    serbo.write(0);
    do{
      digitalWrite( TRIG, LOW );
      delayMicroseconds (4);
      digitalWrite( TRIG, HIGH);
      delayMicroseconds (10);
      digitalWrite( TRIG, LOW );

      duracion = pulseIn(ECHO , HIGH);
      distancia = duracion * 10 / 292 / 2;
      
    }while(distancia<300);
    
  
    //los 20s
    delay(9000);
  }
  serbo.write(90);
}
