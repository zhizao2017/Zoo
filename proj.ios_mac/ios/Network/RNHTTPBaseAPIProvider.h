//
//  RNHTTPBaseAPIProvider.h
//  RNNewsApp
//
//  Created by wangwei on 2017/10/19.
//  Copyright © 2017年 wangwei. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef void(^RNAPIHandler)(NSInteger taskId, id responseData, NSError *error);

@class RNHTTPClient;
@class RNHTTPRequest;

@interface RNHTTPBaseAPIProvider : NSObject

-(NSInteger)callApiWithParams:(NSDictionary *)params withHanlder:(RNAPIHandler)hanlder;


//不要直接调用以下函数，这些函数是给子类重写用的
#pragma mark - protected

//请求的主体，子类必须重写
-(RNHTTPRequest *)HTTPRequst;

//默认使用defaultClient， itoutiao.sogou.com域的API不使用默认的
-(RNHTTPClient *)HTTPClient;

//是否使用默认参数，默认值是YES
-(BOOL)useCommonParameters;

//默认为空，如果子类想要使用
+(NSDictionary *)commonParameters;

@end
