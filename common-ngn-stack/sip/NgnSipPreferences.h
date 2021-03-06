
/* Vincent, GZ, 2012-03-07 */

#import <Foundation/Foundation.h>

@interface NgnSipPreferences : NSObject {
	 BOOL presence;
	 BOOL xcap;
	 BOOL presenceRLS;
	 BOOL presencePub;
     BOOL presenceSub;
     BOOL mwi;
     NSString* impi;
     NSString* impu;
     NSString* realm;
     NSString* pcscfHost;
     int pcscfPort;
     NSString* ipVersion;
	 NSString* transport;
     BOOL ipsecSecAgree;
     NSString* localIp;
     BOOL hackAoR;
    NSString* deviceToken;
}

@property(readwrite) BOOL presence;
@property(readwrite) BOOL xcap;
@property(readwrite) BOOL presenceRLS;
@property(readwrite) BOOL presencePub;
@property(readwrite) BOOL presenceSub;
@property(readwrite) BOOL mwi;
@property(readwrite,retain) NSString* impi;
@property(readwrite,retain)NSString* impu;
@property(readwrite,retain)NSString* realm;
@property(readwrite,retain)NSString* pcscfHost;
@property(readwrite) int pcscfPort;
@property(readwrite,retain)NSString* transport;
@property(readwrite,retain)NSString* ipVersion;
@property(readwrite) BOOL ipsecSecAgree;
@property(readwrite,retain)NSString* localIp;
@property(readwrite) BOOL hackAoR;
@property(readwrite,retain)NSString* deviceToken;
@end
