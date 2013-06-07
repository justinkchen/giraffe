//
//  InstagramClient.h
//  GiraffeiOS
//
//  Created by Bryan Cheng on 5/23/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "AFHTTPClient.h"
#import "AFJSONRequestOperation.h"

@interface InstagramClient : AFHTTPClient

+ (InstagramClient *)sharedClient;

typedef void (^InstagramClientSuccessBlock)(AFHTTPRequestOperation *operation, id responseObject);
typedef void (^InstagramClientFailureBlock)(AFHTTPRequestOperation *operation, NSError *error);


// Get
- (void)beginInstagramNearbyGetWithLatitude:(CGFloat)latitude
                                  longitude:(CGFloat)longitude
                                    success:(InstagramClientSuccessBlock)success
                                    failure:(InstagramClientFailureBlock)failure;

@end
