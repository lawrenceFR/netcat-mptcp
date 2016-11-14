#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <malloc.h>
#include <memory.h>
#include <errno.h>


/* Create a string object representing an IP address.
   This is always a string of the form 'dd.dd.dd.dd' (with variable
   size numbers). */
int makeipaddr(struct sockaddr * addr, int addrlen, char *buf, int bufsize)
{
    int error;

    if(addr->sa_family == AF_INET){
        struct sockaddr_in *in = (struct sockaddr_in *) addr;
        if(in->sin_addr.s_addr == INADDR_BROADCAST){
            if(strlen("<broadcast>") <= bufsize)
                strcpy(buf, "<broadcast>");

            return 0;
        }
    }

    error = getnameinfo(addr, addrlen, buf, bufsize, NULL, 0, NI_NUMERICHOST);
    if (error) {
        return error;
    }
    return 0;
}


// custom (non buggy) version of setipaddr
int setipaddr(int resolve_af, const char *name, struct sockaddr *addr_ret, size_t *addr_ret_size){
    struct addrinfo hints;
    struct addrinfo *result;
    hints.ai_family = resolve_af;
    hints.ai_socktype  =SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = 0;
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    int error = 0;

    // getting address
    if(name[0] == '\0'){
        // empty string representf INET_ANY in python
        error = getaddrinfo(NULL, "0", &hints, &result);

        if (error) {
            return error;
        }

        if (result->ai_next) {
            freeaddrinfo(result);
            // "wildcard resolved to multiple address"
            return -1;
        }
    }
    else if (strcmp(name, "255.255.255.255") == 0 ||
             strcmp(name, "<broadcast>") == 0) {
        // broadcast addresses


        result= calloc(1,sizeof(struct addrinfo));
        result->ai_addr = calloc(1, sizeof(struct sockaddr_in *));
        result->ai_addrlen = sizeof(struct sockaddr_in *);

        struct sockaddr_in *in = (struct sockaddr_in *) result->ai_addr;
        in->sin_family = AF_INET;
        in->sin_addr.s_addr = INADDR_BROADCAST;
    }
    else{
        // host resolving
        error = getaddrinfo(name, NULL, &hints, &result);
        if (error) {
            puts("Unable to resolve!"); 
            errno = EFAULT;
            return error;
        }
    }

    // copying result
    if (result->ai_addrlen < *addr_ret_size)
        *addr_ret_size = result->ai_addrlen;
    memcpy((char *)addr_ret, result->ai_addr, *addr_ret_size);
    freeaddrinfo(result);

    // checking result
    switch (addr_ret->sa_family) {
        case AF_INET:
            return 4;
        case AF_INET6:
            return 16;
        default:
            // "unknown address family"
            puts("Unknown address family"); 
	    printf("    %d\n", addr_ret->sa_family); 
            return -1;
    }
}

int setipaddr_withport(int af, const char *name, int port, struct sockaddr *addr_ret, size_t *addr_ret_size){
    int res = setipaddr(af, name, addr_ret, addr_ret_size);
    if(!res){
        return res;
    }

    if(addr_ret->sa_family == AF_INET){
        struct sockaddr_in *addr_in = (struct sockaddr_in*)addr_ret;
        addr_in->sin_port = htons(port);
    }
    if(addr_ret->sa_family == AF_INET6){
        struct sockaddr_in6 *addr_in = (struct sockaddr_in6*)addr_ret;
        addr_in->sin6_port = htons(port);
    }
    return res;
}
