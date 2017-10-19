#import <Foundation/Foundation.h>

@interface CAPeiment : NSObject

+ (void)peiBegin:(int)amount orderID:(NSString*)orderID peiType:(NSString*)peiType pppID:(NSString*)pppID currencyType:(NSString*)currencyType;
+ (void)peiSuccess:(int)amount orderID:(NSString*)orderID peiType:(NSString*)peiType pppID:(NSString*)pppID currencyType:(NSString*)currencyType;
+ (void)peiFailed:(int)amount orderID:(NSString*)orderID peiType:(NSString*)peiType pppID:(NSString*)pppID currencyType:(NSString*)currencyType;
+ (void)peiCanceled:(int)amount orderID:(NSString*)orderID peiType:(NSString*)peiType pppID:(NSString*)pppID currencyType:(NSString*)currencyType;

@end
