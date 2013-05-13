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
@property (nonatomic, retain) UITextField *usernameEmailField;
//@property (nonatomic, retain) UITextField *emailField;
@property (nonatomic, retain) UITextField *passwordField;
//@property (nonatomic, retain) UITextField *passwordConfirmField;
@property (nonatomic, retain) UIImageView *avatarImageView;
@property (nonatomic, retain) UIControl *avatarImageControl;
@property (nonatomic, retain) UIControl *firstResponderControl;

// Model
@property (nonatomic, retain) UIImage *avatarImage;
@property (nonatomic, assign) CGFloat baseFrameOriginY;
@property (nonatomic, assign) CGFloat visibleFrameHeight;
@property (nonatomic, assign) NSTimeInterval keyboardAnimationDuration;

@end

@implementation UserLoginView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
    }
    return self;
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

#pragma mark - Accessors

//- (NSString *)password
//{
//    NSString *password = nil;
//    if ([self.passwordField.text length] > 0 && [self.passwordConfirmField.text length] > 0 &&
//        [self.passwordField.text isEqualToString:self.passwordConfirmField.text]) {
//        password = self.passwordField.text;
//    }
//    return password;
//}
//
//- (User *)userFromInput
//{
//    User *user = nil;
//    if ([self.usernameEmailField.text length] && [self.emailField.text length] && [self.password length]) {
//        user = [User new];
//        user.username = self.usernameEmailField.text;
//        user.email = self.emailField.text;
//        user.dateCreated = [NSDate date];
//    }
//    return user;
//}

- (NSDictionary *)userParameters
{
    NSDictionary *parameters = nil;
    
    if ([self.usernameEmailField.text length] > 0 &&
        [self.passwordField.text length] > 0) {
        parameters = [NSDictionary dictionaryWithObjects:[NSArray arrayWithObjects:self.usernameEmailField.text, self.passwordField.text, nil]  forKeys:[NSArray arrayWithObjects:@"usernameEmail", @"password", nil]];
    }
    
    return parameters;
}

- (void)displayError:(NSString *)errorMessage {
//    [self.errorLabel setText:errorMessage];
}

#pragma mark - Layout

const CGFloat kUserLoginPadding = 10.0;
const CGFloat kAvatarImageSize = 55.0;
NSString *const kUsernamePlaceholderString = @"Username or Email";
//NSString *const kEmailPlaceholderString = @"Email";
NSString *const kPasswordPlaceholderString = @"Password";
//NSString *const kPasswordConfirmPlaceholderString = @"Confirm Password";

- (void)layoutSubviews
{
    [super layoutSubviews];
    
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
    self.avatarImageView.frameOriginY = kUserLoginPadding;
    self.avatarImageView.frameOriginX = centerOffset(self.avatarImageView.frameWidth, self.frameWidth);
    
    // First responder contro
    if (!self.firstResponderControl) {
        self.firstResponderControl = [UIControl new];
        self.firstResponderControl.backgroundColor = [UIColor clearColor];
        [self.firstResponderControl addTarget:self action:@selector(handleFirstResponderControlTapped:) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:self.firstResponderControl];
    }
    self.firstResponderControl.frame = self.bounds;
    
    // Avatar control
    if (!self.avatarImageControl) {
        self.avatarImageControl = [UIControl new];
        self.avatarImageControl.backgroundColor = [UIColor clearColor];
        [self.avatarImageControl addTarget:self action:@selector(handleAvatarImageTapped:) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:self.avatarImageControl];
    }
    self.avatarImageControl.frame = self.avatarImageView.frame;
    
    // Error message
    // TODO: add error message label
    
    // Username
    if (!self.usernameEmailField) {
        self.usernameEmailField = [UITextField new];
        self.usernameEmailField.delegate = self;
        self.usernameEmailField.borderStyle = UITextBorderStyleBezel;
        self.usernameEmailField.backgroundColor = self.backgroundColor;
        self.usernameEmailField.textColor = [UIColor blackColor];
        self.usernameEmailField.placeholder = kUsernamePlaceholderString;
        self.usernameEmailField.font = [UIFont helveticaNeueCondensedOfSize:18.0 weight:UIFontWeightRegular];
        self.usernameEmailField.layer.cornerRadius = 4.0;
        self.usernameEmailField.autocorrectionType = UITextAutocorrectionTypeNo;
        [self addSubview:self.usernameEmailField];
    }
    self.usernameEmailField.frameHeight = 1.5 * self.usernameEmailField.font.lineHeight;
    self.usernameEmailField.frameWidth = self.frameWidth - 2 * kUserLoginPadding;
    self.usernameEmailField.frameOriginX = kUserLoginPadding;
    self.usernameEmailField.frameOriginY = self.avatarImageView.bottomEdge + kUserLoginPadding;
    
    /*
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
    self.emailField.frameSize = self.usernameEmailField.frameSize;
    self.emailField.frameOriginX = self.usernameEmailField.frameOriginX;
    self.emailField.frameOriginY = self.usernameEmailField.bottomEdge + kUserLoginPadding;
    */
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
    self.passwordField.frameSize = self.usernameEmailField.frameSize;
    self.passwordField.frameOriginX = self.usernameEmailField.frameOriginX;
    self.passwordField.frameOriginY = self.usernameEmailField.bottomEdge + kUserLoginPadding;
    
    /*
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
    self.passwordConfirmField.frameOriginY = self.passwordField.bottomEdge + kUserLoginPadding;
     */
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
    
    [self.delegate userLoginView:self didPickAvatarImage:self.avatarImage];
}

#pragma mark - UITextFieldDelegate

- (void)textFieldDidBeginEditing:(UITextField *)textField
{
    [self.delegate userLoginView:self shouldCenterAroundView:textField];
}

@end
