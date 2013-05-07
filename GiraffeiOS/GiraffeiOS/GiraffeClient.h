//
//  GiraffeClient.h
//  GiraffeiOS
//
//  Created by Bryan Cheng on 5/6/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AFHTTPClient.h"

@interface GiraffeClient : AFHTTPClient

+ (GiraffeClient *)getGiraffeClient;

+ (void)graffitiNearbyGetParameters:(NSDictionary *)parameters
                            success:(void (^) (AFHTTPRequestOperation *operation, id responseObject))success
                            failure:(void (^) (AFHTTPRequestOperation *operation, NSError *error))failure;
+ (void)graffitiNewPostParameters:(NSDictionary *)parameters
                          success:(void (^) (AFHTTPRequestOperation *operation, id responseObject))success
                          failure:(void (^) (AFHTTPRequestOperation *operation, NSError *error))failure;
+ (void)userLoginPostParameters:(NSDictionary *)parameters
                        success:(void (^) (AFHTTPRequestOperation *operation, id responseObject))success
                        failure:(void (^) (AFHTTPRequestOperation *operation, NSError *error))failure;
+ (void)userSignupPostParameters:(NSDictionary *)parameters
                         success:(void (^) (AFHTTPRequestOperation *operation, id responseObject))success
                         failure:(void (^) (AFHTTPRequestOperation *operation, NSError *error))failure;
+ (void)userUpdatePutParameters:(NSDictionary *)parameters
                        success:(void (^) (AFHTTPRequestOperation *operation, id responseObject))success
                        failure:(void (^) (AFHTTPRequestOperation *operation, NSError *error))failure;
+ (void)userLogoutPostParameters:(NSDictionary *)parameters
                         success:(void (^) (AFHTTPRequestOperation *operation, id responseObject))success
                         failure:(void (^) (AFHTTPRequestOperation *operation, NSError *error))failure;



@end
