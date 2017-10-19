#import <Foundation/Foundation.h>

@interface CATask : NSObject

@property (readonly) int GuideLine;            // 新手任务
@property (readonly) int MainLine;             // 主线任务
@property (readonly) int BranchLine;           // 分支任务
@property (readonly) int Daily;                // 日常任务
@property (readonly) int Activity;             // 活动任务
@property (readonly) int Other;                // 其他任务，默认值

+ (void)begin:(NSString*)taskID taskType:(int)taskType;
+ (void)complete:(NSString*)taskID;
+ (void)failed:(NSString*)taskID reason:(NSString*)reason;

+ (int)GuideLine;
+ (int)MainLine;
+ (int)BranchLine;
+ (int)Daily;
+ (int)Activity;
+ (int)Other;

@end
