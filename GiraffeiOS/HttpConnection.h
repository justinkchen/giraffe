//
//  HttpConnection.h
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/29/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface HttpConnection : NSObject

+ (void)graffitiNearbyGetConnection:(id <NSURLConnectionDelegate>)delegate
                         atLatitude:(float)latitude
                        atLongitude:(float)longtitude;
+ (void)graffitiNewPostConnection:(id <NSURLConnectionDelegate>)delegate
                       withParams:(NSData *)graffitiParameters;
+ (void)userLoginPostConnection:(id <NSURLConnectionDelegate>)delegate
                     withParams:(NSData *)userParameters;
+ (void)userSignupPostConnection:(id <NSURLConnectionDelegate>)delegate
                      withParams:(NSData *)userParameters;
+ (void)userUpdatePutConnection:(id <NSURLConnectionDelegate>)delegate
                     withParams:(NSData *)userParameters;
+ (void)userLogoutPostConnection:(id <NSURLConnectionDelegate>)delegate;


@end
