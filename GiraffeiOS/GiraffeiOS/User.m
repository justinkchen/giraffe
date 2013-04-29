//
//  User.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/28/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "User.h"

@interface User()
@property (nonatomic, assign) int userId;
@property (nonatomic, strong) NSString *username;
@property (nonatomic, strong) NSString *email;
@property (nonatomic, strong) NSString *avatar;
//@property (nonatomic, strong) NSDate _dateCreated;
// listerns?
@end

@implementation User

@synthesize userId = _userId;
@synthesize username = _username;
@synthesize email = _email;

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
