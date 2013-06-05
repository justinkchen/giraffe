//
//  GiraffeGraffitiView.h
//  GiraffeiOS
//
//  Created by Bryan Cheng on 6/4/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Graffiti.h"

//@protocol GraffitiViewDelegate;

@interface GiraffeGraffitiView : UIScrollView

@property (nonatomic, weak) id<UIScrollViewDelegate> delegate;
@property (nonatomic, assign) Graffiti *graffiti;

@end

//@protocol GraffitiViewDelegate <UIScrollViewDelegate>

//@end