//
//  RNHTTPClient.m
//  RNNewsApp
//
//  Created by wangwei on 2017/10/19.
//  Copyright © 2017年 wangwei. All rights reserved.
//

#import "RNHTTPClient.h"
#import "RNHTTPRequest.h"

@interface RNHTTPClient()
@property (nonatomic) NSURLSession *session;

@end

@implementation RNHTTPClient

- (void)logDebugInfoWithRequest:(RNHTTPRequest *)request taskId:(NSInteger)taskId{
#ifdef DEBUG
//    if (!self.printLogIfDebug) return;
    NSMutableString *logString = [NSMutableString stringWithString:@"\n\n**************************************************************\n*                       Request Start                        *\n**************************************************************\n\n"];

    [logString appendFormat:@"BaseURL:%@\n", request.baseURL];
    [logString appendFormat:@"API Name:\t\t%@\n", request.path];
    [logString appendFormat:@"Method:\t\t%@\n", request.httpMethod];
    [logString appendFormat:@"Task Id:\t\t%ld\n", (long)taskId];
    [logString appendFormat:@"HTTP Hearder:%@\n", request.httpHeaders];
    [logString appendFormat:@"Params:\n%@", request.params];

    [logString appendFormat:@"\n\n**************************************************************\n*                         Request End                        *\n**************************************************************\n\n\n\n"];
    NSLog(@"%@", logString);
#endif
}

- (void)logDebugInfoWithResponse:(NSHTTPURLResponse *)response
                    responseData:(NSData *)responseData
                           error:(NSError *)error
                         request:(NSURLRequest *)request
                          taskId:(NSInteger)taskId {
#ifdef DEBUG
//    if (!self.printLogIfDebug) return;

    BOOL shouldLogError = error ? YES : NO;
    NSMutableString *logString = [NSMutableString stringWithString:@"\n\n==============================================================\n=                        API Response                        =\n==============================================================\n\n"];

    [logString appendFormat:@"Status:\t%ld\t(%@)\n\n", (long)response.statusCode, [NSHTTPURLResponse localizedStringForStatusCode:response.statusCode]];

    [logString appendFormat:@"URL:\t%@\t\t\n TaskID:%ld\n", request.URL, (long)taskId];

    NSString *responseString = [[NSString alloc] initWithData:responseData encoding:NSUTF8StringEncoding];
    [logString appendFormat:@"Content:\n\t%@\n\n", responseString];
    if (shouldLogError) {
        [logString appendFormat:@"Error Domain:\t\t\t\t\t\t\t%@\n", error.domain];
        [logString appendFormat:@"Error Domain Code:\t\t\t\t\t\t%ld\n", (long)error.code];
        [logString appendFormat:@"Error Localized Description:\t\t\t%@\n", error.localizedDescription];
        [logString appendFormat:@"Error Localized Failure Reason:\t\t\t%@\n", error.localizedFailureReason];
        [logString appendFormat:@"Error Localized Recovery Suggestion:\t%@\n\n", error.localizedRecoverySuggestion];
    }

    [logString appendString:@"\n---------------  Related Request Content  --------------\n"];
    [logString appendFormat:@"\n\n==============================================================\n=                        Response End                        =\n==============================================================\n\n\n\n"];

    NSLog(@"%@", logString);
#endif
}


-(NSInteger)sendRequest:(RNHTTPRequest *)request withHanlder:(RNHTTPResponseHanlder)responseHandler{
    NSURLRequest *req = [self urlRequestFromRequest:request];
    NSURLSessionTask *task = nil;
    __block NSInteger taskId;
    __weak typeof(self) weakSelf = self;
    task  = [self.session dataTaskWithRequest:req completionHandler:^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error) {
        [weakSelf logDebugInfoWithResponse:(NSHTTPURLResponse *)response responseData:data error:error request:req taskId:taskId];
        
        if(responseHandler){
            dispatch_async(dispatch_get_main_queue(), ^{
                responseHandler([task taskIdentifier], data, error);
            });
        }
    }];
    
    [task resume];
    taskId = [task taskIdentifier];
    [self logDebugInfoWithRequest:request taskId:taskId];

    return taskId;
}


-(NSURLRequest *)urlRequestFromRequest:(RNHTTPRequest *)request{
    NSMutableString *urlString = [NSMutableString stringWithFormat:@"%@%@", request.baseURL, request.path];
    BOOL first = YES;
    for(NSString *key in request.params){
        NSCharacterSet *urlSet = [NSCharacterSet URLQueryAllowedCharacterSet];
        NSString *encodedKey = [key stringByAddingPercentEncodingWithAllowedCharacters:urlSet];
        NSString *encodedVal = [request.params[key] stringByAddingPercentEncodingWithAllowedCharacters:urlSet];
        
        if(first){
            [urlString appendString:@"?"];
            [urlString appendFormat:@"%@=%@", encodedKey, encodedVal];
            first = NO;
            continue;
        }

        [urlString appendFormat:@"&%@=%@", encodedKey, encodedVal];
    }

    NSURL *url = [NSURL URLWithString:urlString];
    
    NSMutableURLRequest *urlRequest = [[NSMutableURLRequest alloc] initWithURL:url];
    urlRequest.HTTPMethod = request.httpMethod;

    if([request.httpHeaders count] != 0){
        for(NSString *key in request.httpHeaders){
            [urlRequest setValue:request.httpHeaders[key] forHTTPHeaderField:key];
        }
    }
    
    if([[request.httpMethod lowercaseString] isEqualToString:@"post"] &&
       request.httpBody != nil){
        urlRequest.HTTPBody = request.httpBody;
    }
    
    urlRequest.timeoutInterval = request.timeout;
    
    return [urlRequest copy];
}


-(NSURLSession *)session{
    if(_session == nil){
        NSURLSessionConfiguration *defaultConfig = [NSURLSessionConfiguration defaultSessionConfiguration];
        defaultConfig.requestCachePolicy = NSURLRequestUseProtocolCachePolicy;
        defaultConfig.timeoutIntervalForRequest = 10.0;
        defaultConfig.timeoutIntervalForResource = 20.0;
        _session = [NSURLSession sessionWithConfiguration:defaultConfig delegate:nil delegateQueue:nil];
    }
    
    return _session;
}


+(instancetype)defaultClient{
    static dispatch_once_t onceToken;
    static RNHTTPClient *sharedInstance;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[RNHTTPClient alloc] init];
    });
    
    return sharedInstance;
}


-(void)dealloc{
    [_session invalidateAndCancel];
    _session = nil;
}

@end
