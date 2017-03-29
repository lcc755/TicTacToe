/*
 * tictactoe.ino
 * 
 * Author: Leanne Clarke (lcc755@mun.ca)
 * March 11, 2017
 * 
 * Adafruit_GFX and RGBmatrixPanel libraries:
 * https://learn.adafruit.com/32x16-32x32-rgb-led-matrix/overview
 * 
 * Arduino Uno was used for this project.
 * 
 * This code loads a Tic-Tac-Toe game to a 32x32 matrix. 
 * board.h loads Tic-Tac-Toe board onto Matrix
 * 3x3 matrix of buttons is used to place an X or O in corresponding blocks.
 * X goes first. Click reset on Arduino to begin again. 
 * Can be disconnected from computer and played with just Matrix, Arduino and buttons. 
 * 
 * All 9 buttons are connected to one pin on the Arduino. Each button was given a 
 * resistor with a different value. By reading the input voltage, the code knows 
 * which button was pressed. 
 * 
 * **Value ranges for buttons may need to be changed for different resistors used.**
 *
 */
 
#include <Adafruit_GFX.h>   
#include <RGBmatrixPanel.h> 
#include "board.h"

#define CLK 8 
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);


bool s0,s1,s2,s3,s4,s5,s6,s7,s8;   //spaces in game
int turn = 0;       //Keeps track of who's turn it is
char player1 = 'X';
char player2 = 'O';
int owner[9];     //Keeps track of spaces with already placed X and O

int p = A5;       //All buttons on one pin
int reading;

void setup() {
    matrix.begin();
    matrix.fillScreen(0);
    loadBoard();
    pinMode(p, INPUT);
    Serial.begin(9600);
    //Serial.println(RGBmatrixPanel().PORTD);
  
    s0 = s1 = s2 = s3 = s4 = s5 = s6 = s7 = s8 = false;
}

void loop() {
  reading = analogRead(p);

  if (reading != 0)
  {      
    //Serial.println(reading);
    matrix.setTextColor(matrix.Color333(7,0,0));
    matrix.setTextSize(1);
    
    if (255 < reading && reading < 265 && s0==false) 
    {
      s0 = true;
      turn += 1;
      matrix.setCursor(2, 2);     
        if (turn % 2 == 0)             //Odd number means player 2 just played
        {
          owner[0] = 1;
           matrix.print(player2);
        }
        else                           //else even number means player 1 just played
        {
          owner[0] = 2;
           matrix.print(player1);
        }
        delay(500);
    }
    else if (285 < reading && reading < 295 && s1==false)
    {
      s1 = true;
      turn += 1;
      matrix.setCursor(13, 2);     
        if (turn % 2 == 0)
        {
           owner[1] = 1;
           matrix.print(player2);
        }
        else 
        {
           owner[1] = 2;
           matrix.print(player1);
        }
        delay(500);
    }
    else if (376 < reading && reading < 386 && s2==false)
    {
        s2 = true;
        turn += 1;
        matrix.setCursor(24, 2);   
          if (turn % 2 == 0)
          {
             owner[2] = 1;
             matrix.print(player2);
             
          }
          else 
          {
             owner[2] = 2;
             matrix.print(player1);
          }
          delay(500);
    }
    else if (420 < reading && reading < 430 && s3==false)
    {
        s3 = true;
        turn += 1;
        matrix.setCursor(2, 12); 
          if (turn % 2 == 0)
          {
             owner[3] = 1;
             matrix.print(player2);
          }
          else 
          {
             owner[3] = 2;
             matrix.print(player1);
          }   
          delay(500);
    }
    else if (508 < reading && reading < 518 && s4==false)
    {
        s4 = true;
        turn += 1;
        matrix.setCursor(13, 12);     
          if (turn % 2 == 0)
          {
             owner[4] = 1;
             matrix.print(player2);
          }
          else 
          {
             owner[4] = 2;
             matrix.print(player1);
          }
          delay(500);
    }
    else if (612 < reading && reading < 622 && s5==false)
    {
     s5 = true;
      turn += 1; 
        matrix.setCursor(24, 12);   
          if (turn % 2 == 0)
          {
             owner[5] = 1;
             matrix.print(player2);
          }
          else 
          {
             owner[5] = 2;
             matrix.print(player1);
          }
          delay(500);
    }
    else if (783 < reading && reading < 793 && s6==false)
     {    
      s6 = true;
      turn += 1;
        matrix.setCursor(2, 23); 
          if (turn % 2 == 0)
          {
             owner[6] = 1;
             matrix.print(player2);
          }
          else 
          {
             owner[6] = 2;
             matrix.print(player1);
          }
          delay(500);
      }
    else if (950 < reading && reading < 960 && s7==false)
      {
        s7 = true;
      turn += 1;
      matrix.setCursor(13, 23);  
        if (turn % 2 == 0)
        {
           owner[7] = 1;
           matrix.print(player2);
        }
        else 
        {
           owner[7] = 2;
           matrix.print(player1);
        }  
        delay(500);
     }

  else if (990 < reading && reading < 1000 && s8==false)
     {
      s8 = true;
      turn += 1;
      matrix.setCursor(24, 23);   
        if (turn % 2 == 0)
        {
           owner[8] = 1;
           matrix.print(player2);
        }
        else 
        {
           owner[8] = 2;
           matrix.print(player1);
        }
        delay(500);
      }


  else {} //Do nothing

    check(); //Check for winner
  }
 
  if (turn == 9)  //If there's no more free spaces
     {
           //delay(1000);
           matrix.fillScreen(0);
           while (1==1){
             matrix.setTextColor(matrix.Color333(7,0,0));
           matrix.setTextSize(1);
           matrix.setCursor(10, 1);  
           matrix.print("No");
           matrix.setCursor(5, 8);  
           matrix.print("more");
           matrix.setCursor(1, 15);  
           matrix.print("moves");
           matrix.setCursor(8, 24);  
           matrix.print("!!!");
           }  
      }
}


//Loads the board.h bitmap of Tic-Tac-Toe board 
void loadBoard()
{
  uint8_t *ptr = matrix.backBuffer(); // Get address of matrix data
  memcpy_P(ptr, bmp, sizeof(bmp));
}

//Checks for winner by checking all possible lines 
void check() {
  
  //Did player 2 win?
  if ((s0==true && s1==true && s2==true &&  (owner[0]+owner[1]+owner[2])==3) ||
        (s3==true && s4==true && s5==true && (owner[3]+owner[4]+owner[5])==3) ||
        (s6==true && s7==true && s8==true && (owner[6]+owner[7]+owner[8])==3) ||
        (s0==true && s4==true && s8==true && (owner[0]+owner[4]+owner[8])==3) ||
        (s6==true && s4==true && s2==true && (owner[6]+owner[4]+owner[2])==3) ||
        (s0==true && s3==true && s6==true && (owner[0]+owner[3]+owner[6])==3) ||
        (s1==true && s4==true && s7==true && (owner[1]+owner[4]+owner[7])==3) ||
        (s2==true && s5==true && s8==true && (owner[2]+owner[5]+owner[8])==3) )
        {
             matrix.fillScreen(0);
             for (int i=0; i<999999999999999999; i++)
             {
             matrix.setTextColor(matrix.Color333(random(1,6),random(1,6),random(1,6)));
             matrix.setTextSize(1);
             matrix.setCursor(10, 1);  
             matrix.print("#2");
             matrix.setCursor(3, 11);  
             matrix.print("wins");
             matrix.setCursor(8, 22);  
             matrix.print("!!!");
             delay(200);
             }
        }
        
   //Did player 1 win?    
   if ((s0==true && s1==true && s2==true &&  (owner[0]+owner[1]+owner[2])==6) ||
        (s3==true && s4==true && s5==true && (owner[3]+owner[4]+owner[5])==6) ||
        (s6==true && s7==true && s8==true && (owner[6]+owner[7]+owner[8])==6) ||
        (s0==true && s4==true && s8==true && (owner[0]+owner[4]+owner[8])==6) ||
        (s6==true && s4==true && s2==true && (owner[6]+owner[4]+owner[2])==6) ||
        (s0==true && s3==true && s6==true && (owner[0]+owner[3]+owner[6])==6) ||
        (s1==true && s4==true && s7==true && (owner[1]+owner[4]+owner[7])==6) ||
        (s2==true && s5==true && s8==true && (owner[2]+owner[5]+owner[8])==6) )
        {
             matrix.fillScreen(0);
             for (int i=0; i<999999999999999999; i++)
             {
             matrix.setTextColor(matrix.Color333(random(1,6),random(1,6),random(1,6)));
             matrix.setTextSize(1);
             matrix.setCursor(10, 1);  
             matrix.print("#1");
             matrix.setCursor(3, 11);  
             matrix.print("wins");
             matrix.setCursor(8, 22);  
             matrix.print("!!!");     
             delay(200);
             }       
        }

    else {} //Do nothing

}
