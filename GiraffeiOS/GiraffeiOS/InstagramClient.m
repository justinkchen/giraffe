//
//  InstagramClient.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 5/23/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "InstagramClient.h"

NSString *const kInstagramBaseURL = @"https://api.instagram.com/v1/";

NSString *const kInstagramMediaSearch = @"media/search";
//NSString *const kInstagramMediaSearch = @"users/self/feed";

NSString *const kInstagramParamNameLatitude = @"lat";
NSString *const kInstagramParamNameLongitude = @"lng";
NSString *const kInstagramParamNameDistance = @"distance";
NSString *const kInstagramParamNameAccessToken = @"access_token";

const CGFloat kInstagramDistance = 500.0;
NSString *const kInstagramAccessToken = @"347606217.cbd06da.1ec595a593b34abe88d359d5dc1b50c8";

@implementation InstagramClient

+ (InstagramClient *)sharedClient
{
    // Create Singleton
    static InstagramClient *sharedClient = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedClient = [[InstagramClient alloc] initWithBaseURL:[NSURL URLWithString:kInstagramBaseURL]];
        //        sharedClient.parameterEncoding = AFJSONParameterEncoding;
        [sharedClient setDefaultHeader:@"Accept" value:@"application/json"];
        [sharedClient registerHTTPOperationClass:[AFJSONRequestOperation class]];
        
    });
    
    return sharedClient;
}

- (void)beginInstagramNearbyGetWithLatitude:(CGFloat)latitude longitude:(CGFloat)longitude success:(InstagramClientSuccessBlock)success failure:(InstagramClientFailureBlock)failure
{
    NSDictionary *parameters = @{kInstagramParamNameLatitude: @(latitude),
                                 kInstagramParamNameLongitude: @(longitude),
                                 kInstagramParamNameDistance: @(kInstagramDistance),
                                 kInstagramParamNameAccessToken: kInstagramAccessToken};
    NSLog(@"instagram params %@", parameters);
    [self getPath:kInstagramMediaSearch parameters:parameters success:success failure:failure];
}

@end
