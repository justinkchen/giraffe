//
//  UIKit-Utility.h
//  GiraffeiOS
//
//  Created by Kurtis Horimoto on 5/6/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define centerOffset(smaller, bigger) ((bigger - smaller) / 2.0)

@interface UIView (Utility)

@property (nonatomic) CGSize frameSize;
@property (nonatomic) CGPoint frameOrigin;
@property (nonatomic) CGFloat frameHeight;
@property (nonatomic) CGFloat frameWidth;
@property (nonatomic) CGFloat frameOriginX;
@property (nonatomic) CGFloat frameOriginY;
@property (nonatomic) CGFloat rightEdge;
@property (nonatomic) CGFloat bottomEdge;

- (void)animateLayoutWithDuration:(NSTimeInterval)duration;
- (void)centerHorizontally;
- (void)centerHorizontallyWithView:(UIView *)otherView;
- (void)centerVertically;
- (void)centerVerticallyWithView:(UIView *)otherView;

@end

@interface UIFont (Utility)

typedef enum {
    UIFontWeightThin,
    UIFontWeightLight,
    UIFontWeightRegular,
    UIFontWeightMedium,
    UIFontWeightBold
} UIFontWeight;

+ (UIFont *)helveticaNeueCondensedOfSize:(CGFloat)size weight:(UIFontWeight)weight;

@end
