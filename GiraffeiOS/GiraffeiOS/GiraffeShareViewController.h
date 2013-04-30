//
//  GiraffeShareViewController.h
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/28/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

#import "HttpConnection.h"

@interface GiraffeShareViewController : UIViewController <CLLocationManagerDelegate, NSURLConnectionDelegate> {
    CLLocationManager *locationManager;
}
@property (retain, nonatomic) CLLocationManager *locationManager;

@end
