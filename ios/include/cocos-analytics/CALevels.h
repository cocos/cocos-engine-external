#import <Foundation/Foundation.h>

@interface CALevels : NSObject

+ (void)begin:(NSString*)level;
+ (void)complete:(NSString*)level;
+ (void)failed:(NSString*)level reason:(NSString*)reason;

@end
