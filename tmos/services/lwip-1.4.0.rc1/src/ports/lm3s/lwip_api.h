/*
 * lwip_api.h
 *
 *  Created on: 29.04.2011
 *      Author: Miroslav Kostadinov
 */

#ifndef LWIP_API_H_
#define LWIP_API_H_

#include <lwip/netif.h>
#include <lwip/tcp.h>
#include <mqueue.h>

#define LWIP_CMD_TCP_NEW		(( 0 <<4)+CMD_COMMAND)
#define LWIP_CMD_TCP_BIND		(( 1 <<4)+CMD_COMMAND)
#define LWIP_CMD_TCP_LISTEN		(( 2 <<4)+CMD_COMMAND)
#define LWIP_CMD_TCP_ACCEPT		(( 3 <<4)+CMD_COMMAND)
#define LWIP_CMD_TCP_CONNECT	(( 4 <<4)+CMD_COMMAND)
#define LWIP_CMD_TCP_CLOSE		(( 5 <<4)+CMD_COMMAND)
#define LWIP_CMD_TCP_DNS		(( 6 <<4)+CMD_COMMAND)

#define MAX_LWIPCALLBACK 		7

#ifndef LWIP_DRV_MAX_API_QUEUE
#define LWIP_DRV_MAX_API_QUEUE 	3
#endif

//handle state flags
#define TCPHS_OP_PCB			0x01	// client->mode is valid pcb
#define TCPHS_OP_WRITING		0x02	// Write pending
#define TCPHS_OP_READING		0x04	// Read pending
#define TCPHS_OP_CONNECTING		0x08	// Connect pending
#define TCPHS_OP_ACCEPTING		0x10	// Connect pending

#define TCPHS_OP_BOND			0x20	// Connection bond
#define TCPHS_OP_LISTEN			0x40	// Connection in listen state
#define TCPHS_OP_ESTABLISHED	0x80	// Connection is established (connected or accepted)

// handle states
#define TCPHS_UNKNOWN		0										//can new
#define TCPHS_NEW			(TCPHS_OP_PCB)							//can bind connect
#define TCPHS_CONECTING		(TCPHS_NEW | TCPHS_OP_CONNECTING)
#define TCPHS_BIND			(TCPHS_NEW | TCPHS_OP_BOND)				//can listen
#define TCPHS_LISTEN		(TCPHS_NEW | TCPHS_OP_LISTEN)			//can accept
#define TCPHS_ESTABLISHED	(TCPHS_NEW | TCPHS_OP_ESTABLISHED)		//can read write
#define TCPHS_WRITING		(TCPHS_ESTABLISHED | TCPHS_OP_WRITING)
#define TCPHS_READING		(TCPHS_ESTABLISHED | TCPHS_OP_READING)

#define TCPHS_CANCELABLE	(TCPHS_OP_READING | TCPHS_OP_ACCEPTING)
#define TCPHS_ALLPENDING	(TCPHS_OP_READING | TCPHS_OP_ACCEPTING | TCPHS_OP_WRITING | TCPHS_OP_CONNECTING)

#define LWIP_SHUT_WR		1
#define LWIP_SHUT_RD		2
#define LWIP_SHUT_RDWR		3

/**
 * Handle for lwIP stack operations
 *
 *  Timeouts:
 *  	read operations supports timeouts
 *  	accept supports timeout
 *  	write operations will ignore the timeouts (can block for long period?)
 */
class tcp_handle: public CHandle
{
public:
	tcp_handle(): recv_pos(0) {};

	unsigned int recv_pos;
	fmqueue< struct tcp_pcb*, LWIP_DRV_MAX_API_QUEUE >	accept_que;
	fmqueue< struct pbuf*, LWIP_DRV_MAX_API_QUEUE >	recv_que;


	//--- not blocking functions

#ifdef LWIP_CMD_TCP_NEW
	RES_CODE lwip_tcp_new(unsigned int priority = TCP_PRIO_NORMAL);
#endif

#ifdef LWIP_CMD_TCP_BIND
	RES_CODE lwip_tcp_bind(ip_addr_t *ipaddr, u16_t port);
#endif

#ifdef LWIP_CMD_TCP_LISTEN
	RES_CODE lwip_tcp_listen();
#endif

	//--- blocking functions
#ifdef LWIP_CMD_TCP_ACCEPT
	//waits until connection
	RES_CODE lwip_tcp_accept(struct tcp_pcb*& newpcb, unsigned int time = 1024*1024);
#endif

#ifdef LWIP_CMD_TCP_CONNECT
	RES_CODE lwip_tcp_connect(ip_addr_t *addr, u16_t port);
#endif

#ifdef LWIP_CMD_TCP_CLOSE
RES_CODE lwip_tcp_close(unsigned int rxtx=LWIP_SHUT_RDWR);
#endif

#ifdef LWIP_CMD_TCP_DELETE
RES_CODE lwip_tcp_delete();
#endif

#ifdef LWIP_CMD_TCP_DNS
RES_CODE lwip_tcp_dns(const char* url, ip_addr_t *addr);
#endif

};

RES_CODE lwip_api_read(tcp_handle* client);
RES_CODE lwip_api_write(tcp_handle* client, struct netif *netif);
void lwip_tcp_setup(tcp_handle* client, struct tcp_pcb *pcb);

typedef RES_CODE (*LWIP_API_FUNC)(tcp_handle* client, struct netif *netif);
EXTERN_C const LWIP_API_FUNC lwip_api_functions[MAX_LWIPCALLBACK+1];

#endif /* LWIP_API_H_ */
