/***********************************************************************
/
/  CHANGE PARTICLE TYPE
/
/  written by: Danielle Skinner
/  date:       July, 2021
/  modified1:
/
/  PURPOSE: Given a Particle ID number, change this particle from a Pop 
/           III star to a Neutron Star Binary, and after the merger 
/           takes place, change particle to BH.
/           Checks first to see if particle has already been changed.
/
************************************************************************/

#include "ErrorExceptions.h"
#include "EnzoTiming.h"
#include "performance.h"
#include "macros_and_parameters.h"
#include "typedefs.h"
#include "global_data.h"
#include "units.h"
#include "flowdefs.h"
#include "Fluxes.h"
#include "GridList.h"
#include "ExternalBoundary.h"
#include "Grid.h"
#include "Hierarchy.h"
#include "LevelHierarchy.h"
#include "TopGridData.h"
#include "communication.h"
#include "CommunicationUtilities.h"

int StarParticleChangeType(Star *AllStars)
{
    Star *ThisStar;

    if (PopIII_NeutronStarMergers == 1){
        // Check if the particle has already changed to a PopIII Binary system
        if (PopIII_NSMParticleID == -1){
            
            return SUCCESS;
        }

        else {
            for (ThisStar = AllStars; ThisStar; ThisStar = ThisStar->NextStar){
                //printf("Current Particle ID in StarParticleChangeType = %d \n", ThisStar->ReturnID());
                if (ThisStar->ReturnID() == PopIII_NSMParticleID){
                    ThisStar->SetType(PARTICLE_TYPE_POPIII_BINARY);
                    PopIII_NSMParticleID = -1;
                    printf("PopIII star changed to PopIII_Binary. \n");
                }
            }
        }
    }
}