//
//  TwitterClient.h
//  GiraffeiOS
//
//  Created by Bryan Cheng on 5/24/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "AFHTTPClient.h"
#import "AFJSONRequestOperation.h"

@interface TwitterClient : AFHTTPClient

+ (TwitterClient *)sharedClient;

typedef void (^TwitterClientSuccessBlock)(AFHTTPRequestOperation *operation, id responseObject);
typedef void (^TwitterClientFailureBlock)(AFHTTPRequestOperation *operation, NSError *error);


// Get
- (void)beginTwitterNearbyGetWithLatitude:(CGFloat)latitude
                                longitude:(CGFloat)longitude
                                  success:(TwitterClientSuccessBlock)success
                                  failure:(TwitterClientFailureBlock)failure;

@end
