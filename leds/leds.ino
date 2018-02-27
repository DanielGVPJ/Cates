#include <SoftwareSerial.h>
SoftwareSerial mySerial(8, 9);
int rojo=4;
int azul=3;
int verde=2;
int Datos=5;
int Eliminar=6;
int Ubicacion=7;
String cadena[4];

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
  Serial.print("1");
  delay(2000);
  
  digitalWrite(azul, LOW);
  }
  
  if(digitalRead(Eliminar)==HIGH)
{
  EnviaSMS("002");
  Evaluar();
  digitalWrite(rojo, HIGH);
  Serial.print("2");
  delay(2000);
  digitalWrite(rojo, LOW);
  }
  
  if(digitalRead(Ubicacion)==HIGH)
{
  EnviaSMS("003");
  Evaluar();
  digitalWrite(verde, HIGH);
  Serial.print("3");
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
 cadena[0]=mySerial.read();
 mySerial.println("AT+CMGS=\"+527851005817\"");
 delay(100);                        
 cadena[1]=mySerial.readString();
 mySerial.print(x);
 delay(500);
 cadena[2]=mySerial.read();
 mySerial.print(char(26));
 delay(100);
 cadena[3]=mySerial.read();       
 mySerial.println("");
 delay(100);              
 Serial.print(cadena[3]);            
}
void Evaluar(){
  if(mySerial.available()){         
  Serial.write(mySerial.read());   
} 
  
}

