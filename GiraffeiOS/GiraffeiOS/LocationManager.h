//
//  LocationManager.h
//  GiraffeiOS
//
//  Created by Kurtis Horimoto on 5/8/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@protocol LocationManagerDelegate;

@interface LocationManager : NSObject

@property (nonatomic, retain) NSDate *timestamp;
@property (nonatomic, assign) float latitude;
@property (nonatomic, assign) float longitude;

@property (nonatomic, retain) id<LocationManagerDelegate> delegate;
@property (nonatomic, assign) BOOL waitingForLocation;

+ (LocationManager *)sharedInstance;

@end

@protocol LocationManagerDelegate <NSObject>

- (void)locationFound;

@end