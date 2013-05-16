//
//  User.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/28/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "User.h"

@implementation User

NSString *const kParamNameUser = @"user";
NSString *const kParamNameUserId = @"id";
NSString *const kParamNameUserUsername = @"username";
NSString *const kParamNameUserEmail = @"email";
NSString *const kParamNameUserUsernameEmail = @"usernameEmail";
NSString *const kParamNameUserAvatarUrl = @"avatar";
NSString *const kParamNameUserDateJoined = @"dateJoined";
NSString *const kParamNameUserPassword = @"password";
NSString *const kParamNameUserOldPassword = @"oldPassword";
NSString *const kParamNameUserAvatar = @"avatar";

NSString *const kAvatarImagePlaceholderFilename = @"avatarImagePlaceholder.png";

- (id)initWithDictionary:(NSDictionary *)dictionary
{
    self = [super init];
    if (self) {
        [self updateWithDictionary:dictionary];
    }
    return self;
}

#pragma mark - Current user

+ (User *)currentUser
{
    // Create Singleton
    static User *currentUser = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        currentUser = [User new];
    });
    
    return currentUser;
}

+ (void)saveUser {
    // save to nsuserdefaults?
}

+ (void)loadUser {
    // load from nsuserdefaults
}

- (BOOL)isSignedIn
{
    return self.identifier > 0;
}

- (void)logout
{
    self.identifier = 0;
    self.username = nil;
    self.email = nil;
    self.avatarUrl = nil;
    self.dateJoined = nil;
}

- (NSDictionary *)parameterDictionary
{
    // Construct dictionary with expected paramter names
    return @{ kParamNameUserId         : @(self.identifier),
              kParamNameUserUsername   : (self.username ?: [NSNull null]),
              kParamNameUserEmail      : (self.email ?: [NSNull null]),
              kParamNameUserAvatarUrl  : (self.avatarUrl ?: [NSNull null]),
              kParamNameUserDateJoined : (self.dateJoined ?: [NSNull null])};
}

- (void)updateWithDictionary:(NSDictionary *)dictionary
{
    // Perform reverse of paramterDictionary...unpack json into properties
    if ([dictionary objectForKey:kParamNameUserId]) {
        self.identifier = [[dictionary objectForKey:kParamNameUserId] intValue];
    }
    
    if ([dictionary objectForKey:kParamNameUserUsername]) {
        self.username = [dictionary objectForKey:kParamNameUserUsername];
    }
    
    if ([dictionary objectForKey:kParamNameUserEmail]) {
        self.email = [dictionary objectForKey:kParamNameUserEmail];
    }
    
    if ([dictionary objectForKey:kParamNameUserAvatarUrl]) {
        self.avatarUrl = [dictionary objectForKey:kParamNameUserAvatarUrl];
        
        if ([self.avatarUrl isKindOfClass:[NSNull class]]) {
            self.avatarUrl = nil;
        }
    }
    
    if ([dictionary objectForKey:kParamNameUserDateJoined]) {
        self.dateJoined = [dictionary objectForKey:kParamNameUserDateJoined];
    }
}

@end
