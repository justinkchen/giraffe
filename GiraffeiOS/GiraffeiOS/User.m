//
//  User.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/28/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "User.h"
#import "Foundation-Utility.h"

@implementation User

NSString *const kParamNameUser = @"user";
NSString *const kParamNameUserId = @"id";
NSString *const kParamNameUserUsername = @"username";
NSString *const kParamNameUserEmail = @"email";
NSString *const kParamNameUserUsernameEmail = @"usernameEmail";
NSString *const kParamNameUserAvatarUrl = @"avatarUrl";
NSString *const kParamNameUserDateJoined = @"dateJoined";
NSString *const kParamNameUserPassword = @"password";
NSString *const kParamNameUserOldPassword = @"oldPassword";
NSString *const kParamNameUserAvatar = @"avatar";

// stats
NSString *const kParamNameUserGraffitiCount = @"graffitiCount";
NSString *const kParamNameUserLikeCount = @"likeCount";
NSString *const kParamNameUserBadgeCount = @"badgeCount";

NSString *const kAvatarImagePlaceholderFilename = @"avatarImagePlaceholder.png";

NSString *const kCurrentUserDefaultsKey = @"currentUser";

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
//        currentUser = [[NSUserDefaults standardUserDefaults] objectForKey:kCurrentUserDefaultsKey];
//        if (!currentUser) {
            currentUser = [User new];
//        }
    });
    
    return currentUser;
}

NSString *const kUserDataKey = @"userData";

+ (void)saveUser {
    NSData *encodedUser = [NSKeyedArchiver archivedDataWithRootObject:[User currentUser]];
    [[NSUserDefaults standardUserDefaults] setObject:encodedUser forKey:kUserDataKey];
}

+ (void)loadUser {
    NSLog(@"loading user");
    NSData *encodedUser = [[NSUserDefaults standardUserDefaults] objectForKey:kUserDataKey];
    User *user = [NSKeyedUnarchiver unarchiveObjectWithData: encodedUser];
    User *currentUser = [User currentUser];
    
    currentUser.identifier = user.identifier;
    currentUser.username = user.username;
    currentUser.email = user.email;
    currentUser.avatarUrl = user.avatarUrl;
    currentUser.dateJoined = user.dateJoined;
}

//- (void)saveCurrentUser
//{
//    [NSDefaults setObject:self forKey:kCurrentUserDefaultsKey];
//    [NSDefaults synchronize];
//}

- (void)logout
{
    self.identifier = 0;
    self.username = nil;
    self.email = nil;
    self.avatarUrl = nil;
    self.dateJoined = nil;
    
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"userUpdated" object:nil]];
}

#pragma mark - User Encoding

- (void)encodeWithCoder:(NSCoder *)encoder {
    //Encode properties, other class variables, etc
    [encoder encodeInteger:self.identifier forKey:kParamNameUserId];
    [encoder encodeObject:self.username forKey:kParamNameUserUsername];
    [encoder encodeObject:self.email forKey:kParamNameUserEmail];
    [encoder encodeObject:self.avatarUrl forKey:kParamNameUserAvatarUrl];
    [encoder encodeObject:self.dateJoined forKey:kParamNameUserDateJoined];
    
}

- (id)initWithCoder:(NSCoder *)decoder {
    if((self = [super init])) {
        //decode properties, other class vars
        self.identifier = [decoder decodeIntegerForKey:kParamNameUserId];
        self.username = [decoder decodeObjectForKey:kParamNameUserUsername];
        self.email = [decoder decodeObjectForKey:kParamNameUserEmail];
        self.avatarUrl = [decoder decodeObjectForKey:kParamNameUserAvatarUrl];
        self.dateJoined = [decoder decodeObjectForKey:kParamNameUserDateJoined];
        
    }
    return self;
}

//- (id)initWithCoder:(NSCoder *)aDecoder
//{
//    self.identifier = [aDecoder decodeIntegerForKey:kParamNameUserId];
//    self.username = [aDecoder decodeObjectForKey:kParamNameUserUsername];
//    self.email = [aDecoder decodeObjectForKey:kParamNameUserEmail];
//    self.avatarUrl = [aDecoder decodeObjectForKey:kParamNameUserAvatarUrl];
//    self.dateJoined = [aDecoder decodeObjectForKey:kParamNameUserDateJoined];
//}

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
    
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:@"userUpdated" object:nil]];
}

- (void)updateStatsWithDictionary:(NSDictionary *)dictionary {
    if ([dictionary objectForKey:kParamNameUserGraffitiCount]) {
        self.graffitiCount = [[dictionary objectForKey:kParamNameUserGraffitiCount] intValue];
    }
    
    if ([dictionary objectForKey:kParamNameUserLikeCount]) {
        self.likeCount = [[dictionary objectForKey:kParamNameUserLikeCount] intValue];
    }
    
    if ([dictionary objectForKey:kParamNameUserBadgeCount]) {
        self.badgeCount = [[dictionary objectForKey:kParamNameUserBadgeCount] intValue];
    }
}

@end
