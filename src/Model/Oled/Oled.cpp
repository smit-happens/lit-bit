/**  Display model class
 *
 * Oled.cpp
 * Created 05-24-18 By: Smitty
 *
 * A longer description.
 */

#include "Oled.hpp"


/** 
 * @brief  Oled constructor
 */
Oled::Oled(void)
{
    //initialize the oled library
    display = new MicroOLED(PIN_RESET, DC_JUMPER);

    // initialize the glcd and set the contrast to 0x18
    // display->begin();
    // display->clearBuffer();
    // display->setContrast(130);
    display->begin();    // Initialize the OLED
    display->clear(ALL); // Clear the display's internal memory
    display->display();  // Display what's in the buffer (splashscreen)
    delay(1000);     // Delay 1000 ms
    display->clear(PAGE); // Clear the buffer.

    while(1){
        lineExample();   // Then the line example function
        shapeExample();  // Then the shape example
        textExamples();  // Finally the text example
    }
}


/** 
 * @brief  Oled destructor
 */
Oled::~Oled(void)
{
    //delete display;
}


void Oled::lineExample()
{
  int middleX = display->getLCDWidth() / 2;
  int middleY = display->getLCDHeight() / 2;
  int xEnd, yEnd;
  int lineWidth = min(middleX, middleY);
  
  printTitle("Lines!", 1);
  
  for (int i=0; i<3; i++)
  {
    for (int deg=0; deg<360; deg+=15)
    {
      xEnd = lineWidth * cos(deg * PI / 180.0);
      yEnd = lineWidth * sin(deg * PI / 180.0);
      
      display->line(middleX, middleY, middleX + xEnd, middleY + yEnd);
      display->display();
      delay(10);
    }
    for (int deg=0; deg<360; deg+=15)
    {
      xEnd = lineWidth * cos(deg * PI / 180.0);
      yEnd = lineWidth * sin(deg * PI / 180.0);
      
      display->line(middleX, middleY, middleX + xEnd, middleY + yEnd, BLACK, NORM);
      display->display();
      delay(10);
    }
  }
}


void Oled::shapeExample()
{
  printTitle("Shapes!", 0);
  
  // Silly pong demo. It takes a lot of work to fake pong...
  int paddleW = 3;  // Paddle width
  int paddleH = 15;  // Paddle height
  // Paddle 0 (left) position coordinates
  int paddle0_Y = (display->getLCDHeight() / 2) - (paddleH / 2);
  int paddle0_X = 2;
  // Paddle 1 (right) position coordinates
  int paddle1_Y = (display->getLCDHeight() / 2) - (paddleH / 2);
  int paddle1_X = display->getLCDWidth() - 3 - paddleW;
  int ball_rad = 2;  // Ball radius
  // Ball position coordinates
  int ball_X = paddle0_X + paddleW + ball_rad;
  int ball_Y = random(1 + ball_rad, display->getLCDHeight() - ball_rad);//paddle0_Y + ball_rad;
  int ballVelocityX = 1;  // Ball left/right velocity
  int ballVelocityY = 1;  // Ball up/down velocity
  int paddle0Velocity = -1;  // Paddle 0 velocity
  int paddle1Velocity = 1;  // Paddle 1 velocity
    
  //while(ball_X >= paddle0_X + paddleW - 1)
  while ((ball_X - ball_rad > 1) && 
         (ball_X + ball_rad < display->getLCDWidth() - 2))
  {
    // Increment ball's position
    ball_X+=ballVelocityX;
    ball_Y+=ballVelocityY;
    // Check if the ball is colliding with the left paddle
    if (ball_X - ball_rad < paddle0_X + paddleW)
    {
      // Check if ball is within paddle's height
      if ((ball_Y > paddle0_Y) && (ball_Y < paddle0_Y + paddleH))
      {
        ball_X++;  // Move ball over one to the right
        ballVelocityX = -ballVelocityX; // Change velocity
      }
    }
    // Check if the ball hit the right paddle
    if (ball_X + ball_rad > paddle1_X)
    {
      // Check if ball is within paddle's height
      if ((ball_Y > paddle1_Y) && (ball_Y < paddle1_Y + paddleH))
      {
        ball_X--;  // Move ball over one to the left
        ballVelocityX = -ballVelocityX; // change velocity
      }
    }
    // Check if the ball hit the top or bottom
    if ((ball_Y <= ball_rad) || (ball_Y >= (display->getLCDHeight() - ball_rad - 1)))
    {
      // Change up/down velocity direction
      ballVelocityY = -ballVelocityY;
    }
    // Move the paddles up and down
    paddle0_Y += paddle0Velocity;
    paddle1_Y += paddle1Velocity;
    // Change paddle 0's direction if it hit top/bottom
    if ((paddle0_Y <= 1) || (paddle0_Y > display->getLCDHeight() - 2 - paddleH))
    {
      paddle0Velocity = -paddle0Velocity;
    }
    // Change paddle 1's direction if it hit top/bottom
    if ((paddle1_Y <= 1) || (paddle1_Y > display->getLCDHeight() - 2 - paddleH))
    {
      paddle1Velocity = -paddle1Velocity;
    }
    
    // Draw the Pong Field
    display->clear(PAGE);  // Clear the page
    // Draw an outline of the screen:
    display->rect(0, 0, display->getLCDWidth() - 1, display->getLCDHeight());
    // Draw the center line
    display->rectFill(display->getLCDWidth()/2 - 1, 0, 2, display->getLCDHeight());
    // Draw the Paddles:
    display->rectFill(paddle0_X, paddle0_Y, paddleW, paddleH);
    display->rectFill(paddle1_X, paddle1_Y, paddleW, paddleH);
    // Draw the ball:
    display->circle(ball_X, ball_Y, ball_rad);
    // Actually draw everything on the screen:
    display->display();
    delay(25);  // Delay for visibility
  }
  delay(1000);
}


void Oled::textExamples()
{
    // Demonstrate font 0. 5x8 font
    display->clear(PAGE);     // Clear the screen
    display->setFontType(0);  // Set font to type 0
    display->setCursor(0, 0); // Set cursor to top-left
    // There are 255 possible characters in the font 0 type.
    // Lets run through all of them and print them out!
    for (int i=0; i<=255; i++)
    {
        // You can write byte values and they'll be mapped to
        // their ASCII equivalent character.
        display->write(i);  // Write a byte out as a character
        display->display(); // Draw on the screen
        delay(10);      // Wait 10ms
        // We can only display 60 font 0 characters at a time.
        // Every 60 characters, pause for a moment. Then clear
        // the page and start over.
        if ((i%60 == 0) && (i != 0))
        {
            delay(500);           // Delay 500 ms
            display->clear(PAGE);     // Clear the page
            display->setCursor(0, 0); // Set cursor to top-left
        }
    }
    delay(500);  // Wait 500ms before next example
    
    // Demonstrate font 1. 8x16. Let's use the print function
    // to display every character defined in this font.
    display->setFontType(1);  // Set font to type 1
    display->clear(PAGE);     // Clear the page
    display->setCursor(0, 0); // Set cursor to top-left
    // Print can be used to print a string to the screen:
    display->print(" !\"#$%&'()*+,-./01234");
    display->display();       // Refresh the display
    delay(1000);          // Delay a second and repeat
    display->clear(PAGE);
    display->setCursor(0, 0);
    display->print("56789:;<=>?@ABCDEFGHI");
    display->display();
    delay(1000);
    display->clear(PAGE);
    display->setCursor(0, 0);
    display->print("JKLMNOPQRSTUVWXYZ[\\]^");
    display->display();
    delay(1000);
    display->clear(PAGE);
    display->setCursor(0, 0);
    display->print("_`abcdefghijklmnopqrs");
    display->display();
    delay(1000);
    display->clear(PAGE);
    display->setCursor(0, 0);
    display->print("tuvwxyz{|}~");
    display->display();
    delay(1000);
    
    // Demonstrate font 2. 10x16. Only numbers and '.' are defined. 
    // This font looks like 7-segment displays.
    // Lets use this big-ish font to display readings from the
    // analog pins.
    for (int i=0; i<25; i++)
    {
        display->clear(PAGE);            // Clear the display
        display->setCursor(0, 0);        // Set cursor to top-left
        display->setFontType(0);         // Smallest font
        display->print("A0: ");          // Print "A0"
        display->setFontType(2);         // 7-segment font
        display->print(analogRead(A0));  // Print a0 reading
        display->setCursor(0, 16);       // Set cursor to top-middle-left
        display->setFontType(0);         // Repeat
        display->print("A1: ");
        display->setFontType(2);
        display->print(analogRead(A1));
        display->setCursor(0, 32);
        display->setFontType(0);
        display->print("A2: ");
        display->setFontType(2);
        display->print(analogRead(A2));
        display->display();
        delay(100);
    }
    
    // Demonstrate font 3. 12x48. Stopwatch demo.
    display->setFontType(3);  // Use the biggest font
    int ms = 0;
    int s = 0;
    while (s <= 5)
    {
        display->clear(PAGE);     // Clear the display
        display->setCursor(0, 0); // Set cursor to top-left
        if (s < 10)
            display->print("00");   // Print "00" if s is 1 digit
        else if (s < 100)     
            display->print("0");    // Print "0" if s is 2 digits
        display->print(s);        // Print s's value
        display->print(":");      // Print ":"
        display->print(ms);       // Print ms value
        display->display();       // Draw on the screen
        ms++;         // Increment ms
        if (ms >= 10) // If ms is >= 10
        {
            ms = 0;     // Set ms back to 0
            s++;        // and increment s
        }
    }
}


// Center and print a small title
// This function is quick and dirty. Only works for titles one
// line long.
void Oled::printTitle(String title, int font)
{
  int middleX = display->getLCDWidth() / 2;
  int middleY = display->getLCDHeight() / 2;
  
  display->clear(PAGE);
  display->setFontType(font);
  // Try to set the cursor in the middle of the screen
  display->setCursor(middleX - (display->getFontWidth() * (title.length()/2)),
                 middleY - (display->getFontWidth() / 2));
  // Print the title:
  display->print(title);
  display->display();
  delay(1500);
  display->clear(PAGE);
}


