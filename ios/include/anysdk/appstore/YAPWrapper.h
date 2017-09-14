//
//  YAPWrapper.h
//  PluginProtocol
//
//  Created by cocos2dx on 14-9-9.
//  Copyright (c) 2014年 cocos2dx. All rights reserved.
//

#import <Foundation/Foundation.h>
typedef enum
{
    YAPRESULT_SUCCESS = 0,/**< enum value is callback of succeeding in yaping . */
    YAPRESULT_FAIL,/**< enum value is callback of failing to yap . */
    YAPRESULT_CANCEL,/**< enum value is callback of canceling to yap . */
    YAPRESULT_NETWORK_ERROR,/**< enum value is callback of network error . */
    YAPRESULT_PRODUCTIONINFOR_INCOMPLETE,/**< enum value is callback of incompleting info . */
    YAPRESULT_INIT_SUCCESS,/**< enum value is callback of succeeding in initing sdk . */
    YAPRESULT_INIT_FAIL,/**< enum value is callback of failing to init sdk . */
    YAPRESULT_NOW_YAPING,/**< enum value is callback of yaping now . */
    YAPRESULT_YAPEXTENSION = 30000 /**< enum value is  extension code . */
} YAP_RET_CODE;

typedef enum
{
    REQUESTRESULT_SUCCESS = 31000,/**< enum value is callback of succeeding in yaping . */
    REQUESTRESULT_FAIL/**< enum value is callback of failing to yap . */
} REQUEST_RET_CODE;

@interface YAPWrapper : NSObject

/**
 *  get the identifier of order
 *
 *  @param orderInfo yapment info
 *  @param target    callback object
 *  @param action    callback function
 */
+ (void)getYapOrderId:(NSMutableDictionary*)orderInfo target:(id)target action:(SEL)action;

/**
 *  get order info
 *
 *  @param productInfo product info
 *  @param user        identifier of user
 *
 *  @return order info
 */
+ (NSMutableDictionary*) getOrderInfo:(NSMutableDictionary*)productInfo userID:(NSString*)user;
 /**
 *  The callback interface of yap system
 *
 *  @param pPlugin the yap plugin
 *  @param ret     the code of callback
 *  @param msg     the message of callback
 */
+ (void)onYapResult:(id)pPlugin retCode:(int)ret retMsg:(NSString*)msg;

/**
 *  The callback interface of social system
 *
 *  @param pPlugin the social plugin
 *  @param ret     the code of callback
 *  @param msg     the message of callback
 */
+ (void)onYapResult:(id)pPlugin retCode:(int)ret products:(NSMutableDictionary*)products;

/**
 *  process the notify url
 *
 *  @param class1 plugin
 *  @param url    the source url
 *
 *  @return the destination url
 */
+ (NSString*) replaceNotifyURL:(Class)class1 url:(NSString*)url;

/**
 *  process the  EE Domain
 *
 *  @param domain
 *
 *  @return void
 */
+ (void)replaceEEDomain:(NSString*)domain;

@end
