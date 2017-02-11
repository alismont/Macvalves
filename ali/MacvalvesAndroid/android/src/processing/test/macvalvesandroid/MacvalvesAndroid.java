package processing.test.macvalvesandroid;

import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import io.inventit.processing.android.serial.*; 
import controlP5.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class MacvalvesAndroid extends PApplet {



//import processing.serial.*;  //<>// //<>//
 // importe la librairie GUI controlP5

//-----Variables bargraphe-----------
BarGraphe barGraphe;
BarGraphe barGraphe2;

int value=0;
float yB=0.00f;
float yBPr=0.00f;
float yBSM=0.00f;
float BG1=0;
float BG2=0;

//--------------Variable programme-------
PFont font;

PrintWriter output;
PFont myFont;     // The display font
String inString;  // Input string from serial port
int lf = 10;      // ASCII linefeed 
String t=":";
String[] tag = new String[110];
int MEMOSYN=0;
String TramEcriture="";
int i=0;
int L=50;
char c1;

//--Shape --
PShape s;
PShape s1;
PShape s2;
int sq=0;
//-- GUI --
ControlP5 cp5;    // d\u00e9clare un objet principal de la librairie  controlP5
ListBox l;
Textlabel Tl;
ControlTimer c;
Textlabel tt;
Chart myChart;
Chart myChart2;

//-- Divers --
int TransmissionSQ=0;
int cnt = 0;
int compteur=0;
String Recu="";

BufferedReader reader;
String line;

Toggle togglePause; // d\u00e9clare un/des objets Toggle

Slider sliderCoeff; // d\u00e9clare un/ des objet Slider
Slider sliderBase; // d\u00e9clare un/ des objet Slider

ControlWindow cw1; // d\u00e9clare un/des objet fenetre ControlWindow 

String[] TextValue = new String[100];
String[] men1= new String[100];
String OKPROC="OKPROC";
String OKFIN="OKFIN";  

//------ D\u00e9claration des variables de couleur utiles ----
int jaune=color(255, 255, 0);
int vert=color(0, 255, 0);
int rouge=color(255, 0, 0);
int bleu=color(0, 0, 255);
int noir=color(0, 0, 0);
int blanc=color(255, 255, 255);
int bleuclair=color(0, 255, 255);
int violet=color(255, 0, 255);

// --- Port S\u00e9rie ---
Serial  myPort; // Cr\u00e9ation objet d\u00e9signant le port s\u00e9rie

int PasApas=0;
boolean LAI1=false;
boolean LPSA=false;
boolean LPOS1=false;
boolean LDIO=false;

float AI1=0.0f;
float PSA=0.0f;
String DIO;

float test=0.0f;
int Lu=0;

int LectureAI1=0;
int LecturePSA=0;
int LectureADD=0;
int LectureDIO=0;

int scan=0;
int psq=1;
String ADD="";

//*************************** SETUP ***************************************************************************
public void setup() {
  //size(2000, 1000);
  
  //println(Serial.list()); // affiche dans la console la liste des ports s\ufffdries
  //myPort = new Serial(this, Serial.list()[0], 9600, 'O', 7, 1); // Initialise une nouvelle instance du port S\ufffdrie
  //myPort = new Serial(this, Serial.list(this)[0], 9600, 'O', 7, 1);
  myPort = new Serial(this, Serial.list(this)[0], 9600, 'N', 8, 1); // Initialise une nouvelle instance du port S\ufffdrie
  //myPort.bufferUntil(lf); // attendre arriv\ufffde d'un saut de ligne pour g\ufffdn\ufffdrer \ufffdv\ufffdnement s\ufffdrie 
  myPort.buffer(1000);
  myPort.clear();

  //-- Shape
  s = loadShape("shape1-1.svg");
  s1 = loadShape("shape1-2.svg");
  s2 = loadShape("shape1-3.svg");

  barGraphe = new BarGraphe(500, 90);
  barGraphe2 = new BarGraphe(500, 90);

  //size(displayWidth, displayHeight, P3D);
  orientation(LANDSCAPE);

  font = loadFont("Arial-Black-48.vlw");
  barGraphe.Start(); // start bargraphe
  //barGraphe2.Start(); // start bargraphe

  ControlP5.printPublicMethodsFor(ListBox.class);
  // --- police texte --- 
  PFont font = createFont("arial", 20); // cr\u00e9e un objet de police texte

  //-- Init GUI --
  frameRate(60);
  cp5 = new ControlP5(this);

  c = new ControlTimer();
  tt = new Textlabel(cp5, "--", 120, 120);
  c.setSpeedOfTime(1);
  tt.setPosition(500, 10);
  tt.setFont(createFont("Georgia", 30));


  myChart = cp5.addChart("dataflow")
    .setPosition(300, 400)
    .setSize(500, 200)
    .setRange(-5, 5)
    .setView(Chart.LINE) // use Chart.LINE, Chart.PIE, Chart.AREA, Chart.BAR_CENTERED
    .setStrokeWeight(1.5f)
    .setColorCaptionLabel(color(40))
    ;

  myChart.addDataSet("incoming");
  myChart.setData("incoming", new float[100]);

  myChart2 = cp5.addChart("dataflow2")
    .setPosition(1220, 400)
    .setSize(500, 200)
    .setRange(-4100, 4100)
    .setView(Chart.LINE) // use Chart.LINE, Chart.PIE, Chart.AREA, Chart.BAR_CENTERED
    .setStrokeWeight(1.5f)
    .setColorCaptionLabel(color(40))
    ;

  myChart2.addDataSet("incoming2");
  myChart2.setData("incoming2", new float[100]);

  cp5.addTextfield("DB")
    .setPosition(20, 20)
    .setSize(200, 30)
    .setFont(createFont("arial", 30))
    .setAutoClear(false)
    ;


  Tl= cp5.addTextlabel("label")
    .setText("Valeur: ")
    .setPosition(700, 60)
    .setColorValue(0xffffff00)
    .setFont(createFont("Georgia", 20))
    ;

  cp5.addBang("clear")
    .setPosition(250, 60)
    .setSize(80, 20)
    .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
    ;  

  cp5.addBang("Add")
    .setPosition(250, 20)
    .setSize(80, 30)
    .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
    ;  

  cp5.addBang("AI1")
    .setPosition(130, 220)
    .setSize(80, 20)
    .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
    ;  

  cp5.addBang("PSA")
    .setPosition(130, 250)
    .setSize(80, 20)
    .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
    ; 

  cp5.addBang("EXIT")
    .setPosition(250, 100)
    .setSize(80, 20)
    .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
    ;

  cp5.addBang("DIO")
    .setPosition(130, 280)
    .setSize(80, 20)
    .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
    ;

  background(0);
  textSize(32);
  fill(255, 100, 100);
  //text("MACVALVES..................", 380, 28);

  //-- Init Shape --
  s.setVisible(false);
  s1.setVisible(false);
  s2.setVisible(false);
}

//******************************* MAIN PROGRAMME *********************************************
public void draw() {
  background(0);

  //-- gestion scan
  if (LAI1 && !LPSA) {
    sq=0;
    if (LAI1 && Lu==0 && LectureAI1==0) {
      Lu=1;
      myPort.write("5AI1?");
      myPort.write(13);
      // myPort.write(10);
      LectureAI1=1;
    }
  }

  if (!LAI1 && LPSA) {
    sq=0;
    if (LPSA && Lu==0 && LecturePSA==0) {
      Lu=1;
     myPort.write("5PSA?");
      //myPort.write("5VB5?");
      myPort.write(13);
      //myPort.write(10);
      LecturePSA=1;
    }
  }

  if (LAI1 && LPSA) {
    switch(psq) {
    case 1: 
      //-- Traitement AI1
      if (LAI1 && Lu==0 && LectureAI1==0) {
        Lu=1;
        myPort.write("5AI1?");
        myPort.write(13);
        //myPort.write(10);
        LectureAI1=1;
        psq=2;
      }
      break;
    case 2:
      if (LPSA && Lu==0 && LecturePSA==0) {
        Lu=1;
        myPort.write("5PSA?");
        myPort.write(13);
        //myPort.wr ite(10);
        LecturePSA=1;
        psq=1;
      }
      break;
    }
  }

  if (LDIO) {
    sq=0;
    if (LDIO && Lu==0 && LectureDIO==0) {
      Lu=1;
      myPort.write("5DIN7.8?");
      myPort.write(13);
      //myPort.write(10);
      LectureDIO=1;
    }
  }


  delay(100);
  //--Lecture --
  lectureBuffer();


  //-- Affichage bargraph--

  barGraphe.Display(); // affichage horloge



  //-- Affichage compteur
  tt.setValue(c.toString());
  tt.draw(this);


  //-- Affichage AI--
  if (LAI1) {
    if ( !Float.isNaN(AI1)  ) { 
      fill(250, 226, 5);
      textSize(20);
      text(AI1, 232, 230);
      barGraphe.Running(100, 360);// rafra\u00eechissement image
      //println(AI1);       
      BG1=barGraphe.Integration(AI1, 144, 965, 70, -110, -50);// (float _yB, int _PointBLx, int _PointBLy, int _LargeurX)
    }
  } else {
    fill(250, 226, 5);
    textSize(20);
    text("        ", 232, 230);
  }

  //-- Affichage AI--
  if (LPSA) {
    if ( !Float.isNaN(PSA)  ) {   
      fill(250, 226, 5);
      textSize(20);
      text(PSA, 232, 270);
      //barGraphe.Running(1000, 360);// rafra\u00eechissement image
      //println(PSA);
      //BG1=barGraphe2.Integration(PSA, 1044, 965, 70, -0.50, 0);
    }
  } else {
    fill(250, 226, 5);
    textSize(20);
    text("        ", 232, 270);
  }

  //-- Affichage ADD
  fill(250, 226, 5);
  textSize(20);
  text("Recu: "+ADD, 25, 140);

  //-- Affichage DIO
  if (LDIO) {
    text("DIN7.8: "+DIO, 20, 315);
  } else {
    text("DIN7.8:      ", 20, 315);
  }

  //-- Affichage mouse--
  text(mouseX+"  "+mouseY, 1235, 37);

  //-- Graph --
  myChart.push("incoming", (AI1));
  myChart2.push("incoming2", (PSA));

  //-- Affichage shape --
  shape(s);
  shape(s1);
  shape(s2);
}

//*********************** DEBUT FONCTIONS *************************************

public void lectureBuffer() {
  while (myPort.available() > 0) {
    String inBuffer = myPort.readString();   
    if (inBuffer != null) {


      if (LectureADD==1) {

        //println(inBuffer.substring(0));
        ADD=inBuffer.substring(0);
        LectureADD=0;
      }

      if (LectureAI1==1) {
        //println(inBuffer.substring(8));
        AI1=PApplet.parseFloat(inBuffer.substring(8));
        LectureAI1=0;
      }

      if (LecturePSA==1) {
        //println(inBuffer.substring(8, 14));
        PSA=PApplet.parseFloat(inBuffer.substring(8));
        LecturePSA=0;
      }

      if (LectureDIO==1) {
        //println(inBuffer.substring(11));
        DIO=inBuffer.substring(11);
        println(DIO);
        LectureDIO=0;
      }
    }
    myPort.clear();
    Lu=0;
  }
}

//-- Event bouton CLEAR
public void clear() {
  cp5.get(Textfield.class, "DB").clear();
}

//-- Event bouton ADD
public void Add() {
  if (Lu==0) {
    Lu=1;
    myPort.write(cp5.get(Textfield.class, "DB").getText());
    myPort.write(13);
    //myPort.write(10);
    //println("envoyer"+cp5.get(Textfield.class, "DB").getText());
    LectureADD=1;
  }
}
//-- Set lecture AI1
public void AI1() {
  if (!LAI1) {
    LAI1=true;
    s.setVisible(true);
  } else
  {
    LAI1=false;
    s.setVisible(false);
  }
}

//-- Lecture PSA
public void PSA() {
  if (!LPSA) {
    LPSA=true;
    s1.setVisible(true);
  } else
  {
    LPSA=false;
    s1.setVisible(false);
  }
}
//-- Lecture DIO
public void DIO() {
  if (!LDIO) {
    LDIO=true;
    s2.setVisible(true);
  } else
  {
    LDIO=false;
    s2.setVisible(false);
  }
}
//-- Event
public void controlEvent(ControlEvent theEvent) {
  if (theEvent.isAssignableFrom(Textfield.class)) {
    //println("controlEvent: accessing a string from controller "
    //+theEvent.getName()+"': "
    //+theEvent.getStringValue());
  }
  if (theEvent.getName().equals("myList")) {
  }
}


//--  Mouse press
public void mousePressed() {
  c.reset();
}
//-- Exit bouton
public void EXIT() {
  exit(); // Stops the program
}

//************* CLASS ***************
class BarGraphe
{
  float yB=0;
  float yBPr=0;
  float yBSM=0;
  float H=0;

  boolean running ;
  int x, y ;
  PImage img;

  BarGraphe(int inX, int inY)
  {
    x = inX ;
    y = inY ;
    running = false ;
  }

  public void Display() {

    int s = second();  // Values from 0 - 59 // affichage de l'heure
    int m = minute();  // Values from 0 - 59
    int h = hour();    // Values from 0 - 23
    fill(152);
    textFont(font);
    textSize(30);
    text(h+"/"+m+":"+s, 1000, 50);
  }

  public void Start() {                                                               // chargement image
    img = loadImage("BarGraphe1.jpg");
  }            

  public void Running(int inImgX, int inImgY) {                                                            // affichage image
    image(img, inImgX, inImgY, img.width*2, img.height*2);
  }

  public float Integration(float _yB, int _PointBLx, int _PointBLy, int _LargeurX, float Hcoef1, float Hcoef2) {    // int\u00e9gration affichage
    yB=_yB;// hauteur en pourcent
    yBSM=((yBSM*5)+yB)/6;

    H = ((Hcoef1*yBSM) + Hcoef2); // mise \u00e0 \u00e9chelle 0-1000% 1/10de% vers pixel 
    //println(H);
    fill(253, 86, 99);
    rect( _PointBLx, _PointBLy, _LargeurX, H, 20);
    textSize(20);
    text(String.format("%.2f", yBSM), _PointBLx, _PointBLy-545);
    return (yBSM) ;
  }
}
  public void settings() {  fullScreen(); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "MacvalvesAndroid" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
