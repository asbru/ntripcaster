//
//  mdp.h
//  Majordomo Protocol definitions
//
#ifndef __MDP_H_INCLUDED__
#define __MDP_H_INCLUDED__

#include <stddef.h>

//  This is the version of MDP/Client we implement
#define MDPC_CLIENT "MDPC01"

//  This is the version of MDP/Worker we implement
#define MDPW_WORKER "MDPW01"

//  MDP/Server commands, as strings
#define MDPW_READY "\001"
#define MDPW_REQUEST "\002"
#define MDPW_REPLY "\003"
#define MDPW_HEARTBEAT "\004"
#define MDPW_DISCONNECT "\005"

static char *mdps_commands[]
    = { NULL, "READY", "REQUEST", "REPLY", "HEARTBEAT", "DISCONNECT" };

#endif
