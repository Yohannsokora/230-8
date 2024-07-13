/***********************************************************************
 * Source File:
 *    PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/

#include "projectile.h"
#include "angle.h"
#include "physics.h"

void Projectile::advance(double simulationTime)
{
   if (flightPath.empty())
      return;

   // Retrieve the last state from the flight path
   PositionVelocityTime last = flightPath.back();

   // Time delta
   double dt = simulationTime - last.t;

   // New state
   PositionVelocityTime next;

   // Update time
   next.t = simulationTime;

   // Update position based on velocity
   next.pos.setMetersX(last.pos.getMetersX() + last.v.getDx() * dt + 0.5 * accelerationFromForce(dragForce(last.v, radius), mass) * dt * dt);
   next.pos.setMetersY(last.pos.getMetersY() + last.v.getDy() * dt + 0.5 * accelerationFromForce(gravityForce(mass), mass) * dt * dt);

   // Update velocity based on forces
   next.v.setDx(last.v.getDx() + accelerationFromForce(dragForce(last.v, radius), mass) * dt);
   next.v.setDy(last.v.getDy() + accelerationFromForce(gravityForce(mass), mass) * dt);

   // Add the new state to the flight path
   flightPath.push_back(next);
}

void Projectile::fire(const Position &pos, const Angle &angle, const Velocity &velocity)
{
   PositionVelocityTime pvt;
   pvt.pos = pos;
   pvt.v = velocity;
   pvt.v.setDx(pvt.v.getDx() + velocity.getSpeed() * cos(angle.getRadians()));
   pvt.v.setDy(pvt.v.getDy() + velocity.getSpeed() * sin(angle.getRadians()));
   pvt.t = 0.0;
   flightPath.push_back(pvt);
}

void Projectile::draw(ogstream &gout) const
{
   for (const auto &pvt : flightPath)
   {
      gout.drawProjectile(pvt.pos, radius);
   }
}
