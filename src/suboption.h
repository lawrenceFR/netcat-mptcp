#ifndef SUBOPTION_H
#define SUBOPTION_H

#include <linux/tcp.h>
#include <linux/socket.h>
#include <linux/types.h>

#include <linux/tcp.h>
#include <linux/socket.h>
#include <linux/types.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/**
 * Function used to get a MPTCP subsocket option
 * @param sockfd the file descriptor of the MPTCP connexion
 * @param sub_sso the socket option to get
 * @param optlen the size of option returned (this value is modified by the function)
 * @return 0 if the function succeeded, other value otherwise (and errno is set)
 */
int mptcp_getsubsockopt(int sockfd, struct mptcp_sub_getsockopt *sub_sso, int *optlen);

/**
 * Functino used to set a MPTCP subsocket option
 * @param sockfd the file descriptor of the MPTCP connexion
 * @param sub_sso the socket option to set
 * @return 0 if the function succeeded, other value otherwise (and errno is set)
 */
int mptcp_setsubsockopt(int sockfd, struct mptcp_sub_setsockopt *sub_sso);

#endif
