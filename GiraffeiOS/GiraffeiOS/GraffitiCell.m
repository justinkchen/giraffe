//
//  GraffitiCell.m
//  GiraffeiOS
//
//  Created by Kurtis Horimoto on 5/6/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "GraffitiCell.h"
#import "Graffiti.h"
#import "User.h"
#import "UIKit-Utility.h"
#import <Foundation/Foundation.h>
#import <math.h>

@interface GraffitiCell ()

@property (nonatomic, retain) UIImageView *authorAvatarImage;
@property (nonatomic, retain) UILabel *authorNameLabel;
@property (nonatomic, retain) UILabel *detailLabel;
@property (nonatomic, retain) UILabel *textLabel;
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

const CGFloat kAuthorAvatarSideLength = 45.0;
- (BOOL)shouldShowAuthorAvatar
{
    return [self.graffiti.imageUrl length] > 0;
}

const CGFloat kAuthorNameFontSize = 18.0;
- (UIFont *)authorNameFont
{
    return [UIFont helveticaNeueCondensedOfSize:kAuthorNameFontSize weight:UIFontWeightBold];
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
    CGFloat dLatRad = (self.graffiti.latitute - latitude) * M_PI / 180.0;
    CGFloat dLongRad = (self.graffiti.longitude - longitude) * M_PI / 180.0;
    CGFloat currentLatitudeRad = latitude * M_PI / 180.0;
    CGFloat graffitiLatRad = self.graffiti.latitute * M_PI / 180.0;
    
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
    if (self.graffiti.dateCreated && self.graffiti.latitute && self.graffiti.longitude) {
        detailText = [NSString stringWithFormat:@"Posted %@ away at %@", [self distanceString], [self.graffiti.dateCreated description]];
    } else if (self.graffiti.dateCreated) {
        detailText = [NSString stringWithFormat:@"Posted at %@", [self.graffiti.dateCreated description]];
    } else if (self.graffiti.latitute && self.graffiti.longitude) {
        detailText = [NSString stringWithFormat:@"Posted %@ away", [self distanceString]];
    }
    return detailText;
}

const CGFloat kGraffitiTextSize = 16.0;
- (UIFont *)graffitiTextFont
{
    return [UIFont helveticaNeueCondensedOfSize:kGraffitiTextSize weight:UIFontWeightRegular];
}

const CGFloat kPadding = 8.0;

- (void)layoutSubviews
{
    // Author avatar
    if ([self shouldShowAuthorAvatar]) {
        if (!self.authorAvatarImage) {
            self.authorAvatarImage = [UIImageView new];
            self.authorAvatarImage.backgroundColor = [UIColor orangeColor];
            self.authorAvatarImage.frameSize = CGSizeMake(kAuthorAvatarSideLength, kAuthorAvatarSideLength);
            self.authorAvatarImage.frameOrigin = CGPointMake(kPadding, kPadding);
            [self.contentView addSubview:self.authorAvatarImage];
        }
    } else {
        [self.authorAvatarImage removeFromSuperview];
        self.authorAvatarImage = nil;
    }
    
    // Author name label
    if (!self.authorNameLabel) {
        self.authorNameLabel = [UILabel new];
        self.authorNameLabel.font = [self authorNameFont];
        self.authorNameLabel.frameOriginY = kPadding;
        [self.contentView addSubview:self.authorNameLabel];
    }
    self.authorNameLabel.text = self.graffiti.author.username;
    [self.authorNameLabel sizeToFit];
    self.authorNameLabel.frameOriginX = self.authorAvatarImage.rightEdge + kPadding;
    
    // Detail label
    if (!self.detailLabel) {
        self.detailLabel = [UILabel new];
        self.detailLabel.font = [self detailFont];
        [self.contentView addSubview:self.detailLabel];
    }
    self.detailLabel.text = [self detailText];
    [self.detailLabel sizeToFit];
    self.detailLabel.frameOriginY = self.authorNameLabel.bottomEdge + kPadding;
    self.detailLabel.frameOriginX = self.authorNameLabel.frameOriginX;
    
    // Text label
    if (!self.textLabel) {
        self.textLabel = [UILabel new];
        self.textLabel.font = [self graffitiTextFont];
        [self.contentView addSubview:self.textLabel];
    }
    self.textLabel.text = self.graffiti.text;
    self.textLabel.frameOriginX = kPadding;
    self.textLabel.frameOriginY = MAX(self.detailLabel.bottomEdge, self.authorAvatarImage.bottomEdge) + kPadding;
    self.textLabel.frameSize = [self.graffiti.text sizeWithFont:[self graffitiTextFont] constrainedToSize:CGSizeMake(self.frameWidth, CGFLOAT_MAX)];
}

- (CGSize)sizeThatFits:(CGSize)size
{
    CGFloat height = kPadding;
    if ([self shouldShowAuthorAvatar]) {
        // Author avatar is taller than labels
        height += kAuthorAvatarSideLength;
    } else {
        // Author name label
        height += [self.graffiti.author.username sizeWithFont:[self authorNameFont]].height;
        
        height += kPadding;
        
        // Metadata
        height += [[self detailText] sizeWithFont:[self detailFont]].height;
        
        height += kPadding;
    }
    
    // Add height for text
    height += [self.graffiti.text sizeWithFont:[self graffitiTextFont] constrainedToSize:CGSizeMake(size.width, CGFLOAT_MAX)].height;
    height += 2 * kPadding;
    
    return size;
}

@end
