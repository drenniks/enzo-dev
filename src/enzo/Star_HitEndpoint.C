/***********************************************************************
/
/  FROM THE ATTRIBUTES, DETERMINE WHETHER THE STAR DIES
/
/  written by: John Wise
/  date:       April, 2009
/  modified1:
/
************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "ErrorExceptions.h"
#include "macros_and_parameters.h"
#include "typedefs.h"
#include "global_data.h"
#include "Fluxes.h"
#include "GridList.h"
#include "ExternalBoundary.h"
#include "Grid.h"
#include "Hierarchy.h"
#include "TopGridData.h"
#include "LevelHierarchy.h"
#include "phys_constants.h"

#define NO_DEATH 0
#define KILL_STAR 1
#define KILL_ALL 2

int GetUnits(float *DensityUnits, float *LengthUnits,
             float *TemperatureUnits, float *TimeUnits,
             float *VelocityUnits, FLOAT Time);

int Star::HitEndpoint(FLOAT Time)
{

  const float TypeIILowerMass = 11, TypeIIUpperMass = 40.1;
  const float PISNLowerMass = 140, PISNUpperMass = 260;

  float DensityUnits = 1.0, LengthUnits = 1.0, TemperatureUnits = 1,
    TimeUnits = 1.0, VelocityUnits = 1.0;

  if (GetUnits(&DensityUnits, &LengthUnits, &TemperatureUnits,
               &TimeUnits, &VelocityUnits, Time) == FAIL) {
    fprintf(stderr, "Error in GetUnits.\n");
    return FAIL;
  }

  /* First check if the star's past its lifetime and then check other
     constrains based on its star type */

  int result = NO_DEATH;
  if ((Time > this->BirthTime + this->LifeTime) && this->type >=0)
    result = KILL_STAR;
  else
    return result;

  switch (this->type) {

  case PopIII:
    // If a Pop III star is going supernova, only kill it after it has
    // applied its feedback sphere
    if ((this->Mass >= PISNLowerMass && this->Mass <= PISNUpperMass) ||
        ((this->Mass >= TypeIILowerMass && this->Mass <= TypeIIUpperMass) &&
            PopIIISupernovaExplosions == TRUE)) {

      // Needs to be non-zero (multiply by a small number to retain
      // memory of mass)
      if (this->FeedbackFlag == DEATH) {
	        this->Mass *= tiny_number;  


          // Set lifetime so the time of death is exactly now.
          this->LifeTime = Time - this->BirthTime;

          //this->FeedbackFlag = NO_FEEDBACK;
          result = KILL_STAR;
          //result = NO_DEATH;
      } 
      else {
	      result = NO_DEATH;
      }

    // Check mass: Don't want to kill tracer SN particles formed
    // (above) in the previous timesteps.

    } 
    else if (this->Mass > 1e-9) {
      // Turn particle into a black hole (either radiative or tracer)
      if (PopIIIBlackHoles) {
          this->type = BlackHole;
          this->LifeTime = huge_number;
          this->FeedbackFlag = NO_FEEDBACK;
          result = NO_DEATH;
      } 
      else {
          this->type = PARTICLE_TYPE_DARK_MATTER;
          result = KILL_STAR;
      }
    } else // SN tracers (must refine)
      result = NO_DEATH;



    if (debug)
      printf("HitEndpoint[%"ISYM"]: type = %"ISYM", mass = %"GOUTSYM", result = %"ISYM", feedback = %"ISYM", Time = %"PSYM"/%"PSYM"\n",
	     this->Identifier, this->type, this->Mass, result, this->FeedbackFlag, Time,
	     this->BirthTime+this->LifeTime);

    break;

  case PopIII_Binary:
    if (PopIII_NeutronStarMergers){
      // If a Pop III star is going supernova, only kill it after it has
      // applied its feedback sphere
      float initial_mass, initial_mass2;

             if (this->FeedbackFlag == DEATH) {

            // Needs to be non-zero (multiply by a small number to retain
            // memory of mass)
            
                // Set lifetime so the time of death is exactly now.
                //this->LifeTime = Time - this->BirthTime;

                //this->FeedbackFlag = NO_FEEDBACK;
                initial_mass = this->FinalMass/2.0;
                // Check initial mass of Pop III stars and find remnant mass
                // For now, assuming symmetric NS binary system
                initial_mass2 = initial_mass*initial_mass;

                // Masses from Heger et al. 2010 Fig. 6
                if (10.0 <= initial_mass <= 15.0) {
                  this->Mass = (0.0082 * initial_mass2 + 0.1221*initial_mass - 0.9775) * 2;
                }
                // Masses from Woosley et al. 2002 Fig. 12
                //if (8.0 < initial_mass < 10.6) {
                //  this->Mass = (0.162*initial_mass - 0.071) * 2;
                //}
                //else if (10.6 <= initial_mass <= 19.0) {
                //  this->Mass = 1.66 * 2;
                //}
                //else if (19.0 < initial_mass < 25.9) {
                //  this->Mass = (0.108*initial_mass - 0.387) * 2;
                //}


                // Set lifetime so the time of death is exactly now.
                //this->LifeTime = Time - this->BirthTime;
                this->LifeTime = PopIII_NSMDelayTime*1.0e6*yr_s/TimeUnits; // * TimeUnits; code time for right now
                this->BirthTime = Time;
                this->type = NS_Binary;
                //this->FeedbackFlag = POPIII_BINARY_SN;
                this->FeedbackFlag = NO_FEEDBACK;
                //this->MirrorToParticle();
                //result = KILL_STAR;
                result = NO_DEATH;
           }
            else {
              result = NO_DEATH;
            }
           
           
    }
      if (debug)
      printf("HitEndpoint[%"ISYM"]: type = %"ISYM", mass = %"GOUTSYM", result = %"ISYM", feedback = %"ISYM", Time = %"PSYM"/%"PSYM"\n",
	     this->Identifier, this->type, this->Mass, result, this->FeedbackFlag, Time,
	     this->BirthTime+this->LifeTime);

    break;
    

    case NS_Binary:
    if (PopIII_NeutronStarMergers){
      if (this->FeedbackFlag == DEATH) {
      //float age;
      //age = Time - this->BirthTime;
      //if (age >= PopIII_NSMDelayTime){
        this->type = BlackHole;
        this->BirthTime = Time;
        this->FeedbackFlag = NO_FEEDBACK;
        this->Mass *= tiny_number; 
        result = NO_DEATH;
      //}
      }
      else {
              result = NO_DEATH;
            }
      if (debug)
      printf("HitEndpoint[%"ISYM"]: type = %"ISYM", mass = %"GOUTSYM", result = %"ISYM", feedback = %"ISYM", Time = %"PSYM"/%"PSYM"\n",
	     this->Identifier, this->type, this->Mass, result, this->FeedbackFlag, Time,
	     this->BirthTime+this->LifeTime);

    break;
    }

    else result = NO_DEATH;

    if (debug)
      printf("HitEndpoint[%"ISYM"]: type = %"ISYM", mass = %"GOUTSYM", result = %"ISYM", feedback = %"ISYM", Time = %"PSYM"/%"PSYM"\n",
      this->Identifier, this->type, this->Mass, result, this->FeedbackFlag, Time,
      this->BirthTime+this->LifeTime);

    break;

  case PopII:
    break;

  case BlackHole:
    break;
    
  case MBH:
    break;

  case PopIII_CF:
    break;

  } // ENDSWITCH

  return result;
}
