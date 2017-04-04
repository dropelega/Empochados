/*****************************************
 * name: I2C LCD2004
 * function: You should now see your I2C LCD2004 display "Hello,world!","IIC/I2C LCD2004"
 * "20 cols, 4 rows","www.sunfounder.com"
 ********************************/
//Email:service@sunfounder.com
//Website:www.sunfounder.com

/********************************/
// include the library code
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
/*********************************************************/
const int okButton=2;
const int cancelButton=4;
const int plusButton=7;
const int lessButton=8;

int okButtonState=0;
int cancelButtonState=0;
int plusButtonState=0;
int lessButtonState=0;

int state=0;//estado en el que se encuentra la partida
int players=3;//minimo jugadores 3 maximo jugadores 6
int rounds=0;//se calcularan respecto al numero de jugadores
int cards=40;//se calcularan respecto al numero de jugadores
int score[6]={0,0,0,0,0,0};//puntuacion de jugadores
int inhand=1;//cartas in hand repartidas
void setup()
{
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight 
  pinMode(okButton,INPUT);
  pinMode(cancelButton,INPUT);
  pinMode(plusButton,INPUT);
  pinMode(lessButton,INPUT);
 
  
  lcd.setCursor ( 0, 0 );            // go to the top left corner
  lcd.print("    Hello,world!    "); // write this string on the top row
  lcd.setCursor ( 0, 1 );            // go to the 2nd row
  lcd.print("   Hello Pedro!  "); // pad string with spaces for centering
  lcd.setCursor ( 0, 2 );            // go to the third row
  lcd.print("  Hello Valli   "); // pad with spaces for centering
  lcd.setCursor ( 0, 3 );            // go to the fourth row
  lcd.print(" www.miguelin.com ");
}
/*********************************************************/
void loop() 
{
  okButtonState=digitalRead(okButton);
  cancelButtonState=digitalRead(cancelButton);
  plusButtonState=digitalRead(plusButton);
  lessButtonState=digitalRead(lessButton);  
  switch (state) {
      case 0://Menu Principal
         if(cancelButtonState==HIGH){
           //apagar
         }
         if(plusButtonState==HIGH){
           if(players<6){
             players++;
           }
         }
         if(lessButtonState==HIGH){
           if(players>3){
            players--;
           }
         }
         cards=40-(40%players);
         
         lcd.setCursor ( 0, 0 );            // go to the top left corner
         lcd.print("Nº jugadores:"); // wriute this string on the top row
         lcd.setCursor ( 7, 1 );            // go to the top left corner
         lcd.print(players); // write this string on the top row 
         lcd.setCursor ( 0, 3 );            // go to the top left corner
         lcd.print("Nº cartas:"); // write this string on the top row
         lcd.setCursor ( 7, 4 );            // go to the top left corner
         lcd.print(cards); // write this string on the top row
         if(okButtonState==HIGH){
           rounds = ((cards/players)*2)-1;
           state = 1;
         }
        break;
      case 1://Repartir y poner baraja
        //do something when var equals 2
        break;
      case 2://vision artificial 
        //do something when var equals 2
      break;
      case 3://apuestas
       //do something when var equals 2
      break;
      case 4://jugando
       //do something when var equals 2
      break;
      case 5://apuntar resultados
       //do something when var equals 2
      break;
      case 6://mostrar resultados
        //do something when var equals 2
      break;
      case 7://fin de la partida
       //do something when var equals 2
      break;
      default://errores
        // if nothing else matches, do the default
        // default is optional
      break;
  }
}
