#include "StringSplitter.h"

String msj = "+CMT: \"2321493825,\"\",\"18/02/23,13:42:12-24\"Puto el que lo lea";

  StringSplitter *splitter = new StringSplitter(msj, ',', 4);
  int itemCount = splitter->getItemCount();
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  String msj2 = msj.substring(6);
  int i = 1;
  while(msj2[i] != '"'){
    i++;
    }
  Serial.println(msj2.substring(1,i-1));
  for(int j = 0; j <= 3; j++){
  while(msj2[i] != '"'){
      i++;
    }
      i++;
  }
  Serial.println(msj2.substring(i));
}
