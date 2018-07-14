//
//  SwitchProvider.m
//  HeloCC3-mobile
//
//  Created by 王为 on 2018/7/14.
//

#import "SwitchProvider.h"
#import "RNHTTPRequest.h"

@implementation SwitchProvider


//请求的主体，子类必须重写
-(RNHTTPRequest *)HTTPRequst{
    
    RNHTTPRequest *request = [[RNHTTPRequest alloc] init];
    request.baseURL = @"http://172.104.41.113:8080";
    request.path = @"/update_config";
    request.httpMethod = @"GET";
    request.timeout = 10;
    
    return request;
}


+(NSDictionary *)commonParameters{
    return [[NSMutableDictionary alloc] init];
}

@end
