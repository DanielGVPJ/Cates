#include <SoftwareSerial.h>
SoftwareSerial mySerial(8, 9);
int rojo=4;
int azul=3;
int verde=2;
int Datos=5;
int Eliminar=6;
int Ubicacion=7;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);    
  pinMode(Datos,INPUT);
  pinMode(Eliminar,INPUT);
  pinMode(Ubicacion,INPUT);
  pinMode(rojo,OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(verde,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
//SUBIR DATOS
if(digitalRead(Datos)==HIGH)
{
 EnviaSMS("001");
 //Evaluar();
  digitalWrite(azul, HIGH);
  delay(2000);
  
  digitalWrite(azul, LOW);
  }
  
  if(digitalRead(Eliminar)==HIGH)
{
  EnviaSMS("002");
  Evaluar();
  digitalWrite(rojo, HIGH);
  delay(2000);
  digitalWrite(rojo, LOW);
  }
  
  if(digitalRead(Ubicacion)==HIGH)
{
  EnviaSMS("003");
  Evaluar();
  digitalWrite(verde, HIGH);
  delay(2000);
  digitalWrite(verde, LOW);
  }
  
  else {
    digitalWrite(verde, LOW);
    digitalWrite(rojo, LOW);
    digitalWrite(azul, LOW);
    }
}
void EnviaSMS(String x){              
 mySerial.println("AT+CMGF=1");                 
 delay(100);                                
 mySerial.println("AT+CMGS=\"+527851005817\""); 
 delay(100);                                    
 mySerial.print(x);                 
 delay(500);                                    
 mySerial.print(char(26));                       
 delay(100);                                    
 mySerial.println("");                          
 delay(100);                                    
}
void Evaluar(){
  if(mySerial.available()){         
  Serial.write(mySerial.read());   
} 
  
}

