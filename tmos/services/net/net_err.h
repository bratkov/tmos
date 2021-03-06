/*
 * net_err.h
 *
 *  Created on: Mar 1, 2012
 *      Author: miro
 */

#ifndef NET_ERR_H_
#define NET_ERR_H_


typedef unsigned int  NET_CODE;

//-----------------			 common error codes				 -----------------//
#define NET_IDLE					0x00	//!< No result is available yet
#define NET_OK						0x01	//!< Success (no errors)
#define NET_EOF						0x03	//!< Reached End of File
#define NET_ERROR					0x10	//!< Logical or Unknown error
#define NET_ERR_OUT_OF_MEMORY		0x14	//!< Out of memory
#define NET_ERR_HANDLE_OPEN			0x81	//!< Failed to open handle
#define NET_BAD_DATA_RECEIVED		0x82	//!< Received bad data

//-----------------			Socket error codes				 -----------------//
#define NET_ERR_PHY_NOT_READY		0x90	//!< Physical level (cable or modem)
#define NET_ERR_SOCK_CLOSED			0x91	//!< Socket is closed
#define NET_ERR_SOCK_NOT_CLOSED		0x92	//!< Socket is not closed
#define NET_ERR_SOCK_CREATE			0x93	//!< Failed to get socket
#define NET_ERR_SOCK_CONNECT		0x94	//!< Failed to connect socket
#define NET_ERR_SOCK_DISCONNECT		0x95	//!< Host disconnect socket
#define NET_ERR_SOCK_ABORT			0x96	//!< User disconnect socket
#define NET_ERR_SOCK_READ			0x97	//!< Failed to read from socket
#define NET_ERR_SOCK_WRITE			0x98 	//!< Failed to write into socket
#define NET_ERR_NO_LINK				0x99	//!< Link Layer failed

//-----------------		URL error codes						 -----------------//
#define NET_ERR_URL_SCHEME			0xA0	//!< BAD or unsupported URL scheme
#define NET_ERR_URL_INVALID			0xA1	//!< URL is invalid
#define NET_ERR_URL_DNS				0xA2	//!< Failed to resolve the domain address
#define NET_ERR_URL_REDIRECTED		0xA3	//!< Redirected
#define NET_ERR_HTTP_CODE			0xA4	//!< HTTP code is not 200 OK
#define NET_ERR_HTTP_ERROR			2048	//!< 2048..4096 HTTP code + 2048
#define NET_ERR_FTP_CODE			4096	//!< 4096..81926 FTP code + 4096

//-----------------		file error codes					 -----------------//
#define NET_ERR_FILE_SYSTEM			0xB0	//!< BAD or broken file system
#define NET_ERR_BAD_SECTOR			0xB1	//!< BAD sector
#define NET_ERR_FILE_READ			0xB2	//!< Failed to read sector
#define NET_ERR_FILE_WRITE			0xB3	//!< Failed to write sector
#define NET_ERR_WRITE_PROTECT		0xB4	//!< Failed to write sector



#endif /* NET_ERR_H_ */
