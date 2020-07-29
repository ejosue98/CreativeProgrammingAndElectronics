class Log {

  //each log should have an x,y coordinate and a speed
  float xPos, yPos, speed;

  Log (float x, float y, float  s) {
    xPos = x;
    yPos= y;
    speed = s;
  }

//show log on screen
  void display() {
    //the origin of each image is at top left!!!!!!!!
    image(trunk, xPos, yPos, 100, 35);
  }

  //horizontally translate the log along the river
  void translate () { 
    xPos += speed;
  } 

}
