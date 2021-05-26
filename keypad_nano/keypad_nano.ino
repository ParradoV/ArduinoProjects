#include <Keypad.h>
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
 
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
unsigned char i;
char key[]="1234"; 
int cont = 0;
char codigo[4];

void setup(){
  Serial.begin(9600);
  pinMode(11, OUTPUT);    // pin del relé
  pinMode(12, OUTPUT); // pin de buzzer
}
  
void loop(){
  char customKey = customKeypad.getKey();
  if (customKey){
    codigo[cont]=customKey;
    Serial.println(codigo);//se imprime en el puerto serie la tecla presionada
    cont=cont+1; 
    if (cont==4){
      if(codigo[0]==key[0]&&codigo[1]==key[1]&&codigo[2]==key[2]&&codigo[3]==key[3])
      {
        acierto();
      }
      else{
        fallo();
      }
    }
  } 
}

void reset(){
  codigo[0]='*';
  codigo[1]='*';
  codigo[2]='*';
  codigo[3]='*';

  cont=0;
}

void acierto(){
  
  for(i=0; i<1; i++){
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  delay(1400);
  digitalWrite(12, LOW);
  }
  digitalWrite(11, HIGH); // sets the digital pin 13 on
  delay(1000);
  digitalWrite(11,LOW);
  digitalWrite(13, LOW);
  reset();
}

void fallo(){
  for(i=0;i<4; i++){
    digitalWrite(12, HIGH);
    delay (100);
    digitalWrite(12, LOW);
    delay(200);
  }
  reset();
}
