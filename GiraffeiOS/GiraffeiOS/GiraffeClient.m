//
//  GiraffeClient.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 5/6/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "GiraffeClient.h"
#import "Graffiti.h"
#import "User.h"

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

NSString *const kParamNameLatitude = @"latitude";
NSString *const kParamNameLongitude = @"longitude";

@implementation GiraffeClient

+ (id)sharedClient
{
    // Create Singleton
    static GiraffeClient *sharedClient = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedClient = [[GiraffeClient alloc] initWithBaseURL:[NSURL URLWithString:kBaseURL]];
//        sharedClient.parameterEncoding = AFJSONParameterEncoding;
        [sharedClient setDefaultHeader:@"Accept" value:@"application/json"];
        [sharedClient registerHTTPOperationClass:[AFJSONRequestOperation class]];
        
    });
    
    return sharedClient;
}

- (void)beginGraffitiNearbyGetWithLatitude:(CGFloat)latitude
                                 longitude:(CGFloat)longitude
                                   success:(GiraffeClientSuccessBlock)success
                                   failure:(GiraffeClientFailureBlock)failure
{
    NSDictionary *parameters = @{kParamNameLatitude : @(latitude), kParamNameLongitude : @(longitude)};
    [self getPath:kGraffitiNearby parameters:parameters success:success failure:failure];
}

- (void)beginGraffitiNewPostWithGraffiti:(Graffiti *)graffiti
                                 success:(GiraffeClientSuccessBlock)success
                                 failure:(GiraffeClientFailureBlock)failure
{
    [self postPath:kGraffitiNew parameters:[graffiti parameterDictionary] success:success failure:failure];
}

- (void)beginUserLoginPostWithUserParameters:(NSDictionary *)parameters
                                     success:(GiraffeClientSuccessBlock)success
                                     failure:(GiraffeClientFailureBlock)failure
{
   [self postPath:kUserLogin parameters:parameters success:success failure:failure];
}

- (void)beginUserSignupPostWithUser:(User *)user
                            success:(GiraffeClientSuccessBlock)success
                            failure:(GiraffeClientFailureBlock)failure
{
    [self postPath:kUserSignup parameters:[user parameterDictionary] success:success failure:failure];
}

- (void)beginUserUpdatePutWithUser:(User *)user
                           success:(GiraffeClientSuccessBlock)success
                           failure:(GiraffeClientFailureBlock)failure
{
    [self putPath:kUserUpdate parameters:[user parameterDictionary] success:success failure:failure];
}

- (void)beginUserLogoutPostWithUser:(User *)user
                            success:(GiraffeClientSuccessBlock)success
                            failure:(GiraffeClientFailureBlock)failure
{
    [self postPath:kUserLogout parameters:[user parameterDictionary] success:success failure:failure];
}

@end
