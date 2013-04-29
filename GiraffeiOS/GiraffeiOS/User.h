//
//  User.h
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/28/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface User : NSObject

+ (User *)currentUser;
+ (void)saveUser;
+ (void)loadUser;

//- (void)addListener:(UserListener *)listener;
//- (void)removeObserver

// update??
- (void)clear;

@end
