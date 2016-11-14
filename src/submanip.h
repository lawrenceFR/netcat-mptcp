#ifndef SUBMANIP_H
#define SUBMANIP_H

#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
#include <linux/tcp.h>
#include <linux/socket.h>
#include <linux/types.h>
#include "subinfo.h"

/**
 * Function used to remove a subflow from a MPTCP connection
 * @param sockfd the socket which identifies the mptcp connexion
 * @param subid the id of the flow to close
 * @param how how to close the flow?
 * @return 0 if success, other value in case of failure (and errno is set)
 */
int mptcp_close_subflow(int sockfd, int subid, int how);

/**
 * Function used toi open a new subflow in a MPTCP connexion
 * @param sockfd the socket file descriptor
 * @param af
 * @param host1, port1: A string which identifies the source host and the source port, as a int
 * @param host2, port2: A string which identifies the destination host and port, as a int
 * @param prio priority of this subflow
 * @return 0 in case of success
 */
int mptcp_open_subflow(int sockfd, int af, char *host1, int port1, char *host2, int port2, int prio);

#endif
