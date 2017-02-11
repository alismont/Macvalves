 //<>//
import io.inventit.processing.android.serial.*;
//import com.yourinventit.processing.android.serial.*;
import controlP5.*; // importe la librairie GUI controlP5

//-----Variables bargraphe-----------
BarGraphe barGraphe;
BarGraphe barGraphe2;

int value=0;
float yB=0.00;
float yBPr=0.00;
float yBSM=0.00;
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
ControlP5 cp5;    // déclare un objet principal de la librairie  controlP5
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

Toggle togglePause; // déclare un/des objets Toggle

Slider sliderCoeff; // déclare un/ des objet Slider
Slider sliderBase; // déclare un/ des objet Slider

ControlWindow cw1; // déclare un/des objet fenetre ControlWindow 

String[] TextValue = new String[100];
String[] men1= new String[100];
String OKPROC="OKPROC";
String OKFIN="OKFIN";  

//------ Déclaration des variables de couleur utiles ----
int jaune=color(255, 255, 0);
int vert=color(0, 255, 0);
int rouge=color(255, 0, 0);
int bleu=color(0, 0, 255);
int noir=color(0, 0, 0);
int blanc=color(255, 255, 255);
int bleuclair=color(0, 255, 255);
int violet=color(255, 0, 255);

// --- Port Série ---
Serial  myPort; // Création objet désignant le port série

int PasApas=0;
boolean LAI1=false;
boolean LPSA=false;
boolean LPOS1=false;
boolean LDIO=false;

float AI1=0.0;
float PSA=0.0;
String DIO;

float test=0.0;
int Lu=0;

int LectureAI1=0;
int LecturePSA=0;
int LectureADD=0;
int LectureDIO=0;

int scan=0;
int psq=1;
String ADD="";

//*************************** SETUP ***************************************************************************
void setup() {
  //size(2000, 1000);
  fullScreen();
  println(Serial.list(this)); // affiche dans la console la liste des ports s�ries
  myPort = new Serial(this, Serial.list(this)[0], 9600, 'O', 7, 1); // Initialise une nouvelle instance du port S�rie
 
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
  PFont font = createFont("arial", 20); // crée un objet de police texte

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
    .setStrokeWeight(1.5)
    .setColorCaptionLabel(color(40))
    ;

  myChart.addDataSet("incoming");
  myChart.setData("incoming", new float[100]);

  myChart2 = cp5.addChart("dataflow2")
    .setPosition(1220, 400)
    .setSize(500, 200)
    .setRange(-4100, 4100)
    .setView(Chart.LINE) // use Chart.LINE, Chart.PIE, Chart.AREA, Chart.BAR_CENTERED
    .setStrokeWeight(1.5)
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
void draw() {
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
      barGraphe.Running(100, 360);// rafraîchissement image
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
      //barGraphe.Running(1000, 360);// rafraîchissement image
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

void lectureBuffer() {
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
        AI1=float(inBuffer.substring(8));
        LectureAI1=0;
      }

      if (LecturePSA==1) {
        //println(inBuffer.substring(8, 14));
        PSA=float(inBuffer.substring(8));
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
void controlEvent(ControlEvent theEvent) {
  if (theEvent.isAssignableFrom(Textfield.class)) {
    //println("controlEvent: accessing a string from controller "
    //+theEvent.getName()+"': "
    //+theEvent.getStringValue());
  }
  if (theEvent.getName().equals("myList")) {
  }
}


//--  Mouse press
void mousePressed() {
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

  void Display() {

    int s = second();  // Values from 0 - 59 // affichage de l'heure
    int m = minute();  // Values from 0 - 59
    int h = hour();    // Values from 0 - 23
    fill(152);
    textFont(font);
    textSize(30);
    text(h+"/"+m+":"+s, 1000, 50);
  }

  void Start() {                                                               // chargement image
    img = loadImage("BarGraphe1.jpg");
  }            

  void Running(int inImgX, int inImgY) {                                                            // affichage image
    image(img, inImgX, inImgY, img.width*2, img.height*2);
  }

  float Integration(float _yB, int _PointBLx, int _PointBLy, int _LargeurX, float Hcoef1, float Hcoef2) {    // intégration affichage
    yB=_yB;// hauteur en pourcent
    yBSM=((yBSM*5)+yB)/6;

    H = ((Hcoef1*yBSM) + Hcoef2); // mise à échelle 0-1000% 1/10de% vers pixel 
    //println(H);
    fill(253, 86, 99);
    rect( _PointBLx, _PointBLy, _LargeurX, H, 20);
    textSize(20);
    text(String.format("%.2f", yBSM), _PointBLx, _PointBLy-545);
    return (yBSM) ;
  }
}