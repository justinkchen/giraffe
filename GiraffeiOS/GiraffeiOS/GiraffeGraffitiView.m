//
//  GiraffeGraffitiView.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 6/4/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "GiraffeGraffitiView.h"
#import <MapKit/MapKit.h>
#import "GiraffeClient.h"
#import "LocationManager.h"
#import "UIKit-Utility.h"
#import "NSDate+TimeAgo.h"
#import "UIImageView+AFNetworking.h"
#import <QuartzCore/QuartzCore.h>

@interface GiraffeGraffitiView ()

// Views
@property (nonatomic, retain) UIImageView *userAvatarImage;
@property (nonatomic, retain) UIButton *usernameButton;
@property (nonatomic, retain) UILabel *detailLabel;
@property (nonatomic, retain) UIImageView *graffitiImage;
@property (nonatomic, retain) UILabel *messageLabel;
@property (nonatomic, retain) UIButton *likeButton;
@property (nonatomic, retain) MKMapView *mapView;
@property (nonatomic, retain) UIImageView *platformIcon;

// Util
@property (nonatomic, readonly) CGRect contentFrame;

@end

@implementation GiraffeGraffitiView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

const CGFloat kUserAvatarSideLength = 45.0;
- (BOOL)shouldShowUserAvatar
{
    return [self.graffiti.user.avatarUrl length] > 0;
}

const CGFloat kGraffitiImageSideLength = 200.0;
- (BOOL)shouldShowGraffitiImage
{
    return [self.graffiti.imageUrl length] > 0;
}

- (BOOL)isNative
{
    return !([self.graffiti.platform isEqualToString:@"instagram"] ||
             [self.graffiti.platform isEqualToString:@"twitter"] ||
             [self.graffiti.platform isEqualToString:@"facebook"]);
}

const CGFloat kUsernameFontSize = 18.0;
- (UIFont *)usernameFont
{
    return [UIFont boldSystemFontOfSize:kUsernameFontSize];
}

const CGFloat kDetailFontSize = 14.0;
- (UIFont *)detailFont
{
    return [UIFont italicSystemFontOfSize:kDetailFontSize];
}

const CGFloat kLikesFontSize = 14.0;
- (UIFont *)likesFont
{
    return [UIFont italicSystemFontOfSize:kDetailFontSize];
}

- (NSString *)distanceString
{
    CGFloat latitude = [LocationManager sharedInstance].latitude;
    CGFloat longitude = [LocationManager sharedInstance].longitude;
    CGFloat distance = [self.graffiti distanceFromLatitude:latitude longitude:longitude];
    
    if (distance >= 1) {
        return [NSString stringWithFormat:@"%.02f km", distance];
    } else {
        distance *= 1000;
        return [NSString stringWithFormat:@"%.02f m", distance];
    }
}

- (NSString *)detailText
{
    NSString *detailText = nil;
    if (self.graffiti.dateCreated && self.graffiti.latitude && self.graffiti.longitude) {
        
        detailText = [NSString stringWithFormat:@"Posted %@ away at %@", [self distanceString], [self.graffiti.dateCreated timeAgo]];
    } else if (self.graffiti.dateCreated) {
        detailText = [NSString stringWithFormat:@"Posted at %@", [self.graffiti.dateCreated timeAgo]];
        // TODO convert to timeago
    } else if (self.graffiti.latitude && self.graffiti.longitude) {
        detailText = [NSString stringWithFormat:@"Posted %@ away", [self distanceString]];
    }
    return detailText;
}

const CGFloat kGraffitiTextSize = 16.0;
- (UIFont *)graffitiTextFont
{
    return [UIFont systemFontOfSize:kGraffitiTextSize];
}

- (NSString *)likesText
{
    NSString *likesText = nil;
    if (self.graffiti.likes == 1) {
        likesText = [NSString stringWithFormat:@"%d Like", self.graffiti.likes];
    } else {
        likesText = [NSString stringWithFormat:@"%d Likes", self.graffiti.likes];
    }
    return likesText;
}

- (UIColor *)likeButtonTextColor
{
    return [UIColor colorWithRed:0.22 green:0.33 blue:0.53 alpha:1.0];
}

- (UIColor *)likeButtonLikedBackgroundColor
{
    return [UIColor colorWithRed:0 green:0 blue:1.0 alpha:1.0];
}

- (UIColor *)likeButtonHighlightedBackgroundColor
{
    return [UIColor colorWithRed:0.22 green:0.33 blue:0.53 alpha:1.0];
}

const CGFloat kPlatformIconSideLength = 32.0;

const CGFloat kMapViewHeight = 200.0;

const CGFloat kGraffitiViewPadding = 8.0;

- (void)layoutSubviews
{
    // User avatar
    if ([self shouldShowUserAvatar]) {
        if (!self.userAvatarImage) {
            self.userAvatarImage = [UIImageView new];
            self.userAvatarImage.backgroundColor = self.backgroundColor;
            self.userAvatarImage.frameSize = CGSizeMake(kUserAvatarSideLength, kUserAvatarSideLength);
            self.userAvatarImage.frameOrigin = CGPointMake(kGraffitiViewPadding, kGraffitiViewPadding);
            [self addSubview:self.userAvatarImage];
        }
        [self.userAvatarImage setImageWithURL:[NSURL URLWithString:self.graffiti.user.avatarUrl relativeToURL:[NSURL URLWithString:kBaseURL]] placeholderImage:[UIImage imageNamed:kAvatarImagePlaceholderFilename]];
    } else {
        [self.userAvatarImage removeFromSuperview];
        self.userAvatarImage = nil;
    }
    
    // User username button
    if (!self.usernameButton) {
        self.usernameButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [self.usernameButton addTarget:nil action:@selector(viewProfile:) forControlEvents:UIControlEventTouchUpInside];
        self.usernameButton.titleLabel.font = [self usernameFont];
        [self.usernameButton setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
        self.usernameButton.frameOriginY = kGraffitiViewPadding;
        [self addSubview:self.usernameButton];
    }
    [self.usernameButton setTitle:self.graffiti.user.username forState:UIControlStateNormal];
    [self.usernameButton sizeToFit];
    self.usernameButton.frameOriginX = self.userAvatarImage.rightEdge + kGraffitiViewPadding;
//    self.usernameButton.frame = self.usernameLabel.frame;
    if ([self isNative]) {
        self.usernameButton.enabled = YES;
    } else {
        self.usernameButton.enabled = NO;
    }
    
    // Detail label
    if (!self.detailLabel) {
        self.detailLabel = [UILabel new];
        self.detailLabel.font = [self detailFont];
        [self addSubview:self.detailLabel];
    }
    self.detailLabel.text = [self detailText];
    [self.detailLabel sizeToFit];
    self.detailLabel.frameOriginY = self.usernameButton.bottomEdge + kGraffitiViewPadding;
    self.detailLabel.frameOriginX = self.usernameButton.frameOriginX;
    
    // Graffiti Image
    if ([self shouldShowGraffitiImage]) {
        if (!self.graffitiImage) {
            self.graffitiImage = [UIImageView new];
            self.graffitiImage.backgroundColor = self.backgroundColor;
            self.graffitiImage.frameSize = CGSizeMake(kGraffitiImageSideLength, kGraffitiImageSideLength);
            self.graffitiImage.frameOrigin = CGPointMake(kGraffitiViewPadding, MAX(self.detailLabel.bottomEdge, self.userAvatarImage.bottomEdge) + kGraffitiViewPadding);
            [self addSubview:self.graffitiImage];
        }
        [self.graffitiImage setImageWithURL:[NSURL URLWithString:self.graffiti.imageUrl relativeToURL:[NSURL URLWithString:kBaseURL]] placeholderImage:[UIImage imageNamed:kAvatarImagePlaceholderFilename]];
    } else {
        [self.graffitiImage removeFromSuperview];
        self.graffitiImage = nil;
    }
    
    // Message label
    if (!self.messageLabel) {
        self.messageLabel = [UILabel new];
        self.messageLabel.font = [self graffitiTextFont];
        self.messageLabel.lineBreakMode = NSLineBreakByWordWrapping;
        self.messageLabel.numberOfLines = 0;
        [self addSubview:self.messageLabel];
    }
    self.messageLabel.text = self.graffiti.message;
    self.messageLabel.frameOriginX = kGraffitiViewPadding;
    self.messageLabel.frameOriginY = MAX(MAX(self.detailLabel.bottomEdge, self.userAvatarImage.bottomEdge), self.graffitiImage.bottomEdge) + kGraffitiViewPadding;
    self.messageLabel.frameSize = [self.graffiti.message sizeWithFont:[self graffitiTextFont] constrainedToSize:CGSizeMake(self.frameWidth - 2*kGraffitiViewPadding, CGFLOAT_MAX)];
    
    if ([self isNative]) {
        if (!self.likeButton) {
            self.likeButton = [UIButton buttonWithType:UIButtonTypeCustom];
            [self.likeButton addTarget:nil action:@selector(likeGraffiti:) forControlEvents:UIControlEventTouchUpInside];
            self.likeButton.titleLabel.font = [self likesFont];
            
            self.likeButton.layer.borderColor = [UIColor blackColor].CGColor;
            self.likeButton.layer.borderWidth = 0.5f;
            self.likeButton.layer.cornerRadius = 8.0f;
            self.likeButton.layer.masksToBounds = YES;
            
            [self addSubview:self.likeButton];
        }
        
        [self.likeButton setTitle:[self likesText] forState:UIControlStateNormal];
        if (!self.graffiti.isLiked) {
            [self.likeButton setTitleColor:[self likeButtonTextColor] forState:UIControlStateNormal];
            [self.likeButton setTitleColor:[UIColor whiteColor] forState:UIControlStateHighlighted];
            [self.likeButton setBackgroundImage:[UIImage imageWithColor:[UIColor whiteColor]] forState:UIControlStateNormal];
            [self.likeButton setBackgroundImage:[UIImage imageWithColor:[self likeButtonHighlightedBackgroundColor]] forState:UIControlStateHighlighted];
        } else {
            [self.likeButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
            [self.likeButton setTitleColor:[UIColor whiteColor] forState:UIControlStateHighlighted];
            [self.likeButton setBackgroundImage:[UIImage imageWithColor:[self likeButtonLikedBackgroundColor]] forState:UIControlStateNormal];
            [self.likeButton setBackgroundImage:[UIImage imageWithColor:[self likeButtonHighlightedBackgroundColor]] forState:UIControlStateHighlighted];
        }
        self.likeButton.frame = CGRectMake(kGraffitiViewPadding, self.messageLabel.bottomEdge + kGraffitiViewPadding, 100, [[self likesText] sizeWithFont:[self likesFont]].height);
    } else {
        [self.likeButton removeFromSuperview];
        self.likeButton = nil;
    }
    
    if (!self.platformIcon) {
        self.platformIcon = [UIImageView new];
        self.platformIcon.frameSize = CGSizeMake(kPlatformIconSideLength, kPlatformIconSideLength);
        self.platformIcon.rightEdge = self.rightEdge - kGraffitiViewPadding;
        self.platformIcon.frameOriginY = kGraffitiViewPadding;
        
        [self addSubview:self.platformIcon];
    }
    [self.platformIcon setImage:[UIImage imageNamed:[NSString stringWithFormat:@"%@.png", self.graffiti.platform]]];
    
    if (!self.mapView) {
        self.mapView = [MKMapView new];
        self.mapView.frame = CGRectMake(kGraffitiViewPadding, MAX(self.messageLabel.bottomEdge, self.likeButton.bottomEdge) + kGraffitiViewPadding, self.frameWidth - 2*kGraffitiViewPadding, kMapViewHeight);
        
        [self addSubview:self.mapView];
    }
    self.mapView.showsUserLocation = YES;
    CLLocationCoordinate2D coordinates = (CLLocationCoordinate2D){self.graffiti.latitude, self.graffiti.longitude};
    MKCoordinateRegion viewRegion = MKCoordinateRegionMakeWithDistance(coordinates, 500.0, 500.0);
    MKCoordinateRegion adjustedRegion = [self.mapView regionThatFits:viewRegion];  
    [self.mapView setRegion:adjustedRegion];
    
    // Add an annotation
    MKPointAnnotation *point = [[MKPointAnnotation alloc] init];
    point.coordinate = coordinates;
    point.subtitle = self.graffiti.message;
    point.title = self.graffiti.user.username;
    
    [self.mapView addAnnotation:point];
    
    self.contentSize = CGSizeMake(self.contentSize.width, self.mapView.bottomEdge + kGraffitiViewPadding);
}

@end
