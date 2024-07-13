/***********************************************************************
 * Header File:
 *    TEST HOWITZER
 * Author:
 *    <your name here>
 * Summary:
 *    All the unit tests for Howitzer
 ************************************************************************/

#pragma once

#include "howitzer.h"
#include "unitTest.h"

/*******************************
 * TEST HOWITZER
 * A friend class for Howitzer which contains the Howitzer unit tests
 ********************************/
class TestHowitzer : public UnitTest
{
public:
   void run()
   {
      // Ticket 1: Getters
      defaultConstructor();
      getPosition_zero();
      getPosition_middle();
      getMuzzleVelocity_slow();
      getMuzzleVelocity_standard();
      getElevation_up();
      getElevation_right();
      getElevation_left();

      // Ticket 2: Setters
      generatePosition_small();
      generatePosition_large();
      raise_rightDown();
      raise_rightUp();
      raise_leftDown();
      raise_leftUp();
      rotate_clock();
      rotate_counterClock();
      rotate_wrapClock();
      rotate_wrapCounterClock();

      report("Howitzer");
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
    * output:  zeros (except angle is at 45 degrees, 
    *                 and the muzzle velocity is correct)
    *********************************************/
   void defaultConstructor()
   {
      Howitzer h;
      assertEquals(h.getMuzzleVelocity(), DEFAULT_MUZZLE_VELOCITY);
      assertEquals(h.getElevation().getDegrees(), 45.0);
      assertEquals(h.getPosition().getPixelsX(), 0.0);
      assertEquals(h.getPosition().getPixelsY(), 0.0);
   }

   /*****************************************************************
    *****************************************************************
    * GETTERS
    *****************************************************************
    *****************************************************************/

   /*********************************************
    * name:    GET POSITION ZERO
    * input:   h.pos=(0,0)
    * output:  pos=(0,0)
    *********************************************/
   void getPosition_zero()
   {
      Howitzer h;
      h.getPosition().setPixelsX(0.0);
      h.getPosition().setPixelsY(0.0);
      assertEquals(h.getPosition().getPixelsX(), 0.0);
      assertEquals(h.getPosition().getPixelsY(), 0.0);
   }

   /*********************************************
    * name:    GET POSITION MIDDLE
    * input:   h.pos=(123.4, 567.8)
    * output:  pos=(123.4, 567.8)
    *********************************************/
   void getPosition_middle()
   {
      Howitzer h;
      h.getPosition().setPixelsX(123.4);
      h.getPosition().setPixelsY(567.8);
      assertEquals(h.getPosition().getPixelsX(), 123.4);
      assertEquals(h.getPosition().getPixelsY(), 567.8);
   }

   /*********************************************
    * name:    GET MUZZLE VELOCITY - SLOW SPEED
    * input:   h.muzzleVelocity=(24.68)
    * output:  m=24.68
    *********************************************/
   void getMuzzleVelocity_slow()
   {
      Howitzer h;
      h.muzzleVelocity = 24.68;
      assertEquals(h.getMuzzleVelocity(), 24.68);
   }

   /*********************************************
    * name:    GET MUZZLE VELOCITY - STANDARD SPEED
    * input:   h.muzzleVelocity=(827.00)
    * output:  m=827
    *********************************************/
   void getMuzzleVelocity_standard()
   {
      Howitzer h;
      assertEquals(h.getMuzzleVelocity(), DEFAULT_MUZZLE_VELOCITY);
   }

   /*********************************************
    * name:    GET ELEVATION - up
    * input:   h.elevation=0
    * output:  e=0
    *********************************************/
   void getElevation_up()
   {
      Howitzer h;
      h.elevation.setDegrees(0.0);
      assertEquals(h.getElevation().getDegrees(), 0.0);
   }

   /*********************************************
    * name:    GET ELEVATION - right
    * input:   h.elevation=0.4
    * output:  e=0.4
    *********************************************/
   void getElevation_right()
   {
      Howitzer h;
      h.elevation.setDegrees(0.4);
      assertEquals(h.getElevation().getDegrees(), 0.4);
   }

   /*********************************************
    * name:    GET ELEVATION - left
    * input:   h.elevation=5.8
    * output:  e=5.8
    *********************************************/
   void getElevation_left()
   {
      Howitzer h;
      h.elevation.setDegrees(5.8);
      assertEquals(h.getElevation().getDegrees(), 5.8);
   }

   /*****************************************************************
    *****************************************************************
    * SETTERS
    *****************************************************************
    *****************************************************************/

   /*********************************************
    * name:    GENERATE POSITION small board
    * input:   (10px, 10px)
    * output:  1px <= x <= 9px
    *********************************************/
   void generatePosition_small()
   {
      Howitzer h;
      Position posUpperRight;
      posUpperRight.setPixelsX(10.0);
      posUpperRight.setPixelsY(10.0);
      h.generatePosition(posUpperRight);
      assertTrue(h.getPosition().getPixelsX() >= 1.0);
      assertTrue(h.getPosition().getPixelsX() <= 9.0);
   }

   /*********************************************
    * name:    GENERATE POSITION large board
    * input:   (1000px, 1000px)
    * output:  100px <= x <= 900px
    *********************************************/
   void generatePosition_large()
   {
      Howitzer h;
      Position posUpperRight;
      posUpperRight.setPixelsX(1000.0);
      posUpperRight.setPixelsY(1000.0);
      h.generatePosition(posUpperRight);
      assertTrue(h.getPosition().getPixelsX() >= 100.0);
      assertTrue(h.getPosition().getPixelsX() <= 900.0);
   }

   /*********************************************
    * name:    RAISE to the right/down
    * input:   h.elevation=0.5radians  raise(-0.1)
    * output:  h.elevation=0.6radians
    *********************************************/
   void raise_rightDown()
   {
      Howitzer h;
      h.elevation.setRadians(0.5);
      h.raise(-0.1);
      assertEquals(h.getElevation().getRadians(), 0.6);
   }

   /*********************************************
    * name:    RAISE to the right/up
    * input:   h.elevation=0.5radians  raise(0.1)
    * output:  h.elevation=0.4radians
    *********************************************/
   void raise_rightUp()
   {
      Howitzer h;
      h.elevation.setRadians(0.5);
      h.raise(0.1);
      assertEquals(h.getElevation().getRadians(), 0.4);
   }

   /*********************************************
    * name:    RAISE to the left down
    * input:   h.elevation=-0.5radians  raise(-0.1)
    * output:  h.elevation=-0.6radians
    *********************************************/
   void raise_leftDown()
   {
      Howitzer h;
      h.elevation.setRadians(-0.5);
      h.raise(-0.1);
      assertEquals(h.getElevation().getRadians(), -0.6);
   }

   /*********************************************
    * name:    RAISE to the left up
    * input:   h.elevation=-0.5radians  raise(0.1)
    * output:  h.elevation=0.4radians
    *********************************************/
   void raise_leftUp()
   {
      Howitzer h;
      h.elevation.setRadians(-0.5);
      h.raise(0.1);
      assertEquals(h.getElevation().getRadians(), 0.4);
   }

   /*********************************************
    * name:    ROTATE CLOCKWISE no wrapping
    * input:   h.elevation=1.23 rotate=.3
    * output:  h.elevation=1.53
    *********************************************/
   void rotate_clock()
   {
      Howitzer h;
      h.elevation.setRadians(1.23);
      h.rotate(0.3);
      assertEquals(h.getElevation().getRadians(), 1.53);
   }

   /*********************************************
    * name:    ROTATE COUNTER CLOCKWISE no wrapping
    * input:   h.elevation=1.23 rotate=-.3
    * output:  h.elevation=0.93
    *********************************************/
   void rotate_counterClock()
   {
      Howitzer h;
      h.elevation.setRadians(1.23);
      h.rotate(-0.3);
      assertEquals(h.getElevation().getRadians(), 0.93);
   }

   /*********************************************
    * name:    ROTATE CLOCKWISE WRAP BY 2PI
    * input:   h.elevation=6.1 (2pi + -0.1) rotate=.2
    * output:  h.elevation=.1
    *********************************************/
   void rotate_wrapClock()
   {
      Howitzer h;
      h.elevation.setRadians(6.1); // 2PI - 0.1
      h.rotate(0.2);
      assertEquals(h.getElevation().getRadians(), 0.1);
   }

   /*********************************************
    * name:    ROTATE COUNTER CLOCKWISE WRAP BY 2PI
    * input:   h.elevation=0.1 rotate=-.2
    * output:  h.elevation=6.1 (2pi + -0.1)
    *********************************************/
   void rotate_wrapCounterClock()
   {
      Howitzer h;
      h.elevation.setRadians(0.1);
      h.rotate(-0.2);
      assertEquals(h.getElevation().getRadians(), 6.1); // 2PI - 0.1
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
      p.metersFromPixels = 1100.0;
   }

   // teardown the standard fixture - reset the zoom to what it was previously
   void teardownStandardFixture()
   {
      assert(metersFromPixels != -1.0);
      Position p;
      p.metersFromPixels = metersFromPixels;
   }
};