/***************************************************
DFPlayer - A Mini MP3 Player For Arduino
 <https://www.dfrobot.com/product-1121.html>
 
 ***************************************************
 This example shows the basic function of library for DFPlayer.
 
 Created 2016-12-07
 By [Angelo qiao](Angelo.qiao@dfrobot.com)
 
 GNU Lesser General Public License.
 See <http://www.gnu.org/licenses/> for details.
 All above must be included in any redistribution
 ****************************************************/

/***********Notice and Trouble shooting***************
 1.Connection and Diagram can be found here
 <https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299#Connection_Diagram>
 2.This code is tested on Arduino Uno, Leonardo, Mega boards.
 ****************************************************/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
int caso = 0;
const int fase1 = 0;
const int fase2 = 1;
const int fase3 = 2;
const int fase4 = 3;


int stato[9]; // variabile stato forma se inserita o no fase 1 e 2
int costo[9]; // variabile stato forma se inserita o no fase 3 e 4
int Ledv[9] = {47,14,13,44,20,19,39,38,41}; // led rgb verde
int Ledr[9] = {46,12,15,42,17,23,40,37,33}; // led rgb rosso
int Ledb[9] = {45,16,18,43,22,21,34,35,32}; // led rgb blu
int Led[6] = {24,25,26,27,28,29};  // led rgb controllo batteria e controllo fase
int sensor[10] = {A8,A7,A6,A5,A4,A3,A2,A1,A0,A15}; // 9 sensori + 1 sensore volmetro
int val[10];  // variabile lettura sensore
int tempo = 500; // tempo spettacolo lampeggio forma
int a = 0;  // variabile numero lampeggi led su forma
int b[9];  // possibilita di spettacolo su forma in fase 2 e 4

void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);  // seriale arduino
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
  for (int i = 0;i < 9; i++){  // led rgb verde output
  pinMode(Ledv[i], OUTPUT);
  }
  for (int i = 0;i < 9; i++){  // led rgb rosso output
  pinMode(Ledr[i], OUTPUT);
  }
  for (int i = 0;i < 9; i++){  // led rgb blu output
  pinMode(Ledb[i], OUTPUT);
  }
  for (int i = 0;i < 6; i++){  // led rgb controllo batteria e controllo fase output
  pinMode(Led[i], OUTPUT);
  }

  
  for ( int i = 0;i < 10; i++){  // 9 sensori + 1 sensore volmetro input
   pinMode(sensor[i], INPUT); 
    }
  for ( int i = 0;i < 9; i++){   // variabile stato forma se inserita o no fase 3 e 4 = 0
    stato[i] = 0;
   }
  for ( int i = 0;i < 9; i++){  // variabile stato forma se inserita o no fase 1 e 2 = 0
    costo[i] = 0;
   }
  caso = fase1;  // passa a fase 1
  digitalWrite (Led[0], LOW); // led acceso verde fase 1
  digitalWrite (Led[1], HIGH);
  digitalWrite (Led[2], HIGH);  
  
}

void loop(){

switch (caso) {

case fase1: // togli le forme dal gioco
  for ( int i = 0;i < 9; i++){ // contatore b[] = 0
    b[i] = 0;
   }
  val[9] = analogRead(sensor[9]); // controllo batteria
  if (val[9]>990) //se valore maggiore di 573 allora....
   {  
    digitalWrite (Led[3], LOW);
    digitalWrite (Led[4], HIGH);
    digitalWrite (Led[5], HIGH);
   }
  if ((val[9]<990)&&(val[9] >=900)) //se valore maggiore di 450 e valore minore di 573 allora....
   {
    digitalWrite (Led[3], HIGH);
    digitalWrite (Led[4], HIGH);
    digitalWrite (Led[5], LOW);
   }
  if (val[9]<900)//se valore minore di 450 allora....
   {
    digitalWrite (Led[3], HIGH);
    digitalWrite (Led[4], LOW);
    digitalWrite (Led[5], HIGH);
   }


  val[0] = digitalRead(sensor[0]); //Read the sensor
 
  if(val[0] == 1 && costo[0] == 0){
    costo[0] = 1;
    Serial.println("val 0 :");
    Serial.println(val[0]);    
    Serial.println("costo 0 :");
    Serial.println(costo[0]);
  }
  if(val[0] == 0 && costo[0] == 1){
    costo[0] = 0;
  
  }
  
  val[1] = digitalRead(sensor[1]); //Read the sensor
 
  if(val[1] == 1 && costo[1] == 0){    
    costo[1] = 1;
    Serial.println("val 1 :");
    Serial.println(val[1]);    
    Serial.println("costo 1 :");
    Serial.println(costo[1]);
  }
  if(val[1] == 0 && costo[1] == 1){
    costo[1] = 0;  
  }

  val[2] = digitalRead(sensor[2]); //Read the sensor
 
  if(val[2] == 1 && costo[2] == 0){
    costo[2] = 1;
    Serial.println("val 2 :");
    Serial.println(val[2]);    
    Serial.println("costo 2 :");
    Serial.println(costo[2]);
  }
  if(val[2] == 0 && costo[2] == 1){
    costo[2] = 0;
  
  }

  val[3] = digitalRead(sensor[3]); //Read the sensor
 
  if(val[3] == 1 && costo[3] == 0){
    costo[3] = 1;
    Serial.println("val 3 :");
    Serial.println(val[3]);    
    Serial.println("costo 3 :");
    Serial.println(costo[3]);
  }
  if(val[3] == 0 && costo[3] == 1){
    costo[3] = 0;
  
  }

  val[4] = digitalRead(sensor[4]); //Read the sensor
 
  if(val[4] == 1 && costo[4] == 0){
    costo[4] = 1;
    Serial.println("val 4 :");
    Serial.println(val[4]);    
    Serial.println("costo 4 :");
    Serial.println(costo[4]);
  }
  if(val[4] == 0 && costo[4] == 1){
    costo[4] = 0;
  
  }

  val[5] = digitalRead(sensor[5]); //Read the sensor
 
  if(val[5] == 1 && costo[5] == 0){
    costo[5] = 1;
    Serial.println("val 5 :");
    Serial.println(val[5]);    
    Serial.println("costo 5 :");
    Serial.println(costo[5]);
  }
  if(val[5] == 0 && costo[5] == 1){
    costo[5] = 0;
  
  }

  val[6] = digitalRead(sensor[6]); //Read the sensor
 
  if(val[6] == 1 && costo[6] == 0){
    costo[6] = 1;
    Serial.println("val 6 :");
    Serial.println(val[6]);    
    Serial.println("costo 6 :");
    Serial.println(costo[6]);
  }
  if(val[6] == 0 && costo[6] == 1){
    costo[6] = 0;
  
  }

  val[7] = digitalRead(sensor[7]); //Read the sensor
 
  if(val[7] == 1 && costo[7] == 0){
    costo[7] = 1;
    Serial.println("val 7 :");
    Serial.println(val[7]);    
    Serial.println("costo 7 :");
    Serial.println(costo[7]);
  }
  if(val[7] == 0 && costo[7] == 1){
    costo[7] = 0;
  
  }

  val[8] = digitalRead(sensor[8]); //Read the sensor
 
  if(val[8] == 1 && costo[8] == 0){
    costo[8] = 1;
    Serial.println("val 8 :");
    Serial.println(val[8]);    
    Serial.println("costo 8 :");
    Serial.println(costo[8]);
  }
  if(val[8] == 0 && costo[8] == 1){
    costo[8] = 0;
  
  }      
  if (costo[0] == 1 && costo[1] == 1 && costo[2] == 1 && costo[3] == 1 && costo[4] == 1 && costo[5] == 1 && costo[6] == 1 && costo[7] == 1 && costo[8] == 1){
    Serial.println("passaggio fase2");
    digitalWrite (Led[0], HIGH); // accendi il led di rosso fase 2
    digitalWrite (Led[1], LOW);
    digitalWrite (Led[2], HIGH);

    caso = fase2;  // passa a fase 2
    }
  delay (20);
  break;
case fase2: // metti le forme nel gioco
  val[9] = analogRead(sensor[9]); // controllo batteria
  if (val[9]>990) //se valore maggiore di 573 allora....
   {
    digitalWrite (Led[3], LOW);
    digitalWrite (Led[4], HIGH);
    digitalWrite (Led[5], HIGH);
   }
  if ((val[9]<990)&&(val[9] >=900)) //se valore maggiore di 450 e valore minore di 573 allora....
   {
    digitalWrite (Led[3], HIGH);
    digitalWrite (Led[4], HIGH);
    digitalWrite (Led[5], LOW);
   }
  if (val[9]<900)//se valore minore di 450 allora....
   {
    digitalWrite (Led[3], HIGH);
    digitalWrite (Led[4], LOW);
    digitalWrite (Led[5], HIGH);
   }


  val[0] = digitalRead(sensor[0]); //Read the sensor
 
  if(val[0] == 0 && stato[0] == 0) //when magnetic field is detected, turn led on
  {
    if (b[0] <= 3){  // b controlla che lo spettacolo venga eseguito solo 4 volte
      myDFPlayer.play(19);
      a = 0;
      while (a <= 4){ // a controlla che i led vengano accesi per 5 volte
        digitalWrite(Ledv[0], HIGH);
        delay (tempo);
        digitalWrite(Ledv[0], LOW);
        delay (tempo);
        a = a + 1;    
        } 
    }
    stato[0] = 1;
    b[0]= b[0] + 1;
    Serial.println("stato 0 :");
    Serial.println(stato[0]);
    Serial.println("b 0 :");
    Serial.println(b[0]);
   }else{
     digitalWrite(Ledv[0], LOW);
   
  
  }
 if(val[0] == 1 && stato[0] == 1){ // se la forma viene tolta,stato torna a 0 per eseguire lo spettacolo 
  stato[0] = 0;
  
  }



  val[1] = digitalRead(sensor[1]); //Read the sensor
 
  if(val[1] == 0 && stato[1] == 0) //when magnetic field is detected, turn led on
  {
    if (b[1] <= 3){
      myDFPlayer.play(12); 
      a = 0;
      while (a <= 4){
        digitalWrite(Ledv[1], HIGH);
        delay (tempo);
        digitalWrite(Ledv[1], LOW);
        delay (tempo);
        a = a + 1;
    } 
    }
    stato[1] = 1;
    b[1]= b[1] + 1;
    Serial.println("stato 1 :");
    Serial.println(stato[1]);
    Serial.println("b 1 :");
    Serial.println(b[1]);
    }else{
    digitalWrite(Ledv[1], LOW);
   
  
  }
  if(val[1] == 1 && stato[1] == 1){
  stato[1] = 0;
   
  }

  val[2] = digitalRead(sensor[2]); //Read the sensor
 
  if(val[2] == 0 && stato[2] == 0) //when magnetic field is detected, turn led on
  {
    if (b[2] <= 3){ 
      myDFPlayer.play(7);
      a = 0;
      while (a <= 4){
        digitalWrite(Ledv[2], HIGH);
        delay (tempo);
        digitalWrite(Ledv[2], LOW);
        delay (tempo);
      
        a = a + 1;
    } 
    }
    stato[2] = 1;
    b[2]= b[2] + 1;    
    Serial.println("stato 2 :");
    Serial.println(stato[2]);
    Serial.println("b 2 :");
    Serial.println(b[2]);
   }else{
     digitalWrite(Ledv[2], LOW);
   
  
  }
 if(val[2] == 1 && stato[2] == 1){
  stato[2] = 0;
  
  }

  val[3] = digitalRead(sensor[3]); //Read the sensor
 
  if(val[3] == 0 && stato[3] == 0) //when magnetic field is detected, turn led on
  {
    if (b[3] <= 3){ 
      myDFPlayer.play(2);
      a = 0;
      while (a <= 4){
        digitalWrite(Ledv[3], HIGH);
        delay (tempo);
        digitalWrite(Ledv[3], LOW);
        delay (tempo);
      
        a = a + 1;
    } 
    }
    stato[3] = 1;
    b[3]= b[3] + 1;
    Serial.println("stato 3 :");
    Serial.println(stato[3]);
    Serial.println("b 3 :");
    Serial.println(b[3]);
   }else{
     digitalWrite(Ledv[3], LOW);
   
  
  }
 if(val[3] == 1 && stato[3] == 1){
  stato[3] = 0;
  
  }

  val[4] = digitalRead(sensor[4]); //Read the sensor
 
  if(val[4] == 0 && stato[4] == 0) //when magnetic field is detected, turn led on
  {
    if (b[4] <= 3){ 
      myDFPlayer.play(13);
      a = 0;
      while (a <= 4){
        digitalWrite(Ledv[4], HIGH);
        delay (tempo);
        digitalWrite(Ledv[4], LOW);
        delay (tempo);
      
        a = a + 1;
    } 
    }
    stato[4] = 1;
    b[4]= b[4] + 1;
    Serial.println("stato 4 :");
    Serial.println(stato[4]);
    Serial.println("b 4 :");
    Serial.println(b[4]);
   }else{
     digitalWrite(Ledv[4], LOW);
   
  
  }
 if(val[4] == 1 && stato[4] == 1){
  stato[4] = 0;
  
  }

  val[5] = digitalRead(sensor[5]); //Read the sensor
 
  if(val[5] == 0 && stato[5] == 0) //when magnetic field is detected, turn led on
  {
    if (b[5] <= 3){  
      myDFPlayer.play(17);
      a = 0;
      while (a <= 4){
        digitalWrite(Ledv[5], HIGH);
        delay (tempo);
        digitalWrite(Ledv[5], LOW);
        delay (tempo);
      
        a = a + 1;
    } 
    }
    stato[5] = 1;
    b[5]= b[5] + 1;
    Serial.println("stato 5 :");
    Serial.println(stato[5]);
    Serial.println("b 5 :");
    Serial.println(b[5]);
   }else{
     digitalWrite(Ledv[5], LOW);
   
  
  }
 if(val[5] == 1 && stato[5] == 1){
  stato[5] = 0;
  
  }

  val[6] = digitalRead(sensor[6]); //Read the sensor
 
  if(val[6] == 0 && stato[6] == 0) //when magnetic field is detected, turn led on
  {
    if (b[6] <= 3){ 
      myDFPlayer.play(9);
      a = 0;
      while (a <= 4){
        digitalWrite(Ledv[6], HIGH);
        delay (tempo);
        digitalWrite(Ledv[6], LOW);
        delay (tempo);
      
        a = a + 1;
    } 
    }
    stato[6] = 1;
    b[6]= b[6] + 1;
    Serial.println("stato 6 :");
    Serial.println(stato[6]);
    Serial.println("b 6 :");
    Serial.println(b[6]);
   }else{
     digitalWrite(Ledv[6], LOW);
   
  
  }
 if(val[6] == 1 && stato[6] == 1){
  stato[6] = 0;
  
  }

  val[7] = digitalRead(sensor[7]); //Read the sensor
 
  if(val[7] == 0 && stato[7] == 0) //when magnetic field is detected, turn led on
  {
    if (b[7] <= 3){  
      myDFPlayer.play(15);
      a = 0;
      while (a <= 4){
        digitalWrite(Ledv[7], HIGH);
        delay (tempo);
        digitalWrite(Ledv[7], LOW);
        delay (tempo);
      
        a = a + 1;
    } 
    }
    stato[7] = 1;
    b[7]= b[7] + 1;
    Serial.println("stato 7 :");
    Serial.println(stato[7]);
    Serial.println("b 7 :");
    Serial.println(b[7]);
   }else{
     digitalWrite(Ledv[7], LOW);
   
  
  }
 if(val[7] == 1 && stato[7] == 1){
  stato[7] = 0;
  
  }

  val[8] = digitalRead(sensor[8]); //Read the sensor
 
  if(val[8] == 0 && stato[8] == 0) //when magnetic field is detected, turn led on
  {
    if (b[8] <= 3){ 
      myDFPlayer.play(5);
      a = 0;
      while (a <= 4){
        digitalWrite(Ledv[8], HIGH);
        delay (tempo);
        digitalWrite(Ledv[8], LOW);
        delay (tempo);
      
        a = a + 1;
    } 
    }
    stato[8] = 1;
    b[8]= b[8] + 1;
    Serial.println("stato 8 :");
    Serial.println(stato[8]);
    Serial.println("b 8 :");
    Serial.println(b[8]);
   }else{
     digitalWrite(Ledv[8], LOW);
   
  
  }
 if(val[8] == 1 && stato[8] == 1){
  stato[8] = 0;
  
  }
// tutte le forme sono al loro posto parte lo spettacolo  
  if (stato [0] == 1 && stato [1] == 1 && stato [2] == 1 && stato [3] == 1 && stato [4] == 1 && stato [5] == 1 && stato [6] == 1 && stato [7] == 1 && stato [8] == 1){ 
    Serial.println("passaggio fase3");
    digitalWrite (Led[0], HIGH); // accende il led di blu fase 3
    digitalWrite (Led[1], HIGH);
    digitalWrite (Led[2], LOW);    
    delay (1000);
    myDFPlayer.play(10);
    a = 0;
    while (a <= 21){ // a mantiene il gioco di luci per 16 secondi come la durata della musica
      digitalWrite(Ledr[0], HIGH);
      digitalWrite(Ledr[1], HIGH);
      digitalWrite(Ledr[2], HIGH);
      digitalWrite(Ledr[3], HIGH);
      digitalWrite(Ledr[4], HIGH);
      digitalWrite(Ledr[5], HIGH);
      digitalWrite(Ledr[6], HIGH);
      digitalWrite(Ledr[7], HIGH);
      digitalWrite(Ledr[8], HIGH);
      delay (250);
      digitalWrite (Ledr[0], LOW);
      digitalWrite (Ledr[1], LOW);
      digitalWrite (Ledr[2], LOW);
      digitalWrite (Ledr[3], LOW);
      digitalWrite (Ledr[4], LOW);
      digitalWrite (Ledr[5], LOW);
      digitalWrite (Ledr[6], LOW);
      digitalWrite (Ledr[7], LOW);
      digitalWrite (Ledr[8], LOW);
                    
      digitalWrite(Ledb[0], HIGH);
      digitalWrite(Ledb[1], HIGH);
      digitalWrite(Ledb[2], HIGH);
      digitalWrite(Ledb[3], HIGH);
      digitalWrite(Ledb[4], HIGH);
      digitalWrite(Ledb[5], HIGH);
      digitalWrite(Ledb[6], HIGH);
      digitalWrite(Ledb[7], HIGH);
      digitalWrite(Ledb[8], HIGH);
      delay (250);
      digitalWrite (Ledb[0], LOW);
      digitalWrite (Ledb[1], LOW);
      digitalWrite (Ledb[2], LOW);
      digitalWrite (Ledb[3], LOW);
      digitalWrite (Ledb[4], LOW);
      digitalWrite (Ledb[5], LOW);
      digitalWrite (Ledb[6], LOW);
      digitalWrite (Ledb[7], LOW);
      digitalWrite (Ledb[8], LOW);
      
      digitalWrite(Ledv[0], HIGH);
      digitalWrite(Ledv[1], HIGH);
      digitalWrite(Ledv[2], HIGH);
      digitalWrite(Ledv[3], HIGH);
      digitalWrite(Ledv[4], HIGH);
      digitalWrite(Ledv[5], HIGH);
      digitalWrite(Ledv[6], HIGH);
      digitalWrite(Ledv[7], HIGH);
      digitalWrite(Ledv[8], HIGH);
      delay (250);
      digitalWrite (Ledv[0], LOW);
      digitalWrite (Ledv[1], LOW);
      digitalWrite (Ledv[2], LOW);
      digitalWrite (Ledv[3], LOW);
      digitalWrite (Ledv[4], LOW);
      digitalWrite (Ledv[5], LOW);
      digitalWrite (Ledv[6], LOW);
      digitalWrite (Ledv[7], LOW);
      digitalWrite (Ledv[8], LOW);      
      
      a = a + 1;
    }
    caso = fase3;  // passa a fase 3

  }
 
  delay (20);
  
  
  break;


case fase3: // togli le forme dal gioco

  for ( int i = 0;i < 9; i++){  // contatore b[] = 0
    b[i] = 0;
   }
  val[9] = analogRead(sensor[9]); // controllo batteria
  if (val[9]>990) //se valore maggiore di 573 allora....
   {
    digitalWrite (Led[3], LOW);
    digitalWrite (Led[4], HIGH);
    digitalWrite (Led[5], HIGH);
   }
  if ((val[9]<990)&&(val[9] >=900)) //se valore maggiore di 450 e valore minore di 573 allora....
   {
    digitalWrite (Led[3], HIGH);
    digitalWrite (Led[4], HIGH);
    digitalWrite (Led[5], LOW);
   }
  if (val[9]<900)//se valore minore di 450 allora....
   {
    digitalWrite (Led[3], HIGH);
    digitalWrite (Led[4], LOW);
    digitalWrite (Led[5], HIGH);
   }

  val[0] = digitalRead(sensor[0]); //Read the sensor
 
  if(val[0] == 1 && costo[0] == 1){
    costo[0] = 0;
    Serial.println("val 0 :");
    Serial.println(val[0]);    
    Serial.println("costo 0 :");
    Serial.println(costo[0]);
  }
  if(val[0] == 0 && costo[0] == 0){
    costo[0] = 1;  
  }
  
  
  val[1] = digitalRead(sensor[1]); //Read the sensor
 
  if(val[1] == 1 && costo[1] == 1){
    costo[1] = 0;
    Serial.println("val 1 :");
    Serial.println(val[1]);    
    Serial.println("costo 1 :");
    Serial.println(costo[1]);
  }
  if(val[1] == 0 && costo[1] == 0){
    costo[1] = 1;
  
  }

  val[2] = digitalRead(sensor[2]); //Read the sensor
 
  if(val[2] == 1 && costo[2] == 1){
    costo[2] = 0;
    Serial.println("val 2 :");
    Serial.println(val[2]);    
    Serial.println("costo 2 :");
    Serial.println(costo[2]);
  }
  if(val[2] == 0 && costo[2] == 0){
    costo[2] = 1;  
  }  


  val[3] = digitalRead(sensor[3]); //Read the sensor
 
  if(val[3] == 1 && costo[3] == 1){
    costo[3] = 0;
    Serial.println("val 3 :");
    Serial.println(val[3]);    
    Serial.println("costo 3 :");
    Serial.println(costo[3]);
  }
  if(val[3] == 0 && costo[3] == 0){
    costo[3] = 1;  
  }

  val[4] = digitalRead(sensor[4]); //Read the sensor
 
  if(val[4] == 1 && costo[4] == 1){
    costo[4] = 0;
    Serial.println("val 4 :");
    Serial.println(val[4]);    
    Serial.println("costo 4 :");
    Serial.println(costo[4]);
  }
  if(val[4] == 0 && costo[4] == 0){
    costo[4] = 1;  
  }


  val[5] = digitalRead(sensor[5]); //Read the sensor
 
  if(val[5] == 1 && costo[5] == 1){
    costo[5] = 0;
    Serial.println("val 5 :");
    Serial.println(val[5]);    
    Serial.println("costo 5 :");
    Serial.println(costo[5]);
  }
  if(val[5] == 0 && costo[5] == 0){
    costo[5] = 1;  
  }

  val[6] = digitalRead(sensor[6]); //Read the sensor
 
  if(val[6] == 1 && costo[6] == 1){
    costo[6] = 0;
    Serial.println("val 6 :");
    Serial.println(val[6]);    
    Serial.println("costo 6 :");
    Serial.println(costo[6]);
  }
  if(val[6] == 0 && costo[6] == 0){
    costo[6] = 1;  
  }

  val[7] = digitalRead(sensor[7]); //Read the sensor
 
  if(val[7] == 1 && costo[7] == 1){
    costo[7] = 0;
    Serial.println("val 7 :");
    Serial.println(val[7]);    
    Serial.println("costo 7 :");
    Serial.println(costo[7]);
  }
  if(val[7] == 0 && costo[7] == 0){
    costo[7] = 1;  
  }

  val[8] = digitalRead(sensor[8]); //Read the sensor
 
  if(val[8] == 1 && costo[8] == 1){
    costo[8] = 0;
    Serial.println("val 8 :");
    Serial.println(val[8]);    
    Serial.println("costo 8 :");
    Serial.println(costo[8]);
  }
  if(val[8] == 0 && costo[8] == 0){
    costo[8] = 1;  
  }          
  if (costo[0] == 0 && costo[1] == 0 && costo[2] == 0 && costo[3] == 0 && costo[4] == 0 && costo[5] == 0 && costo[6] == 0 && costo[7] == 0 && costo[8] == 0){ 
    Serial.println("passaggio fase4");
    digitalWrite (Led[0], HIGH); // spegni il led fase 4
    digitalWrite (Led[1], HIGH);
    digitalWrite (Led[2], HIGH);        
    caso = fase4;  // passa a fase 4

    }
  delay (20);
  break;
  
case fase4: // metti le forme nel gioco

  val[9] = analogRead(sensor[9]);  // controllo batteria
  if (val[9]>990) //se valore maggiore di 573 allora....
   {
    digitalWrite (Led[3], LOW);
    digitalWrite (Led[4], HIGH);
    digitalWrite (Led[5], HIGH);
   }
  if ((val[9]<990)&&(val[9] >=900)) //se valore maggiore di 450 e valore minore di 573 allora....
   {
    digitalWrite (Led[3], HIGH);
    digitalWrite (Led[4], HIGH);
    digitalWrite (Led[5], LOW);
   }
    if (val[9]<900)//se valore minore di 450 allora....
   {
    digitalWrite (Led[3], HIGH);
    digitalWrite (Led[4], LOW);
    digitalWrite (Led[5], HIGH);
   }

  val[0] = digitalRead(sensor[0]); //Read the sensor
 
  if(val[0] == 0 && stato[0] == 0) //when magnetic field is detected, turn led on
  {
    if (b[0] <= 3){  // b controlla che lo spettacolo venga eseguito solo 4 volte     
      myDFPlayer.play(3);
      a = 0;
      while (a <= 4){  // a controlla che i led vengano accesi per 5 volte
        digitalWrite(Ledv[0], HIGH);
        delay (tempo);
        digitalWrite(Ledv[0], LOW);
        delay (tempo);
        a = a + 1;
    } 
    }
    stato[0] = 1;
    b[0]= b[0] + 1;
    Serial.println("stato 0 :");
    Serial.println(stato[0]);
    Serial.println("b 0 :");
    Serial.println(b[0]);
 }else{
    digitalWrite(Ledv[0], LOW);
   
  
  }
  if(val[0] == 1 && stato[0] == 1){
  stato[0] = 0;

  }



  val[1] = digitalRead(sensor[1]); //Read the sensor
 
  if(val[1] == 0 && stato[1] == 0) //when magnetic field is detected, turn led on
  {
    if (b[1] <= 3){
      myDFPlayer.play(1); 
      a = 0;
      while (a <= 4){
        digitalWrite(Ledv[1], HIGH);
        delay (tempo);
        digitalWrite(Ledv[1], LOW);
        delay (tempo);
        a = a + 1;
    } 
    }
    stato[1] = 1;
    b[1]= b[1] + 1;
    Serial.println("stato 1 :");
    Serial.println(stato[1]);
    Serial.println("b 1 :");
    Serial.println(b[1]);
 }else{
    digitalWrite(Ledv[1], LOW);
   
  
  }
 if(val[1] == 1 && stato[1] == 1){
  stato[1] = 0;
  }


  val[2] = digitalRead(sensor[2]); //Read the sensor
 
  if(val[2] == 0 && stato[2] == 0) //when magnetic field is detected, turn led on
  {
    if (b[2] <= 3){ 
      myDFPlayer.play(8);
      a = 0;
      while (a <= 4){
        digitalWrite(Ledv[2], HIGH);
        delay (tempo);
        digitalWrite(Ledv[2], LOW);
        delay (tempo);
        a = a + 1;
    } 
    }
    stato[2] = 1;
    b[2]= b[2] + 1;
    Serial.println("stato 2 :");
    Serial.println(stato[2]);
    Serial.println("b 2 :");
    Serial.println(b[2]);
 }else{
    digitalWrite(Ledv[2], LOW);
   
  
  }
  if(val[2] == 1 && stato[2] == 1){
  stato[2] = 0;

  }

  val[3] = digitalRead(sensor[3]); //Read the sensor
 
  if(val[3] == 0 && stato[3] == 0) //when magnetic field is detected, turn led on
  {
    if (b[3] <= 3){ 
      myDFPlayer.play(4);
      a = 0;
      while (a <= 4){
        digitalWrite(Ledv[3], HIGH);
        delay (tempo);
        digitalWrite(Ledv[3], LOW);
        delay (tempo);
        a = a + 1;
    } 
    }
    stato[3] = 1;
    b[3]= b[3] + 1;
    Serial.println("stato 3 :");
    Serial.println(stato[3]);
    Serial.println("b 3 :");
    Serial.println(b[3]);
 }else{
    digitalWrite(Ledv[3], LOW);
   
  
  }
  if(val[3] == 1 && stato[3] == 1){
  stato[3] = 0;

  }  

  val[4] = digitalRead(sensor[4]); //Read the sensor
 
  if(val[4] == 0 && stato[4] == 0) //when magnetic field is detected, turn led on
  {
    if (b[4] <= 3){ 
      myDFPlayer.play(14);
      a = 0;
      while (a <= 4){
        digitalWrite(Ledv[4], HIGH);
        delay (tempo);
        digitalWrite(Ledv[4], LOW);
        delay (tempo);
        a = a + 1;
    } 
    }
    stato[4] = 1;
    b[4]= b[4] + 1;
    Serial.println("stato 4 :");
    Serial.println(stato[4]);
    Serial.println("b 4 :");
    Serial.println(b[4]);
 }else{
    digitalWrite(Ledv[4], LOW);
   
  
  }
  if(val[4] == 1 && stato[4] == 1){
  stato[4] = 0;

  }

  val[5] = digitalRead(sensor[5]); //Read the sensor
 
  if(val[5] == 0 && stato[5] == 0) //when magnetic field is detected, turn led on
  {
    if (b[5] <= 3){  
      myDFPlayer.play(18);
      a = 0;
      while (a <= 4){
        digitalWrite(Ledv[5], HIGH);
        delay (tempo);
        digitalWrite(Ledv[5], LOW);
        delay (tempo);
        a = a + 1;
    } 
    }
    stato[5] = 1;
    b[5]= b[5] + 1;
    Serial.println("stato 5 :");
    Serial.println(stato[5]);
    Serial.println("b 5 :");
    Serial.println(b[5]);
 }else{
    digitalWrite(Ledv[5], LOW);
   
  
  }
  if(val[5] == 1 && stato[5] == 1){
  stato[5] = 0;

  }

  val[6] = digitalRead(sensor[6]); //Read the sensor
 
  if(val[6] == 0 && stato[6] == 0) //when magnetic field is detected, turn led on
  {
    if (b[6] <= 3){  
      myDFPlayer.play(11);
      a = 0;
      while (a <= 4){
        digitalWrite(Ledv[6], HIGH);
        delay (tempo);
        digitalWrite(Ledv[6], LOW);
        delay (tempo);
        a = a + 1;
    } 
    }
    stato[6] = 1;
    b[6]= b[6] + 1;
    Serial.println("stato 6 :");
    Serial.println(stato[6]);
    Serial.println("b 6 :");
    Serial.println(b[6]);
 }else{
    digitalWrite(Ledv[6], LOW);
   
  
  }
  if(val[6] == 1 && stato[6] == 1){
  stato[6] = 0;

  }

  val[7] = digitalRead(sensor[7]); //Read the sensor
 
  if(val[7] == 0 && stato[7] == 0) //when magnetic field is detected, turn led on
  {
    if (b[7] <= 3){ 
      myDFPlayer.play(16);
      a = 0;
      while (a <= 4){
        digitalWrite(Ledv[7], HIGH);
        delay (tempo);
        digitalWrite(Ledv[7], LOW);
        delay (tempo);
        a = a + 1;
    } 
    }
    stato[7] = 1;
    b[7]= b[7] + 1;
    Serial.println("stato 7 :");
    Serial.println(stato[7]);
    Serial.println("b 7 :");
    Serial.println(b[7]);
 }else{
    digitalWrite(Ledv[7], LOW);
   
  
  }
  if(val[7] == 1 && stato[7] == 1){
  stato[7] = 0;

  }

  val[8] = digitalRead(sensor[8]); //Read the sensor
 
  if(val[8] == 0 && stato[8] == 0) //when magnetic field is detected, turn led on
  {
    if (b[8] <= 3){ 
      myDFPlayer.play(6);
      a = 0;
      while (a <= 4){
        digitalWrite(Ledv[8], HIGH);
        delay (tempo);
        digitalWrite(Ledv[8], LOW);
        delay (tempo);
        a = a + 1;
    }
    }  
    stato[8] = 1;
    b[8]= b[8] + 1;
    Serial.println("stato 8 :");
    Serial.println(stato[8]);
    Serial.println("b 8 :");
    Serial.println(b[8]);
 }else{
    digitalWrite(Ledv[8], LOW);
   
  
  }
  if(val[8] == 1 && stato[8] == 1){
  stato[8] = 0;

  }      
  if (stato [0] == 1 && stato [1] == 1 && stato [2] == 1 && stato [3] == 1 && stato [4] == 1 && stato [5] == 1 && stato [6] == 1 && stato [7] == 1 && stato [8] == 1){    
    Serial.println("passaggio fase1");
    digitalWrite (Led[0], LOW);  // accende il led di verde fase 1
    digitalWrite (Led[1], HIGH);
    digitalWrite (Led[2], HIGH);
    delay (1000);
    myDFPlayer.play(10);
    a = 0;
    while (a <= 21){  // a mantiene il gioco di luci per 16 secondi come la durata della musica
      digitalWrite(Ledr[0], HIGH);
      digitalWrite(Ledr[1], HIGH);
      digitalWrite(Ledr[2], HIGH);
      digitalWrite(Ledr[3], HIGH);
      digitalWrite(Ledr[4], HIGH);
      digitalWrite(Ledr[5], HIGH);
      digitalWrite(Ledr[6], HIGH);
      digitalWrite(Ledr[7], HIGH);
      digitalWrite(Ledr[8], HIGH);
      delay (250);
      digitalWrite (Ledr[0], LOW);
      digitalWrite (Ledr[1], LOW);
      digitalWrite (Ledr[2], LOW);
      digitalWrite (Ledr[3], LOW);
      digitalWrite (Ledr[4], LOW);
      digitalWrite (Ledr[5], LOW);
      digitalWrite (Ledr[6], LOW);
      digitalWrite (Ledr[7], LOW);
      digitalWrite (Ledr[8], LOW);
                    
      digitalWrite(Ledb[0], HIGH);
      digitalWrite(Ledb[1], HIGH);
      digitalWrite(Ledb[2], HIGH);
      digitalWrite(Ledb[3], HIGH);
      digitalWrite(Ledb[4], HIGH);
      digitalWrite(Ledb[5], HIGH);
      digitalWrite(Ledb[6], HIGH);
      digitalWrite(Ledb[7], HIGH);
      digitalWrite(Ledb[8], HIGH);
      delay (250);
      digitalWrite (Ledb[0], LOW);
      digitalWrite (Ledb[1], LOW);
      digitalWrite (Ledb[2], LOW);
      digitalWrite (Ledb[3], LOW);
      digitalWrite (Ledb[4], LOW);
      digitalWrite (Ledb[5], LOW);
      digitalWrite (Ledb[6], LOW);
      digitalWrite (Ledb[7], LOW);
      digitalWrite (Ledb[8], LOW);
      
      digitalWrite(Ledv[0], HIGH);
      digitalWrite(Ledv[1], HIGH);
      digitalWrite(Ledv[2], HIGH);
      digitalWrite(Ledv[3], HIGH);
      digitalWrite(Ledv[4], HIGH);
      digitalWrite(Ledv[5], HIGH);
      digitalWrite(Ledv[6], HIGH);
      digitalWrite(Ledv[7], HIGH);
      digitalWrite(Ledv[8], HIGH);
      delay (250);
      digitalWrite (Ledv[0], LOW);
      digitalWrite (Ledv[1], LOW);
      digitalWrite (Ledv[2], LOW);
      digitalWrite (Ledv[3], LOW);
      digitalWrite (Ledv[4], LOW);
      digitalWrite (Ledv[5], LOW);
      digitalWrite (Ledv[6], LOW);
      digitalWrite (Ledv[7], LOW);
      digitalWrite (Ledv[8], LOW);      
      
      a = a + 1;  

  
    }
    caso = fase1; // passa a fase 1
  }
 
  delay (20);

  break;

}
}
 



 
