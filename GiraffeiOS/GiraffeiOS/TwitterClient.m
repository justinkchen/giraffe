//
//  TwitterClient.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 5/24/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "TwitterClient.h"

NSString *const kTwitterBaseURL = @"https://search.twitter.com/";

NSString *const kTwitterSearch = @"search.json";

NSString *const kTwitterParamNameQuery = @"q";
NSString *const kTwitterParamNameGeocode = @"geocode";
NSString *const kTwitterParamNameRPP = @"rpp";

NSString *const kTwitterQuery = @"%23";
const NSUInteger kTwitterRPP = 100;
NSString *const kTwitterGeocodeFormat = @"%f,%f,%fkm";
const CGFloat kTwitterDistance = 0.5;

@implementation TwitterClient

+ (TwitterClient *)sharedClient
{
    // Create Singleton
    static TwitterClient *sharedClient = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedClient = [[TwitterClient alloc] initWithBaseURL:[NSURL URLWithString:kTwitterBaseURL]];
        //        sharedClient.parameterEncoding = AFJSONParameterEncoding;
        [sharedClient setDefaultHeader:@"Accept" value:@"application/json"];
        [sharedClient registerHTTPOperationClass:[AFJSONRequestOperation class]];
        
    });
    
    return sharedClient;
}

- (void)beginTwitterNearbyGetWithLatitude:(CGFloat)latitude longitude:(CGFloat)longitude success:(TwitterClientSuccessBlock)success failure:(TwitterClientFailureBlock)failure
{
    NSDictionary *parameters = @{kTwitterParamNameQuery: kTwitterQuery,
                                 kTwitterParamNameRPP: @(kTwitterRPP),
                                 kTwitterParamNameGeocode: [NSString stringWithFormat:kTwitterGeocodeFormat, latitude, longitude, kTwitterDistance]};
    NSLog(@"twitter params %@", parameters);
    [self getPath:kTwitterSearch parameters:parameters success:success failure:failure];
}


@end
