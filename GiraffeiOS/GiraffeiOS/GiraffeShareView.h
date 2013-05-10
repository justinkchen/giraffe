//
//  GiraffeShareView.h
//  GiraffeiOS
//
//  Created by Kurtis Horimoto on 5/8/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import <UIKit/UIKit.h>

@class Graffiti;
@protocol GiraffeShareViewDelegate;

@interface GiraffeShareView : UIView

@property (nonatomic, assign) id<GiraffeShareViewDelegate> delegate;

- (void)updateMapView;

@end

@protocol GiraffeShareViewDelegate <NSObject>

- (void)postButtonTappedWithGraffiti:(Graffiti *)graffiti;
- (void)showUserLogin;

@end