#include "vex.h"
#include <string>
int autonToRun = 0;

class Button
{
  public:
    int x, y, width, height;
    std::string text;
    vex::color buttonColor, textColor;

    Button(int x, int y, int width, int height, std::string text, vex::color buttonColor, vex::color textColor)
    : x(x), y(y), width(width), height(height), text(text), buttonColor(buttonColor), textColor(textColor){}

    void render()
    {
      Brain.Screen.drawRectangle(x, y, width, height, buttonColor);
      // Brain.Screen.printAt(x + 30, y + 30, false, text.c_str());
      Brain.Screen.printAt(x + width / 3, y + height / 2, false, text.c_str());
    }
    

    bool isClicked()
    {
      if(Brain.Screen.pressing() && Brain.Screen.xPosition() >= x && Brain.Screen.xPosition() <= x + width &&
      Brain.Screen.yPosition() >= y && Brain.Screen.yPosition() <= y + height) {
      return true;}
      else return false;
    }
};

Button isRed = Button(370, 30, 60, 90, "RED", vex::black, vex::white);
Button isBlue = Button(370, 140, 60, 90, "BLUE", vex::black, vex::white);

Button autonButtons[] = {
  // Button(50, 50, 75, 50, "1", vex::white, vex::black),
  // Button(200, 50, 100, 50, "2", vex::white, vex::black),
  // Button(350, 50, 100, 50, "3", vex::white, vex::black),

  // Button(50, 110, 100, 50, "4", vex::white, vex::black),
  // Button(200, 110, 100, 50, "5", vex::white, vex::black),
  // Button(350, 110, 100, 50, "6", vex::white, vex::black),

  // Button(50, 170, 100, 50, "7", vex::white, vex::black),
  // Button(200, 170, 100, 50, "8", vex::white, vex::black),
  // Button(350, 170, 100, 50, "9", vex::white, vex::black),

  Button(20, 30, 60, 60, "1", vex::white, vex::black),
  Button(100, 30, 60, 60, "2", vex::white, vex::black),
  Button(180, 30, 60, 60, "3", vex::white, vex::black),
  Button(260, 30, 60, 60, "4", vex::white, vex::black),

  Button(20, 100, 60, 60, "5", vex::white, vex::black),
  Button(100, 100, 60, 60, "6", vex::white, vex::black),
  Button(180, 100, 60, 60, "7", vex::white, vex::black),
  Button(260, 100, 60, 60, "8", vex::white, vex::black),

  Button(20, 170, 60, 60, "9", vex::white, vex::black),
  Button(100, 170, 60, 60, "10", vex::white, vex::black),
  Button(180, 170, 60, 60, "11", vex::white, vex::black),
  Button(260, 170, 60, 60, "12", vex::white, vex::black),
};