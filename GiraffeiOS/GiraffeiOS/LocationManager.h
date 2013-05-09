//
//  LocationManager.h
//  GiraffeiOS
//
//  Created by Kurtis Horimoto on 5/8/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@interface LocationManager : NSObject

@property (nonatomic, assign) float latitude;
@property (nonatomic, assign) float longitude;

+ (LocationManager *)sharedInstance;

@end
