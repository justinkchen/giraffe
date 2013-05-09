//
//  User.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/28/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "User.h"

@implementation User

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
    
}

+ (void)loadUser {
    
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

@end
