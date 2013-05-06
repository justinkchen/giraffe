//
//  User.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/28/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "User.h"

@implementation User

static User *_currentUser;

+ (User *)currentUser {
    if (_currentUser == nil) {
        _currentUser = [[User alloc] init];
    }
    return _currentUser;
}

+ (void)saveUser {
    
}

+ (void)loadUser {
    
}

- (void)clear {
    
}

@end
