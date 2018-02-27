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
}

void loop() {
  timer = millis();
  if(timer < 2000 && digitalRead(Datos)==HIGH && sync == 2){
    syncIn();
  }
  if(timer >= 2000 && sync != 1){sync = 0;}
  //--------------------------------------------------------------------------------------------------------------------------------------------
  if(mySerial.available()){
    //Serial.println("avai");
    //mensaje = mySerial.readString();
    //if(sync == 1 && mensaje[4] == ':'){getData(mensaje);}
  Serial.write(mySerial.read());
  }
  //--------------------------------------------------------------------------------------------------------------------------------------------
   if (Serial.available()){            // Si la comunicacion serie normal tiene datos
    while(Serial.available()) {       // y mientras tenga datos que mostrar 
      mySerial.write(Serial.read());  // Los sacamos por la comunicacion SoftwareSerial
    } 
    mySerial.println();               // Enviamos un fin de linea
  }
  
  if(sync == 0){
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
//--------------------------------------------------------------------------------------------------------------------------------------------
void getData(String msj){
  String msj2 = msj.substring(6);
  int i = 1;
  while(msj2[i] != '"'){
    i++;
    }
  numUsuario = msj2.substring(1,i-1);
  for(int j = 0; j <= 3; j++){
  while(msj2[i] != '"'){
      i++;
    }
      i++;
  }
  mensajeSync = msj2.substring(i);
  Serial.println(numUsuario);
  Serial.println(mensajeSync);
}
//--------------------------------------------------------------------------------------------------------------------------------------------
void syncIn(){
    mySerial.println("AT+CMGF=1");
    delay(100);
    mySerial.println("AT+CNMI=1,2,0,0,0");
    sync = 1;
    digitalWrite(verde, HIGH);
    digitalWrite(azul, HIGH);
  }
  
void Evaluar(){
  if(mySerial.available()){         
  Serial.write(mySerial.read());   
} 
  
}

