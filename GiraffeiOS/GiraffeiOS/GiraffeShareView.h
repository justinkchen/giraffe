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
- (void)resetView;

@property (nonatomic, readonly) Graffiti *graffitiFromInput;

@end

@protocol GiraffeShareViewDelegate <NSObject>

- (void)showUserLogin;

@end