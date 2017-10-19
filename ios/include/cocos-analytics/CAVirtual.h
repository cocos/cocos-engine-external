#import <Foundation/Foundation.h>

@interface CAVirtual : NSObject

+ (void)setVirtualNum:(NSString*)type count:(long)count;
+ (void)get:(NSString*)type count:(long)count reason:(NSString*)reason;
+ (void)consume:(NSString*)type count:(long)count reason:(NSString*)reason;

@end
