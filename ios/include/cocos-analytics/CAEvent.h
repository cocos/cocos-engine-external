#import <Foundation/Foundation.h>

@interface CAEvent : NSObject

+ (void)onEvent:(NSString*)eventName;
+ (void)onEventStart:(NSString*)eventName;
+ (void)onEventEnd:(NSString*)eventName;

@end
