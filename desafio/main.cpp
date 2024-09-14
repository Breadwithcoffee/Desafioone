#include <iostream>

using namespace std;

// el codigo que lee los datos de la señal

/*
int analogPing = 0;
int val = 0;

void setup()
{
  Serial.begin(9600);
}
void loop()
{
  val = analogRead(analogPing);
  Serial.println(val);
}
*/
// C++ code
//
int analogPing = 0;
int val = 0;
int contadorarray = 0;
unsigned long segundosanterior = 0;
const long intervalos = 1000;
int maximo = 0;
int minimo = 0;
int array0[201];
int array1[201];
void picosfuncion(){
maximo = array0[0];
minimo = array0;[0]}
for (int i; i < 201;i++){
if(array0[i] > maximo) maximo = array0[i];
if (array0[i] < minimo) minim0 = array0[i];
}
}
void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long actualsegundos = millis();


  val = analogRead(analogPing);


  if (actualsegundos - segundosanterior >= intervalos) {
    segundosanterior = actualsegundos;


    if (contadorarray < 201) {
      array0[contadorarray] = val;
      contadorarray++;
      if (array0 = array1){
      picosfuncion();
      }
    }


    if (contadorarray == 201) {
      for (int i = 0; i < 201; i++) {
        array1[i] = array0[i];
        array0[i] = 0;
      }
      contadorarray = 0;
    }

    Serial.println(val);
  }
}
