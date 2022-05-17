/***********************************************************************
/
/  POP III IMF LOOKUP TABLE INITIALIZATION FOR NSM
/  Creates a table for the desired mass range for PopIII stars to become NSs
/
/  written by: Danielle Skinner
/  date:       May, 2022
/  modified1:
/
************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
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

void mt_init(unsigned_int seed);
unsigned_long_int mt_random(void);

int StarParticlePopIII_ForceMassInitialize(void)
{

  int i;
  float dm;

  if (NSM_IMFData != NULL)
    return SUCCESS;

  NSM_IMFData = new float[NSM_IMF_TABLE_ENTRIES];
  dm = (NSMUpperMassCutoff - NSMLowerMassCutoff) / NSM_IMF_TABLE_ENTRIES ;

  for (int i = 0; i <= NSM_IMF_TABLE_ENTRIES; i++){
      NSM_IMFData[i] = NSMLowerMassCutoff + i*dm ;
  }
  // Normalize
  for (i = 0; i < NSM_IMF_TABLE_ENTRIES; i++)
      NSM_IMFData[i] /= NSM_IMFData[NSM_IMF_TABLE_ENTRIES-1];

if (PopIII_NSM_Seed == INT_UNDEFINED)
    mt_init(time(NULL)); //+100*MyProcessorNumber);
  else
    mt_init(PopIII_NSM_Seed); //+100*MyProcessorNumber);
  unsigned_long_int trash;
  for (i = 0; i < 1+PopIII_NSM_Seed; i++)
    trash = mt_random();

  return SUCCESS;

}
