#include <netinet/in.h>
#include <stdlib.h>
#include <linux/tcp.h>
#include <linux/socket.h>
#include <linux/types.h>
#include "makeaddr.h"

int mptcp_remove_subflow(int sockfd, int subid, int how)
{
    unsigned int optlen;
    struct mptcp_close_sub_id sub_sso;
    sub_sso.id = subid;
    // sub_sso.how = how; | ! | For the moment, that field is not set in the structure
    optlen = sizeof(struct mptcp_close_sub_id);
    int res = getsockopt(sockfd, IPPROTO_TCP, MPTCP_CLOSE_SUB_ID,
                         &sub_sso, &optlen);

    return res;
}

int mptcp_add_subflow(int sockfd, int resolve_af, char *host1, int port1, char *host2, int port2, int prio)
{
    unsigned int optlen;
    struct mptcp_sub_tuple *sub_tuple;
    optlen = sizeof(struct mptcp_sub_tuple) + 2 * sizeof(struct sockaddr_in);
    sub_tuple = malloc(optlen);

    sub_tuple->id = 0;
    // sub_tuple->prio = prio; | ! | That field is not yet implemented

    struct sockaddr_in *addr = (struct sockaddr_in *)&sub_tuple->addrs[0];

    int ret_size = 0;

    int l1 = sizeof(*addr);
    int r1 = setipaddr_withport(resolve_af, host1, port1, addr, &l1);
    printf("\nHere at setipaddr_withoutport. r1 = %d\n", r1);
    if (r1 < 0) {
	printf("\nResolve failed 1 !!!\n");
	return r1;
    }

    addr++;

    int l2 = sizeof(*addr);
    int r2 = setipaddr_withport(resolve_af, host2, port2, addr, &l2);
    printf("\nHere at setipaddr_withoutport. r2 = %d\n", r2);

    if (r2 < 0) {
	printf("\nResolve failed 2 !!!\n");
	return r2;
    }

    int res = getsockopt(sockfd, IPPROTO_TCP, MPTCP_OPEN_SUB_TUPLE, sub_tuple, &optlen);
    printf("\nHere after getsockopt. res = %d\n", res);

    return res;

    return sub_tuple->id;
}
