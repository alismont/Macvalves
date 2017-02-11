//************************************** PORT SERIE
import processing.serial.*;
import controlP5.*; 

Serial myPort;
int baudRate = 9600;
int lf = 10;

//-- GUI --
ControlP5 cp5;

Textlabel Tl; 

//***************************************
void setup(){
  fullScreen();
  
  println(Serial.list());
 //exemple de liste de ports: COM3 COM24 COM25 COM26 COM30 COM31
  myPort = new Serial(this, Serial.list()[9], baudRate); 
  
  myPort.buffer(1000);
  myPort.clear();

  frameRate(60);
  cp5 = new ControlP5(this);


  Tl= cp5.addTextlabel("label")
    .setText("Profondeur gauche 5VF4: ")
    .setPosition(20, 5)
    .setColorValue(100)
    .setFont(createFont("Georgia", 20))
    ;  

  cp5.addBang("Add")
    .setPosition(250, 30)
    .setSize(80, 30)
    .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
    ; 

  cp5.addTextfield("DB")
    .setPosition(20, 30)
    .setSize(200, 30)
    .setFont(createFont("arial", 30))
    .setAutoClear(false)
    ;

  cp5.addBang("clear")
    .setPosition(350, 35)
    .setSize(80, 20)
    .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
    ; 
//**************************************
  Tl= cp5.addTextlabel("label2")
    .setText("Profondeur droit   6VF4: ")
    .setPosition(20, 75)
    .setColorValue(100)
    .setFont(createFont("Georgia", 20))
    ;  

  cp5.addBang("Add2")
    .setPosition(250, 100)
    .setSize(80, 30)
    .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
    ; 

  cp5.addTextfield("DB2")
    .setPosition(20, 100)
    .setSize(200, 30)
    .setFont(createFont("arial", 30))
    .setAutoClear(false)
    ;

  cp5.addBang("clear2")
    .setPosition(350, 105)
    .setSize(80, 20)
    .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
    ; 

}
 
//******************************** 
void draw()
{
  background(#FEFFFC);
  fill(0);

 lectureBuffer();

}
 
 
//**********************
void lectureBuffer() {
  while (myPort.available() > 0) {
    String inBuffer = myPort.readString();   
    if (inBuffer != null) {
      println(inBuffer);
    }
    
  }
}

//*********************************
//-- Event bouton ADD
public void Add() {
    myPort.write("5VF4");
    myPort.write(cp5.get(Textfield.class, "DB").getText());
    myPort.write(13);
}
//*********************************
//-- Event bouton ADD2
public void Add2() {
    myPort.write("6VF4");
    myPort.write(cp5.get(Textfield.class, "DB2").getText());
    myPort.write(13);
}
//***********************************
//-- Event bouton CLEAR
public void clear() {
  cp5.get(Textfield.class, "DB").clear();
}
//***********************************
//-- Event bouton CLEAR2
public void clear2() {
  cp5.get(Textfield.class, "DB2").clear();
}
//**********************************

 