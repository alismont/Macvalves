/**
 * ControlP5 Button
 * this example shows how to create buttons with controlP5.
 * 
 * find a list of public methods available for the Button Controller 
 * at the bottom of this sketch's source code
 *
 * by Andreas Schlegel, 2012
 * www.sojamo.de/libraries/controlp5
 *
 */
import android.content.Intent;
import android.os.Bundle;
import ketai.net.bluetooth.*;
import ketai.ui.*;
import ketai.net.*; 
import controlP5.*;

ControlP5 cp5;

int myColor = color(255);

int c1, c2;

float n, n1;

PFont fontMy;
boolean bReleased = true; //no permament sending when finger is tap
KetaiBluetooth bt;
boolean isConfiguring = true;
String info = "";
KetaiList klist;
ArrayList devicesDiscovered = new ArrayList();


//----------------------------------------------------------------------- 
void setup() {


  size(displayWidth, displayHeight);
  noStroke();

  frameRate(10);
  //orientation(PORTRAIT);
  //background(0);

  //start listening for BT connections
  bt.start();
  //at app start select device…
  isConfiguring = true;
  //font size
  fontMy = createFont("SansSerif", 40);
  textFont(fontMy);





  cp5 = new ControlP5(this);

  // create a new button with name 'buttonA'
  cp5.addButton("colorA")
    .setValue(0)
    .setPosition(500, 100)
    .setSize(200, 190)
    ;

  // and add another 2 buttons
  cp5.addButton("colorB")
    .setValue(100)
    .setPosition(100, 120)
    .setSize(200, 19)
    ;

  cp5.addButton("colorC")
    .setPosition(100, 140)
    .setSize(200, 19)
    .setValue(0)
    ;

  PImage[] imgs = {loadImage("button_a.png"), loadImage("button_b.png"), loadImage("button_c.png")};
  cp5.addButton("play")
    .setValue(128)
    .setPosition(140, 300)
    .setImages(imgs)
    .updateSize()
    ;

  cp5.addButton("playAgain")
    .setValue(128)
    .setPosition(210, 300)
    .setImages(imgs)
    .updateSize()
    ;
}

//--------------------------------------------------------------------------------------
void draw() {
  background(myColor);
  myColor = lerpColor(c1, c2, n);
  n += (1-n)* 0.1; 

  //at app start select device
  if (isConfiguring)
  {
    ArrayList names;
    background(78, 93, 75);
    klist = new KetaiList(this, bt.getPairedDeviceNames());
    isConfiguring = false;
  } else
  {
    background(0, 50, 0);
    if ((mousePressed) && (bReleased == true))
    {
      //send with BT
      byte[] data = {'s', 'w', 'i', 't', 'c', 'h', '\r'};
      bt.broadcast(data);
      //first tap off to send next message
      bReleased = false;
    }
    if (mousePressed == false)
    {
      bReleased = true; //finger is up
    }
    //print received data
    fill(255);
    noStroke();
    textAlign(LEFT);
    text(info, 20, 104);
  }
}
//---------------
public void controlEvent(ControlEvent theEvent) {
  println(theEvent.getController().getName());
  n = 0;
}

// function colorA will receive changes from 
// controller with name colorA
public void colorA(int theValue) {
  println("a button event from colorA: "+theValue);
  c1 = c2;
  c2 = color(0, 160, 100);
      //if (bReleased == true)
    //{
      println("Envoie");
      //send with BT
      byte[] data = {'s', 'w', 'i', 't', 'c', 'h', '\r'};
      //bt.broadcast(data);
      bt.broadcast("data");
      //first tap off to send next message
      bReleased = false;
    //}
}

// function colorB will receive changes from 
// controller with name colorB
public void colorB(int theValue) {
  println("a button event from colorB: "+theValue);
  c1 = c2;
  c2 = color(150, 0, 0);
}

// function colorC will receive changes from 
// controller with name colorC
public void colorC(int theValue) {
  println("a button event from colorC: "+theValue);
  c1 = c2;
  c2 = color(255, 255, 0);
}

public void play(int theValue) {
  println("a button event from buttonB: "+theValue);
  c1 = c2;
  c2 = color(0, 0, 0);
}

//********************************************************************
// The following code is required to enable bluetooth at startup.
//********************************************************************

void onCreate(Bundle savedInstanceState) {
  super.onCreate(savedInstanceState);
  bt = new KetaiBluetooth(this);
}

void onActivityResult(int requestCode, int resultCode, Intent data) {
  bt.onActivityResult(requestCode, resultCode, data);
}
void onKetaiListSelection(KetaiList klist) {
  String selection = klist.getSelection();
  bt.connectToDeviceByName(selection);
  //dispose of list for now
  klist = null;
}

//Call back method to manage data received
void onBluetoothDataEvent(String who, byte[] data) {
  if (isConfiguring)
    return;
  //received
  info += new String(data);
  //clean if string to long
  if (info.length() > 150)
    info = "";
}