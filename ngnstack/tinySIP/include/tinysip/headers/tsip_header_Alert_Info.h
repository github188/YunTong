
/* 2012-03-07 */

#ifndef _TSIP_HEADER_ALERT_INFO_H_
#define _TSIP_HEADER_ALERT_INFO_H_

#include "tinysip_config.h"
#include "tinysip/headers/tsip_header.h"

TSIP_BEGIN_DECLS

////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief	SIP header 'Alert-Info' as per RFC 3261 subclause .
///
/// @par ABNF
/// 	
////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct tsip_header_Alert_Info_s
{	
	TSIP_DECLARE_HEADER;
}
tsip_header_Alert_Info_t;

TSIP_END_DECLS

#endif /* _TSIP_HEADER_ALERT_INFO_H_ */

