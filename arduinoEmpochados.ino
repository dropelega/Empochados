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

int summer=0;
boolean enterok = true; //comprueba que solo se ha realizado una pulsacion del boton ok
boolean entercancel= true; //comprueba que solo se ha realizado una pulsacion del boton cancel
boolean enterplus= true; //comprueba que solo se ha realizado una pulsacion del boton plus
boolean enterless = true; //comprueba que solo se ha realizado una pulsacion del boton less
int state=0;//estado en el que se encuentra la partida
int players=3;//minimo jugadores 3 maximo jugadores 6
int rounds=0;//se calcularan respecto al numero de jugadores
int cards=40;//se calcularan respecto al numero de jugadores
int score[6]={0,0,0,0,0,0};//puntuacion de jugadores
int bets[6]={0,0,0,0,0,0};//apuestas por rondas
int inhand=1;//cartas in hand repartidas
int crupier=1;//jugador que reparte
String beer="Oros";
int better=-1;
int bazer=0;
int currentPlayer=0;
void setup()
{
  //Iniciamos el Serial:
  Serial.begin(9600);
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight 
  pinMode(okButton,INPUT);
  pinMode(cancelButton,INPUT);
  pinMode(plusButton,INPUT);
  pinMode(lessButton,INPUT);
 
  
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
           if(entercancel == true){
             entercancel = false;
           }
           //apagar
         }else{
           entercancel = true;
         }
         if(plusButtonState==HIGH){
           if(enterplus==true){
             if(players<6){
               players++;
             }
             enterplus = false;
           }
         }else{
           enterplus = true;
         }
         if(lessButtonState==HIGH){
           if(enterless == true){
             if(players>3){
              players--;
             }
             enterless = false;
           }
         }else{
           enterless = true;
         }
         cards=40-(40%players);
         
         lcd.setCursor ( 0, 0 );            // go to the top left corner
         lcd.print("Num jugadores:"); // wriute this string on the top row
         lcd.setCursor ( 7, 1 );            // go to the top left corner
         lcd.print(players); // write this string on the top row 
         lcd.setCursor ( 0, 2);            // go to the top left corner
         lcd.print("Num cartas:"); // write this string on the top row
         lcd.setCursor ( 7, 3 );            // go to the top left corner
         lcd.print(cards); // write this string on the top row
         if(okButtonState==HIGH){
           if(enterok == true){
             rounds = ((cards/players)*2)-1;
             reset();
             enterok = false;
             state = 1;
           }
         }else{
           enterok = true;
         }
        break;
      case 1://Repartir y poner baraja
         if(okButtonState==HIGH){
           if(enterok==true){
             reset();
             state = 3;//cambiar estado para que utilice la vision
             if(crupier!=players){
               better=crupier+1;
             }else{
               better=0;
             }
             enterok = false;
           }
         }else{
           enterok = true;
         }
         if(cancelButtonState==HIGH){
           if(entercancel == true){
             reset();
             state=0;
             entercancel = false;
           }
         }else{
           entercancel = true;
         }
         
         lcd.setCursor ( 0, 0 );
         lcd.print("Reparte:"); 
         lcd.setCursor ( 0, 1 );           
         lcd.print("El jugador ");
         lcd.setCursor ( 14,1);
         lcd.print(crupier); 
         lcd.setCursor ( 0, 2);        
         lcd.print("Coloca la baraja"); 
         lcd.setCursor ( 0, 3 );        
         lcd.print("en su zona"); 
         
        break;
      case 2://vision artificial 
      //hablar con python
        if(okButtonState==HIGH){
          if(enterok == true ){
            Serial.write('d');
            enterok = false;
          }
        }else{
          enterok = false;
        }
        if(Serial.available() >= 1){
          switch(Serial.read()){
            case 'o':
                beer="oros";
                reset();
                state=3; 
            break;
            case 'e':
               beer="espadas";
               reset();
               state=3; 
            break;     
            case 'c':
              beer="copas";
              reset();
              state=3; 
            break;
            case 'b':
              beer="bastos";
              reset();
              state=3; 
            break;
            }
          }
        
      break;
      case 3://apuestas
        if(okButtonState==HIGH){
          if(enterok == true ){
            if(better==crupier-1){
              if(crupier!=players){
               better=crupier+1;
              }else{
               better=0;
             }
             reset();
             state = 4;
            }else{
             if(better==players){
               better=0;
             }else{
              better++;
             }
            }
            enterok = false; 
          }
         }else{
           enterok = true;
         }
         if(cancelButtonState==HIGH){
           if(entercancel == true){
             reset();
             state=0;
             entercancel = false;
           }
         }else{
           entercancel = true;
         }
         if(plusButtonState==HIGH){
           if(enterplus == true){
             bets[better]++;
             /*if(better+1==crupier){//meter condiciones de maxima y minima apuesta
               summer=0;
               for(int i=0;i<6;i++){
                 if(i!=crupier){
                   summer+=bets[i];
                 }
                if(bets[better]+summer==inhand){
                  bets[better]++;
                }
               }
             }*/
             enterplus = false;
           }
         }else{
           enterplus = true;
         }
         if(lessButtonState==HIGH){
           if(enterless == true){
             bets[better]--;
             /*if(better==crupier){
               int summer=0;
               for(int i=0;i<6;i++){
                 if(i!=crupier){
                   summer+=bets[i];
                 }
                if(bets[better]+summer==inhand){
                  bets[better]--;
                }
               }
             }*/
             enterless = false;
           }
         }else{
           enterless = true;
         }
      
         lcd.setCursor ( 0, 0 );
         lcd.print("Pinte: "+beer);
         lcd.setCursor ( 8, 0 );
         lcd.print(beer);  
         lcd.setCursor ( 0, 1 );           
         lcd.print("Apuesta Jug "); 
         lcd.setCursor ( 13, 1 );
         lcd.print(better); 
         lcd.setCursor ( 0, 2);        
         lcd.print("Apuesta: ");
         lcd.setCursor(0,3);
         lcd.print("                ");
         lcd.setCursor ( 7, 3 );        
         lcd.print(bets[better]); 
      
        /*
         lcd.setCursor ( 0, 0 );
         lcd.print("Pinte: "+beer);
         lcd.setCursor ( 8, 0 );
         lcd.print(beer);  
         lcd.setCursor ( 0, 1 );           
         lcd.print("Apuesta Jug "); 
         lcd.setCursor ( 13, 1 );
         lcd.print(better); 
         lcd.setCursor ( 0, 2);        
         lcd.print("Apuesta: ");
         lcd.setCursor(0,3);
         lcd.print("                ");
         lcd.setCursor ( 7, 3 );        
         lcd.print(bets[better]); 
        */
      break;
      case 4://jugando
         if(okButtonState==HIGH){
           reset();
           state = 5;
         }
         if(cancelButtonState==HIGH){
           reset();
           state=0;
         }
         lcd.setCursor ( 0, 0 );
         lcd.print("Pinte: "); 
         lcd.setCursor ( 0, 8 );
         lcd.print(beer); 
         lcd.setCursor ( 0, 1 );           
         lcd.print("    "); 
         lcd.setCursor ( 3, 2 );        
         lcd.print("Jugando.."); 
         lcd.setCursor( 0,  3);        
         lcd.print(" "); 
      break;
      case 5://apuntar resultados
       if(okButtonState==HIGH){
         if(enterok == true){ 
            if(bazer==bets[better]){
              score[better]+=10+bazer*5;
            }else{
              score[better]-=abs(bazer-bets[better])*5;
            }
            if(better==crupier){
             reset();
             state =6;
            }else{
             if(better==players-1){
               better=0;
             }else{
              better++;
             }
            }
            enterok = false;
         }
       }else{
         enterok = true;
       }
       if(cancelButtonState==HIGH){
         if(entercancel == true){
         reset();
         state=0;
         entercancel = false;
         }
       }else{
         entercancel = true;
       }
       if(plusButtonState==HIGH){
         if(enterplus == true){ 
           bazer++;
           enterplus = false;
         }
       }else{
         enterplus = true;
       }
       if(lessButtonState==HIGH){
         if(enterless == true){
           bazer--;     //meter lo de los oros dobles
           enterless = false;  
         }
       }else {
         enterless = true;
       }
    
       lcd.setCursor ( 0, 0 );
       lcd.print("Pinte: "+beer); 
       lcd.setCursor ( 0, 1 );           
       lcd.print("Bazas Jugador "+better); 
       lcd.setCursor ( 0, 2);        
       lcd.print("Num Bazas: "); 
       lcd.setCursor ( 7, 3 );        
       lcd.print(bazer); 
          
       break;
      case 6://mostrar resultados
           if(okButtonState==HIGH){
             if(enterok == true){
               if(inhand<rounds){
                 inhand++;
               }else{
                 inhand--;
               }
               rounds--;
               if(inhand==0){
                 reset();
                 state=7; 
               }else{
                 reset();
                 state=1;
               }
               enterok = false;
             }
           }else{
             enterok = true;
           }
          if(cancelButtonState==HIGH){
            if(entercancel == true){
             reset();
             state=0;
             entercancel = false;
            }
           }else{
             entercancel = true;
           }
           if(plusButtonState==HIGH){
             if(enterplus == true){
               if(currentPlayer<players){
                 currentPlayer++;
               }
               enterplus = false;
             }
           }else{
             enterplus = true;
           }
           if(lessButtonState==HIGH){
             if(enterless == true){
               if(currentPlayer!=0){
                 currentPlayer--;
               }    
               enterless = false;
             }
           }else{
             enterless = true;
           }
         lcd.setCursor ( 2, 0);        
         lcd.print("Puntuaciones"); 
         lcd.setCursor ( 0, 1);
         lcd.print("Jugador "+(currentPlayer+1)); 
         lcd.setCursor ( 0, 2);           
         lcd.print(score[currentPlayer]+" puntos"); 
         lcd.setCursor ( 0, 3 );        
         lcd.print(""); 
         break;
      case 7://fin de la partida
        {
        int winneador=0;
        for(int i=0;i<players;i++){
          if(score[i]>score[winneador]){
            winneador=i;
          }
        }
         lcd.setCursor ( 0, 0);        
         lcd.print("El ganador es:"); 
         lcd.setCursor ( 0, 1);
         lcd.print("Jugador "+ winneador); 
         lcd.setCursor ( 0, 2);           
         lcd.print(score[winneador] +" puntos"); 
         lcd.setCursor ( 0, 3 );        
         lcd.print("¡Felicidades!");
        }
         break;
      default://errores
        break;
  }
}
void reset(){
     lcd.setCursor ( 0, 0);        
     lcd.print("                "); 
     lcd.setCursor ( 0, 1);
     lcd.print("                "); 
     lcd.setCursor ( 0, 2);           
     lcd.print("                "); 
     lcd.setCursor ( 0, 3 );        
     lcd.print("                ");

}

