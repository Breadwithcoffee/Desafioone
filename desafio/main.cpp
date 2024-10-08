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

#include <Adafruit_LiquidCrystal.h>
int segundos = 0;
Adafruit_LiquidCrystal lcd_1(0);
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
    lcd_1.begin(16, 2);

    lcd_1.print("Iniciando....");
    delay(3000);
    lcd_1.clear();
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
            lcd_1.begin(16, 2);
            lcd_1.print("pico del primer segundo");
            lcd_1.setCursor(0, 1);
            lcd_1.print(maximoprimer);


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


// se ha corregido todo el pasado debido a errores, el primer error es que cuando me imprime en el lcd deja de adquirir datos, el segundo es
// por optimizacion ya que en realidad no necesitamos el primer segundo solo nos interesa el segundo antes de detener la ejecucion.
// me estoy basando en una radio.


int analogPin = 0;
int val = 0;
int *arraymomentaneo = nullptr;
int *ultimosegundo = nullptr;
int sizearraymomentaneo = 0;
int sizeultimo = 0;
float a = 0;

unsigned long tiempoanterior = 0;
unsigned long intervalo = 1000;

const int botoninicioPin = 2;
const int botondetenerPin = 3;

bool adquiriendodatos = false;

void setup() {
    Serial.begin(9600);
    pinMode(botoninicioPin, INPUT_PULLUP);
    pinMode(botondetenerPin, INPUT_PULLUP);

    lcd_1.begin(16, 2);
    lcd_1.print("encendiendo....");
    delay(2000);
    lcd_1.clear();
}
int cambiodesigno(int *array, int size) {
    int contador = 0;
    if (size < 2) {
        return contador;
    }
    for (int i = 0; i < size - 1; i++) {
        if ((array[i] < 0 && array[i + 1] >= 0) || (array[i] >= 0 && array[i + 1] < 0)) {
            contador++;
        }
    }
    return contador;
}

void loop() {
    unsigned long tiempoactual = millis();
    bool begin = digitalRead(botoninicioPin) == LOW;
    bool done = digitalRead(botondetenerPin) == LOW;
    val = analogRead(analogPin);

    if (begin) {
        adquiriendodatos = true;
    }
    if (done) {
        adquiriendodatos = false;


        if (sizeultimo > 0) {
            int maximoultimo = ultimosegundo[0];
            for (int i = 1; i < sizeultimo; i++) {
                if (ultimosegundo[i] > maximoultimo) {
                    maximoultimo = ultimosegundo[i];
                }
            }
            Serial.print("pico del ultimo segundo: ");
            Serial.println(maximoultimo);
            a = maximoultimo;
            a = a/100;
            lcd_1.clear();
            lcd_1.print("amplitud: ");
            lcd_1.setCursor(0, 1);
            lcd_1.print(a);
            lcd_1.print(" V");
        }
    }

    if (adquiriendodatos) {
        if (tiempoactual - tiempoanterior >= intervalo) {


            if (sizearraymomentaneo > 0) {
                delete[] ultimosegundo;
                ultimosegundo = new int[sizearraymomentaneo];
                for (int i = 0; i < sizearraymomentaneo; i++) {
                    ultimosegundo[i] = arraymomentaneo[i];
                }
                sizeultimo = sizearraymomentaneo;
            }

            delete[] arraymomentaneo;
            arraymomentaneo = new int[1];
            arraymomentaneo[0] = val;
            sizearraymomentaneo = 1;

            tiempoanterior = tiempoactual;

        } else {

            int *nuevoarray = new int[sizearraymomentaneo + 1];
            for (int i = 0; i < sizearraymomentaneo; i++) {
                nuevoarray[i] = arraymomentaneo[i];
            }
            nuevoarray[sizearraymomentaneo] = val;

            delete[] arraymomentaneo;
            arraymomentaneo = nuevoarray;
            sizearraymomentaneo++;

            Serial.print("valor: ");
            Serial.println(val);
        }
    }
}

// ahora solo miramos el ultimo segundo y  los valores aparecen al final de presionar el otro boton.


// cambios como despues de detener que me lea durante otros 3 segundos para estar seguros del cambio
// mas sugerencias en el lcd
#include <Adafruit_LiquidCrystal.h>
int tri = 0;
int soc = 0;
int analogPin = 0;
int val = 0;
int *arraymomentaneo = nullptr;
int *ultimosegundo = nullptr;
int sizearraymomentaneo = 0;
int sizeultimo = 0;
float a = 0;
int frecuencia = 0;
Adafruit_LiquidCrystal lcd_1(0);

unsigned long tiempoanterior = 0;
unsigned long intervalo = 1000;

const int botoninicioPin = 2;
const int botondetenerPin = 3;

bool adquiriendodatos = false;

void setup() {
    Serial.begin(9600);
    pinMode(botoninicioPin, INPUT_PULLUP);
    pinMode(botondetenerPin, INPUT_PULLUP);

    lcd_1.begin(16, 2);
    lcd_1.print("encendiendo....");
    delay(2000);
    lcd_1.clear();
}

int* valoresmayores(int* array, int size) {
    const int sizemax = 100;
    int* mayores = new int[sizemax];
    int count = 0;

    if (size == 0) {
        delete[] mayores;
        return nullptr;
    }

    int mayoractual = array[0];
    if (mayoractual > 0) {
        mayores[count++] = mayoractual;
    }

    for (int i = 1; i < size; i++) {
        if (array[i] > mayoractual && array[i] > 0) {
            mayoractual = array[i];
            if (count < sizemax) {
                mayores[count++] = mayoractual;
            }
        }
    }

    if (count == 0) {
        delete[] mayores;
        return nullptr;
    }

    int* resultado = new int[count];
    for (int i = 0; i < count; i++) {
        resultado[i] = mayores[i];
    }

    delete[] mayores;
    return resultado;
}

int cambiodesigno(int *array, int size) {
    float contador = 0;
    if (size < 2) {
        return contador;
    }
    for (int i = 0; i < size - 1; i++) {
        if ((array[i] < 0 && array[i + 1] >= 0) || (array[i] >= 0 && array[i + 1] < 0)) {
            contador++;
        }
    }
    return contador;
}

void loop() {
    unsigned long tiempoactual = millis();
    bool begin = digitalRead(botoninicioPin) == LOW;
    bool done = digitalRead(botondetenerPin) == LOW;
    val = analogRead(analogPin);



    if (begin) {
        adquiriendodatos = true;
        lcd_1.clear();
        lcd_1.print("adquiriendo datos");
    }

    if (adquiriendodatos) {
        if (tiempoactual - tiempoanterior >= intervalo) {
            if (sizearraymomentaneo > 0) {
                delete[] ultimosegundo;
                ultimosegundo = new int[sizearraymomentaneo];
                for (int i = 0; i < sizearraymomentaneo; i++) {
                    ultimosegundo[i] = arraymomentaneo[i];
                }
                sizeultimo = sizearraymomentaneo;
            }

            delete[] arraymomentaneo;
            arraymomentaneo = new int[1];
            arraymomentaneo[0] = val;
            sizearraymomentaneo = 1;

            tiempoanterior = tiempoactual;

        } else {
            int *nuevoarray = new int[sizearraymomentaneo + 1];
            for (int i = 0; i < sizearraymomentaneo; i++) {
                nuevoarray[i] = arraymomentaneo[i];
            }
            nuevoarray[sizearraymomentaneo] = val;

            delete[] arraymomentaneo;
            arraymomentaneo = nuevoarray;
            sizearraymomentaneo++;

            Serial.print("valor: ");
            Serial.println(val);
        }
    }

    if (done) {
        lcd_1.clear();
        if (sizeultimo > 0) {
            float maximoultimo = ultimosegundo[0];
            for (int i = 1; i < sizeultimo; i++) {
                if (ultimosegundo[i] > maximoultimo) {
                    maximoultimo = ultimosegundo[i];
                }
            }
            Serial.print("pico del ultimo segundo: ");
            Serial.println(maximoultimo);
            a = maximoultimo / 100;
            lcd_1.print("amplitud: ");
            lcd_1.setCursor(0, 1);
            lcd_1.print(a);
            lcd_1.print(" V");
            delay(2000);

            float cambios = cambiodesigno(ultimosegundo, sizeultimo);
            frecuencia = cambios/ 2;

            Serial.print("frecuencia calculada: ");
            Serial.println(frecuencia);
            lcd_1.clear();
            lcd_1.print("frecuencia:");
            lcd_1.setCursor(5, 1);
            lcd_1.print(frecuencia);
            lcd_1.print(" Hz");
            delay(2000);

            lcd_1.clear();
            int* maxx = valoresmayores(ultimosegundo, sizeultimo);
            if (maxx != nullptr) {
                for (int i = 0; i < sizeultimo - 1; i++) {
                    if (maxx[i] > 0 && maxx[i + 1] > 0) {
                        Serial.print("Comparando ");
                        Serial.print(maxx[i]);
                        Serial.print(" y ");
                        Serial.println(maxx[i + 1]);
                        if (maxx[i] < maxx[i + 1]) {
                            Serial.println("Triangular");
                            tri++;
                        } else {
                            Serial.println("S o C");
                            soc++;
                        }
                    }
                }
                if (tri >= soc) {
                    lcd_1.print("triangular");
                    tri = 0;
                    soc = 0;
                } else if (tri < soc) {
                    lcd_1.print("sinosoidal o");
                    delay(200);
                    lcd_1.clear();
                    lcd_1.print("Cuadrada");
                    tri = 0;
                    soc = 0;
                }

                delete[] maxx;
            }

            delete[] ultimosegundo;
            ultimosegundo = nullptr;
            delete[] arraymomentaneo;
            arraymomentaneo = nullptr;

            sizearraymomentaneo = 0;
            sizeultimo = 0;
        }
    }
}

// existen limitaciones con el tinkercad o me falto optimizacion, terminado los puntos de frecuencia y amplitud usando puntadores y memoria
// dinamica ultima parte diferenciar una funcion a otra.


