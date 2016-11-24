BarGraphe barGraphe;
BarGraphe barGraphe2;

int value=0;
float yB=0.00;
float yBPr=0.00;
float yBSM=0.00;
float BG1=0;
float BG2=0;

PFont font;



//*********************************************************************************
void setup() {

   barGraphe = new BarGraphe(500, 90);
   barGraphe2 = new BarGraphe(500, 90);

  size(displayWidth, displayHeight, P3D);
  orientation(LANDSCAPE);

  font = loadFont("Arial-Black-48.vlw");
  barGraphe.Start(); // start bargraphe
  barGraphe2.Start(); // start bargraphe
}

//************************************
void draw() {  

  background(255);// rafraîchissement fond d'écran

  barGraphe.Running(300, 100);// rafraîchissement image
  BG1=barGraphe.Integration(10, 344, 710, 70, -5, 0);// (float _yB, int _PointBLx, int _PointBLy, int _LargeurX)
  barGraphe.Display(); // affichage horloge

  barGraphe2.Running(500, 100);// rafraîchissement image
  BG2=barGraphe2.Integration(50, 544, 710, 70, -5, 0);// (float _yB, int _PointBLx, int _PointBLy, int _LargeurX)
}

//*********************************************************************************************************************************************************************************************************