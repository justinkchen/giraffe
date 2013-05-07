//
//  GiraffeClient.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 5/6/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "GiraffeClient.h"

NSString *const kBaseURL = @"http://ec2-54-243-69-6.compute-1.amazonaws.com/";

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

static GiraffeClient *_giraffeClientSingleton;

@implementation GiraffeClient

+ (GiraffeClient *)getGiraffeClient {
    if (_giraffeClientSingleton == nil) {
        _giraffeClientSingleton = [[GiraffeClient alloc] initWithBaseURL:[NSURL URLWithString:kBaseURL]];
    }
    return _giraffeClientSingleton;
}

+ (void)graffitiNearbyGetParameters:(NSDictionary *)parameters
                            success:(void (^) (AFHTTPRequestOperation *operation, id responseObject))success
                            failure:(void (^) (AFHTTPRequestOperation *operation, NSError *error))failure {
    GiraffeClient *client = [GiraffeClient getGiraffeClient];
    [client getPath:kGraffitiNearby parameters:parameters success:success failure:failure];
}

+ (void)graffitiNewPostParameters:(NSDictionary *)parameters
                          success:(void (^) (AFHTTPRequestOperation *operation, id responseObject))success
                          failure:(void (^) (AFHTTPRequestOperation *operation, NSError *error))failure {
    GiraffeClient *client = [GiraffeClient getGiraffeClient];
    [client postPath:kGraffitiNew parameters:parameters success:success failure:failure];
}

+ (void)userLoginPostParameters:(NSDictionary *)parameters
                        success:(void (^) (AFHTTPRequestOperation *operation, id responseObject))success
                        failure:(void (^) (AFHTTPRequestOperation *operation, NSError *error))failure {
    GiraffeClient *client = [GiraffeClient getGiraffeClient];
    [client postPath:kUserLogin parameters:parameters success:success failure:failure];
}

+ (void)userSignupPostParameters:(NSDictionary *)parameters
                         success:(void (^) (AFHTTPRequestOperation *operation, id responseObject))success
                         failure:(void (^) (AFHTTPRequestOperation *operation, NSError *error))failure {
    GiraffeClient *client = [GiraffeClient getGiraffeClient];
    [client postPath:kUserSignup parameters:parameters success:success failure:failure];
}

+ (void)userUpdatePutParameters:(NSDictionary *)parameters
                        success:(void (^) (AFHTTPRequestOperation *operation, id responseObject))success
                        failure:(void (^) (AFHTTPRequestOperation *operation, NSError *error))failure {
    GiraffeClient *client = [GiraffeClient getGiraffeClient];
    [client putPath:kUserUpdate parameters:parameters success:success failure:failure];
}

+ (void)userLogoutPostParameters:(NSDictionary *)parameters
                         success:(void (^) (AFHTTPRequestOperation *operation, id responseObject))success
                         failure:(void (^) (AFHTTPRequestOperation *operation, NSError *error))failure {
    GiraffeClient *client = [GiraffeClient getGiraffeClient];
    [client postPath:kUserLogout parameters:NULL success:success failure:failure];
}

@end
