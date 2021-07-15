/***********************************************************************
/
/  CHANGE PARTICLE TYPES - P3 --> NS , NS --> BH
/
/  written by: Danielle Skinner
/  date:       July, 2021
/  modified1:
/
/  NOTES:   Don't need this anymore.
/          
/
************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ErrorExceptions.h"
#include "macros_and_parameters.h"
#include "typedefs.h"
#include "global_data.h"
#include "Fluxes.h"
#include "GridList.h"
#include "ExternalBoundary.h"
#include "Grid.h"

int grid::ChangeParticleType(void)
{

  if (MyProcessorNumber != ProcessorNumber)
    return SUCCESS;

  if (NumberOfParticles == 0)
    return SUCCESS;

printf("Number of Particles = %d \n", NumberOfParticles);

  int i;
  Star *NewStar, *cstar;
  bool exists;

  //for (cstar = Stars; cstar; cstar = cstar->NextStar)
  //  if (cstar->Identifier == PopIII_NSMParticleID) {
	//  cstar->type = PARTICLE_TYPE_POPIII_BINARY;
	 // break;
	//} 

  for (i = 0; i < NumberOfParticles; i++){
	printf("(ChangeParticleType) Particle Type = %d \n", ParticleType[i]);
	printf("(ChangeParticleType) Particle number = %d \n", ParticleNumber[i]);
	printf("(ChangeParticleType) PopIII_NSMParticleID = %d \n", PopIII_NSMParticleID);
	
	/* Adding check for PopIIIParticleID to change Pop III star to binary system*/ 
	//if (ParticleNumber[i] == PopIII_NSMParticleID) {
	//	ParticleType[i] = -PARTICLE_TYPE_POPIII_BINARY;
    //    PopIII_NSMParticleID = -1;
     //   }
	}
   
  return SUCCESS;

}