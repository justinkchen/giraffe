//
//  FacebookClient.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 5/25/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "FacebookClient.h"

NSString *const kFacebookParamNameType = @"type";
NSString *const kFacebookParamNameCenter = @"center";
NSString *const kFacebookParamNameDistance = @"distance";
NSString *const kFacebookParamNameLimit = @"limit";

NSString *const kFacebookCenterFormat = @"%f,%f";

NSString *const kFacebookType = @"location";
const NSUInteger kFacebookDistance = 500;
const NSUInteger kFacebookLimit = 100;

NSString *const kFacebookParamNameData = @"data";

@implementation FacebookClient

+ (FacebookClient *)sharedClient
{
    // Create Singleton
    static FacebookClient *sharedClient = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedClient = [FacebookClient new];
    });
    
    return sharedClient;
}

- (void)beginFacebookNearbyGetWithLatitude:(CGFloat)latitude
                                 longitude:(CGFloat)longitude
                                   success:(FacebookClientSuccessBlock)success
                                   failure:(FacebookClientFailureBlock)failure
{
    NSLog(@"start fb connection");
    NSDictionary *parameters = @{kFacebookParamNameType:kFacebookType,
                                 kFacebookParamNameCenter:[NSString stringWithFormat:kFacebookCenterFormat, latitude, longitude],
                                 kFacebookParamNameDistance: [NSString stringWithFormat:@"%d", kFacebookDistance],
                                 kFacebookParamNameLimit: [NSString stringWithFormat: @"%d", kFacebookLimit]
                                 };
    NSLog(@"facebook params %@", parameters);
    // Get the most recent status
    [FBRequestConnection startWithGraphPath:@"search" parameters:parameters HTTPMethod:@"GET" completionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
        if (error) {
            return failure(connection, result, error);
        }
        
        // parse results and send batch request
        if ([result isKindOfClass:[NSDictionary class]]) {
            NSArray *facebookLocationDicts= [result objectForKey:kFacebookParamNameData];
            
            FBRequestConnection *batchConnection = [[FBRequestConnection alloc] init];
            
            for (NSDictionary *locationDict in facebookLocationDicts) {
                NSString *postId = [locationDict objectForKey:@"id"];
                
                FBRequest *request = [FBRequest requestForGraphPath:postId];
                [batchConnection addRequest:request completionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
                    if (error) {
                        return failure(connection, result, error);
                    }
                    success(connection, result);
                }];
            }
            
            [batchConnection start];
        }
    }];
}

@end
