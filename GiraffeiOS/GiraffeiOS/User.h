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
extern NSString *const kParamNameUserImageUrl;
extern NSString *const kParamNameUserDateCreated;

@property (nonatomic, assign) int identifier;
@property (nonatomic, strong) NSString *username;
@property (nonatomic, strong) NSString *email;
@property (nonatomic, strong) NSString *imageUrl;
@property (nonatomic, strong) NSDate *dateCreated;

+ (User *)currentUser;
+ (void)saveUser;
+ (void)loadUser;

- (void)clear;

- (NSDictionary *)parameterDictionary;
- (void)updateWithDictionary:(NSDictionary *)dictionary;

@end
