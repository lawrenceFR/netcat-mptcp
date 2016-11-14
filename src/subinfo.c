#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
#include <linux/tcp.h>
#include <linux/socket.h>
#include <linux/types.h>
#include "makeaddr.h"
#include "subinfo.h"

#define INIT_SUBNUM 2
#define MAX_SUBNUM 33
#define SUBNUM_FACT 2
#define MAX_ADDR_SIZE 2048

int mptcp_get_sub_list(int sockfd, struct mptcp_sub_tuple_list **out_list)
{
    int i;
    unsigned int optlen;
    struct mptcp_sub_ids *ids;

    int maxSub = INIT_SUBNUM;
    int res = 0;

    while(maxSub < MAX_SUBNUM){
        // tries to match at most maxSub subflows

        optlen = sizeof(struct mptcp_sub_ids) + maxSub * sizeof(struct mptcp_sub_status);
        ids = malloc(optlen);
        int res = getsockopt(sockfd, IPPROTO_TCP, MPTCP_GET_SUB_IDS, ids, &optlen);

        if(res >= 0){
            // enough memory and good result
            break;
        }
        else if(errno != EINVAL){
            // enough memory and bad result
            return errno;
        }
        // else: not enough memory: loop

        maxSub *= SUBNUM_FACT;
    }

    if(res < 0){
        return res; 
   }

    *out_list = calloc(1, sizeof(struct mptcp_sub_tuple_list));
    if(ids->sub_count > 0){
        (*out_list)->subid = ids->sub_status[0].id;
        (*out_list)->priority = ids->sub_status[0].low_prio;

        struct mptcp_sub_tuple_list *n = *out_list;

	int i;
        for (i = 1; i < ids->sub_count; i++) {
            n->next = calloc(1, sizeof(struct mptcp_sub_tuple_list));

            n->next->subid =  ids->sub_status[i].id;
            n->next->priority = ids->sub_status[i].low_prio;
            n = n->next;
        }
    }


    return 0;
}

int mptcp_get_sub_tuple(int sockfd, int subid, struct mptcp_sub_tuple_info *ret_tuple)
{
    unsigned int optlen;
    struct mptcp_sub_tuple *sub_tuple;

    optlen = sizeof(struct mptcp_sub_tuple) + 2 * sizeof(struct sockaddr_in);
    sub_tuple = malloc(optlen);

    sub_tuple->id = subid;
    int res = getsockopt(sockfd, IPPROTO_TCP, MPTCP_GET_SUB_TUPLE, sub_tuple, &optlen);

    if (res < 0) {
        return res;
    }

    struct sockaddr_in *sin = (struct sockaddr_in *)&sub_tuple->addrs[0];

    char *bufA = malloc(sizeof(char) * MAX_ADDR_SIZE);
    int rA = makeipaddr((struct sockaddr *)sin, sizeof(struct sockaddr_in), bufA, MAX_ADDR_SIZE);
    if(rA < 0) return rA;
    int portA = htons(sin->sin_port);

    sin++;

    char *bufB = malloc(sizeof(char) * MAX_ADDR_SIZE);
    int rB = makeipaddr((struct sockaddr *)sin, sizeof(struct sockaddr_in), bufB, MAX_ADDR_SIZE);
    if(rB < 0) return rB;
    int portB = htons(sin->sin_port);

    ret_tuple->sourceH = bufA;
    ret_tuple->destH = bufB;
    ret_tuple->sourceP = portA;
    ret_tuple->destP = portB;

    return 0;
}
