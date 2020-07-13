// Will be creating images with Following Names
PImage spongeBob;
PImage jellyFish;
PImage jellyFish2;
PImage jellyFish3;
PImage bubbles;

// Initial Angle for Spongebob's Eyes
float angle = 90;


/* Starting position of 3 Jellyfish */
int jelX1 = 0;
int jelY1= 0;

int jelX2 = 20;
int jelY2= 40;

int jelX3 = 80;
int jelY3= 20;

//Used for Bubble Movement
float bAngle = 0.05;

void setup() {
  //Canvas Size
  size(800, 600);
  
  //URL's of Images
  String sponge = "https://i.pinimg.com/originals/69/68/65/696865b0736fe48a7f9628d74fb0b46f.png";
  String jelly = "https://vignette.wikia.nocookie.net/nickelodeon/images/a/a5/Jellyfish_in_2018.png/";
  
  // Load images from a web server
  spongeBob = loadImage(sponge, "png");
  jellyFish = loadImage(jelly, "png");
  bubbles = loadImage("bubbles.png"); //this image was saved on Computer
}


void draw() {
  //Reset Background each iteration
  background(140, 230, 245);

  //Make Figure bubbles move in circular motion
  float x = 370 + sin(bAngle) * .05;   
  float y =  250 + cos(bAngle) * .05;    //combination sin and cos positions create circle
  bAngle = bAngle + 0.5; 
  image(bubbles, x, y);                  //load image according to position
  bubbles.resize(500, 250);              //original image was too large, so I compressed it


  //Jellyfish Configuration
  image(spongeBob, width/4, height/1.5);
  image(jellyFish, jelX1, jelY1);
  jellyFish.resize(220, 250);

  PImage jellyFish3 = jellyFish;
  image(jellyFish3, jelX3, jelY3);
  jellyFish.resize(220, 250);


  PImage jellyFish2 = jellyFish;
  image(jellyFish2, jelX2, jelY2);
  jellyFish.resize(220, 250);

  //Small Bubble Movement
  for (int i = 0; i < 9; i = i+1) {            //Used for loop to create multiple bubbles at once
    fill(255, 255, 255, 150);
    if (width*i % (i+1) == 0) {     
      stroke(255);
      circle(i*90, height- angle*2, 80);
      noStroke();
      circle(i*90+10, (height- angle*2)-20, 25);
      

    } else {
      stroke(255);
      circle(i*100, height- angle*3, 90);
      noStroke();
      circle(i*100+10, (height- angle*3)-20, 25);
    }
  }


  /*eye movement */

  //left eyeball
  noStroke();
  fill(255);
  circle(308, 500, 45);
  stroke(0);
  translate(308, 500);
  rotate(radians(angle));
  fill(0, 191, 255);
  circle(0, 10, 30);
  fill(0);
  circle(0, 12, 15);
  resetMatrix();

  ////right eyeball
  noStroke();
  fill(255);
  circle(380, 515, 45);
  stroke(0);
  translate(380, 515);
  rotate(radians(angle));
  fill(0, 191, 255);
  circle(0, 10, 30);
  fill(0);
  circle(0, 12, 15);
  resetMatrix();


//restart motion once near end of screen
  if (angle >= 245) {
    angle = 90;
    jelX1 = 0;
    jelX2 = 20;
    jelX3 = 80;
  }

  jelX1 += 1;
  jelX2 += 1;
  jelX3 += 1;
  angle = angle + .25;
}
