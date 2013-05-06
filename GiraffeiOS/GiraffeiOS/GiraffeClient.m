//
//  GiraffeClient.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 5/6/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "GiraffeClient.h"

NSString *const kBaseURL = @"http://ec2-54-243-69-6.compute-1.amazonaws.com/";

/*
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
*/
static GiraffeClient *_giraffeClientSingleton;

@implementation GiraffeClient

+ (GiraffeClient *)getGiraffeClient {
    if (_giraffeClientSingleton == nil) {
        _giraffeClientSingleton = [[GiraffeClient alloc] initWithBaseURL:[NSURL URLWithString:kBaseURL]];
    }
    return _giraffeClientSingleton;
}

@end
