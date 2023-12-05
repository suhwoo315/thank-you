import ddf.minim.*;
import ddf.minim.effects.*;
import processing.serial.*;

Serial myPort;
Minim minim;
AudioPlayer rain;
AudioPlayer umbrella;

int prev = 50;

void setup()
{
  printArray(Serial.list()); // check port number in your environment
  String portName = Serial.list()[1];
  myPort = new Serial(this, portName, 9600);
  
  minim = new Minim(this);
  rain = minim.loadFile("rain.mp3", 2048);
  umbrella = minim.loadFile("umbrella.mp3", 2048);
  rain.loop();
  
  fullScreen();
  background(0);
  textSize(35);
  textAlign(CENTER, CENTER);
  text("thank_you", displayWidth/2, displayHeight/2);
}

void draw()
{
  int input = 50;
  
  if (myPort.available() > 0){
    input = myPort.read();
    
    if (input == 49){
      if (prev == 50){
        umbrella.loop();
      }
    }
    else if (input == 50){
      if (prev == 49){
        umbrella.pause();
      }
    }
    
    prev = input;
  }
}

// 50: no umbrella
// 49: umbrella
