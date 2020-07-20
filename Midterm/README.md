![](start.png)

![](game.png)

![](gameOver.jpg)

![](victory.jpg)


This project features an arcade-like game where the obective is to 
safely guide a stranded bunny across a river using the user's mouse.

The inspiration to write this game came after reminiscing of my childhood games. When I was a child, I remember visiting my local
computer store to play games during the weekends. One of the games I had most fun was the one implemented, where a racoon had to cross a street in order 
to proceed to the next levels. 


Though the game is quite simplistic, it's implementation required a great load of creativity throughout the course of a week.

The most challenging tasks consisted of: 
1) Creating multiple logs at once, with different positions, and speeds.
2) Determining whether the bunny is found within the river region.
3) Determining whether the bunny was standing on a log or on the river - particularly difficult with multiple moving logs.
4) Implementing a program fast enough that would not slow down the overall quality and runtime of the game.
5) Finding a way to display a start screen, a game screen, a victory screen, and a game over screen in the program.

Approach to each problem: 
1) This was the first problem I encountered. My initial approach was to "hard code" various logs and individually assign each of them a horizontal position, vertical position, and speed. As the game began to gain more and more complexity, I decided to create a "Log" class which allowed for a much quicker implementation. After creating a Log class, I simply declared an array of multiple logs and had each log be defined inside of a loop. 

2) The following problem was how to determine whether the user's bunny would be standing within a river region. This was perhaps the quickest problem to implement, but simultaneously very time consuming. My approach was to finalize the environment I'd like to have my game to display. This would be a river image displayed in the middle of the screen while at the top and bottom edges of the screen would be 2 hills. After adjusting the sizes of each image and placing them where I found most convenient, I loaded the pixels from the screen and found the location of the first and last pixels the river image occupied. Once done, I created a Bunny class and made 2 of its variables x and y coordinates. As a result, I was able to determine whether the bunny's location was between the first and last pixels the river image occupied. If so, the bunny was declared to be within a region of danger. 

3) The most time consuming by far problem was finding a way to figure out whether the bunny was standing on a log or water once inside the river region. This was particularly difficult considering that I could not simply look at the pixels the bunny's location was occupying. My solution was the following: 
    *1. From the very beginning of the game, declare and place an image of the river logs at the top left corner of the canvas.
    *2. Run a for-loop that would extract the color of each pixel this log was occupying and save this color to an array. (this process itself was really tedious on         its own)
    *3. Determine whether the bunny is standing on the river region (previously found)
    *4. Extract the color of the surface the bunny's image was standing on
        *- this was the most difficult problem of all. As I could not simply extract the colors of each pixel from the region the bunny image was standing on. Doing         *    so would output colors of the bunny image - not the surface on which it was standing (could be river or log).
    *5. To approach the issue above, I finally came to the solution of prior to placing the image of the bunny, I would create 3 invisible rectangles that layed            exactly where the bunny image would be placed. One rectangle would be over the Bunny's head, another over the bunny's torso, and the last over the bunny's           body and tail. 
    *6. As soon as these invisible shapes were placed, I would scan the pixels where these layed and extract their colors. Because they were invisible, I would be        able to know whether the bunny woould be standing on a log or on the river.
    *7. Once scanned, these pixels' colors were then compared to the previously defined colors of the log array. If more than half of the pixels were found to match        with colors of the log array, then the bunny was known to be standing on a log.
4)  The previous problem requires a great load of computation, which means my computer would slow down and so would the game. Therefore, to speed up the process of pixel comparison, I decided to compare each surface pixel to the colors of the log array as it was scanned rather than comparing 2 large arrays and their individual elements. 
5) This final solution was also a bit creative as it allowed me to have multiple screens displayed based on the "mode" of the game. My fear was that I would be restricted to only displaying one screen since I only had the draw() function to work with. However, I remembered that in a course I had taken a couple of years ago, we made use of a variable integer which would dictate the mode in which the program should run. I decided to implement that solution and was able to create multiple functions that would be called in the draw() function which would then dictate what screen to display based on the mode the game was currently operating. For instance, if the game was over, this integer would change appropriately and the draw() function would take note of this integer value to call the appropriate "game over" method associated with the integer.




Overall, this midterm assignment was extremely enriching and was also a great way to practice open-mindedness/creativity. I really enjoyed creating a game on my own, with my own rules - which was both enjoyable yet difficult since we had no guidance besides basic programming foundations. 


The images used for this program were found in the following websites: 

https://t3.ftcdn.net/jpg/00/48/58/10/240_F_48581058_pkT5sMkjFAhgIoV2FjBTE35vhffEME11.jpg
https://lh3.googleusercontent.com/proxy/jjwEy4PeBqMHkM_7aR8gnK_QWmCZ4STjNMuP_5ktv2QeSmW0QueG-u3rMdX21Y4d1ZRh-s_HNvDSSlCM4cbgzO-hx8br8CsG9oY9GSoMmpamoqmJ1C3foWEwznU

https://img1.picmix.com/output/stamp/normal/7/9/3/0/420397_8c780.gif
http://clipart-library.com/clipart/554061.htm
https://www.pixilart.com/art/you-win-screen-8b85771539cbccc



