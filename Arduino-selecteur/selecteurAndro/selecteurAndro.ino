/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 11.02.2017 00:32:42
 Project     :
 Libraries   :
 Author      :
 Description :
******************************************************************/

#include <EEPROM.h>
#include "VirtuinoBluetooth.h" 

float P5VF4,P0_5VF4=2.50,P1_5VF4=2.51,P2_5VF4=2.52,P3_5VF4=2.53;
float P5VF4memo=999;
float P6VF4,P0_6VF4=2.60,P1_6VF4=2.60,P2_6VF4=2.60,P3_6VF4=2.60;
float P6VF4memo=999;
int intP5VF4,intP0_5VF4,intP1_5VF4,intP2_5VF4,intP3_5VF4; 
int intP6VF4,intP0_6VF4,intP1_6VF4,intP2_6VF4,intP3_6VF4;

float P5VF5,P0_5VF5=10000,P1_5VF5=10000,P2_5VF5=10000,P3_5VF5=10000;
float P5VF5memo=999;
float P6VF5,P0_6VF5=5000,P1_6VF5=5000,P2_6VF5=5000,P3_6VF5=5000;
float P6VF5memo=999;
int intP5VF5,intP0_5VF5,intP1_5VF5,intP2_5VF5,intP3_5VF5; 
int intP6VF5,intP0_6VF5,intP1_6VF5,intP2_6VF5,intP3_6VF5;
 
int adresse;
int seq=1,val,val1;
int prog; //0 à 3


char octetReception;
char caractereReception;
char octetReceptionProc;
char caractereReceptionProc;
String chaineReception, Tram;
String chaineReceptionProc, TramProc;
char charVal[10]; 

int ValChg=0;
char CR=13;
int Lu=1;

 VirtuinoBluetooth virtuino(Serial1,9600);                                                             
float Testread=0.00;

//-------------
void setup()
{

//sauverInt(0, 250); 
//  sauverInt(2, 251); 
//   sauverInt(4, 252); 
//    sauverInt(6, 253);
//    
// sauverInt(8, 260); 
//  sauverInt(10, 261); 
//   sauverInt(12, 262); 
//    sauverInt(14, 263); 
//
//
//sauverInt(16, 10000); 
//  sauverInt(18, 10000); 
//   sauverInt(20, 10000); 
//    sauverInt(22, 10000);
//    
// sauverInt(24, 5000); 
//  sauverInt(26, 5000); 
//   sauverInt(28, 5000); 
//    sauverInt(30, 5000); 
//

  pinMode(2, INPUT); 
  pinMode(3, INPUT);
digitalWrite(2, HIGH);
digitalWrite(3, HIGH);

Serial1.begin(9600);
Serial.begin(9600);

Serial2.begin(9600,SERIAL_7O1);

Serial3.begin(9600,SERIAL_7O1);

LecturePrg();
}

//-------------
void loop()
{    
   virtuino.run();  
   virtuino.vMemoryWrite(0, prog);
   

   

    // sequence
    switch (seq) 
    {
      case 1: 
            LectureEprom();
            seq=2;
        break;
        
      case 2: 
            LecturePrg();
            seq=4;
        break;
   
      case 3: 
            AffichageParam();
            seq=4;
        break;
      case 4: 
            Reception();
            seq=5;
        break;  
       case 5: 
            EcritureVersGE();
            seq=1;
        break;       
    }

delay(200);
    
}
//*************************************************************
//fonction d'écriture d'un type int en mémoire EEPROM
void sauverInt(int adresse, int lval) 
{   
    //découpage de la variable val qui contient la valeur à sauvegarder en mémoire
    unsigned char faible = lval & 0x00FF; //récupère les 8 bits de droite (poids faible) -> 0010 1100 
    //calcul : 1101 0111 0010 1100 & 0000 0000 1111 1111 = 0010 1100

    unsigned char fort = (lval >> 8) & 0x00FF;  //décale puis récupère les 8 bits de gauche (poids fort) -> 1101 0111
    //calcul : 1101 0111 0010 1100 >> 8 = 0000 0000 1101 0111 puis le même & qu’avant

    //puis on enregistre les deux variables obtenues en mémoire
    EEPROM.write(adresse, fort) ; //on écrit les bits de poids fort en premier
    EEPROM.write(adresse+1, faible) ; //puis on écrit les bits de poids faible à la case suivante
}


//****************
//lecture de la variable de type int enregistrée précédemment par la fonction que l'on a créée
int lireInt(int adresse)
{
    int lval = 0 ; //variable de type int, vide, qui va contenir le résultat de la lecture

    unsigned char fort = EEPROM.read(adresse);     //récupère les 8 bits de gauche (poids fort) -> 1101 0111
    unsigned char faible = EEPROM.read(adresse+1); //récupère les 8 bits de droite (poids faible) -> 0010 1100

    //assemblage des deux variable précédentes
    lval = fort ;         // val vaut alors 0000 0000 1101 0111
    lval = lval << 8 ;     // val vaut maintenant 1101 0111 0000 0000 (décalage)
    lval = lval | faible ; // utilisation du masque
    // calcul : 1101 0111 0000 0000 | 0010 1100 = 1101 0111 0010 1100

    return lval ; //on n’oublie pas de retourner la valeur lue !
}

//*********************
// Lecture sélecteur programme
void LecturePrg()
{

 val = digitalRead(2);
 val1 = digitalRead(3); 
 val1=val1 << 1;
 
  prog=val |val1;

// si sel sur  ---programme x--
    switch (prog) {
      case 0: 
        P5VF4=P0_5VF4;
          P6VF4=P0_6VF4;    
        P5VF5=P0_5VF5; 
          P6VF5=P0_6VF5; 
      break;
      case 1: 
        P5VF4=P1_5VF4;  
          P6VF4=P1_6VF4;    
        P5VF5=P1_5VF5; 
          P6VF5=P1_6VF5; 
      break;
      case 2: 
        P5VF4=P2_5VF4;  
          P6VF4=P2_6VF4;    
        P5VF5=P2_5VF5; 
          P6VF5=P2_6VF5; 
      break;
      case 3: 
        P5VF4=P3_5VF4;  
          P6VF4=P3_6VF4;    
        P5VF5=P3_5VF5; 
          P6VF5=P3_6VF5; 
      break;
      }
}

//************************
// lecture eeprom
void LectureEprom()
{
  intP0_5VF4= lireInt(0); // octets 0,1
  P0_5VF4=float(intP0_5VF4)/100;
    intP1_5VF4=lireInt(2); // octets 2,3
    P1_5VF4=float(intP1_5VF4)/100;
      intP2_5VF4=lireInt(4); // octets 4,5
      P2_5VF4=float(intP2_5VF4)/100;
        intP3_5VF4=lireInt(6); // octets 6,7
        P3_5VF4=float(intP3_5VF4)/100;
        

  intP0_6VF4= lireInt(8); // octets 8,9
  P0_6VF4=float(intP0_6VF4)/100;
    intP1_6VF4=lireInt(10); // octets 10,11
    P1_6VF4=float(intP1_6VF4)/100;
      intP2_6VF4=lireInt(12); // octets 12,13
      P2_6VF4=float(intP2_6VF4)/100;
        intP3_6VF4=lireInt(14); // octets 14,15
        P3_6VF4=float(intP3_6VF4)/100;
        

  intP0_5VF5= lireInt(16); // octets 16
  P0_5VF5=float(intP0_5VF5)/1;
    intP1_5VF5=lireInt(18); // octets 18
    P1_5VF5=float(intP1_5VF5)/1;
      intP2_5VF5=lireInt(20); // octets 20
      P2_5VF5=float(intP2_5VF5)/1;
        intP3_5VF5=lireInt(22); // octets 22
        P3_5VF5=float(intP3_5VF5)/1;
        

  intP0_6VF5= lireInt(24); // octets 24
  P0_6VF5=float(intP0_6VF5)/1;
    intP1_6VF5=lireInt(26); // octets 26
    P1_6VF5=float(intP1_6VF5)/1;
      intP2_6VF5=lireInt(28); // octets 28
      P2_6VF5=float(intP2_6VF5)/1;
        intP3_6VF5=lireInt(30); // octets 30
        P3_6VF5=float(intP3_6VF5)/1;
        
}

//***************************
void EcritureEprom5VF4()
{
ValChg=1;
// si sel sur  ---programme x--
    switch (prog) {
      case 0: 
          intP0_5VF4=int(P5VF4 *100);
          sauverInt(0, intP0_5VF4); 
          break;
      case 1: 
          intP1_5VF4=int(P5VF4 *100);
          sauverInt(2, intP1_5VF4); 
          break;
      case 2: 
          intP2_5VF4=int(P5VF4 *100);      
          sauverInt(4, intP2_5VF4); 
          break;
      case 3: 
          intP3_5VF4=int(P5VF4 *100);       
          sauverInt(6, intP3_5VF4); 
          break;
      }
}

//***************************
void EcritureEprom6VF4()
{
ValChg=1;
// si sel sur  ---programme x--
    switch (prog) {
      case 0: 
          intP0_6VF4=int(P6VF4 *100);
          sauverInt(8, intP0_6VF4); 
          break;
      case 1: 
          intP1_6VF4=int(P6VF4 *100);
          sauverInt(10, intP1_6VF4); 
          break;
      case 2: 
          intP2_6VF4=int(P6VF4 *100);      
          sauverInt(12, intP2_6VF4); 
          break;
      case 3: 
          intP3_6VF4=int(P6VF4 *100);       
          sauverInt(14, intP3_6VF4); 
          break;
      }
}
//**********************************
void EcritureEprom5VF5()
{
ValChg=1;
// si sel sur  ---programme x--
    switch (prog) {
      case 0: 
          intP0_5VF5=int(P5VF5 *1);
          sauverInt(16, intP0_5VF5); 
          break;
      case 1: 
          intP1_5VF5=int(P5VF5 *1);
          sauverInt(18, intP1_5VF5); 
          break;
      case 2: 
          intP2_5VF5=int(P5VF5 *1);      
          sauverInt(20, intP2_5VF5); 
          break;
      case 3: 
          intP3_5VF5=int(P5VF5 *1);       
          sauverInt(22, intP3_5VF5); 
          break;
      }
}


//***************************
void EcritureEprom6VF5()
{
ValChg=1;
// si sel sur  ---programme x--
    switch (prog) {
      case 0: 
          intP0_6VF5=int(P6VF5 *1);
          sauverInt(24, intP0_6VF5); 
          break;
      case 1: 
          intP1_6VF5=int(P6VF5 *1);
          sauverInt(26, intP1_6VF5); 
          break;
      case 2: 
          intP2_6VF5=int(P6VF5 *1);      
          sauverInt(28, intP2_6VF5); 
          break;
      case 3: 
          intP3_6VF5=int(P6VF5 *1);       
          sauverInt(30, intP3_6VF5); 
          break;
      }
}
//*********************************************************
void Reception() {

 P5VF4memo=virtuino.vMemoryRead(1)/100.0;
 if (P5VF4memo!=0){
  if (P5VF4!=P5VF4memo){
    P5VF4=P5VF4memo;
    EcritureEprom5VF4();

  }
} else {
  virtuino.vMemoryWrite(1, P5VF4*100);
          P5VF4memo=P5VF4;
}

 P5VF5memo=virtuino.vMemoryRead(2)*100.0;
 if (P5VF5memo!=0){
  if (P5VF5!=P5VF5memo){
    P5VF5=P5VF5memo;
    EcritureEprom5VF5();

  }
} else {
  virtuino.vMemoryWrite(2, P5VF5/100);
          P5VF5memo=P5VF5;
}


 P6VF4memo=virtuino.vMemoryRead(3)/100.0;
 if (P6VF4memo!=0){
  if (P6VF4!=P6VF4memo){
    P6VF4=P6VF4memo;
    EcritureEprom6VF4();

  }
} else {
  virtuino.vMemoryWrite(3, P6VF4*100);
          P6VF4memo=P6VF4;
}


  P6VF5memo=virtuino.vMemoryRead(4)*100.0;
 if (P6VF5memo!=0){
  if (P6VF5!=P6VF5memo){
    P6VF5=P6VF5memo;
    EcritureEprom6VF5();

  }
} else {
  virtuino.vMemoryWrite(4, P6VF5/100);
          P6VF5memo=P6VF5;
}
  
//Serial.println(P5VF4);
//Serial.println(P5VF5);
//Serial.println(P6VF4);
//Serial.println(P6VF5);

/* while (Serial1.available() > 0) { 

    octetReception = Serial1.read(); 
    
    if (octetReception == 13) { 
          
          
        //if (chaineReception.substring(0, 4) == "5VF4")  
        //{
        //  String InString;
        //  InString = chaineReception.substring(4);
        //  P5VF4=InString.toFloat();
        //  EcritureEprom5VF4();         
        //}

        
        if (chaineReception.substring(0, 4) == "6VF4")  
        {
          String InString;
          InString = chaineReception.substring(4);
          P6VF4=InString.toFloat();
          EcritureEprom6VF4();         
        }  

              if (chaineReception.substring(0, 4) == "5VF5")  
        {
          String InString;
          InString = chaineReception.substring(4);
          P5VF5=InString.toFloat();
          EcritureEprom5VF5();         
        }
        
        if (chaineReception.substring(0, 4) == "6VF5")  
        {
          String InString;
          InString = chaineReception.substring(4);
          P6VF5=InString.toFloat();
          EcritureEprom6VF5();         
        }  
        
          if (chaineReception.substring(0, 2) == "Lu")  
        {
              Lu=0; 
        Serial.println(Lu);      
        }         
      chaineReception = ""; 
      break; 
    }
    else { 
      caractereReception = char(octetReception); 
      chaineReception = chaineReception + caractereReception; 
      delay(1); // laisse le temps au caractères d'arriver
    }

    }*/
}

//***********************************
void AffichageParam(){

/*if (Lu==0){
Lu=1;
Serial.println(Lu);
    dtostrf( P5VF4, 1, 3, charVal);
    TramProc = charVal;
    TramProc = TramProc + "/";
   
    dtostrf( P6VF4, 1, 3, charVal);
    TramProc = TramProc +charVal + "/";
    
    dtostrf( P5VF5, 5, 0, charVal);
    TramProc = TramProc +charVal + "/";
   
    dtostrf( P6VF5, 5, 0, charVal);
    TramProc = TramProc +charVal + "/";

    dtostrf( prog, 1, 0, charVal);
    TramProc = TramProc +charVal + "/"+"*";
    Serial1.print(TramProc); 
    
Serial.println(TramProc); 
 
//    Serial1.print("*");
//Serial.println("*");
      }*/
}

//***********************************
void EcritureVersGE(){

//if (ValChg==1){

   Serial2.print("5VF4=");
    Serial2.print(P5VF4);
        Serial2.write('\r');       
          Serial.println(P5VF4);
    
   Serial3.print("6VF4=");
     Serial3.print(P6VF4);
        Serial3.write('\r');
          Serial.println(P6VF4);        
   
   Serial2.print("5VF5=");
     Serial2.print(P5VF5);
        Serial2.write('\r');
          Serial.println(P5VF5);
          
   Serial3.print("6VF5=");
     Serial3.print(P6VF5);
       Serial3.write('\r');
          Serial.println(P6VF5);
          
ValChg=0;
//}
}
//************************************