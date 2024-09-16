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




// RASTREO Y MONITOREO DE LOS VALORES PRIMRE Y SEGUNDO SEGUNDO.


int analogPin = 0;
int val = 0;
int *primersegundo = nullptr;
int *arraymomentaneo = nullptr;
int *ultimosegundo = nullptr;
int sizeprimer = 0; int sizearraymomentaneo = 0; int sizeultimo = 0;
unsigned long tiempoanterior = 0;
unsigned long intervalo = 1000;
// Pulsadore
const int botoninicioPin = 2;
const int botondetenerPin = 3;

bool adquiriendodatos = false;

void setup(){
    Serial.begin(9600);
    pinMode(botoninicioPin , INPUT_PULLUP);
    pinMode(botondetenerPin , INPUT_PULLUP);
}

// se tenia una idea que fue modificada ya que aveces el monitor serial no lee los ceros , la idea era leer los ceros de los array para asi contar
// su frecuencia

/*int ceros(int *array, int size) {
  int contador = 0;
  bool encero = false;

  for (int i = 0; i < size; i++) {
    if (array[i] >= -3 && array[i] <= 3) {
      if (!encero) {
        contador++;
        encero = true;
      }
    } else {
      encero= false;
    }
  }

  return contador;
}*/

// Ahora la mejor opcion es contar cada cuanto los valores pasan de negativo a positivos y vicecersa.

int cambiodesigno(int *array , int size){
    int contador = 0;
    if(size < 2){
        return contador;
    }
    for(int i = 0; i < size - 1; i++){
        if((array[i] < 0 && array[i+1] >= 0) || (array[i] >= 0 && array[i+1] < 0)){
            contador++;
        }
    }
    return contador;
}

void loop(){
    unsigned long tiempoactual = millis();
    bool begin = digitalRead(botoninicioPin) == LOW;
    bool done = digitalRead(botondetenerPin) == LOW;

    if(begin){
        adquiriendodatos = true;
    }
    if (done){
        adquiriendodatos = false;
    }

 if (adquiriendodatos){
    val = analogRead(analogPin);
    if(tiempoactual - tiempoanterior >= intervalo){

        if(sizeprimer > 0){
            int maximoprimer = primersegundo[0];
            for(int i = 1; i < sizeprimer; i++){
                if(primersegundo[i] > maximoprimer){
                    maximoprimer = primersegundo[i];
                }
            }
            Serial.print("pico del primer segundo ");
            Serial.println(maximoprimer);

            int crucesdesigno = cambiodesigno(primersegundo, sizeprimer);
            Serial.print("numero de ceros ");
            Serial.println(crucesdesigno);
        }


        if(sizearraymomentaneo > 0){
            delete[] ultimosegundo;
            ultimosegundo = new int[sizearraymomentaneo];
            for(int i = 0; i < sizearraymomentaneo; i++){
                ultimosegundo[i] = arraymomentaneo[i];
            }
            sizeultimo = sizearraymomentaneo;
        }


        if(sizeultimo > 0){
            int maximoultimo = ultimosegundo[0];
            for(int i = 1; i < sizeultimo; i++){
                if(ultimosegundo[i] > maximoultimo){
                    maximoultimo = ultimosegundo[i];
                }
            }
            Serial.print("pico del ultimo segundo ");
            Serial.println(maximoultimo);
        }


        delete[] arraymomentaneo;
        arraymomentaneo = new int[sizeprimer];
        for(int i = 0; i < sizeprimer; i++){
            arraymomentaneo[i] = primersegundo[i];
        }
        sizearraymomentaneo = sizeprimer;


        delete[] primersegundo;
        primersegundo = new int[1];
        primersegundo[0] = val;
        sizeprimer = 1;


        tiempoanterior = tiempoactual;
    } else {

        int *nuevoarray = new int[sizeprimer + 1];
        for(int i = 0; i < sizeprimer; i++){
            nuevoarray[i] = primersegundo[i];
        }
        nuevoarray[sizeprimer] = val;

        delete[] primersegundo;
        primersegundo = nuevoarray;
        sizeprimer++;

        Serial.print("valor: ");
        Serial.println(val);
    }
}
}
