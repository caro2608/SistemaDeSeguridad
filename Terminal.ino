/*
    ENTREGABLE  SISTEMA DE SEGURIDAD
    UNIVERSIDAD DEL CAUCA - TECNOLOGIA EN TELEMATICA

    
    REALIZADO POR:
    - CAROLINA FERNANDEZ cONDA   
    - lUIS FERNANDO LUBO
    
*/


#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE
#include <DabbleESP32.h>
#include "AsyncTaskLib.h"
#include <DHT.h> 
#define DHTPIN 4
#define DHTTYPE DHT11

//#include <ezbuzzer>

String Serialdata = "";
bool dataflag = 0;
int cont = 0;
int iden = 0;
int intento = 0;

int LED1 = 21;
int LED2 = 22;
int LED3 = 23;
int temp;
int humedad;
int contador = 22;
int contador1 = 25;
DHT dht(DHTPIN, DHTTYPE);

#define LIGHT_SENSOR_PIN  26  // ESP32 pin GIOP36 (ADC0) connected to light sensor
int LED_PIN = 22;  // ESP32 pin GIOP22 connected to LED
#define ANALOG_THRESHOLD  500

//variables para el control del buzzer analogico
#include <EasyBuzzer.h>
//#include  <tonos.h>
#define pin_buzz 18
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
int duraciones[] = { 8, 8, 4, 4 };    // array con la duracion de cada nota
int melodia[] = { NOTE_B6, NOTE_C7, NOTE_CS7, NOTE_D7 };//// array con las notasa a reproducir

//int buzzer = 33;

char clave[4] = {'1','2','3','4'};
char claveUsuario [4];
char Tecla;



void sensorD();

void sensorD(){
  
    humedad=dht.readHumidity();
    temp=dht.readTemperature();
    Serial.print("Temperatura: ");
    Serial.print(temp);
    Terminal.print(temp);
    Terminal.print(" C");       
    Serial.print(" C");
    Serial.print("Humedad: ");
    Serial.print(humedad);
    Terminal.print(humedad);
    Terminal.print("%");   
    Serial.print("%");
 if(temp <= contador){
    Serial.print("ALERTA TEMP MIN");
    digitalWrite(LED1,HIGH);
    }else if(temp >= contador1){
     Serial.print("ALERTA TEMP MAX");
     digitalWrite(LED2,HIGH);
    }else{
       digitalWrite(LED3,HIGH);
    }     
  
}

void photo() {
  int analogValue = analogRead(LIGHT_SENSOR_PIN); // read the value on analog pin
  Terminal.print(analogValue);
  if (analogValue < ANALOG_THRESHOLD)
    digitalWrite(LED_PIN, HIGH); // turn on LED
  else
    digitalWrite(LED_PIN, LOW);  // turn off LED
}





AsyncTask asyncTaskTemp(2000, true, sensorD);
AsyncTask asyncTaskPhoto(1000, true, photo);





void setup() {
  Serial.begin(115200);       // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin("Holis");    //set bluetooth name of your device

  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  //pinMode(buzzer, OUTPUT);
   
  dht.begin();}

  //asyncTaskTemp.Start();
  //asyncTaskPhoto.Start();

  //Serial.begin(9600);

// configure LED PWM functionalitites

   


void loop() {



if (intento == 3) {
  superado();
  }

  else {
    recorrido();
    seguridad();
    asyncTaskTemp.Update();
    asyncTaskPhoto.Update();    
    
    }
}


void recorrido(){
  
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  while (Serial.available() != 0)
  {
  
    Serialdata = String(Serialdata + char(Serial.read()));
    dataflag = 1;
  }
  if (dataflag == 1){
    
    Terminal.print(Serialdata);
    Serialdata = "";
    dataflag = 0;
  }
  if (Terminal.available() != 0)
  {
    while (Terminal.available() != 0)
    {
      do{
        Tecla = Terminal.read();

          if(Tecla){
          claveUsuario[cont] = Tecla;
          cont++;
        }
        if(cont == 4){
          for(int i = 0; i<=3;i++){
          if(claveUsuario[i] != clave[i]){
            iden = 1;               
          }else if(claveUsuario[i] == clave[i]){
            iden = 2;
          }
          

          }
        }

        }while (cont < 4);    }
    Serial.println();
  }
}



void seguridad() {

if(iden == 1){

    Terminal.print("CLAVE");
    Terminal.print("INCORRECTA"); 
    intento++;
    delay(600);
    cont = 0;
    iden = 0;
    Terminal.print("INGRESE DENUEVO");
    digitalWrite(LED1,HIGH);
    }
  else if(iden==2){
    Terminal.print("CLAVE");
    Terminal.print("CORRECTA"); 
    delay(900);
    iden = 0;    
    Terminal.print("Bienvenido a Digitales");
    //sensorD();
    //photo();           

    asyncTaskTemp.Start();
    asyncTaskPhoto.Start();    
    cont= 0;
      
  }

}

void superado(){

    Terminal.print("INTENTOS");
    Terminal.print("SUPERADOS"); 
    delay(800);
    intento = 0;
    delay (800);
    digitalWrite(LED2,HIGH);
    loop();
}



/*void sonar_buzz() { // funcion encargada de hacer sonar el buzzer
  for (int i = 0; i < 3; i++) {      // bucle repite 4 veces, 1 por cada nota
    int duracion = 1000 / duraciones[i];    // duracion de la nota en milisegundos
    tone (pin_buzz, melodia[i], duracion);  // ejecuta el tono con la duracion
    int pausa = duracion * 1.30;      // calcula pausa
    delay(pausa);         // demora con valor de pausa
    noTone (pin_buzz);        // detiene reproduccion de tono
  }
}*/
