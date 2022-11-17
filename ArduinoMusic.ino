#include <Keypad.h> // Libreria para que funcione el teclado
#include <LiquidCrystal.h> // Libreria para que funcione el LCD

//LCD
LiquidCrystal lcd(1, 0, A1, A2, 10, 9); // RS=1 , E=0, A1=D4, A2=D5, 10=D6, 9= D7 esta linea muestra en que pines debe ir conectado la pantalla LCD a nuestro Arduino  //Creacion del LCD

//Teclado             
const byte ROWS = 4;                                                               //Creacion del teclado definiendo sus dimensiones, en este caso, 4x4
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'7', '8', '9', 'A'},
  {'4', '5', '6', 'B'},                                                            //Asignacion de columnas y filas a valores (para identificar el modelo del teclado)
  {'1', '2', '3', 'C'},
  {'E', '0', 'F', 'D'}
};

byte rowPins[ROWS] = {12, 11, 8, 7}; //Filas(pines del 7,8 y 12, 13)
byte colPins[COLS] = {6, 5, 4, 2}; //Columnas (pines del 2, 4 al 6)

bool sostenido;       //Bool para las notas sostenidas

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );           //Definicion de la entidad teclado 

//Parlante
int tonePin = 3;         //Pin de parlante

//Mi corazon encantado
int length = 191; // Numero de notas (incluido espacios)
char notes[] = "cgfgegdg ggefgagfed eecdefedc=0 00caggcdefedcdcc=cde !BAGFEDC ccccc-9-c- -------989-9 99998888668468 99-ccccccc-9-c---cddr-989 9-98888gfffrdrcdrrcrrcr rfrdcc-8--8-- 8-cddrcddrc cgfffrfg"; // Reproduccion del tono, cada espacio representa un descanso
float beats[] = {4, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2, 1, 2, 2, 1, 2, 2, 1, 1, 1, 1, 2, 1, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1, 3, 1, 1, 2, 2, 2, 2, 3, 2, 2, 1, 8, 8, 2, 1, 2, 2, 2, 2, 2, 2, 2, 4, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 3, 1, 1, 2, 2, 1, 2, 1, 2, 2, 1, 2, 2, 1, 2, 6, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 3, 1, 2, 2, 1, 3, 1, 2, 2, 1, 6, 1, 1, 1, 1, 2, 2, 1, 2, 2, 1, 4, 1, 1, 1, 6, 2, 2, 1, 2, 1, 1, 2, 1, 3, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 3, 1, 5, 1, 1, 2, 1, 1, 1, 2, 3, 1, 1, 1, 1, 10}; //Duracion de cada nota
int tempo = 170; //Velocidad de reproduccion

void playTone(int ton1, int duration) {
  for (long i = 0; i < duration * 1000L; i += ton1) {                //Metodo para la cancion "mi corazon encantado"
    tone(tonePin, ton1);
    delayMicroseconds(ton1);
  }
  noTone(tonePin);
}

void playNote(char note, int duration) {
  char names[] = { ' ',  '!', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 'c', 'd', 'r', 'e', 'f', 'g', 'S',  'a', 'b', 's', 'C', 'D', 'R', 'E', 'F', 'G', 'O', 'A', 'o', 'B', 'i', 'N', 'R', 'u',  '1', 'L', 'k'}; // Notas musicales
  int tones[] =  {   0, 1046, 138, 146, 155, 164, 174, 184, 195, 207, 220, 233, 246, 261, 293, 311, 329, 349, 391, 415, 440, 493, 466 , 523, 587, 622, 659, 698, 783, 831, 880, 932, 987, 466, 740, 622, 415, 1046, 622u, 227}; // Frecuencia de cada nota

  // Tocando nota por nota del vector notes[]
  for (int i = 0; i < 40; i++) {
    if (names[i] == note) {
      titilar(50);
      playTone(tones[i], duration);                      //Metodo para la cancion "mi corazon encantado"
    }
  }
}

//LED
int rojo = 13;                                                //Pin del led

void titilar(int retraso)
{
  analogWrite(rojo,255);                                            
  delay(retraso);                                         //Metodo que hace un juego de luces led roja
  analogWrite(rojo,0);
  }

void sonido(String nota, int frecuency)
{
  tone(tonePin, frecuency, 200);
  delay(300);
  lcd.clear();
  lcd.setCursor(7, 0);
  lcd.print(nota);                                                                  //Metodo para las notas musicales y demas funcionalidades
  analogWrite(rojo, 255);
  delay(200);
  analogWrite(rojo,0);

}

void setup() {
  pinMode(tonePin, OUTPUT);                                                        //Configuracion del parlante
  analogWrite(tonePin, 0);                                                         //Configuracion del parlante
  pinMode(rojo, OUTPUT);                                                           //Configuracion del LED
  lcd.begin(16, 2);                                                                //Definimos la dimension del LCD el cual va a mostrar las notas
  lcd.print("Notas musicales");                                                    //Mostramos en el LCD el texto "Notas musicales"
 

}

void loop() {   
  char key = 'x';                                                                  //Modifica el valor de la variable "key" a x para que no ocurra nada raro
  key = keypad.getKey();                                                           //Modifica el valor de la variable "key" a la que sea ingresada mediante el teclado
  if (key) {                                                                       
    switch (key)                                                                   //Mediante un switch, va a buscar si el valor de "key" coincide con alguna de las opciones
    {
      case 'A':                                                                    
        sostenido = true;                                                          //Si "key" tiene valor A, el bool "sostenido" va a pasar a tener valor true
        break;
      case '7': //DO                                                               //Si "key" tiene valor 7, y el bool sostenido es true
        if (sostenido)
        {
          sonido("DO#", 277);                                                      //Reproduce la nota DO sostenida y su respectivo sonido
          sostenido = false;                                                       //Modifica el valor de "sostenido" a false

        }
        else                                                                       //Si "key" tiene valor 7, y el bool sostenido es false
        {
          sonido("DO", 262);                                                       //Reproduce la nota DO con su respectivo sonido
        }
        break;
      case '8': //RE                                                               //Si "key" tiene valor 8, y el bool sostenido es true
        if (sostenido)
        {
          sonido("RE#", 311);                                                      //Reproduce la nota RE sostenida y su respectivo sonido
          sostenido = false;                                                       //Modifica el valor de "sostenido" a false

        }
        else                                                                       //Si "key" tiene valor 8, y el bool sostenido es false
        {
          sonido("RE", 294);                                                       //Reproduce la nota RE con su respectivo sonido
        }
        break;
      case '9': //MI                                                               //Si "key" tiene valor 9. Esta nota no utiliza la variable sostenido ya que MI# no existe
        sonido("MI", 330);                                                         //Reproduce la nota MI con su respectivo sonido
        break;
      case '4': //FA                                                               //Si "key" tiene valor 4, y el bool sostenido es true
        if (sostenido)
        {
          sonido("FA#", 370);                                                      //Reproduce la nota FA sostenida y su respectivo sonido
          sostenido = false;                                                       //Modifica el valor de "sostenido" a false

        }
        else                                                                       //Si "key" tiene valor 4, y el bool sostenido es false
        {
          sonido("FA", 349);                                                       //Reproduce la nota FA con su respectivo sonido
        }
        break;
      case '5': //SOL                                                              //Si "key" tiene valor 5, y el bool sostenido es true
        if (sostenido)
        {
          sonido("SOL#", 415);                                                     //Reproduce la nota SOL sostenida y su respectivo sonido
          sostenido = false;                                                       //Modifica el valor de "sostenido" a false

        }
        else                                                                       //Si "key" tiene valor 5, y el bool sostenido es false
        {
          sonido("SOL", 392);                                                      //Reproduce la nota SOL con su respectivo sonido
        }
        break;
      case '6': //LA                                                               //Si "key" tiene valor 6, y el bool sostenido es true
        if (sostenido)
        {
          sonido("LA#", 466);                                                      //Reproduce la nota LA sostenida y su respectivo sonido
          sostenido = false;                                                       //Modifica el valor de "sostenido" a false

        }
        else                                                                       //Si "key" tiene valor 6, y el bool sostenido es false
        {
          sonido("LA", 440);                                                       //Reproduce la nota LA con su respectivo sonido
        }
        break;
      case '1':                                                                    //Si "key" tiene valor 1. Esta nota no utiliza la variable sostenido ya que SI# no existe
        sonido("SI", 494);                                                         //Reproduce la nota SI con su respectivo sonido
        break;

      case 'D':                                                                    //Si "key" tiene valor D. Reproduce la cancion "Mi corazon encantado"
   
        for (int i = 0; i < length; i++) {                                         //Codigo para reproducir la cancion "Mi corazon encantado"
          if (notes[i] == ' ') {
            delay(beats[i] * tempo); 
        
          }
          else
          {
            playNote(notes[i], beats[i] * tempo);                                  //Codigo para reproducir la cancion "Mi corazon encantado"
         
            
          }
          delay(tempo / 2);
        }
        break;
      case '0':
        lcd.clear();
        lcd.setCursor(0, 1);                                                       //Vacio por limitaciones del arduino
        lcd.print("");
        break;
      case '2':
        lcd.clear();
        lcd.setCursor(0, 1);                                                       //Vacio por limitaciones del arduino
        lcd.print("");
        break;
      case '3':
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("");                                                              //Vacio por limitaciones del arduino
        break;

    }
  }
}
