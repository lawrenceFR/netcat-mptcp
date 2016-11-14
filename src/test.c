#include "makeaddr.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/tcp.h>
#include <linux/socket.h>
#include <linux/types.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include "submanip.h"
#include "subinfo.h"
#include "suboption.h"

/*int main(int argc, char **argv){

    // Try to open a IPV4 socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd <= 0){ perror("Socket creation failed: "); }

    // resolve a connexion point
    struct sockaddr_in *addr = malloc(sizeof(struct sockaddr_in));

    size_t ret_size = sizeof(*addr);
    int setipaddr_res = setipaddr_withport(AF_UNSPEC, "10.0.0.2",64002, (struct sockaddr *)addr, &ret_size);
    if(setipaddr_res < 0){ perror("Setting address failed: "); }

    // debug: print the connexion point
    char buf[512] = "";
    makeipaddr(addr, ret_size, buf, 512);
    printf("Resolved address: %s\n", buf);

    // connect to the server
    int res = connect(sockfd, (const struct sockaddr *)addr, ret_size);
    if(res != 0){ perror("Connect failed: "); }

    // and add a new subflow
    int res2 = mptcp_add_subflow(sockfd, AF_UNSPEC, "10.0.0.1", 64123, "10.0.0.2", 64002, 1);
    if(res2 != 0){ perror("Unable to add"); }

    // and now, list the subflows

    struct mptcp_sub_tuple_list *list;
    int res3 = mptcp_get_sub_list(sockfd,&list);
    while(list != NULL){
        struct mptcp_sub_tuple_info struc;
        mptcp_get_sub_tuple(sockfd, list->subid, &struc);
        printf("(%s %d) -> (%s %d)\n", struc.sourceH, struc.sourceP, struc.destH, struc.destP);
        list = list->next;
    }

    // remove the first subflow
    puts("Removing first subflow");
    mptcp_remove_subflow(sockfd, 1, 0);

    // re-show the lsit of subflows
    int res4 = mptcp_get_sub_list(sockfd,&list);
    while(list != NULL){
        struct mptcp_sub_tuple_info struc;
        mptcp_get_sub_tuple(sockfd, list->subid, &struc);
        printf("(%s %d) -> (%s %d)\n", struc.sourceH, struc.sourceP, struc.destH, struc.destP);
        list = list->next;
    }
}*/
