//
//  GiraffeShareViewController.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/28/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "GiraffeShareViewController.h"

@interface GiraffeShareViewController ()

@property (weak, nonatomic) IBOutlet UITextView *message;
@property (weak, nonatomic) IBOutlet UIWebView *mapView;
@property (weak, nonatomic) IBOutlet UILabel *radiusDisplay;
@property (weak, nonatomic) IBOutlet UISlider *radiusSlider;
@property (weak, nonatomic) IBOutlet UIButton *postButton;

@property (strong, nonatomic) CLLocation *location;

@end

@implementation GiraffeShareViewController

@synthesize message = _message;
@synthesize mapView = _mapView;
@synthesize radiusDisplay = _radiusDisplay;
@synthesize radiusSlider = _radiusSlider;
@synthesize postButton = _postButton;

@synthesize locationManager = _locationManager;
@synthesize location = _location;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        locationManager = [[CLLocationManager alloc] init];
        locationManager.delegate = self;
        locationManager.distanceFilter = kCLDistanceFilterNone;
        locationManager.desiredAccuracy = kCLLocationAccuracyBest;
        [locationManager startUpdatingLocation];
    }
    return self;
}

- (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray *)locations {
    NSLog(@"updating!");
    self.location = [locations objectAtIndex:0];
}

- (IBAction)radiusChanged:(UISlider *)sender {
    self.radiusDisplay.text = [NSString stringWithFormat:@"%d", (int)sender.value];
}

- (IBAction)postGraffiti:(UIButton *)sender {
    NSLog(@"lat%f - lon%f", self.location.coordinate.latitude, self.location.coordinate.longitude);
    
    [HttpConnection graffitiNewPostConnection:self withParams:[[NSString stringWithFormat:@"abc%d", 1] dataUsingEncoding:NSUTF8StringEncoding]];
}


- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
