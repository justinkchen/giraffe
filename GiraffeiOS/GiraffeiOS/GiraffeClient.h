//
//  GiraffeClient.h
//  GiraffeiOS
//
//  Created by Bryan Cheng on 5/6/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AFHTTPClient.h"
#import "AFJSONRequestOperation.h"

@class Graffiti;
@class User;

extern NSString *const kBaseURL;

@interface GiraffeClient : AFHTTPClient

+ (GiraffeClient *)sharedClient;

+ (void)saveCookies;
+ (void)loadCookies;

typedef void (^GiraffeClientSuccessBlock)(AFHTTPRequestOperation *operation, id responseObject);
typedef void (^GiraffeClientFailureBlock)(AFHTTPRequestOperation *operation, NSError *error);

// Session
- (void)beginSessionConnectGetWithSuccess:(GiraffeClientSuccessBlock)success
                                  failure:(GiraffeClientFailureBlock)failure;

// Graffiti
- (void)beginGraffitiNearbyGetWithLatitude:(CGFloat)latitude
                                 longitude:(CGFloat)longitude
                                   success:(GiraffeClientSuccessBlock)success
                                   failure:(GiraffeClientFailureBlock)failure;

- (void)beginGraffitiNewPostWithGraffiti:(Graffiti *)graffiti
                                   image:(UIImage *)image
                                 success:(GiraffeClientSuccessBlock)success
                                 failure:(GiraffeClientFailureBlock)failure;

- (void)beginGraffitiLikePostWithGraffiti:(Graffiti *)graffiti
                                  success:(GiraffeClientSuccessBlock)success
                                  failure:(GiraffeClientFailureBlock)failure;

// User
- (void)beginUserLoginPostWithUsernameOrEmail:(NSString *)usernameOrEmail
                                    password:(NSString *)password
                                     success:(GiraffeClientSuccessBlock)success
                                     failure:(GiraffeClientFailureBlock)failure;
- (void)beginUserSignupPostWithUser:(User *)user
                           password:(NSString *)password
                            success:(GiraffeClientSuccessBlock)success
                            failure:(GiraffeClientFailureBlock)failure;
- (void)beginUserUpdatePutWithUser:(User *)user
                           success:(GiraffeClientSuccessBlock)success
                           failure:(GiraffeClientFailureBlock)failure;
- (void)beginUserPasswordUpdatePutWithPassword:(NSString *)password
                                   oldPassword:(NSString *)oldPassword
                                       success:(GiraffeClientSuccessBlock)success
                                       failure:(GiraffeClientFailureBlock)failure;
- (void)beginUserAvatarUpdatePutWithImage:(UIImage *)avatarImage
                                  success:(GiraffeClientSuccessBlock)success
                                  failure:(GiraffeClientFailureBlock)failure;
- (void)beginUserGraffitiGetWithId:(int)identifier
                           success:(GiraffeClientSuccessBlock)success
                           failure:(GiraffeClientFailureBlock)failure;


- (void)beginUserStatsGetWithId:(int)identifier
                        success:(GiraffeClientSuccessBlock)success
                        failure:(GiraffeClientFailureBlock)failure;

- (void)beginUserLogoutPostWithUser:(User *)user
                            success:(GiraffeClientSuccessBlock)success
                            failure:(GiraffeClientFailureBlock)failure;

@end
