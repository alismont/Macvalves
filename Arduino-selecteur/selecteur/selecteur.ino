/******************************************************************
 Created with PROGRAMINO IDE for Arduino - 11.02.2017 00:32:42
 Project     :
 Libraries   :
 Author      :
 Description :
******************************************************************/

#include <EEPROM.h>


float P5VF4,P0_5VF4=2.50,P1_5VF4=2.51,P2_5VF4=2.52,P3_5VF4=2.53;
float P6VF4,P0_6VF4=2.60,P1_6VF4=2.60,P2_6VF4=2.60,P3_6VF4=2.60;
int intP5VF4,intP0_5VF4,intP1_5VF4,intP2_5VF4,intP3_5VF4; //en eprom
int intP6VF4,intP0_6VF4,intP1_6VF4,intP2_6VF4,intP3_6VF4; //en eprom
int adresse;
int seq=1,val,val1;
int prog; //0 à 3


char octetReception;
char caractereReception;
char octetReceptionProc;
char caractereReceptionProc;
String chaineReception, Tram;
String chaineReceptionProc, TramProc;


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

  pinMode(2, INPUT); 
  pinMode(3, INPUT);
digitalWrite(2, HIGH);
digitalWrite(3, HIGH);

Serial1.begin(9600);
Serial.begin(9600);

LecturePrg();
}

//-------------
void loop()
{    
    // sequence
    switch (seq) 
    {
      case 1: 
            LectureEprom();
            seq=2;
        break;
        
      case 2: 
            LecturePrg();
            seq=3;
        break;
   
      case 3: 
            AffichageParam();
            seq=4;
        break;
      case 4: 
            Reception();// de processing chg valeur
            seq=1;
        break;     
    }
 

delay(10);
    
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

      break;
      case 1: 
        P5VF4=P1_5VF4;  

      break;
      case 2: 
        P5VF4=P2_5VF4;  

      break;
      case 3: 
        P5VF4=P3_5VF4;  

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
        
        //Serial.println(P0_5VF4);
        //        Serial.println(P1_5VF4);
        //                Serial.println(P2_5VF4);
        //                        Serial.println(P3_5VF4);

  intP0_6VF4= lireInt(8); // octets 8,9
  P0_6VF4=float(intP0_6VF4)/100;
    intP1_6VF4=lireInt(10); // octets 10,11
    P1_6VF4=float(intP1_6VF4)/100;
      intP2_6VF4=lireInt(12); // octets 12,13
      P2_6VF4=float(intP2_6VF4)/100;
        intP3_6VF4=lireInt(14); // octets 14,15
        P3_6VF4=float(intP3_6VF4)/100;
        
              //Serial.println(P0_6VF4);
              //  Serial.println(P1_6VF4);
              //          Serial.println(P2_6VF4);
              //                  Serial.println(P3_6VF4);
}

//***************************
void EcritureEprom5VF4()
{
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
// si sel sur  ---programme x--
    switch (prog) {
      case 0: 
          intP0_6VF4=int(P6VF4 *100);
          sauverInt(0, intP0_5VF4); 
          break;
      case 1: 
          intP1_6VF4=int(P6VF4 *100);
          sauverInt(2, intP1_5VF4); 
          break;
      case 2: 
          intP2_6VF4=int(P6VF4 *100);      
          sauverInt(4, intP2_5VF4); 
          break;
      case 3: 
          intP3_6VF4=int(P6VF4 *100);       
          sauverInt(6, intP3_5VF4); 
          break;
      }
}
//**********************************
void Reception() {
while (Serial1.available() > 0) { 

    octetReception = Serial1.read(); 
    
    if (octetReception == 13) { 
          
          
        if (chaineReception.substring(0, 4) == "5VF4")  
        {
          String InString;
          InString = chaineReception.substring(4);
          P5VF4=InString.toFloat();
          EcritureEprom5VF4();         
        }
        
        if (chaineReception.substring(0, 4) == "6VF4")  
        {
          String InString;
          InString = chaineReception.substring(4);
          P6VF4=InString.toFloat();
          EcritureEprom6VF4();         
        }        
      chaineReception = ""; 
      break; 
    }
    else { 
      caractereReception = char(octetReception); 
      chaineReception = chaineReception + caractereReception; 
      delay(1); // laisse le temps au caractères d'arriver
    }

    }
}

//***********************************
void AffichageParam(){

  Serial.print("5VF4:");
  Serial.println(P5VF4);
  
    Serial.print("6VF4:");
  Serial.println(P6VF4);
}