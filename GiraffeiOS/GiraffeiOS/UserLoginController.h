//
//  UserLoginController.h
//  GiraffeiOS
//
//  Created by Kurtis Horimoto on 5/10/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "User.h"

//@protocol UserLoginViewControllerDelegate;

@interface UserLoginController : UIViewController

@property (nonatomic, assign) UIViewController *delegate;

- (void)displayUserLoginViewController;


@end