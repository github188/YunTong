
/* 2012-03-07 */

#ifndef TINYMEDIA_MANAGER_H
#define TINYMEDIA_MANAGER_H

#include "tinyrtp_config.h"

#include "tinynet.h"

TRTP_BEGIN_DECLS

/* Forward declarations */
struct trtp_rtp_packet_s;
struct trtp_rtcp_packet_s;

typedef int (*trtp_manager_rtp_cb_f)(const void* callback_data, const struct trtp_rtp_packet_s* packet);
typedef int (*trtp_manager_rtcp_cb_f)(const void* callback_data, const struct trtp_rtcp_packet_s* packet);

/** RTP/RTCP manager */
typedef struct trtp_manager_s
{
	TSK_DECLARE_OBJECT;

	struct{
		uint16_t seq_num;
		uint32_t timestamp;
		uint32_t ssrc;
		uint8_t payload_type;

		char* remote_ip;
		tnet_port_t remote_port;
		struct sockaddr_storage remote_addr;

		char* public_ip;
		tnet_port_t public_port;

		const void* callback_data;
		trtp_manager_rtp_cb_f callback;
	} rtp;

	struct{
		char* remote_ip;
		tnet_port_t remote_port;
		struct sockaddr_storage remote_addr;
		tnet_socket_t* local_socket;

		char* public_ip;
		tnet_port_t public_port;

		const void* callback_data;
		trtp_manager_rtcp_cb_f callback;
	} rtcp;
	
	char* local_ip;
	tsk_bool_t ipv6;
	tsk_bool_t started;
	tsk_bool_t enable_rtcp;
	tsk_bool_t socket_disabled;
	tnet_transport_t* transport;
	struct{
		uint16_t start;
		uint16_t stop;
	} port_range;
}
trtp_manager_t;

TINYRTP_API trtp_manager_t* trtp_manager_create(tsk_bool_t enable_rtcp, const char* local_ip, tsk_bool_t ipv6);
TINYRTP_API int trtp_manager_prepare(trtp_manager_t* self);
TINYRTP_API tsk_bool_t trtp_manager_is_prepared(trtp_manager_t* self);
TINYRTP_API int trtp_manager_set_natt_ctx(trtp_manager_t* self, tnet_nat_context_handle_t* natt_ctx);
TINYRTP_API int trtp_manager_set_rtp_callback(trtp_manager_t* self, trtp_manager_rtp_cb_f callback, const void* callback_data);
TINYRTP_API int trtp_manager_set_payload_type(trtp_manager_t* self, uint8_t payload_type);
TINYRTP_API int trtp_manager_set_rtp_remote(trtp_manager_t* self, const char* remote_ip, tnet_port_t remote_port);
TINYRTP_API int trtp_manager_set_rtp_remote(trtp_manager_t* self, const char* remote_ip, tnet_port_t remote_port);
TINYRTP_API int trtp_manager_set_rtcp_remote(trtp_manager_t* self, const char* remote_ip, tnet_port_t remote_port);
TINYRTP_API int trtp_manager_set_port_range(trtp_manager_t* self, uint16_t start, uint16_t stop);
TINYRTP_API int trtp_manager_start(trtp_manager_t* self);
TINYRTP_API int trtp_manager_send_rtp(trtp_manager_t* self, const void* data, tsk_size_t size, uint32_t duration, tsk_bool_t marker, tsk_bool_t last_packet);
TINYRTP_API int trtp_manager_send_rtp_2(trtp_manager_t* self, const struct trtp_rtp_packet_s* packet);
TINYRTP_API int trtp_manager_stop(trtp_manager_t* self);

TINYRTP_GEXTERN const tsk_object_def_t *trtp_manager_def_t;

TRTP_END_DECLS

#endif /* TINYMEDIA_MANAGER_H */
