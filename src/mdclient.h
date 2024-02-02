//  Majordomo Protocol client example
//  Uses the mdcli API to hide all MDP aspects

//  Lets us build this source without creating a library

#ifndef __MDCLIENT_H_INCLUDED__
#define __MDCLIENT_H_INCLUDED__

#include "mdcliapi.h"

/* basic.c. ajd ****************************************************/

typedef struct mdp_point_t
{
  char name[7];
  double lat; // Latitude of point
  double lon; // Longitude of point
  double hgt; // Height of point
} mdp_point_t;

int get_closest_cell (mdp_point_t *pnt, mdp_point_t *cll);

#endif