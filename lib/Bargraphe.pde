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
    textSize(62);
    text(h+"/"+m+"/"+s, 1700, 50);
  }

  void Start() {                                                               // chargement image
    img = loadImage("BarGraphe1.jpg");
  }            

  void Running(int inImgX, int inImgY) {                                                            // affichage image
    image(img, inImgX, inImgY, img.width*2, img.height*2);
  }

  float Integration(float _yB, int _PointBLx, int _PointBLy, int _LargeurX, float Hcoef1, float Hcoef2) {    // intégration affichage
    yB=_yB;// hauteur en pourcent
    yBSM=((yBSM*100)+yB)/101;

    H = ((Hcoef1*yB) + Hcoef2); // mise à échelle 0-1000% 1/10de% vers pixel 
    println(H);
    fill(253, 86, 99);
    rect( _PointBLx, _PointBLy, _LargeurX, H, 20);
    textSize(20);
    text(String.format("%.2f", yBSM), _PointBLx, _PointBLy-545);
    return (yBSM) ;
  }
}