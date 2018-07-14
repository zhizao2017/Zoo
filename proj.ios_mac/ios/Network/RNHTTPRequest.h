//
// Created by wangwei on 2017/9/6.
// Copyright (c) 2017 RECN. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RNHTTPRequest : NSObject

@property (nonatomic, copy) NSString *baseURL;
@property (nonatomic, copy) NSString *path;
@property (nonatomic, copy) NSString *httpMethod;
@property (nonatomic, copy) NSDictionary *params;
@property (nonatomic, copy) NSDictionary *httpHeaders;
@property (nonatomic, copy) NSData *httpBody;
@property (nonatomic, assign) NSTimeInterval timeout;

@end
