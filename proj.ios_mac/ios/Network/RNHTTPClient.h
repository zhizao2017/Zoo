//
//  RNHTTPClient.h
//  RNNewsApp
//
//  Created by wangwei on 2017/10/19.
//  Copyright © 2017年 wangwei. All rights reserved.
//

#import <Foundation/Foundation.h>

@class RNHTTPRequest;

typedef void(^RNHTTPResponseHanlder)(NSInteger requestId, NSData *responseData, NSError* error);

@interface RNHTTPClient : NSObject

//注意itoutiao.sogou.com开头的API暂时不要用default的Client，应该每次创建一个新的Client
//原因见：https://forums.developer.apple.com/message/268503#268503
+(instancetype)defaultClient;

-(NSInteger)sendRequest:(RNHTTPRequest *)request withHanlder:(RNHTTPResponseHanlder)responseHandler;

@end
