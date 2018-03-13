#include <SoftwareSerial.h>
SoftwareSerial mySerial(8, 9);
unsigned long timer = 0;

String mensaje;
String numUsuario;
String mensajeSync;

int sync = 2;
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

  delay(100);
  mySerial.println("AT+CPBF=\"01\"");
}

void loop() {
  timer = millis();
  if(timer < 2000 && digitalRead(Datos)==HIGH && sync == 2){
    mySerial.println("AT+CMGF=1");
    digitalWrite(azul, HIGH);
    delay(500);
    digitalWrite(azul, LOW);
    mySerial.println("AT+CNMI=1,2,0,0,0");
    digitalWrite(rojo, HIGH);
    delay(500);
    digitalWrite(rojo, LOW);
    syncIn();
  }
  if(timer >= 2000 && sync != 1){sync = 0;}
  //--------------------------------------------------------------------------------------------------------------------------------------------
  if(mySerial.available()){
    mensaje = mySerial.readString();
    delay(100);
    if(sync==1 && mensaje.substring(2,7)=="+CMT:"){
      getData(mensaje);digitalWrite(verde, HIGH);delay(500);digitalWrite(rojo, LOW);}
    if(sync==2 && mensaje.substring(15,21)=="+CPBF:"){
      
        getNumber(mensaje);
        
      }
      
    delay(100);
  Serial.println(mensaje);
  Serial.println("---------------------");
  }
  //--------------------------------------------------------------------------------------------------------------------------------------------
   if (Serial.available()){            // Si la comunicacion serie normal tiene datos
    while(Serial.available()) {       // y mientras tenga datos que mostrar 
      mySerial.write(Serial.read());  // Los sacamos por la comunicacion SoftwareSerial
    } 
    mySerial.println();               // Enviamos un fin de linea
  }
  if(sync == 0){
    digitalWrite(azul, LOW);
    digitalWrite(rojo, LOW);
    digitalWrite(verde, LOW);
    
        // put your main code here, to run repeatedly:
    //SUBIR DATOS
    if(digitalRead(Datos)==HIGH)
    {
     EnviaSMS("001",numUsuario);
     //Evaluar();
      digitalWrite(azul, HIGH);
      delay(2000);
      
      digitalWrite(azul, LOW);
      }
      
      if(digitalRead(Eliminar)==HIGH)
    {
      EnviaSMS("002",numUsuario);
      Evaluar();
      digitalWrite(rojo, HIGH);
      delay(2000);
      digitalWrite(rojo, LOW);
      }
      
      if(digitalRead(Ubicacion)==HIGH)
    {
      EnviaSMS("003",numUsuario);
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
}

void EnviaSMS(String x,String num){
 mySerial.println("AT+CMGF=1"); 
 String sms="+52"+num;
 String smsNum="AT+CMGS=\""+sms+"\"";
 delay(100);                                
 mySerial.println(smsNum); 
 delay(100);                                    
 mySerial.print(x);                 
 delay(500);                                    
 mySerial.print(char(26));                       
 delay(100);                                    
 mySerial.println("");                          
 delay(100);                                    
}
//--------------------------------------------------------------------------------------------------------------------------------------------
void getData(String msj){
  String msj2 = msj.substring(9);
  int i = 1;
  while(msj2[i] != '"'){
    i++;
    }
  numUsuario = msj2.substring(0,i);
  for(int j = 0; j <= 3; j++){
      i++;
  while(msj2[i] != '"'){
      i++;
    }
    digitalWrite(azul, LOW);
    delay(100);
    digitalWrite(azul, HIGH);
    delay(100);
  }
  mensajeSync = msj2.substring(i+3,i+8);
  Serial.print(numUsuario);
  Serial.print(mensajeSync);
  Serial.println("0");
  EvaluarSMS(numUsuario,mensajeSync);
}
//--------------------------------------------------------------------------------------------------------------------------------------------
void syncIn(){
    sync = 1;
    digitalWrite(verde, HIGH);
    digitalWrite(azul, HIGH);
  }
  
void Evaluar(){
  if(mySerial.available()){         
  Serial.write(mySerial.read());   
} }

void EvaluarSMS(String numero,String mensaje){
  if(mensaje=="85E72")
  {
    mySerial.println("AT+CPBW=1,\"+52"+numero+"\",145,\"01\"");
    EnviaSMS("se ha sincronizado",numero);
    sync=0;
    
    }
    
  
}
void getNumber(String msj)
{
  String msj2 = msj.substring(28);
  int i = 1;
  while(msj2[i] != '"'){
    i++;
    }
  numUsuario = msj2.substring(0,i);
  Serial.println(msj2);
  Serial.println(numUsuario);
  
  
  }

