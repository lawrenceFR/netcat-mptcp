#ifdef MAKEADDR_H
#define MAKEADDR_H

/**
    Useful functions used to read and create sockaddr structures only by specifying
    simple informations such as host name, and port without needning to calls like
    gethostbyname, etc ...

    Handles both IPv6 and IPv4, by CLAREMBEAU Alexis
*/

/**
    Makes (returns) a string with dot notation describing an IP address

    Params:
        addr: the sockaddr structure containing the infomations about the addres
        addrlen: the size of the addr structure
        buf: the string buffer that will contain the result
        busize: the capacity of the buffer

    Returns:
        Puts the dot notation of the address inside buf
*/
int makeipaddr(struct sockaddr * addr, int addrlen, char *buf, int bufsize);

/**
    Constructs an sockaddr structure with the right hostname and port.
    If needed, resolves the host.

    Params:
        af: the address family to resolve
        name: the name of the address to build
        port: the port to connect to
        addr_ret: the variable that will contain the result
        addr_rer_size: the variable taht will store the real size of addr_ret
*/
int setipaddr_withport(int resolve_af, const char *name, int port, struct sockaddr *addr_ret, size_t *addr_ret_size);


/**
    Constructs an sockaddr structure with the right hostname.
    If needed, resolves the host.

    Params:
        af: the address family to resolve
        name: the name of the address to build
        port: the port to connect to
        addr_ret: the variable that will contain the result
        addr_rer_size: the variable taht will store the real size of addr_ret
*/
int setipaddr(int af, const char *name, struct sockaddr *addr_ret, size_t addr_ret_size);

#endif