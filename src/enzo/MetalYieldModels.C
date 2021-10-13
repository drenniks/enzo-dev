/***********************************************************************
/
/  MODELS FOR METAL YIELDS FOR POPIII STARS
/
/  written by: Danielle Skinner
/  date:       October, 2021
/  modified1: 
/             
/  PopIII_MetalYield = 0 # Nomoto model
/  PopIII_MetalYield = 1 # Limongi+ 12
/  PopIII_MetalYield = 2 # Takahashi+ 14
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
#include "Hierarchy.h"
#include "TopGridData.h"
#include "LevelHierarchy.h"
#include "phys_constants.h"