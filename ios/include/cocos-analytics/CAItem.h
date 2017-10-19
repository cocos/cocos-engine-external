#import <Foundation/Foundation.h>

@interface CAItem : NSObject

+ (void)buy:(NSString*)itemID type:(NSString*)itemType count:(int)itemCount virtualCoin:(int)virtualCoin
virtualType:(NSString*)virtualType consumePoint:(NSString*)consumePoint;
+ (void)get:(NSString*)itemID type:(NSString*)itemType count:(int)itemCount reason:(NSString*)reason;
+ (void)consume:(NSString*)itemID type:(NSString*)itemType count:(int)itemCount reason:(NSString*)reason;

@end
