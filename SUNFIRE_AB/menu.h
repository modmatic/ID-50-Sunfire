#ifndef MENU_H
#define MENU_H

#include "globals.h"

byte x_ship;
byte y_ship;


void drawTitleScreen()
{
  x_ship = random(0, 2);
  y_ship = random(0, 2);
  for (byte i = 0; i < 16; i++) sprites.drawSelfMasked(i * 8, 0, titleWhite, 0);
  sprites.drawSelfMasked(0, 11, titleSun, 0);
  sprites.drawSelfMasked(58, 11, titleFire, 0);
  sprites.drawSelfMasked(18, 40, titleSolar, 0);
  sprites.drawPlusMask(42 + x_ship, 33 + y_ship, titleShip_plus_mask, 0);
}

void stateMenuIntro()
{
  globalCounter++;
  sprites.drawSelfMasked(34, 4, T_arg, 0);
  if (globalCounter > 120)
  {
    gameState = STATE_MENU_MAIN;
  }
}

void stateMenuMain()
{
  drawTitleScreen();
  for (byte i = 0; i < 4; i++) sprites.drawErase(13 + (28 * i), 2, titleMenu, i);
  sprites.drawErase(((menuSelection - 2) * 27) + 9, 2, titlePointer, 0);
  if (arduboy.justPressed(RIGHT_BUTTON) && (menuSelection < 5)) menuSelection++;
  if (arduboy.justPressed(LEFT_BUTTON) && (menuSelection > 2)) menuSelection--;
  if (arduboy.justPressed(B_BUTTON)) gameState = menuSelection;
}

void stateMenuHelp()
{
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}


void stateMenuInfo()
{
  drawTitleScreen();
  sprites.drawErase(37, 2, titleInfo, 0);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

void stateMenuSoundfx()
{
  drawTitleScreen();
  for (byte i = 0; i < 3; i++) sprites.drawErase(31 + (28 * i), 2, titleMenu, i+4);
  sprites.drawErase((arduboy.audio.enabled() * 28) + 54, 2, titlePointer, 0);
  if (arduboy.justPressed(RIGHT_BUTTON)) arduboy.audio.on();
  if (arduboy.justPressed(LEFT_BUTTON)) arduboy.audio.off();
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    arduboy.audio.saveOnOff();
    gameState = STATE_MENU_MAIN;
  }
}

#endif
