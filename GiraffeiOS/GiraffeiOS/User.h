//
//  User.h
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/28/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface User : NSObject

extern NSString *const kParamNameUser;
extern NSString *const kParamNameUserId;
extern NSString *const kParamNameUserUsername;
extern NSString *const kParamNameUserEmail;
extern NSString *const kParamNameUserAvatarUrl;
extern NSString *const kParamNameUserDateJoined;
extern NSString *const kParamNameUserPassword;
extern NSString *const kParamNameUserOldPassword;
extern NSString *const kParamNameUserAvatar;

extern NSString *const kAvatarImagePlaceholderFilename;

@property (nonatomic, assign) int identifier;
@property (nonatomic, strong) NSString *username;
@property (nonatomic, strong) NSString *email;
@property (nonatomic, strong) NSString *avatarUrl;
@property (nonatomic, strong) NSDate *dateJoined;
@property (nonatomic, readonly) BOOL isSignedIn;

+ (User *)currentUser;
+ (void)saveUser;
+ (void)loadUser;

- (void)logout;

- (NSDictionary *)parameterDictionary;
- (void)updateWithDictionary:(NSDictionary *)dictionary;
- (id)initWithDictionary:(NSDictionary *)dictionary;

@end
