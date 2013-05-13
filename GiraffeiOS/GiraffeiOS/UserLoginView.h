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

@property (nonatomic, assign) id<UserLoginViewDelegate> delegate;
//@property (nonatomic, readonly) User *userFromInput;
//@property (nonatomic, readonly) NSString *password;

- (NSDictionary *)userParameters;
- (void)displayError:(NSString *)errorMessage;

@end

@protocol UserLoginViewDelegate <NSObject>

- (void)userLoginView:(UserLoginView *)loginView showImagePicker:(UIImagePickerController *)imagePicker;
- (void)userLoginView:(UserLoginView *)loginView didPickAvatarImage:(UIImage *)avatarImage;
- (void)userLoginView:(UserLoginView *)loginView shouldCenterAroundView:(UIView *)viewToCenter;

@end