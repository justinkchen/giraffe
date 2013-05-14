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

@interface GiraffeClient : AFHTTPClient

+ (GiraffeClient *)sharedClient;

+ (void)saveCookies;
+ (void)loadCookies;

typedef void (^GiraffeClientSuccessBlock)(AFHTTPRequestOperation *operation, id responseObject);
typedef void (^GiraffeClientFailureBlock) (AFHTTPRequestOperation *operation, NSError *error);

- (void)beginGraffitiNearbyGetWithLatitude:(CGFloat)latitude
                                 longitude:(CGFloat)longitude
                                   success:(GiraffeClientSuccessBlock)success
                                   failure:(GiraffeClientFailureBlock)failure;
- (void)beginGraffitiNewPostWithGraffiti:(Graffiti *)graffiti
                                 success:(GiraffeClientSuccessBlock)success
                                 failure:(GiraffeClientFailureBlock)failure;
- (void)beginUserLoginPostWithUser:(User *)user
                          password:(NSString *)password
                           success:(GiraffeClientSuccessBlock)success
                           failure:(GiraffeClientFailureBlock)failure;
- (void)beginUserSignupPostWithUser:(User *)user
                           password:(NSString *)password
                            success:(GiraffeClientSuccessBlock)success
                            failure:(GiraffeClientFailureBlock)failure;
- (void)beginUserUpdatePutWithUser:(User *)user
                          password:(NSString *)password
                       avatarImage:(UIImage *)avatar
                           success:(GiraffeClientSuccessBlock)success
                           failure:(GiraffeClientFailureBlock)failure;
- (void)beginUserLogoutPostWithUser:(User *)user
                            success:(GiraffeClientSuccessBlock)success
                            failure:(GiraffeClientFailureBlock)failure;

@end
