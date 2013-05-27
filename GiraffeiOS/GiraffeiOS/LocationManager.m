//
//  LocationManager.m
//  GiraffeiOS
//
//  Created by Kurtis Horimoto on 5/8/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "LocationManager.h"

@interface LocationManager () <CLLocationManagerDelegate>

@property (nonatomic, retain) CLLocationManager *manager;

@end

@implementation LocationManager

- (id)init
{
    self = [super init];
    if (self) {
        self.manager = [[CLLocationManager alloc] init];
        self.manager.delegate = self;
        self.manager.desiredAccuracy = kCLLocationAccuracyBest;
        self.manager.distanceFilter = kCLDistanceFilterNone;
        [self.manager startUpdatingLocation];
        
        self.waitingForLocation = YES;
    }
    return self;
}

+ (LocationManager *)sharedInstance
{
    // Create Singleton
    static LocationManager *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [LocationManager new];
    });
    
    return sharedInstance;
}

- (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray *)locations
{
    CLLocation *location = [locations lastObject];
    CLLocationCoordinate2D coords = location.coordinate;
    
    self.timestamp = location.timestamp;
    self.latitude = coords.latitude;
    self.longitude = coords.longitude;
    
    if (self.waitingForLocation && !(self.latitude == 0 && self.longitude == 0)) {
        self.waitingForLocation = NO;
        [self.delegate locationFound];
    }
}

@end
