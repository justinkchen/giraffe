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

//NSString *const kBaseURL = @"http://ec2-54-243-69-6.compute-1.amazonaws.com";

NSString *const kBaseURL = @"http://localhost:3000";

// API methods
NSString *const kSessionConnect = @"/session/connect";

NSString *const kGraffitiNearby = @"/graffiti/nearby";
NSString *const kGraffitiNew = @"/graffiti/new";
NSString *const kGraffitiLike = @"/graffiti/like";
NSString *const kGraffitiFlag = @"/graffiti/flag";

NSString *const kUserLogin = @"/users/login";
NSString *const kUserSignup = @"/users/signup";
NSString *const kUserUpdate = @"/users/update";
NSString *const kUserGraffiti = @"/users/graffiti";
NSString *const kUserStats = @"/users/stats";
NSString *const kUserLogout = @"/users/logout";

NSString *const kParamNameLatitude = @"latitude";
NSString *const kParamNameLongitude = @"longitude";

NSString *const kParamNameId = @"id";

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

NSString *const kCookiesDataKey = @"cookiesData";

+ (void)saveCookies
{
    NSLog(@"saving cookies");
    NSArray *cookies = [[NSHTTPCookieStorage sharedHTTPCookieStorage] cookiesForURL:[NSURL URLWithString:kBaseURL]];
    if ([cookies count] > 0) {
        // save cookies to NSUserDefaults
        [[NSUserDefaults standardUserDefaults] setObject:[NSKeyedArchiver  archivedDataWithRootObject:cookies] forKey:kCookiesDataKey];
    }
}

+ (void)loadCookies
{
    NSLog(@"loading cookies");
    NSData *cookiesdata = [[NSUserDefaults standardUserDefaults] objectForKey:kCookiesDataKey];
    if ([cookiesdata length]) {
        NSArray *cookies = [NSKeyedUnarchiver unarchiveObjectWithData:cookiesdata];
        
        NSHTTPCookie *cookie;
        for (cookie in cookies) {
            [[NSHTTPCookieStorage sharedHTTPCookieStorage] setCookie:cookie];
        }
    }
}

- (void)beginSessionConnectGetWithSuccess:(GiraffeClientSuccessBlock)success
                                  failure:(GiraffeClientFailureBlock)failure
{
    [self getPath:kSessionConnect parameters:nil success:success failure:failure];
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
    
}

- (void)beginGraffitiNewPostWithGraffiti:(Graffiti *)graffiti
                                   image:(UIImage *)image
                                 success:(GiraffeClientSuccessBlock)success
                                 failure:(GiraffeClientFailureBlock)failure
{
    if (!image) {
        NSLog(@"no image");
        [self postPath:kGraffitiNew parameters:[graffiti parameterDictionary] success:success failure:failure];
    } else {
        NSLog(@"image");
        // Create a block operation to process image
        NSBlockOperation* imageOp = [NSBlockOperation blockOperationWithBlock: ^{
            NSData *imageData = UIImagePNGRepresentation(image);
            NSURLRequest *request = [self multipartFormRequestWithMethod:@"POST" path:kGraffitiNew parameters:[graffiti parameterDictionary] constructingBodyWithBlock: ^(id <AFMultipartFormData> formData) {
                [formData appendPartWithFileData:imageData name:@"image" fileName:@"image.png" mimeType:@"image/png"];
            }];
            
            AFJSONRequestOperation *operation = [[AFJSONRequestOperation alloc] initWithRequest:request];
            [operation setUploadProgressBlock:^(NSUInteger bytesWritten, long long totalBytesWritten, long long totalBytesExpectedToWrite) {
                NSLog(@"Sent %lld of %lld bytes", totalBytesWritten, totalBytesExpectedToWrite);
            }];
            [operation setCompletionBlockWithSuccess:success failure:failure];
            [operation start];
        }];
        
        NSOperationQueue *queue = [[NSOperationQueue alloc] init];
        [queue addOperation:imageOp];
    }
}

- (void)beginGraffitiLikePostWithGraffiti:(Graffiti *)graffiti
                                  success:(GiraffeClientSuccessBlock) success
                                  failure:(GiraffeClientFailureBlock) failure
{
    [self postPath:kGraffitiLike parameters:[graffiti parameterDictionary] success:success failure:failure];
}

- (void)beginUserLoginPostWithUsernameOrEmail:(NSString *)usernameOrEmail
                                     password:(NSString *)password
                                      success:(GiraffeClientSuccessBlock)success
                                      failure:(GiraffeClientFailureBlock)failure
{
    NSDictionary *parameters = @{kParamNameUserUsernameEmail : usernameOrEmail, kParamNameUserPassword : password};
    [self postPath:kUserLogin parameters:parameters success:success failure:failure];
}

- (void)beginUserSignupPostWithUser:(User *)user
                           password:(NSString *)password
                            success:(GiraffeClientSuccessBlock)success
                            failure:(GiraffeClientFailureBlock)failure
{
    NSMutableDictionary *parameters = [[user parameterDictionary] mutableCopy];
    [parameters setObject:password forKey:kParamNameUserPassword];
    [self postPath:kUserSignup parameters:parameters success:success failure:failure];
}

- (void)beginUserUpdatePutWithUser:(User *)user
                           success:(GiraffeClientSuccessBlock)success
                           failure:(GiraffeClientFailureBlock)failure
{
    [self putPath:kUserUpdate parameters:[user parameterDictionary] success:success failure:failure];
}

- (void)beginUserPasswordUpdatePutWithPassword:(NSString *)password
                                   oldPassword:(NSString *)oldPassword
                                       success:(GiraffeClientSuccessBlock)success
                                       failure:(GiraffeClientFailureBlock)failure
{
    NSDictionary *parameters = @{kParamNameUserPassword : password, kParamNameUserOldPassword : oldPassword};
    [self putPath:kUserUpdate parameters:parameters success:success failure:failure];
}

- (void)beginUserAvatarUpdatePutWithImage:(UIImage *)avatarImage
                                  success:(GiraffeClientSuccessBlock)success
                                  failure:(GiraffeClientFailureBlock)failure
{
    // Create a block operation to process image
    NSBlockOperation* imageOp = [NSBlockOperation blockOperationWithBlock: ^{
        NSData *imageData = UIImagePNGRepresentation(avatarImage);
        NSURLRequest *request = [self multipartFormRequestWithMethod:@"PUT" path:kUserUpdate parameters:nil constructingBodyWithBlock: ^(id <AFMultipartFormData> formData) {
            [formData appendPartWithFileData:imageData name:@"avatar" fileName:@"avatar.png" mimeType:@"image/png"];
        }];
        
        AFJSONRequestOperation *operation = [[AFJSONRequestOperation alloc] initWithRequest:request];
        [operation setUploadProgressBlock:^(NSUInteger bytesWritten, long long totalBytesWritten, long long totalBytesExpectedToWrite) {
            NSLog(@"Sent %lld of %lld bytes", totalBytesWritten, totalBytesExpectedToWrite);
        }];
        [operation setCompletionBlockWithSuccess:success failure:failure];
        [operation start];
    }];
    
    NSOperationQueue *queue = [[NSOperationQueue alloc] init];
    [queue addOperation:imageOp];
}

- (void)beginUserGraffitiGetWithId:(int)identifier
                           success:(GiraffeClientSuccessBlock)success
                           failure:(GiraffeClientFailureBlock)failure
{
    NSDictionary *parameters = @{kParamNameId : @(identifier)};
    [self getPath:kUserGraffiti parameters:parameters success:success failure:failure];
}

- (void)beginUserStatsGetWithId:(int)identifier
                        success:(GiraffeClientSuccessBlock)success
                        failure:(GiraffeClientFailureBlock)failure
{
    NSDictionary *parameters = @{kParamNameId : @(identifier)};
    [self getPath:kUserStats parameters:parameters success:success failure:failure];
}



- (void)beginUserLogoutPostWithUser:(User *)user
                            success:(GiraffeClientSuccessBlock)success
                            failure:(GiraffeClientFailureBlock)failure
{
    [self postPath:kUserLogout parameters:nil success:success failure:failure];
}

@end
