//
//  HttpConnection.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/29/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "HttpConnection.h"

NSString *const kHostURL = @"http://ec2-54-243-69-6.compute-1.amazonaws.com/";

// API methods
NSString *const kGraffitiNearby = @"graffiti/nearby";
NSString *const kGraffitiNew = @"graffiti/new";
NSString *const kGraffitiLike = @"graffiti/like";
NSString *const kGraffitiFlag = @"graffiti/flag";

NSString *const kUserLogin = @"users/login";
NSString *const kUserSignup = @"users/signup";
NSString *const kUserUpdate = @"users/update";
NSString *const kUserPosts = @"users/graffiti";
NSString *const kUserStats = @"users/stats";
NSString *const kUserLogout = @"users/logout";

@interface HttpConnection() {
    
}

@end

@implementation HttpConnection

+ (void)createConnection:(id <NSURLConnectionDelegate>)delegate
               withRoute:(NSString *)route
              withMethod:(NSString *)method
                withData:(NSData *)data {
    // create request
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc] init];
    [request setCachePolicy:NSURLRequestReloadIgnoringLocalCacheData];
    [request setHTTPShouldHandleCookies:NO]; // probably should be yes
    [request setTimeoutInterval:30];
    [request setHTTPMethod:method];
    
    // set Content-Type in HTTP header
    NSString *contentType = [NSString stringWithFormat:@"multipart/form-data;"];
    [request setValue:contentType forHTTPHeaderField: @"Content-Type"];
    
    // setting the body of the post to the reqeust
    [request setHTTPBody:data];
    
    // set the content-length
    NSString *postLength = [NSString stringWithFormat:@"%d", [data length]];
    [request setValue:postLength forHTTPHeaderField:@"Content-Length"];
    
    // set URL
    [request setURL:[NSString stringWithFormat:@"%@%@", kHostURL, route]];
    
    NSURLConnection *connection = [[NSURLConnection alloc] initWithRequest:request delegate:delegate];
    [connection start];
    
}

+ (void)graffitiNearbyGetConnection:(id <NSURLConnectionDelegate>)delegate
                         atLatitude:(float)latitude
                        atLongitude:(float)longtitude {
    
}

+ (void)graffitiNewPostConnection:(id <NSURLConnectionDelegate>)delegate
                       withParams:(NSData *)graffitiParameters {
    [self createConnection:delegate withRoute:kGraffitiNew withMethod:@"POST" withData:graffitiParameters];
}

+ (void)userLoginPostConnection:(id <NSURLConnectionDelegate>)delegate
                     withParams:(NSData *)userParameters {
    
}

+ (void)userSignupPostConnection:(id <NSURLConnectionDelegate>)delegate
                      withParams:(NSData *)userParameters {
    
}

+ (void)userUpdatePutConnection:(id <NSURLConnectionDelegate>)delegate
                     withParams:(NSData *)userParameters {
    
}

+ (void)userLogoutPostConnection:(id <NSURLConnectionDelegate>)delegate {
    
}

@end
