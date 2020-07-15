float x, y, speedX, speedY; //position and speed variables
float d = random(50,90); //Circle Diameter
float rectHeight = 200; //user bar length



void setup() {
  fullScreen();   //program takes up entire screen
  fill(0, 0, 255);
  restart();            //restart will make ball start at center and restart Game
}

void draw() { 
  background(255);
  circle(x, y, d);

  //wall to left
  int wallThickness = 20;
  rect(0, 0, wallThickness, height);

  //moveable user bar
  int barThickness = 30;
  int barSurface = width-barThickness;
  int surfaceWidth = 10;
  float surfaceCenter = mouseY-rectHeight/2;
  rect(barSurface, surfaceCenter, surfaceWidth, rectHeight);

  x += speedX;
  y += speedY;


  // if ball hits movable bar, invert X direction
  int leftWall = width - wallThickness;
  if ( x >= barSurface && x < leftWall && y > surfaceCenter && y < mouseY+rectHeight/2 ) {
    speedX = speedX * -1;
  } 


  //  check for left wall collision 
  if (x + d/2 <= 40) {
    speedX *= -1;
  }


  // check for wall collision along Y
  if ( y > height || y < 0 ) {
    speedY *= -1;
  }

//Game is Over if goes Past Bar
  if (x > width) { 
    String message= "Game Over \n Click to Retry";  //Display Message
    PFont f = createFont("monaco", 32);
    textFont(f, 50);

    fill(255, 0, 0);
    textAlign(CENTER);
    text(message, width/2, height/2);
  }
}

void mousePressed() {
  restart();
}

void restart() {
  fill(0, 0, 255);
  x = width/2;
  y = height/2;
  speedX = random(5, 10);     //random speed
  speedY = random(5, 10);   //random speed
  background(255);
}
