//
//  UIKit-Utility.m
//  GiraffeiOS
//
//  Created by Kurtis Horimoto on 5/6/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "UIKit-Utility.h"


@implementation UIView (Utility)

- (CGSize)frameSize
{
    return self.frame.size;
}

- (void)setFrameSize:(CGSize)frameSize
{
    CGRect rect = self.frame;
    rect.size = frameSize;
    self.frame = rect;
}

- (CGPoint)frameOrigin
{
    return self.frame.origin;
}

- (void)setFrameOrigin:(CGPoint)frameOrigin
{
    CGRect rect = self.frame;
    rect.origin = frameOrigin;
    self.frame = rect;
}

- (CGFloat)frameHeight
{
    return self.frame.size.height;
}

- (void)setFrameHeight:(CGFloat)frameHeight
{
    CGRect rect = self.frame;
    rect.size.height = frameHeight;
    self.frame = rect;
}

- (CGFloat)frameWidth
{
    return self.frame.size.width;
}

- (void)setFrameWidth:(CGFloat)frameWidth
{
    CGRect rect = self.frame;
    rect.size.width = frameWidth;
    self.frame = rect;
}

- (CGFloat)frameOriginX
{
    return self.frame.origin.x;
}

- (void)setFrameOriginX:(CGFloat)frameOriginX
{
    CGRect rect = self.frame;
    rect.origin.x = frameOriginX;
    self.frame = rect;
}

- (CGFloat)frameOriginY
{
    return self.frame.origin.y;
}

- (void)setFrameOriginY:(CGFloat)frameOriginY
{
    CGRect rect = self.frame;
    rect.origin.y = frameOriginY;
    self.frame = rect;
}

- (CGFloat)rightEdge
{
    return CGRectGetMaxX(self.frame);
}

- (void)setRightEdge:(CGFloat)rightEdge
{
    CGRect rect = self.frame;
    rect.origin.x = rightEdge - rect.size.width;
    self.frame = rect;
}

- (CGFloat)bottomEdge
{
    return CGRectGetMaxY(self.frame);
}

- (void)setBottomEdge:(CGFloat)bottomEdge
{
    CGRect rect = self.frame;
    rect.origin.y = bottomEdge - rect.size.height;
    self.frame = rect;
}

- (void)animateLayoutWithDuration:(NSTimeInterval)duration
{
    [UIView animateWithDuration:duration animations:^{
        [self setNeedsLayout];
        [self layoutIfNeeded];
    }];
}

- (void)centerHorizontally
{
    self.frameOriginX = floorf(centerOffset(self.frameWidth, self.superview.frameWidth));
}

- (void)centerHorizontallyWithView:(UIView *)otherView
{
    self.frameOriginX = floorf(otherView.frameOriginX + centerOffset(self.frameWidth, otherView.frameWidth));
}

- (void)centerVertically
{
    self.frameOriginY = floorf(centerOffset(self.frameHeight, self.superview.frameHeight));
}

- (void)centerVerticallyWithView:(UIView *)otherView
{
    self.frameOriginY = floorf(otherView.frameOriginY + centerOffset(self.frameHeight, otherView.frameHeight));
}

@end


@implementation UIFont (Utility)

NSString *const helveticaNeueCondensedThin = @"HelveticaNeueLTW1G-ThCn";
NSString *const helveticaNeueCondensedLight = @"HelveticaNeueLTW1G-LtCn";
NSString *const helveticaNeueCondensedRegular = @"HelveticaNeueLTW1G-Cn";
NSString *const helveticaNeueCondensedMedium = @"HelveticaNeueLTW1G-MdCn";
NSString *const helveticaNeueCondensedBold = @"HelveticaNeueLTW1G-BdCn";

+ (UIFont *)helveticaNeueCondensedOfSize:(CGFloat)size weight:(UIFontWeight)weight
{
    NSString *fontName = nil;
    switch (weight) {
        case UIFontWeightThin:
            fontName = helveticaNeueCondensedThin;
            break;
        case UIFontWeightLight:
            fontName = helveticaNeueCondensedLight;
            break;
        case UIFontWeightMedium:
            fontName = helveticaNeueCondensedMedium;
            break;
        case UIFontWeightBold:
            fontName = helveticaNeueCondensedBold;
            break;
        case UIFontWeightRegular:
        default:
            fontName = helveticaNeueCondensedRegular;
            break;
    }
    return [UIFont fontWithName:fontName size:size];
}

@end

@implementation UIColor (Utility)

+ (UIColor *)linkTextColor
{
    return [UIColor colorWithRed:59.0/255.0 green:185.0/255.0 blue:1.0 alpha:1.0];
}

@end
