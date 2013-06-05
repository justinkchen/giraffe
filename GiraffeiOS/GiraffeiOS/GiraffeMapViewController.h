//
//  GiraffeSecondViewController.h
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/24/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol MapViewDataSource;

@interface GiraffeMapViewController : UIViewController

@property (nonatomic, assign) id<MapViewDataSource> dataSource;

@end

@protocol MapViewDataSource <NSObject>

- (NSArray *)getGraffitiList;

@end
