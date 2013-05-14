//
//  UserLoginView.h
//  GiraffeiOS
//
//  Created by Kurtis Horimoto on 5/10/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import <UIKit/UIKit.h>

@class User;
@protocol UserLoginViewDelegate;

@interface UserLoginView : UIView

typedef enum {
    UserLoginTypeSignup = 0,
    UserLoginTypeLogin
} UserLoginType;

@property (nonatomic, assign) id<UserLoginViewDelegate> delegate;
@property (nonatomic, assign) UserLoginType loginType;
@property (nonatomic, readonly) User *userFromInput;
@property (nonatomic, readonly) NSString *password;
@property (nonatomic, retain) UIImage *avatarImage;

@end

@protocol UserLoginViewDelegate <NSObject>

- (void)userLoginView:(UserLoginView *)loginView showImagePicker:(UIImagePickerController *)imagePicker;
- (void)userLoginView:(UserLoginView *)loginView shouldCenterAroundView:(UIView *)viewToCenter;
- (void)userLoginView:(UserLoginView *)loginView didChooseLoginType:(UserLoginType)loginType;

@end