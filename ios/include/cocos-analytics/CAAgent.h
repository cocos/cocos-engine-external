#import <Foundation/Foundation.h>

@interface CAAgent : NSObject

+ (void)init:(NSString*)channelID appID:(NSString*)appID appSecret:(NSString*)appSecret;

+ (void)onResume;
+ (void)onPause;
+ (void)onDestroy;
+ (void)enableDebug:(BOOL)enable;

+ (BOOL)isInited;

@end
