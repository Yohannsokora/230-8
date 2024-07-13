/**********************************************************************
 * Header File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#pragma once
#include "position.h"
#include "projectile.h"
#include "howitzer.h"
#include "uiDraw.h"

/*********************************************
 * Simulation
 * Execute one simulation of a projectile being fired.
 *********************************************/
class Simulation
{
public:
   Simulation(const Position &posUpperRight) : posUpperRight(posUpperRight) {}

   void advance(double time)
   {
      projectile.advance(time);
      howitzer.generatePosition(posUpperRight);
   }

   void draw(ogstream &gout)
   {
      howitzer.draw(gout, projectile.flightPath.back().t);
      projectile.draw(gout);
   }

private:
   Position posUpperRight;
   Projectile projectile;
   Howitzer howitzer;
};
