//
//  GiraffeShareView.m
//  GiraffeiOS
//
//  Created by Kurtis Horimoto on 5/8/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "GiraffeShareView.h"
#import "Graffiti.h"
#import "User.h"
#import "LocationManager.h"
#import "UIKit-Utility.h"
#import <QuartzCore/QuartzCore.h>

@interface GiraffeShareView () <UIWebViewDelegate, UIAlertViewDelegate>

// Views
@property (nonatomic, retain) UILabel *textLabel;
@property (nonatomic, retain) UITextView *textView;
@property (nonatomic, retain) UIWebView *webView;
@property (nonatomic, retain) UILabel *radiusLabel;
@property (nonatomic, retain) UISlider *radiusSlider;
@property (nonatomic, retain) UIButton *postButton;
@property (nonatomic, retain) UIButton *imageButton;

// Util
@property (nonatomic, readonly) CGRect contentFrame;

@end

@implementation GiraffeShareView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Listen to keyboard events
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleKeyboardFrameChange:) name:UIKeyboardWillChangeFrameNotification object:nil];
    }
    return self;
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

#pragma mark - Accessors

const CGFloat kContentInset = 8.0;

- (CGRect)contentFrame
{
    return UIEdgeInsetsInsetRect(self.bounds, UIEdgeInsetsMake(kContentInset, kContentInset, kContentInset, kContentInset));
}

- (Graffiti *)graffitiFromInput
{
    if (![self.textView.text length]) {
        [self.delegate shareView:self displayMessage:@"Message cannot be blank."];
        return nil;
    }
    
    Graffiti *graffiti = [Graffiti new];;
    
    graffiti.user = [User currentUser];
    graffiti.message = self.textView.text;
    graffiti.latitude = [LocationManager sharedInstance].latitude;
    graffiti.longitude = [LocationManager sharedInstance].longitude;
    graffiti.radius = self.radiusSlider.value;
    graffiti.dateCreated = [NSDate date];
    
    return graffiti;
}

#pragma mark - Layout

- (BOOL)keyboardVisible
{
    return !self.textView || self.textView.isFirstResponder;
}

NSString *const kRadiusLabelTextFormat = @"Graffiti radius: %.0f m";

- (NSString *)radiusLabelText
{
    return [NSString stringWithFormat:kRadiusLabelTextFormat, self.radiusSlider.value];
}

NSString *const kTextLabelText = @"Graffiti text:";
const CGFloat kTextViewCornerRadius = 4.0;
const CGFloat kShareViewPadding = 8.0;

- (void)layoutSubviews
{
    [super layoutSubviews];
    
    CGRect contentFrame = self.contentFrame;
    
    // Text Label
    if (!self.textLabel) {
        self.textLabel = [UILabel new];
        self.textLabel.font = [UIFont helveticaNeueCondensedOfSize:18.0 weight:UIFontWeightRegular];
        self.textLabel.backgroundColor = self.backgroundColor;
        self.textLabel.text = kTextLabelText;
        [self addSubview:self.textLabel];
    }
    [self.textLabel sizeToFit];
    self.textLabel.frameOriginX = contentFrame.origin.x;
    self.textLabel.frameOriginY = contentFrame.origin.y;
    
    // Text View
    if (!self.textView) {
        self.textView = [UITextView new];
        self.textView.font = [UIFont helveticaNeueCondensedOfSize:18.0 weight:UIFontWeightRegular];
        self.textView.textColor = [UIColor blackColor];
        self.textView.backgroundColor = [UIColor whiteColor];
        self.textView.layer.cornerRadius = kTextViewCornerRadius;
        self.textView.layer.borderColor = [UIColor grayColor].CGColor;
        self.textView.layer.borderWidth = 1.0;
        self.textView.frameWidth = contentFrame.size.width;
        self.textView.frameHeight = 4 * self.textView.font.lineHeight;
        [self addSubview:self.textView];
    }
    self.textView.frameOriginY = self.textLabel.bottomEdge + kShareViewPadding;
    self.textView.frameOriginX = contentFrame.origin.x;
    
    // Web view
    if (!self.webView) {
        self.webView = [UIWebView new];
        self.webView.delegate = self;
        self.webView.frameWidth = contentFrame.size.width;
        self.webView.frameHeight = 0.6 * self.webView.frameWidth;
        self.webView.userInteractionEnabled = NO;
        [self addSubview:self.webView];
    }
    self.webView.frameOriginX = contentFrame.origin.x;
    self.webView.frameOriginY = self.textView.bottomEdge + kShareViewPadding;
    self.webView.alpha = [self keyboardVisible] ? 0.0 : 1.0;
    
    // Image temp view
    if (!self.imageView) {
        self.imageView = [UIImageView new];
        self.imageView.frame = self.webView.frame;
        [self addSubview:self.imageView];
    }
    self.imageView.frame = self.webView.frame;
    self.imageView.alpha = [self keyboardVisible] ? 0.0 : 1.0;
    
    // Radius Slider
    if (!self.radiusSlider) {
        self.radiusSlider = [UISlider new];
        [self.radiusSlider addTarget:self action:@selector(radiusSliderValueDidChange:) forControlEvents:UIControlEventValueChanged];
        self.radiusSlider.frameWidth = self.webView.frameWidth;
        self.radiusSlider.minimumValue = 5.0;
        self.radiusSlider.maximumValue = 500.0;
        self.radiusSlider.value = 50.0;
        [self sizeToFit];
        [self addSubview:self.radiusSlider];
    }
    
    // Radius label
    if (!self.radiusLabel) {
        self.radiusLabel = [UILabel new];
        self.radiusLabel.font = [UIFont helveticaNeueCondensedOfSize:18.0 weight:UIFontWeightRegular];
        self.radiusLabel.backgroundColor = self.backgroundColor;
        [self addSubview:self.radiusLabel];
    }
    self.radiusLabel.text = [self radiusLabelText];
    [self.radiusLabel sizeToFit];
    self.radiusLabel.frameOriginX = contentFrame.origin.x;
    self.radiusLabel.frameOriginY = kShareViewPadding + ([self keyboardVisible] ? self.textView.bottomEdge : self.webView.bottomEdge);

    self.radiusSlider.frameOriginX = contentFrame.origin.x;
    self.radiusSlider.frameOriginY = self.radiusLabel.bottomEdge + kShareViewPadding;
    
    // first responder control
    if (!self.firstResponderControl) {
        self.firstResponderControl = [UIControl new];
        self.firstResponderControl.backgroundColor = [UIColor clearColor];
        self.firstResponderControl.exclusiveTouch = NO;
        [self.firstResponderControl addTarget:self action:@selector(handleFirstResponderControlTapped:) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:self.firstResponderControl];
    }
    self.firstResponderControl.frame = self.bounds;
    self.firstResponderControl.hidden = ![self keyboardVisible];
    
    // Bring controls to front
    [self bringSubviewToFront:self.textView];
    [self bringSubviewToFront:self.postButton];
    [self bringSubviewToFront:self.radiusSlider];
}

- (void)resetView
{
    self.textView.text = @"";
    self.radiusSlider.value = 50;
}

#pragma mark - Map view

NSString *const kAddGraffitiMapUrlFormat = @"http://ec2-54-243-69-6.compute-1.amazonaws.com/addgraffiti_map.html?latitude=%f&longitude=%f";

- (void)updateMapView
{
    NSURL *url = [NSURL URLWithString:[NSString stringWithFormat:kAddGraffitiMapUrlFormat, [LocationManager sharedInstance].latitude, [LocationManager sharedInstance].longitude]];
    NSURLRequest *request = [NSURLRequest requestWithURL:url];
    [self.webView loadRequest:request];
}

#pragma mark - Slider

NSString *const kMapViewRadiusJavascriptFormat = @"updateRadius(%f);";

- (void)radiusSliderValueDidChange:(id)sender
{
    if ([self.radiusSlider isEqual:sender]) {
        // Update label
        self.radiusLabel.text = [self radiusLabelText];
        [self.radiusLabel sizeToFit];
        
        // Update map
        [self.webView stringByEvaluatingJavaScriptFromString:[NSString stringWithFormat:kMapViewRadiusJavascriptFormat, self.radiusSlider.value]];
    }
}

#pragma mark - Buttons

- (void)handleFirstResponderControlTapped:(id)control
{
    if ([self.firstResponderControl isEqual:control]) {
        [self.textView resignFirstResponder];
        [self setNeedsLayout];
    }
}

#pragma mark - Keyboard

- (void)handleKeyboardFrameChange:(NSNotification *)notification
{
    NSTimeInterval animationDuration = [[notification.userInfo objectForKey:UIKeyboardAnimationDurationUserInfoKey] doubleValue];
    [self animateLayoutWithDuration:animationDuration];
}

@end
