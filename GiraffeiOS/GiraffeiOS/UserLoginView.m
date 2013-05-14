//
//  UserLoginView.m
//  GiraffeiOS
//
//  Created by Kurtis Horimoto on 5/10/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "UserLoginView.h"
#import "User.h"
#import "UIKit-Utility.h"
#import <QuartzCore/QuartzCore.h>

@interface UserLoginView () <UIActionSheetDelegate, UIImagePickerControllerDelegate, UINavigationControllerDelegate, UITextFieldDelegate>

// Subviews
@property (nonatomic, retain) UILabel *errorLabel;
@property (nonatomic, retain) UITextField *usernameField;
@property (nonatomic, retain) UITextField *emailField;
@property (nonatomic, retain) UITextField *passwordField;
@property (nonatomic, retain) UITextField *passwordConfirmField;
@property (nonatomic, retain) UIImageView *avatarImageView;
@property (nonatomic, retain) UIControl *avatarImageControl;
@property (nonatomic, retain) UIControl *firstResponderControl;
@property (nonatomic, retain) UIButton *switchTypeButton;

// Model
@property (nonatomic, assign) CGFloat baseFrameOriginY;
@property (nonatomic, assign) CGFloat visibleFrameHeight;
@property (nonatomic, assign) NSTimeInterval keyboardAnimationDuration;

@end

@implementation UserLoginView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        self.loginType = UserLoginTypeSignup;
    }
    return self;
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

#pragma mark - Accessors

- (NSString *)usernameOrEmail
{
    NSString *usernameOrEmail = nil;
    if (self.loginType == UserLoginTypeLogin && [self.usernameField.text length] > 0) {
        usernameOrEmail = self.usernameField.text;
    }
    return usernameOrEmail;
}

- (NSString *)password
{
    NSString *password = nil;
    if ([self.passwordField.text length] > 0 && [self.passwordConfirmField.text length] > 0 &&
        [self.passwordField.text isEqualToString:self.passwordConfirmField.text]) {
        password = self.passwordField.text;
    }
    return password;
}

- (User *)userFromInput
{
    User *user = nil;
    if ([self.usernameField.text length] && [self.emailField.text length] && [self.password length]) {
        user = [User new];
        user.username = self.usernameField.text;
        user.email = self.emailField.text;
        user.dateJoined = [NSDate date];
    }
    return user;
}

- (void)setLoginType:(UserLoginType)loginType
{
    if (_loginType != loginType) {
        _loginType = loginType;
        [self.delegate userLoginView:self didChooseLoginType:loginType];
        [self setNeedsLayout];
    }
}

#pragma mark - Layout

const CGFloat kUserLoginPadding = 10.0;
const CGFloat kAvatarImageSize = 55.0;
NSString *const kUsernameSignupPlaceholderString = @"Username";
NSString *const kUsernameLoginPlaceholderString = @"Username or Email";
NSString *const kEmailPlaceholderString = @"Email";
NSString *const kPasswordPlaceholderString = @"Password";
NSString *const kPasswordConfirmPlaceholderString = @"Confirm Password";
NSString *const kSwitchToLoginButtonTitle = @"Already have an account?";
NSString *const kSwitchToSignupButtonTitle = @"Don't have an account?";

- (void)layoutSubviews
{
    [super layoutSubviews];
    
    CGFloat topInset = kUserLoginPadding;
    
    // First responder control
    if (!self.firstResponderControl) {
        self.firstResponderControl = [UIControl new];
        self.firstResponderControl.backgroundColor = [UIColor clearColor];
        [self.firstResponderControl addTarget:self action:@selector(handleFirstResponderControlTapped:) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:self.firstResponderControl];
    }
    self.firstResponderControl.frame = self.bounds;
    
    if (self.loginType == UserLoginTypeSignup) {
        // Avatar image
        if (!self.avatarImageView) {
            self.avatarImageView = [UIImageView new];
            self.avatarImageView.image = [UIImage imageNamed:kAvatarImagePlaceholderFilename];
            self.avatarImageView.frameSize = CGSizeMake(kAvatarImageSize, kAvatarImageSize);
            self.avatarImageView.layer.cornerRadius = 4.0;
            [self addSubview:self.avatarImageView];
        }
        if (self.avatarImage) {
            self.avatarImageView.image = self.avatarImage;
            self.avatarImageView.layer.borderWidth = 0.0;
        } else {
            self.avatarImageView.layer.borderWidth = 1.0;
            self.avatarImageView.layer.borderColor = [UIColor grayColor].CGColor;
        }
        self.avatarImageView.hidden = NO;
        self.avatarImageView.frameOriginX = centerOffset(self.avatarImageView.frameWidth, self.frameWidth);
        self.avatarImageView.frameOriginY = topInset;
        topInset = self.avatarImageView.bottomEdge + kUserLoginPadding;
        
        // Avatar control
        if (!self.avatarImageControl) {
            self.avatarImageControl = [UIControl new];
            self.avatarImageControl.backgroundColor = [UIColor clearColor];
            [self.avatarImageControl addTarget:self action:@selector(handleAvatarImageTapped:) forControlEvents:UIControlEventTouchUpInside];
            [self addSubview:self.avatarImageControl];
        }
        self.avatarImageControl.frame = self.avatarImageView.frame;
        self.avatarImageControl.enabled = YES;
    } else {
        self.avatarImageView.hidden = YES;
        self.avatarImageControl.enabled = NO;
    }

    // Switch type button
    if (!self.switchTypeButton) {
        self.switchTypeButton = [UIButton new];
        self.switchTypeButton.backgroundColor = self.backgroundColor;
        self.switchTypeButton.titleLabel.font = [UIFont helveticaNeueCondensedOfSize:16.0 weight:UIFontWeightRegular];
        [self.switchTypeButton addTarget:self action:@selector(switchTypeButtonTapped:) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:self.switchTypeButton];
    }
    switch (self.loginType) {
        case UserLoginTypeLogin:
            [self.switchTypeButton setTitle:kSwitchToSignupButtonTitle forState:UIControlStateNormal];
            break;
        case UserLoginTypeSignup:
        default:
            [self.switchTypeButton setTitle:kSwitchToLoginButtonTitle forState:UIControlStateNormal];
            break;
    }
    [self.switchTypeButton sizeToFit];
    [self.switchTypeButton centerHorizontally];
    self.switchTypeButton.frameOriginY = topInset;
    topInset = self.switchTypeButton.bottomEdge + kUserLoginPadding;
    
    // Username
    if (!self.usernameField) {
        self.usernameField = [UITextField new];
        self.usernameField.delegate = self;
        self.usernameField.borderStyle = UITextBorderStyleBezel;
        self.usernameField.backgroundColor = self.backgroundColor;
        self.usernameField.textColor = [UIColor blackColor];
        self.usernameField.font = [UIFont helveticaNeueCondensedOfSize:18.0 weight:UIFontWeightRegular];
        self.usernameField.layer.cornerRadius = 4.0;
        self.usernameField.autocorrectionType = UITextAutocorrectionTypeNo;
        [self addSubview:self.usernameField];
    }
    switch (self.loginType) {
        case UserLoginTypeLogin:
            self.usernameField.placeholder = kUsernameLoginPlaceholderString;
            break;
        case UserLoginTypeSignup:
        default:
            self.usernameField.placeholder = kUsernameSignupPlaceholderString;
            break;
    }
    self.usernameField.frameHeight = 1.5 * self.usernameField.font.lineHeight;
    self.usernameField.frameWidth = self.frameWidth - 2 * kUserLoginPadding;
    self.usernameField.frameOriginX = kUserLoginPadding;
    self.usernameField.frameOriginY = topInset;
    topInset = self.usernameField.bottomEdge + kUserLoginPadding;
    
    if (self.loginType == UserLoginTypeSignup) {
        // Email
        if (!self.emailField) {
            self.emailField = [UITextField new];
            self.emailField.delegate = self;
            self.emailField.borderStyle = UITextBorderStyleBezel;
            self.emailField.backgroundColor = self.backgroundColor;
            self.emailField.textColor = [UIColor blackColor];
            self.emailField.placeholder = kEmailPlaceholderString;
            self.emailField.font = [UIFont helveticaNeueCondensedOfSize:18.0 weight:UIFontWeightRegular];
            self.emailField.layer.cornerRadius = 4.0;
            [self addSubview:self.emailField];
        }
        self.emailField.hidden = NO;
        self.emailField.frameSize = self.usernameField.frameSize;
        self.emailField.frameOriginX = self.usernameField.frameOriginX;
        self.emailField.frameOriginY = topInset;
        topInset = self.emailField.bottomEdge + kUserLoginPadding;
    } else {
        self.emailField.hidden = YES;
    }
    
    // Password
    if (!self.passwordField) {
        self.passwordField = [UITextField new];
        self.passwordField.delegate = self;
        self.passwordField.borderStyle = UITextBorderStyleBezel;
        self.passwordField.backgroundColor = self.backgroundColor;
        self.passwordField.textColor = [UIColor blackColor];
        self.passwordField.placeholder = kPasswordPlaceholderString;
        self.passwordField.font = [UIFont helveticaNeueCondensedOfSize:18.0 weight:UIFontWeightRegular];
        self.passwordField.layer.cornerRadius = 4.0;
        self.passwordField.secureTextEntry = YES;
        self.passwordField.autocorrectionType = UITextAutocorrectionTypeNo;
        [self addSubview:self.passwordField];
    }
    self.passwordField.frameSize = self.usernameField.frameSize;
    self.passwordField.frameOriginX = self.usernameField.frameOriginX;
    self.passwordField.frameOriginY = topInset;
    topInset = self.passwordField.bottomEdge + kUserLoginPadding;
    
    if (self.loginType == UserLoginTypeSignup) {
        // Password
        if (!self.passwordConfirmField) {
            self.passwordConfirmField = [UITextField new];
            self.passwordConfirmField.delegate = self;
            self.passwordConfirmField.borderStyle = UITextBorderStyleBezel;
            self.passwordConfirmField.backgroundColor = self.backgroundColor;
            self.passwordConfirmField.textColor = [UIColor blackColor];
            self.passwordConfirmField.placeholder = kPasswordConfirmPlaceholderString;
            self.passwordConfirmField.font = [UIFont helveticaNeueCondensedOfSize:18.0 weight:UIFontWeightRegular];
            self.passwordConfirmField.layer.cornerRadius = 4.0;
            self.passwordConfirmField.secureTextEntry = YES;
            [self addSubview:self.passwordConfirmField];
        }
        self.passwordConfirmField.frameSize = self.passwordField.frameSize;
        self.passwordConfirmField.frameOriginX = self.passwordField.frameOriginX;
        self.passwordConfirmField.frameOriginY = topInset;
        topInset = self.passwordConfirmField.bottomEdge + kUserLoginPadding;
        self.passwordConfirmField.hidden = NO;
    } else {
        self.passwordConfirmField.hidden = YES;
    }
}

#pragma mark - Buttons

NSString *const kImageActionSheetCamera = @"Take Photo";
NSString *const kImageActionSheetLibrary = @"Choose Existing";
NSString *const kImageActionSheetCancel = @"Cancel";

- (void)handleAvatarImageTapped:(UIControl *)sender
{
    if ([self.avatarImageControl isEqual:sender]) {
        UIActionSheet *actionSheet = nil;
        if ([UIImagePickerController isCameraDeviceAvailable:UIImagePickerControllerCameraDeviceRear]) {
            actionSheet = [[UIActionSheet alloc] initWithTitle:nil
                                                                     delegate:self
                                                            cancelButtonTitle:kImageActionSheetCancel
                                                       destructiveButtonTitle:nil
                                                            otherButtonTitles:kImageActionSheetCamera, kImageActionSheetLibrary, nil];
        } else {
            actionSheet = [[UIActionSheet alloc] initWithTitle:nil
                                                      delegate:self
                                             cancelButtonTitle:kImageActionSheetCancel
                                        destructiveButtonTitle:nil
                                             otherButtonTitles:kImageActionSheetLibrary, nil];
        }
        [actionSheet showInView:self];
    }
}

- (void)handleFirstResponderControlTapped:(UIControl *)sender
{
    if ([self.firstResponderControl isEqual:sender]) {
        [self endEditing:YES];
    }
}

- (void)switchTypeButtonTapped:(UIButton *)button
{
    switch (self.loginType) {
        case UserLoginTypeLogin:
            self.loginType = UserLoginTypeSignup;
            break;
        case UserLoginTypeSignup:
        default:
            self.loginType = UserLoginTypeLogin;
            break;
    }
}

#pragma mark - Action sheet

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    NSString *buttonTitle = [actionSheet buttonTitleAtIndex:buttonIndex];
    if (![buttonTitle isEqualToString:kImageActionSheetCancel]) {
        UIImagePickerController *imagePickerController = [UIImagePickerController new];
        imagePickerController.delegate = self;
        if ([buttonTitle isEqualToString:kImageActionSheetCamera]) {
            imagePickerController.sourceType = UIImagePickerControllerSourceTypeCamera;
        } else if ([buttonTitle isEqualToString:kImageActionSheetLibrary]) {
            imagePickerController.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
        }
        [self.delegate userLoginView:self showImagePicker:imagePickerController];
    }
}

#pragma mark - UIImagePickerControllerDelegate


- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    // figure out which image to use here and set it in self.avatarImage
}

#pragma mark - UITextFieldDelegate

- (void)textFieldDidBeginEditing:(UITextField *)textField
{
    [self.delegate userLoginView:self shouldCenterAroundView:textField];
}

@end
