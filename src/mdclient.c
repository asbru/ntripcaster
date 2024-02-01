//  Majordomo Protocol client example
//  Uses the mdcli API to hide all MDP aspects

//  Lets us build this source without creating a library
#include "mdcliapi.c"
#include "ntripcaster.h"

/* basic.c. ajd ****************************************************/

extern server_info_t info;

const char *MDP_SERVICE_PNT = "avc.rpc.pnt";
/* --- */

int
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
  zmsg_t *msg = mdcli_send (session, MDP_SERVICE_PNT, &request);
  if (msg)
    {
      // Read header
      zframe_t *header_frame = zmsg_pop (msg);
      char *header_data = zframe_strdup (header_frame);
      zclock_log ("header %s", header_data);
      zframe_destroy (&header_frame);

      // Reat Latitude
      zframe_t *lat_frame = zmsg_pop (msg);
      char *lat_data = zframe_strdup (lat_frame);
      zclock_log ("lat %s", lat_data);
      zframe_destroy (lat_frame);

      // Reat Longitude
      zclock_log ("header %s", header_data);
      zframe_t *lon_frame = zmsg_pop (msg);
      char *lon_data = zframe_strdup (lon_frame);
      zclock_log ("lat %s", lon_data);
      zframe_destroy (lon_frame);

      zmsg_destroy (&msg);
      return 0;
    }
  else
    {
      strcpy (cell_name, "VC00000");
      return -1;
    }
}
