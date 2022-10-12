
#include <Keypad.h>
#include <LiquidCrystal.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

const int rs = 10, en = 12, d4 = 15, d5 = 16, d6 = 17, d7 = 18;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

int cont = 0;
int iden = 0;
int con2 = 5;
int intento = 0;

int verd = 0;
int ledRojo = 19;
int ledVerde = 20;
int ledAmarillo = 21; 


char clave[4] = {'1','2','3','4'};
char claveUsuario [4];


byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


char Tecla;

void setup(){
  Serial.begin(9600);
  
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("DIGIT CONTRASENA");
  pinMode (ledRojo, OUTPUT);
  pinMode (ledVerde, OUTPUT);
  pinMode (ledAmarillo, OUTPUT);
  
}

void loop(){
    recorrido();
    seguridad();

  
if (intento == 3) {
  superado();
  }
//if (verd = 2){
    //  lcd.clear();
     // lcd.setCursor(0,0);
     // lcd.print("Bienvenido DIG2"); 
 // }
  else {
    recorrido();
    seguridad();
    }

  
  
  }

void recorrido(){

do{
  Tecla = keypad.getKey();
    if(Tecla){
     claveUsuario[cont] = Tecla;
     cont++;
    
     
     
     
     lcd.setCursor(con2,1);
     lcd.print(Tecla);
     con2++;
  }
   if(cont == 4){
    for(int i = 0; i<=3;i++){
     if(claveUsuario[i] != clave[i]){
      iden = 1;
    }
    }
   }

  }while (cont < 4);
}



void seguridad() {

if(iden == 1){
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("CLAVE");
    lcd.setCursor(3,1);
    lcd.print("INCORRECTA"); 
    intento++;
    delay(600);
    digitalWrite(ledAmarillo,HIGH);
    delay(600);
    digitalWrite(ledRojo,LOW);
    digitalWrite(ledVerde,LOW);
    cont = 0;
    iden = 0;
    con2 = 5;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("INGRESE DENUEVO");
    }
  else{
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("CLAVE");
    lcd.setCursor(4,1);
    lcd.print("CORRECTA"); 
    delay(900);
    digitalWrite(ledVerde,HIGH);
    delay(900);
    digitalWrite(ledRojo,LOW);
    digitalWrite(ledAmarillo,LOW);
    delay(1000);
    digitalWrite(ledRojo,HIGH);
    delay(500);
    digitalWrite(ledVerde,HIGH);
    delay(500);
    digitalWrite(ledAmarillo,LOW);
    delay(500);
    digitalWrite(ledRojo,LOW);
    delay(500);
    digitalWrite(ledVerde,LOW);
    delay(500);
    digitalWrite(ledAmarillo,HIGH);
    delay(500);
    digitalWrite(ledRojo,HIGH);
    delay(500);
    digitalWrite(ledVerde,HIGH);
    delay(500);
    digitalWrite(ledRojo,LOW);
    digitalWrite(ledAmarillo,LOW);
    digitalWrite(ledVerde,LOW);
    verd = 0;
    con2 =5;
    cont= 0;
      
  }

}

void superado(){


    lcd.clear(); 
    lcd.setCursor(5,0);
    lcd.print("INTENTOS");
    lcd.setCursor(3,1);
    lcd.print("SUPERADOS"); 
    delay(800);
    digitalWrite(ledRojo,HIGH);
    delay(200);
    digitalWrite(ledVerde,LOW);
    digitalWrite(ledAmarillo,LOW);
    intento = 0;
}




  
  
   



  


  
  
