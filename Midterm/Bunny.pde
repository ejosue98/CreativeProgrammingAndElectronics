class Bunny {

  // variables to define position of bunny
  float xPos, yPos; 

  //constructor method
  Bunny(float x, float y) {
    xPos = x;
    yPos= y;
  }

  //update position to be user's mouse
  void update(float x, float y) {
    xPos = x;
    yPos= y;
  }

  /* READ CAREFULLY: 
   A set of 3 rectangular figures was created to be placed below the actual image the bunny. This was done to collect the pixel colors from the surface on which the bunny is stepping. 
   These colors are then collected inside of a Color Array. This array will then be compared to the previously defined array "logColors". See below for purposes
   */


  //display bunny
  void display() {

    noStroke();
    fill(255, 255, 255, 0); // 0 = transparent
    rect(xPos+28, yPos+20, 35, 15); //head
    rect(xPos+35, yPos+35, 25, 10); //torse
    rect(xPos+15, yPos+45, 45, 20); //tail&body


    if ( crossedRiver() ) {  // if bunny has crossed, initiate victory screen 
      state = 2;
    } 

    if (overRiver()) { // if bunny is detected on the river region, check to see if it is stepping on log
      if (!(standingOnLog(logColors, surface())) ) { //if bunny not standing on a log while on river region, it is considered dead :(
        state = 0; // will trigger Game Over State
      }
    }  
    
    //after drawing previously defined body rectangles, now we can draw bunny
    image(rabbit, mouseX, mouseY, 70, 70); // if this line is placed before, the program will wrongly scan the colors of the screen. Will collect colors of bunny image rather than colors BELOW bunny image
  }

  //this will check if the bunny is above the river {river runs over region (0,250) --> (1000,550)}
  boolean overRiver() { 
    float loc = xPos + yPos*1000;
    return (loc > 195000 && loc < 490000); //bunny is over river if True
  }

  //this will check if the bunny has crossed the river {top edge runs over region (0,1000) --> (0,250)}
  boolean crossedRiver() { 
    float loc = xPos + yPos*1000;
    return (loc > 1000 && loc < 160000); //bunny is crossed river if True
  }

  // this method compares trunk/log pixels to surface bunny is standing on
  // if majority of bunny is standing on log, it is considered alive
  boolean standingOnLog (int [] trunkColors, int [] bunnySurface) { 
    int sum = 0;
    for (int i = 0; i < bunnySurface.length; i++) { 
      for (int j = 0; j < trunkColors.length; j++) {
        if (color(bunnySurface[i]) == color(trunkColors[j])) {  //this line will see if the colors of the surface the bunny standing on match the color pixels from the "logColors" array
          sum += 1;
        }
      }
    } 
    return sum*2 > ((bunnySurface.length)); //if more than half of bunny is standing on log, it is considered alive
  }


  // this method will scan the surface bunny is standing on. Needed to collect pixel colors of Surface. Will either be river (blue hue) pixels, or log (brown hue) pixels
  int [] surface() {
    int [] surColors = new int[1675];
    //int [] surColors = new int[1150]; //only tail and body
    int surIndex = 0;


    //check head color pixels
    for (int x1 = int(xPos+28); x1 < xPos+28+35; x1++) { 
      for (int y1 = int(yPos+20); y1 < yPos+20+15; y1++) { 
        color curColor = get(x1, y1);
        String hexy = hex(curColor, 8); 
        int unhexy = unhex(hexy);
        surColors[surIndex] = unhexy;
        surIndex +=1;
      }
    }

    //check torso color pixels
    for (int x2 = int(xPos+35); x2 < xPos+35+25; x2++) { 
      for (int y2= int(yPos+35); y2 < yPos+35+10; y2++) { 
        color curColor = get(x2, y2);
        String hexy = hex(curColor, 8); 
        int unhexy = unhex(hexy);
        surColors[surIndex] = unhexy;
        surIndex +=1;
      }
    }

    //check body&tail color pixels
    for (int x3 = int(xPos+15); x3 < xPos+15+45; x3++) { 
      for (int y3 = int(yPos+45); y3 < yPos+45+20; y3++) { 
        color curColor = get(x3, y3);
        String hexy = hex(curColor, 8); 
        int unhexy = unhex(hexy);
        surColors[surIndex] = unhexy;
        surIndex +=1;
      }
    }
    return surColors;
  }
}
