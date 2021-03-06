
/* Vincent, GZ, 2012-03-07 */

#import <Foundation/Foundation.h>

#import "sip/NgnSipStack.h"

#import "SipSession.h"

typedef enum ConnectionState_e{
	CONN_STATE_NONE,
	CONN_STATE_CONNECTING,
	CONN_STATE_CONNECTED,
	CONN_STATE_TERMINATING,
	CONN_STATE_TERMINATED,
}
ConnectionState_t;

@interface NgnSipSession : NSObject {
	NgnSipStack* mSipStack;
    BOOL mOutgoing;
    NSString* mFromUri;
    NSString* mToUri;
    NSString* mCompId;
    NSString* mRemotePartyUri;
    NSString* mRemotePartyDisplayName;
    long mId;
    ConnectionState_t mConnectionState;
}

@property(readonly, getter=getId) long id;
@property(readonly, getter=getConnectionState) ConnectionState_t connectionState;
@property(readwrite, assign, getter=getRemotePartyUri, setter=setRemotePartyUri:) NSString* remotePartyUri;
@property(readonly, getter=getFromUri) NSString* fromUri;
@property(readonly, getter=getToUri) NSString* toUri;
@property(readonly, getter=isConnected) BOOL connected;
@property(readonly, getter=getSession) SipSession* session;

-(NgnSipSession*)initWithSipStack:(NgnSipStack*)sipStack;
-(void)initialize;
-(long)getId;
-(NSNumber*)getIdAsNumber;
-(BOOL)isOutgoing;
-(NgnSipStack*)getSipStack;
-(BOOL)addHeaderWithName:(NSString*)name andValue:(NSString*)value;
-(BOOL)removeHeaderWithName:(NSString*)name;
-(BOOL)addCapsWithName:(NSString*)name;
-(BOOL)addCapsWithName:(NSString*)name andValue:(NSString*)value;
-(BOOL)removeCapsWithName:(NSString*)name;
-(BOOL)isConnected;
-(ConnectionState_t)getConnectionState;
-(void)setConnectionState:(ConnectionState_t)state;
-(NSString*)getFromUri;
-(BOOL)setFromUri:(NSString*)uri;
-(NSString*)getToUri;
-(BOOL)setToUri:(NSString*)uri;
-(NSString*)getRemotePartyUri;
-(void)setRemotePartyUri:(NSString*)uri;
-(void)setSigCompId:(NSString*)compId;
-(BOOL)setExpires:(unsigned)expires;
-(SipSession*)getSession;

@end
