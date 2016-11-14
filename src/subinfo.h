#ifndef SUBINFO_H
#define SUBINFO_H

struct mptcp_sub_tuple_list{
    int subid;
    int priority;
    struct mptcp_sub_tuple_list *next;
};

struct mptcp_sub_tuple_info{
    char *sourceH;
    int sourceP;
    char *destH;
    int destP;
};

/**
 * Function which lists all the subflow of a mptcp connexion, as a list:
 *  [subflow id, subflow priority]
 * @param sockfd the file descriptor which describes the socket
 * @param ret_array the retured array
 * @param ret_array_size the returned array size
 * @return
 */
int mptcp_get_sub_list(int sockfd, struct mptcp_sub_tuple_list **out);
int mptcp_get_sub_tuple(int sockfd, int subid,struct mptcp_sub_tuple_info *ret_tuple);

#endif
