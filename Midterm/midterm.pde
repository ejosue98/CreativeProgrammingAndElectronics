import processing.sound.*; // importing library will allow to play music

//the following are the names of files to be uploaded
SoundFile game;
SoundFile gameO;
SoundFile victory;

//Images to be loaded - Note they must be in the same directory
PImage river;
PImage bottomEdge;
PImage topEdge;
PImage trunkBase;
PImage trunk;
PImage rabbit;
PImage gameOver;
PImage success;
PImage start;

//Creating object Instance of class Bunny 
Bunny bunny;

// Array containing all the tree trunks to be used
Log [] logs = new Log[15]; // will have a total of 5 rows for trunks/logs

//Will load a tree trunk image and collect all pixel colors in here
final int [] logColors = new int [3500];  //collect all color combinations inside trunk image
int logIndex = 0; //index used to define trunk's pixel colors

int state = -1; //state will define what screen to display
/*  1 indicates game is in playing mode. 
    0 if game is over
    2 if bunny has crossed the river
    -1 load screen
 */


void setup() { 
  size(1000, 800);

  //define music files previously initiated
  game = new SoundFile(this, "game.mp3");
  gameO = new SoundFile(this, "gameOver.mp3");
  victory = new SoundFile(this, "victory.mp3");

  baseTrunk(); // very important to place this line here (random trunk on screen appears otherwise)

  start = loadImage("start.png"); //loadScreen



} 



// there are multiple screens to display - state defines which to load (display according to state)
void draw () {

  if ( state == -1 ) { //Game State
    load();
  } else if ( state == 1 ) { //Game State
    draw_playing();
  } else if ( state == 0 ) { //Game Over State
    draw_GameOver();
  } else if ( state == 2 ) { //Victory State
    draw_victory();
  }
  
}

// state = 2, player is still in game
void load() { 
    image(start, 0, 0, 1000, 800);
    if (mousePressed) {
      state = 1;
    }    
} 

// state = 1, player is still in game
void draw_playing() { 
  setting();     //method which defines environment
  loadTrunks();  //load trunks on river
  bunny.update(mouseX, mouseY); //bunny follows user's mouse
  bunny.display(); //see bunny Class
  if (!(game.isPlaying())) {     // check is game soundtrack is not already playing
    game = new SoundFile(this, "game.mp3");  //play game soundtrack
    gameO.pause();  //pause game over soundtrack in case it is playing
    game.pause();
    game.play();//play music File
  }
} 

/* NOTE THAT PAUSE() METHOD IS CALLED FOR FOLLOWING 3 FUNCTIONS IN ORDER 
 TO STOP ANY SOUNTRACK ALREADY PLAYING */

//similar to above - this method is called if user has won
void draw_victory() {
  if (!(victory.isPlaying())) { 
    victory = new SoundFile(this, "victory.mp3");
    victory.pause();
    gameO.pause();
    game.pause();
    victory.play();
  } 
  success = loadImage("victory.jpg");
  image(success, 0, 0, 1000, 800); //victory game is displayed
}

//similar to previous 2 - this method is called if user has lost
void draw_GameOver() {
  if (!(gameO.isPlaying())) { 
    gameO = new SoundFile(this, "gameOver.mp3");
    game.pause();
    victory.pause();
    gameO.play();
  } 
  gameOver = loadImage("gameOver.jpg");
  image(gameOver, 0, 0, 1000, 800); //display game over screen
}

//game will begin from scratch if this is called
void  restart() { 
  //load images to be used - this is the environment
  river = loadImage("river.png");
  topEdge = loadImage("topEdge.jpg");
  bottomEdge = loadImage("bottomEdge.jpg");
  rabbit = loadImage("rabbit.png");

  //re-load setting
  setting();
  defineTrunks();
} 


// if the mouse if pressed, everything should reset
void mousePressed() {
  state = 1;     //regular game is considered to be running
  game.pause();  //pause the currently "game" file currently playing
  game = new SoundFile(this, "game.mp3"); //begin new game soundtrack
  restart();  // reset setting
}


// this method will define the settinge/environment
void setting () { 

  image(topEdge, 0, 0, 1000, 250);      // Top Edge is between   y = {0,250}
  image(bottomEdge, 0, 550, 1000, 300); //Bottom Edge is between y = {550,850} -- 300 tall
  image(river, 0, 250, 1000, 300);      //river is between y = {250,300} --> 550 tall

  //User Controlled Rabbit
  bunny = new Bunny(mouseX, mouseY);
} 


//define the trunk image model to be used
void defineTrunks() {
  trunk = loadImage("trunk.png");
  int y = 255; //first log will be at  y = 255
  for (int k = 0; k <logs.length; k++) { //define all indeces as trunks
    logs[k] = new Log(random(0, 300), y, random(4, 10)); // log(x position ,y position,speed)
    y += 50; // this is the height distance between each trunk
    if (y > 505) { //last log will be at y = 505
      y = 255;
    }
  }
} 


//Once defined, the trunks will be loaded
void loadTrunks() { 
  ////load all trunks
  for (int k = 0; k <logs.length; k++) {
    logs[k].translate();  //log method which moves logs horizontally
    logs[k].display();
    if ( logs[k].xPos >= 1000) {  //if logs reach the right end of the screen, reset them to left edge
      logs[k].xPos = 0;
    }
  }
} 

//collect all colors from a trunk image in an array. Will use array to check if rabbit is stepping on trunk
void baseTrunk () { 
  trunkBase = loadImage("trunk.png");
  image(trunkBase, 0, 0, 100, 35);
  for (int y = 0; y < 35; y++) {
    for (int x = 0; x < 100; x++) {
      color curColor = get(x, y);
      String hexy = hex(curColor, 8);
      int unhexy = unhex(hexy);
      logColors[logIndex] = unhexy;
      logIndex +=1;
    }
  }
}
