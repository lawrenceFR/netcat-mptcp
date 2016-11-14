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
#include "makeaddr.h"
#include "suboption.h" 

int mptcp_getsubsockopt(int sockfd, struct mptcp_sub_getsockopt *sub_sso, int *optlen)
{
    *optlen = sizeof(struct mptcp_sub_getsockopt);
    int res = getsockopt(sockfd, IPPROTO_TCP, MPTCP_SUB_GETSOCKOPT, sub_sso, optlen);
    return res;
}

int mptcp_setsubsockopt(int sockfd, struct mptcp_sub_setsockopt *sub_sso)
{
		unsigned int optlen;
		optlen = sizeof(struct mptcp_sub_setsockopt);
		int res = setsockopt(sockfd, IPPROTO_TCP, MPTCP_SUB_SETSOCKOPT, sub_sso, optlen);
		return res;
}
