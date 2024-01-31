//  Majordomo Protocol client example
//  Uses the mdcli API to hide all MDP aspects

//  Lets us build this source without creating a library
#include "mdcliapi.c"
#include "ntripcaster.h"

/* basic.c. ajd ****************************************************/

extern server_info_t info;

const char *MDP_SERVICE_PNT = "avc.rpc.pnt";
/* --- */

get_closest_cell (double lat, double lon, int verbose, char *cell_name)
{
  mdcli_t *session = mdcli_new (info.mdp_url, verbose);
  zmsg_t *request = zmsg_new ();
  char buf[32];
  zmsg_t *request = zmsg_new ();
  sprintf (buf, "%.7f", lat);
  zmsg_pushstr (request, buf);
  sprintf (buf, "%.7f", lon);
  zmsg_pushstr (request, buf);
  zmsg_t *reply = mdcli_send (session, MDP_SERVICE_PNT, &request);
  if (reply)
    {
      zmsg_destroy (&reply);
      return 0;
    }
  else
    {
      strcpy (cell_name, "VC00000");
      return -1;
    }
}
