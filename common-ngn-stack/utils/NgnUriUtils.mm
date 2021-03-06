
/* Vincent, GZ, 2012-03-07 */

#import "NgnUriUtils.h"
#import "NgnEngine.h"
#import "NgnStringUtils.h"
#import "NgnConfigurationEntry.h"

#import "SipUri.h"

#define kMaxPhoneNumber 1000000000000L
#define kDefaultRealm	@"cloudcall.hk"
#define kInvalidSipUri	@"sip:invalid@cloudcall.hk"


@interface NgnUriUtils (Private)
+(NSString*) trimInvalidStrings: (NSString*)uri;
@end

@implementation NgnUriUtils (Private)

#define kkInvalidStringsSize 4
static NSString* kInvalidStrings[kkInvalidStringsSize][2] = 
{
	{@"(", @""},
	{@")", @""},
	{@" ", @""},
	{@"#", @"%23"}
};

+(NSString*) trimInvalidStrings: (NSString*)uri{
	for(int i = 0; i<kkInvalidStringsSize; i++){
		uri = [uri stringByReplacingOccurrencesOfString: kInvalidStrings[i][0] withString:kInvalidStrings[i][1]];
	}
	return uri;
}

@end


@implementation NgnUriUtils

+(NSString*) getDisplayName:(NSString*)uri{
	NSString* displayname = nil;
	if(![NgnStringUtils isNullOrEmpty: uri]){
		NgnContact* contact =  [[NgnEngine sharedInstance].contactService getContactByUri: uri];
		if(contact != nil  && (displayname = contact.displayName) != nil){
			return displayname;
		}
		
		SipUri* _sipUri = new SipUri([NgnStringUtils toCString: uri]);
		if(_sipUri && _sipUri->isValid()){
			displayname = [NgnStringUtils toNSString: _sipUri->getUserName()];
			contact = [[NgnEngine sharedInstance].contactService getContactByPhoneNumber: displayname];
			if(contact != nil && ![NgnStringUtils isNullOrEmpty: contact.displayName]){
				displayname = contact.displayName;
			}
		}
		if(_sipUri){
			delete _sipUri, _sipUri = tsk_null;
		}
	}
	return displayname == nil ? uri : displayname;
}

+(NSString*) getUserName: (NSString*)validUri{
	SipUri* _sipUri = new SipUri([NgnStringUtils toCString: validUri]);
	NSString* userName = validUri;
	if(_sipUri && _sipUri->isValid()){
		userName = [NgnStringUtils toNSString: _sipUri->getUserName()];
	}
	if(_sipUri){
		delete _sipUri, _sipUri = tsk_null;
	}
	return userName;
}

+(BOOL) isValidSipUri: (NSString*)uri{
	return SipUri::isValid([NgnStringUtils toCString: uri]);
}

// Very very basic
+(NSString*)makeValidSipUri: (NSString*)uri{
	if([NgnStringUtils isNullOrEmpty: uri]){
		return kInvalidSipUri;
	}
	
	if([uri hasPrefix: @"sip:"] || [uri hasPrefix: @"sips:"]){
		return [NgnUriUtils trimInvalidStrings: uri];
	}
	else if([uri hasPrefix: @"tel:"]){
		return uri;
	}
	else{
		if([NgnStringUtils contains: uri subString: @"@"]){
			return [NSString stringWithFormat: @"sip:%@", uri];
		}
		else{
			NSString* realm = [[NgnEngine sharedInstance].configurationService getStringWithKey: NETWORK_REALM];
			if([NgnStringUtils isNullOrEmpty: realm]){
				realm = kDefaultRealm;
			}
			if([NgnStringUtils contains:realm subString:@":"]){
				realm = [realm substringFromIndex:
						 [realm rangeOfString:@":"].location + 1];
			}
			// FIXME: Should be done
			uri = [NgnUriUtils trimInvalidStrings: uri];
			return [NSString stringWithFormat: @"sip:%@@%@", uri, realm];
		}
	}
}

+(NSString*) getValidPhoneNumber: (NSString*)uri{
	return nil;
}

@end
