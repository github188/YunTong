
/* 2012-03-07 */


#ifndef TNET_DHCP6_H
#define TNET_DHCP6_H

#include "tinynet_config.h"

#include "tnet_dhcp6_message.h"

#include "tnet_utils.h"

#include "tsk_object.h"
#include "tsk_safeobj.h"

TNET_BEGIN_DECLS

#define TNET_DHCP6_VENDOR_CLASS_DATA_DEFAULT		"weicall/v0.0.0"

/** RFC 3315 - 5.1. Multicast Addresses
*	A link-scoped multicast address used by a client to communicate with
*   neighboring (i.e., on-link) relay agents and servers.
*   All servers and relay agents are members of this multicast group.
*/
#define TNET_DHCP6_All_DHCP_Relay_Agents_and_Servers	"FF02::1:2"

/** RFC 3315 - 5.1. Multicast Addresses
*	A site-scoped multicast address used by a relay agent to communicate with servers, either
*	because the relay agent wants to send messages to all servers or because it does not know the unicast
*	addresses of the servers.  Note that in order for a relay agent to use this address, it must have an
*	address of sufficient scope to be reachable by the servers.  All servers within the site are members of
*	this multicast group.
*/
#define TNET_DHCP6_All_DHCP_Servers					"FF05::1:3"

/*== RFC 3315 - 5.5. Transmission and Retransmission Parameters
 * This section presents a table of values used to describe the message 
 *	transmission behavior of clients and servers.
*/
#define TNET_DHCP6_RT_SOL_MAX_DELAY		1   /**< 1 sec   Max delay of first Solicit */
#define TNET_DHCP6_RT_SOL_TIMEOUT		1   /**< 1 sec   Initial Solicit timeout */
#define TNET_DHCP6_RT_SOL_MAX_RT		120	/**< 120 secs  Max Solicit timeout value */
#define TNET_DHCP6_RT_REQ_TIMEOUT		1   /**< 1 sec   Initial Request timeout */
#define TNET_DHCP6_RT_REQ_MAX_RT		30	/**< 30 secs  Max Request timeout value */
#define TNET_DHCP6_RT_REQ_MAX_RC		10	/**< 10       Max Request retry attempts */
#define TNET_DHCP6_RT_CNF_MAX_DELAY		1   /**< 1 sec   Max delay of first Confirm */
#define TNET_DHCP6_RT_CNF_TIMEOUT		1   /**< 1 sec   Initial Confirm timeout */
#define TNET_DHCP6_RT_CNF_MAX_RT		4   /**< 4 secs  Max Confirm timeout */
#define TNET_DHCP6_RT_CNF_MAX_RD		10	/**< 10 secs  Max Confirm duration */
#define TNET_DHCP6_RT_REN_TIMEOUT		10	/**< 10 secs  Initial Renew timeout */
#define TNET_DHCP6_RT_REN_MAX_RT		600	/**< 600 secs  Max Renew timeout value */
#define TNET_DHCP6_RT_REB_TIMEOUT		10	/**< 10 secs  Initial Rebind timeout */
#define TNET_DHCP6_RT_REB_MAX_RT		600	/**< 600 secs  Max Rebind timeout value */
#define TNET_DHCP6_RT_INF_MAX_DELAY		1   /**< 1 sec   Max delay of first Information-request */
#define TNET_DHCP6_RT_INF_TIMEOUT		1   /**< 1 sec   Initial Information-request timeout */
#define TNET_DHCP6_RT_INF_MAX_RT		120	/**< 120 secs  Max Information-request timeout value */
#define TNET_DHCP6_RT_REL_TIMEOUT		1   /**< 1 sec   Initial Release timeout */
#define TNET_DHCP6_RT_REL_MAX_RC		5   /**< 5       MAX Release attempts */
#define TNET_DHCP6_RT_DEC_TIMEOUT		1   /**< 1 sec   Initial Decline timeout */
#define TNET_DHCP6_RT_DEC_MAX_RC		5   /**< 5       Max Decline attempts */
#define TNET_DHCP6_RT_REC_TIMEOUT		2   /**< 2 secs  Initial Reconfigure timeout */
#define TNET_DHCP6_RT_REC_MAX_RC		2   /**< 8       Max Reconfigure attempts */
#define TNET_DHCP6_RT_HOP_COUNT_LIMIT	32	/**< 32     Max hop count in a Relay-forward message */

/** RFC 3315 - 5.6  Representation of time values and "Infinity" as a time value */
#define TNET_DHCP6_TIMEVAL_INFINITY		0XFFFFFFFF

/**< Local port(client) to bind to for incoming DHCP messages as per RFC 3315 subclause 5.2. */
#define TNET_DHCP6_CLIENT_PORT		546
/**< Destination port(Server) for outgoing DHCP messages as per RFC 3315 subclause 5.2. */
#define TNET_DHCP6_SERVER_PORT		547

/**@ingroup tnet_dhcpv_group
* DHCPv6 context.
*/
typedef struct tnet_dhcp6_ctx_s
{
	TSK_DECLARE_OBJECT;
	
	uint16_t pen; /**< Private Enterprise Number assigned by the IANA. Default= @ref TNET_IANA_PEN.*/
	char* vendor_class_data;

	uint64_t timeout;

	tnet_port_t port_client; /**< Local port to bind to for incloming DHCPv6 messages. Default: 546 */
	tnet_port_t server_port; /**< Destination port for outgoing DHCPv6 messages. Default: 547 */
	tnet_interfaces_L_t *interfaces;
	
	TSK_DECLARE_SAFEOBJ;
}
tnet_dhcp6_ctx_t;

TINYNET_API tnet_dhcp6_reply_t* tnet_dhcp6_requestinfo(const tnet_dhcp6_ctx_t* ctx, const tnet_dhcp6_option_orequest_t *orequest);

TINYNET_API tnet_dhcp6_ctx_t* tnet_dhcp6_ctx_create();

TINYNET_GEXTERN const tsk_object_def_t *tnet_dhcp6_ctx_def_t;

TNET_END_DECLS

#endif /* TNET_DHCP6_H */
