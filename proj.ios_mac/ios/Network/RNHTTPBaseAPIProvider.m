//
//  RNHTTPBaseAPIProvider.m
//  RNNewsApp
//
//  Created by wangwei on 2017/10/19.
//  Copyright © 2017年 wangwei. All rights reserved.
//

#import "RNHTTPBaseAPIProvider.h"
#import "RNHTTPRequest.h"
#import "RNHTTPClient.h"

@implementation RNHTTPBaseAPIProvider

-(NSInteger)callApiWithParams:(NSDictionary *)params withHanlder:(RNAPIHandler)hanlder{
    
    NSMutableDictionary *mutableParams = nil;
    if([self useCommonParameters]){
        mutableParams = [NSMutableDictionary dictionaryWithDictionary:
                         [[self class] commonParameters]];
        
        //用户传入的参数覆盖公共参数
        [params enumerateKeysAndObjectsUsingBlock:^(id key, id obj, BOOL *stop) {
            mutableParams[key] = obj;
        }];
    }else{
        mutableParams = [NSMutableDictionary dictionaryWithDictionary:params];
    }
    
    RNHTTPRequest *request = [self HTTPRequst];
    request.params = [mutableParams copy];
    
    //添加公共UA
    NSMutableDictionary *httpHeaders = [[NSMutableDictionary alloc] init];
    request.httpHeaders = httpHeaders;
    
    NSInteger requestId = -1;
    requestId = [[self HTTPClient] sendRequest:request withHanlder:^(NSInteger requestId, NSData *responseData, NSError *error) {
        if(hanlder){
            if(error){
                hanlder(requestId, nil, error);
            }else{
                hanlder(requestId, responseData, nil);
            }
        }
    }];
    
    return requestId;
}


-(RNHTTPClient *)HTTPClient{
    return [RNHTTPClient defaultClient];
}


-(BOOL)useCommonParameters{
    return YES;
}


+(NSDictionary *)commonParameters{
    return @{};
}


-(RNHTTPRequest *)HTTPRequst{
    NSAssert(NO, @"子类必须重写HTTPRequst方法");
    return nil;
}

@end
