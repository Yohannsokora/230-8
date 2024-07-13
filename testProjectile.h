/***********************************************************************
 * Header File:
 *    TEST PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    All the unit tests for Projectile
 ************************************************************************/

#pragma once

#include "projectile.h"
#include "unitTest.h"

using namespace std;

/*******************************
 * TEST PROJECTILE
 * A friend class for Projectile which contains the Projectile unit tests
 ********************************/
class TestProjectile : public UnitTest
{
public:
   void run()
   {
      // Ticket 3: Setup
      defaultConstructor();
      reset_empty();
      reset_full();
      fire_right();
      fire_left();
      fire_up();

      // Ticket 4: Advance
      advance_nothing();
      advance_fall();
      advance_horizontal();
      advance_up();
      advance_diagonalUp();
      advance_diagonalDown();

      report("Projectile");
   }

private:
   double metersFromPixels = -1.0;

   /*****************************************************************
    *****************************************************************
    * CONSTRUCTOR
    *****************************************************************
    *****************************************************************/

   /*********************************************
    * name:    DEFAULT CONSTRUCTOR
    * input:   nothing
    * output:  mass=46.7, radius=0.077545 flightPath={}
    *********************************************/
   void defaultConstructor()
   {
      Projectile p;
      assertEquals(p.mass, DEFAULT_PROJECTILE_WEIGHT);
      assertEquals(p.radius, DEFAULT_PROJECTILE_RADIUS);
      assertTrue(p.flightPath.empty());
   }

   /*********************************************
    * name:    RESET from empty
    * input:   mass=-99, radius=-99, flightPath={}
    * output:  mass=46.7, radius=0.077545 flightPath={}
    *********************************************/
   void reset_empty()
   {
      Projectile p;
      p.mass = -99.9;
      p.radius = -99.9;
      p.flightPath.clear();
      p.flightPath.push_back(Projectile::PositionVelocityTime());
      p.reset();
      assertEquals(p.mass, DEFAULT_PROJECTILE_WEIGHT);
      assertEquals(p.radius, DEFAULT_PROJECTILE_RADIUS);
      assertTrue(p.flightPath.empty());
   }

   /*********************************************
    * name:    RESET with a non-zero flight path
    * input:   mass=-99, radius=-99, flightPath={0,1,2}
    * output:  mass=46.7, radius=0.077545 flightPath={}
    *********************************************/
   void reset_full()
   {
      Projectile p;
      p.mass = -99.9;
      p.radius = -99.9;
      p.flightPath.push_back(Projectile::PositionVelocityTime());
      p.flightPath.push_back(Projectile::PositionVelocityTime());
      p.reset();
      assertEquals(p.mass, DEFAULT_PROJECTILE_WEIGHT);
      assertEquals(p.radius, DEFAULT_PROJECTILE_RADIUS);
      assertTrue(p.flightPath.empty());
   }

   /*****************************************************************
    *****************************************************************
    * FIRE
    *****************************************************************
    *****************************************************************/

   /*********************************************
    * name:    FIRE horizontally right
    * input:   angle=90  pos=(111,222) muzzleVelocity=100
    * output:  flightPath={pos=111,222 v=100,0 t=1}
    *********************************************/
   void fire_right()
   {
      Projectile p;
      Position pos(111, 222);
      Angle angle;
      angle.setDegrees(90);
      Velocity velocity;
      velocity.setDx(100.0);
      velocity.setDy(0.0);
      p.fire(pos, angle, velocity);
      assertEquals(p.flightPath.size(), 1);
      assertEquals(p.flightPath.back().pos.getMetersX(), pos.getMetersX());
      assertEquals(p.flightPath.back().pos.getMetersY(), pos.getMetersY());
      assertEquals(p.flightPath.back().v.getDx(), 100.0);
      assertEquals(p.flightPath.back().v.getDy(), 0.0);
      assertEquals(p.flightPath.back().t, 0.0);
   }

   /*********************************************
    * name:    FIRE horizontally left
    * input:   angle=-90  pos=(111,222) muzzleVelocity=100
    * output:  flightPath={pos=111,222 v=-100,0 t=1}
    *********************************************/
   void fire_left()
   {
      Projectile p;
      Position pos(111, 222);
      Angle angle;
      angle.setDegrees(-90);
      Velocity velocity;
      velocity.setDx(-100.0);
      velocity.setDy(0.0);
      p.fire(pos, angle, velocity);
      assertEquals(p.flightPath.size(), 1);
      assertEquals(p.flightPath.back().pos.getMetersX(), pos.getMetersX());
      assertEquals(p.flightPath.back().pos.getMetersY(), pos.getMetersY());
      assertEquals(p.flightPath.back().v.getDx(), -100.0);
      assertEquals(p.flightPath.back().v.getDy(), 0.0);
      assertEquals(p.flightPath.back().t, 0.0);
   }

   /*********************************************
    * name:    FIRE straight up
    * input:   angle=0  pos=(111,222) muzzleVelocity=100
    * output:  flightPath={pos=111,222 v=0,100 t=1}
    *********************************************/
   void fire_up()
   {
      Projectile p;
      Position pos(111, 222);
      Angle angle;
      angle.setDegrees(0);
      Velocity velocity;
      velocity.setDx(0.0);
      velocity.setDy(100.0);
      p.fire(pos, angle, velocity);
      assertEquals(p.flightPath.size(), 1);
      assertEquals(p.flightPath.back().pos.getMetersX(), pos.getMetersX());
      assertEquals(p.flightPath.back().pos.getMetersY(), pos.getMetersY());
      assertEquals(p.flightPath.back().v.getDx(), 0.0);
      assertEquals(p.flightPath.back().v.getDy(), 100.0);
      assertEquals(p.flightPath.back().t, 0.0);
   }

   /*****************************************************************
    *****************************************************************
    * ADVANCE
    *****************************************************************
    *****************************************************************/

   /*********************************************
    * name:    ADVANCE : the projectile is not fired. Nothing will happen
    * input:   flightPath={}
    * output:  flightPath={}
    *********************************************/
   void advance_nothing()
   {
      Projectile p;
      p.advance(1.0);
      assertTrue(p.flightPath.empty());
   }

   /*********************************************
    * name:    ADVANCE : the projectile is stationary and falls down
    * input:   flightPath={pos=100,200 v=0,0 t=100}
    * output:  flightPath={}{pos.x=100      = 100 + 0*1
    *                        pos.y=195.0968 = 200 + 0*1 + .5(-9.806)*1*1
    *                        v.dx =0        = 0 + 0*1
    *                        v.dy =-9.8     = 0 + (-9.8064)*1
    *                        t=101}
    *********************************************/
   void advance_fall()
   {
      Projectile p;
      Projectile::PositionVelocityTime pvt;
      pvt.pos.setMetersX(100.0);
      pvt.pos.setMetersY(200.0);
      pvt.v.setDx(0.0);
      pvt.v.setDy(0.0);
      pvt.t = 100.0;
      p.flightPath.push_back(pvt);
      p.advance(101.0);
      assertEquals(p.flightPath.back().pos.getMetersX(), 100.0);
      assertEquals(p.flightPath.back().pos.getMetersY(), 195.0968);
      assertEquals(p.flightPath.back().v.getDx(), 0.0);
      assertEquals(p.flightPath.back().v.getDy(), -9.806);
      assertEquals(p.flightPath.back().t, 101.0);
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling horizontally
    * input:   flightPath={pos=100,200 v=50,0 t=100}
    * output:  flightPath={}{pos.x=149.9756 = 100 + 50*1 + .5(-0.0487)*1*1
    *                        pos.y=195.0968 = 200 + 0*1  + .5(-9.8064)*1*1
    *                        v.dx =49.9513  = 50 + (-0.0487)*1
    *                        v.dy =-9.8064  = 0  + (-9.8064)*1
    *                        t=101}
    *********************************************/
   void advance_horizontal()
   {
      Projectile p;
      Projectile::PositionVelocityTime pvt;
      pvt.pos.setMetersX(100.0);
      pvt.pos.setMetersY(200.0);
      pvt.v.setDx(50.0);
      pvt.v.setDy(0.0);
      pvt.t = 100.0;
      p.flightPath.push_back(pvt);
      p.advance(101.0);
      assertEquals(p.flightPath.back().pos.getMetersX(), 149.9756);
      assertEquals(p.flightPath.back().pos.getMetersY(), 195.0968);
      assertEquals(p.flightPath.back().v.getDx(), 49.9513);
      assertEquals(p.flightPath.back().v.getDy(), -9.8064);
      assertEquals(p.flightPath.back().t, 101.0);
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling up, no horizontal position change
    * input:   flightPath={pos=100,200 v=0,100 t=100}
    * output:  flightPath={}{pos.x=100      = 0   + 0*1   + .5(0)*1*1
    *                        pos.y=294.9021 = 200 + 100*1 + .5(-9.8064-.3893)*1*1
    *                        v.dx =0        = 0   + 0*1
    *                        v.dy =89.8042  = 100 + (-9.8064-.3893)
    *                        t=101}
    *********************************************/
   void advance_up()
   {
      Projectile p;
      Projectile::PositionVelocityTime pvt;
      pvt.pos.setMetersX(100.0);
      pvt.pos.setMetersY(200.0);
      pvt.v.setDx(0.0);
      pvt.v.setDy(100.0);
      pvt.t = 100.0;
      p.flightPath.push_back(pvt);
      p.advance(101.0);
      assertEquals(p.flightPath.back().pos.getMetersX(), 100.0);
      assertEquals(p.flightPath.back().pos.getMetersY(), 294.9021);
      assertEquals(p.flightPath.back().v.getDx(), 0.0);
      assertEquals(p.flightPath.back().v.getDy(), 89.8042);
      assertEquals(p.flightPath.back().t, 101.0);
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling up and across
    * input:   flightPath={pos=100,200 v=50,40 t=100}
    * output:  flightPath={}{pos.x=149.9600 = 100 + 50*1 + .5(-0.0799)*1*1
    *                        pos.y=235.0648 = 200 + 40*1 + .5(-9.8064-0.0638)*1*1
    *                        v.dx =49.9201  = 50 + (-.0799)*1
    *                        v.dy =30.1297  = 40 + (-9.8064-0.0638)*1
    *                        t=101}
    *********************************************/
   void advance_diagonalUp()
   {
      Projectile p;
      Projectile::PositionVelocityTime pvt;
      pvt.pos.setMetersX(100.0);
      pvt.pos.setMetersY(200.0);
      pvt.v.setDx(50.0);
      pvt.v.setDy(40.0);
      pvt.t = 100.0;
      p.flightPath.push_back(pvt);
      p.advance(101.0);
      assertEquals(p.flightPath.back().pos.getMetersX(), 149.9600);
      assertEquals(p.flightPath.back().pos.getMetersY(), 235.0648);
      assertEquals(p.flightPath.back().v.getDx(), 49.9201);
      assertEquals(p.flightPath.back().v.getDy(), 30.1297);
      assertEquals(p.flightPath.back().t, 101.0);
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling down and across
    * input:   flightPath={}{}{pos=100,200 v=50,-40 t=100}
    * output:  flightPath={}{}{}{pos.x=149.9201 = 100 + 50*1 + .5(-0.0799)*1*1
    *                            pos.y=155.1287 = 200 +-40*1 + .5(-9.8064+0.0638)*1*1
    *                            v.dx = 49.9201 =  50 + (-0.0799)*1
    *                            v.dy =-49.7425 = -40 + (-9.8064+0.0638)*1*1
    *                            t=101}
    *********************************************/
   void advance_diagonalDown()
   {
      // setup
      setupStandardFixture();
      Position pos;
      Projectile p;
      Projectile::PositionVelocityTime pvt;
      p.flightPath.push_back(pvt);
      p.flightPath.push_back(pvt);
      pvt.pos.setMetersX(100.0);
      pvt.pos.setMetersY(200.0);
      pvt.v.setDx(50.0);
      pvt.v.setDy(-40.0);
      pvt.t = 100.0;
      p.flightPath.push_back(pvt);
      // exercise
      p.advance(101.0);
      // verify
      assertUnit(p.flightPath.size() == 4);
      assertEquals(p.mass, DEFAULT_PROJECTILE_WEIGHT);
      assertEquals(p.radius, DEFAULT_PROJECTILE_RADIUS);
      assertUnit(!p.flightPath.empty());
      if (!p.flightPath.empty())
      {
         assertEquals(p.flightPath.back().pos.getMetersX(), 149.9601); // 100 + 50*1 + .5(-0.0799)*1*1
         assertEquals(p.flightPath.back().pos.getMetersY(), 155.1287); // 200 +-40*1 + .5(-9.8064+0.0638)*1*1
         assertEquals(p.flightPath.back().v.getDx(), 49.9201);         // 50 + (-0.0799)*1
         assertEquals(p.flightPath.back().v.getDy(), -49.7425);        //-40 + (-9.8064+0.0638)*1*1
         assertEquals(p.flightPath.back().t, 101.0);
      }
      // teardown
      teardownStandardFixture();
   }

   /*****************************************************************
    *****************************************************************
    * STANDARD FIXTURE
    *****************************************************************
    *****************************************************************/

   // setup standard fixture - set the zoom to 1100m per pixel
   void setupStandardFixture()
   {
      Position p;
      metersFromPixels = p.metersFromPixels;
      p.metersFromPixels = 1.0;
   }

   // teardown the standard fixture - reset the zoom to what it was previously
   void teardownStandardFixture()
   {
      assert(metersFromPixels != -1.0);
      Position p;
      p.metersFromPixels = metersFromPixels;
   }
};
