#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, Gender) {
    Gender_Unknown,
    Gender_Male,
    Gender_Female
};

@interface CAAccount : NSObject

+ (void)loginStart;
+ (void)loginSuccess:(NSString*)uid;
+ (void)loginFailed;
+ (void)logout;
+ (void)setAccountType:(NSString*)accountType;
+ (void)setAge:(int)age;
+ (void)setGender:(int)gender;
+ (void)createRole:(NSString*)roleID userName:(NSString*)userName race:(NSString*)race
         roleClass:(NSString*)roleClass gameServer:(NSString*)gameServer;
+ (void)setLevel:(int)level;

@end
