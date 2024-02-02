//  Majordomo Protocol client example
//  Uses the mdcli API to hide all MDP aspects

//  Lets us build this source without creating a library

#include "mdclient.h"

/* basic.c. ajd ****************************************************/

char *MDP_SERVICE_PNT = "avc.rpc.pnt";
char *MDP_SERVICE_INF = "avc.rpc.inf";
char *CELL_DUMMY = "VC00000";

/* --- */

int
get_closest_cell (mdp_point_t *pnt, mdp_point_t *cll)
{
  int rc;
  int verbose = 1;
  char buf[32];
  mdcli_t *session = mdcli_new ("tcp://127.0.0.1:5554", verbose);
  zmsg_t *request = zmsg_new ();
  char *cell_id_mdp;
  zmsg_addstrf (request, "%.7f", pnt->lat);
  zmsg_addstrf (request, "%.7f", pnt->lon);
  zmsg_t *msg = mdcli_send (session, MDP_SERVICE_PNT, &request);
  zframe_t *frame;
  if (msg)
    {
      // Cell-Id
      frame = zmsg_pop (msg);
      cell_id_mdp = zframe_strdup (frame);
      // Cell-Action
      frame = zmsg_pop (msg);
      char *cell_action_data = zframe_strdup (frame);
      // Cell-Change
      frame = zmsg_pop (msg);
      char *cell_change_data = zframe_strdup (frame);
      zmsg_destroy (&msg);
      rc = 0;
    }
  else
    {
      rc = -1;
    }

  if (strncasecmp (cell_id_mdp, CELL_DUMMY, 7) == 0)
    rc = -2;

  if (rc == 0)
    {
      request = zmsg_new ();
      zmsg_addstrf (request, cell_id_mdp);
      msg = mdcli_send (session, MDP_SERVICE_INF, &request);
      if (msg)
        {
          // Cell-Id
          frame = zmsg_pop (msg);
          // Cell-Latitude
          frame = zmsg_pop (msg);
          char *lat = zframe_strdup (frame);
          cll->lat = atof (lat);
          // Cell-Longitude
          frame = zmsg_pop (msg);
          char *lon = zframe_strdup (frame);
          cll->lon = atof (lon);
          // Cell-Height
          frame = zmsg_pop (msg);
          char *hgt = zframe_strdup (frame);
          cll->hgt = atof (hgt);
          rc = 0;

          strncpy (cll->name, cell_id_mdp, 7);
          cll->name[7] = '\0';
        }
      else
        rc = -3;
    }

  return rc;
}

// int
// main ()
// {
//   struct mdp_point_t pnt = { "CLI-123", 48.0, 16.0, 100.0 };
//   struct mdp_point_t cll = { "", 0.0, 0.0, 0.0 };
//   strncpy (cll.name, CELL_DUMMY, 7);
//   cll.name[7] = '\0';
//   int rc = get_closest_cell (&pnt, &cll);
//   zclock_log ("%s, %.7f, %.7f, %.3f", cll.name, cll.lat, cll.lon, cll.hgt);
// }