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

NSString *const kUserDataKey = @"userData";

+ (void)saveUser {
    NSData *encodedUser = [NSKeyedArchiver archivedDataWithRootObject:[User currentUser]];
    [[NSUserDefaults standardUserDefaults] setObject:encodedUser forKey:kUserDataKey];
}

+ (void)loadUser {
    NSData *encodedUser = [[NSUserDefaults standardUserDefaults] objectForKey:kUserDataKey];
    User *user = [NSKeyedUnarchiver unarchiveObjectWithData: encodedUser];
    User *currentUser = [User currentUser];
    
    currentUser.identifier = user.identifier;
    currentUser.username = user.username;
    currentUser.email = user.email;
    currentUser.avatarUrl = user.avatarUrl;
    currentUser.dateJoined = user.dateJoined;
}

- (void)encodeWithCoder:(NSCoder *)encoder {
    //Encode properties, other class variables, etc
    [encoder encodeObject:@(self.identifier) forKey:kParamNameUserId];
    [encoder encodeObject:self.username forKey:kParamNameUserUsername];
    [encoder encodeObject:self.email forKey:kParamNameUserEmail];
    [encoder encodeObject:self.avatarUrl forKey:kParamNameUserAvatarUrl];
    [encoder encodeObject:self.dateJoined forKey:kParamNameUserDateJoined];
    
}

- (id)initWithCoder:(NSCoder *)decoder {
    if((self = [super init])) {
        //decode properties, other class vars
        self.identifier = [[decoder decodeObjectForKey:kParamNameUserId] intValue];
        self.username = [decoder decodeObjectForKey:kParamNameUserUsername];
        self.email = [decoder decodeObjectForKey:kParamNameUserEmail];
        self.avatarUrl = [decoder decodeObjectForKey:kParamNameUserAvatarUrl];
        self.dateJoined = [decoder decodeObjectForKey:kParamNameUserDateJoined];

    }
    return self;
}

- (BOOL)isSignedIn
{
    return self.identifier > 0;
}

- (void)logout {
    self.identifier = 0;
    self.username = @"";
    self.email = @"";
    self.avatarUrl = @"";
    self.dateJoined = nil;
}

- (NSDictionary *)parameterDictionary
{
    // Construct dictionary with expected paramter names
    return @{kParamNameUserId: @(self.identifier),
             kParamNameUserUsername: self.username,
             kParamNameUserEmail: self.email,
             kParamNameUserAvatarUrl: self.avatarUrl,
             kParamNameUserDateJoined: self.dateJoined};
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

- (id)initWithDictionary:(NSDictionary *)dictionary
{
    self = [super init];
    if (self) {
        [self updateWithDictionary:dictionary];
    }
    return self;
}

@end
