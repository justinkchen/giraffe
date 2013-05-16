//
//  GraffitiCell.m
//  GiraffeiOS
//
//  Created by Kurtis Horimoto on 5/6/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <math.h>
#import "GraffitiCell.h"
#import "Graffiti.h"
#import "User.h"
#import "GiraffeClient.h"
#import "UIKit-Utility.h"
#import "UIImageView+AFNetworking.h"

NSString *const kGraffitiCellIdentifier = @"graffitiCell";

@interface GraffitiCell ()

@property (nonatomic, retain) UIImageView *userAvatarImage;
@property (nonatomic, retain) UILabel *usernameLabel;
@property (nonatomic, retain) UILabel *detailLabel;
@property (nonatomic, retain) UILabel *messageLabel;
@property (nonatomic, retain) UIImageView *graffitiImage; // will add later

@end

@implementation GraffitiCell

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
    }
    return self;
}

const CGFloat kUserAvatarSideLength = 45.0;
- (BOOL)shouldShowUserAvatar
{
    return [self.graffiti.user.avatarUrl length] > 0;
}

const CGFloat kUsernameFontSize = 18.0;
- (UIFont *)usernameFont
{
    return [UIFont helveticaNeueCondensedOfSize:kUsernameFontSize weight:UIFontWeightBold];
}

const CGFloat kDetailFontSize = 14.0;
- (UIFont *)detailFont
{
    return [UIFont helveticaNeueCondensedOfSize:kDetailFontSize weight:UIFontWeightLight];
}

- (NSString *)distanceString
{
    CGFloat latitude = 1;
    CGFloat longitude = 1;
    CGFloat earthRadius = 6371.0;
    CGFloat dLatRad = (self.graffiti.latitude - latitude) * M_PI / 180.0;
    CGFloat dLongRad = (self.graffiti.longitude - longitude) * M_PI / 180.0;
    CGFloat currentLatitudeRad = latitude * M_PI / 180.0;
    CGFloat graffitiLatRad = self.graffiti.latitude * M_PI / 180.0;
    
    CGFloat a = sinf(dLatRad / 2.0) * sinf(dLatRad / 2.0) +
                sinf(dLongRad / 2.0) * sinf(dLongRad / 2.0) *
                cosf(currentLatitudeRad) * cosf(graffitiLatRad);
    CGFloat c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    CGFloat distance = earthRadius * c;
    
    return [NSString stringWithFormat:@"%f km", distance];
}

- (NSString *)detailText
{
    NSString *detailText = nil;
    if (self.graffiti.dateCreated && self.graffiti.latitude && self.graffiti.longitude) {
        detailText = [NSString stringWithFormat:@"Posted %@ away at %@", [self distanceString], [self.graffiti.dateCreated description]];
    } else if (self.graffiti.dateCreated) {
        detailText = [NSString stringWithFormat:@"Posted at %@", [self.graffiti.dateCreated description]];
    } else if (self.graffiti.latitude && self.graffiti.longitude) {
        detailText = [NSString stringWithFormat:@"Posted %@ away", [self distanceString]];
    }
    return detailText;
}

const CGFloat kGraffitiTextSize = 16.0;
- (UIFont *)graffitiTextFont
{
    return [UIFont helveticaNeueCondensedOfSize:kGraffitiTextSize weight:UIFontWeightRegular];
}

const CGFloat kGraffitiCellPadding = 8.0;

- (void)layoutSubviews
{
    // User avatar
    if ([self shouldShowUserAvatar]) {
        if (!self.userAvatarImage) {
            NSLog(@"show image yo");
            self.userAvatarImage = [UIImageView new];
            self.userAvatarImage.backgroundColor = [UIColor orangeColor];
            self.userAvatarImage.frameSize = CGSizeMake(kUserAvatarSideLength, kUserAvatarSideLength);
            self.userAvatarImage.frameOrigin = CGPointMake(kGraffitiCellPadding, kGraffitiCellPadding);
            [self.userAvatarImage setImageWithURL:[NSURL URLWithString:self.graffiti.user.avatarUrl relativeToURL:[NSURL URLWithString:kBaseURL]] placeholderImage:[UIImage imageNamed:kAvatarImagePlaceholderFilename]];
            [self.contentView addSubview:self.userAvatarImage];
        }
    } else {
        [self.userAvatarImage removeFromSuperview];
        self.userAvatarImage = nil;
    }
    
    // User username label
    if (!self.usernameLabel) {
        self.usernameLabel = [UILabel new];
        self.usernameLabel.font = [self usernameFont];
        self.usernameLabel.frameOriginY = kGraffitiCellPadding;
        [self.contentView addSubview:self.usernameLabel];
    }
    self.usernameLabel.text = self.graffiti.user.username;
    [self.usernameLabel sizeToFit];
    self.usernameLabel.frameOriginX = self.userAvatarImage.rightEdge + kGraffitiCellPadding;
    
    // Detail label
    if (!self.detailLabel) {
        self.detailLabel = [UILabel new];
        self.detailLabel.font = [self detailFont];
        [self.contentView addSubview:self.detailLabel];
    }
    self.detailLabel.text = [self detailText];
    [self.detailLabel sizeToFit];
    self.detailLabel.frameOriginY = self.usernameLabel.bottomEdge + kGraffitiCellPadding;
    self.detailLabel.frameOriginX = self.usernameLabel.frameOriginX;
    
    // Text label
    if (!self.messageLabel) {
        self.messageLabel = [UILabel new];
        self.messageLabel.font = [self graffitiTextFont];
        [self.contentView addSubview:self.messageLabel];
    }
    self.messageLabel.text = self.graffiti.message;
    self.messageLabel.frameOriginX = kGraffitiCellPadding;
    self.messageLabel.frameOriginY = MAX(self.detailLabel.bottomEdge, self.userAvatarImage.bottomEdge) + kGraffitiCellPadding;
    self.messageLabel.frameSize = [self.graffiti.message sizeWithFont:[self graffitiTextFont] constrainedToSize:CGSizeMake(self.frameWidth, CGFLOAT_MAX)];
}

- (CGSize)sizeThatFits:(CGSize)size
{
    CGFloat height = kGraffitiCellPadding;
    
    if ([self shouldShowUserAvatar]) {
        // User avatar is taller than labels
        height += kUserAvatarSideLength;
    } else {
        // User name label
        height += [self.graffiti.user.username sizeWithFont:[self usernameFont]].height;
        
        height += kGraffitiCellPadding;
        
        // Metadata
        height += [[self detailText] sizeWithFont:[self detailFont]].height;
        
        height += kGraffitiCellPadding;
    }
    
    // Add height for text
    height += [self.graffiti.message sizeWithFont:[self graffitiTextFont] constrainedToSize:CGSizeMake(size.width, CGFLOAT_MAX)].height;
    height += 2 * kGraffitiCellPadding;
    
    size.height = height;
    
    return size;
}

@end
