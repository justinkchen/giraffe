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
NSString *const kParamNameUserImageUrl = @"imageUrl";
NSString *const kParamNameUserDateCreated = @"dateCreated";
NSString *const kParamNameUserPassword = @"password";
NSString *const kParamNameUserAvatar = @"avatar";

NSString *const kAvatarImagePlaceholderFilename = @"avatarImagePlaceholder.png";

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

- (void)clear {
    
}

- (NSDictionary *)parameterDictionary
{
    // Construct dictionary with expected paramter names
    return nil;
}

- (void)updateWithDictionary:(NSDictionary *)dictionary
{
    // Perform reverse of paramterDictionary...unpack json into properties
    
}

- (id)initWithDictionary:(NSDictionary *)dictionary
{
    self = [super init];
    if (self) {
        [self updateWithDictionary:dictionary];
    }
    return self;
}

@end
