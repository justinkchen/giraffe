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

@implementation UIColor (Utility)

+ (UIColor *)linkTextColor
{
    return [UIColor colorWithRed:59.0/255.0 green:185.0/255.0 blue:1.0 alpha:1.0];
}

@end

@implementation UIImage (Utility)

+ (UIImage *)imageWithColor:(UIColor *)color
{
    CGRect rect = CGRectMake(0, 0, 1, 1);
    UIGraphicsBeginImageContext(rect.size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetFillColorWithColor(context, [color CGColor]);
    //  [[UIColor colorWithRed:222./255 green:227./255 blue: 229./255 alpha:1] CGColor]) ;
    CGContextFillRect(context, rect);
    UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return image;
}

-(UIImage*)scaleToSize:(CGSize)size
{
    // Create a bitmap graphics context
    // This will also set it as the current context
    UIGraphicsBeginImageContext(size);
    
    // Draw the scaled image in the current context
    [self drawInRect:CGRectMake(0, 0, size.width, size.height)];
    
    // Create a new image from current context
    UIImage* scaledImage = UIGraphicsGetImageFromCurrentImageContext();
    
    // Pop the current context from the stack
    UIGraphicsEndImageContext();
    
    // Return our new scaled image
    return scaledImage;
}

@end