//
//  FacebookClient.h
//  GiraffeiOS
//
//  Created by Bryan Cheng on 5/25/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FacebookSDK/FacebookSDK.h>

@interface FacebookClient : NSObject

+ (FacebookClient *)sharedClient;

typedef void (^FacebookClientSuccessBlock)(FBRequestConnection *connection, id result);
typedef void (^FacebookClientFailureBlock)(FBRequestConnection *connection, id result, NSError *error);

- (void)beginFacebookNearbyGetWithLatitude:(CGFloat)latitude
                                 longitude:(CGFloat)longitude
                                   success:(FacebookClientSuccessBlock)success
                                   failure:(FacebookClientFailureBlock)failure;


@end
