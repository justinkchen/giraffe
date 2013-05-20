//
//  GiraffeSecondViewController.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/24/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "GiraffeMapViewController.h"
#import "LocationManager.h"

@interface GiraffeMapViewController () <UIWebViewDelegate>

@property (nonatomic, retain) UIWebView *webView;

@property (nonatomic, assign) float latitude;
@property (nonatomic, assign) float longitude;

@end

@implementation GiraffeMapViewController

#pragma mark - View Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.webView = [[UIWebView alloc] initWithFrame:self.view.bounds];
    self.webView.delegate = self;
    [self.view addSubview:self.webView];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

NSString *const kHeatmapUrlFormat = @"http://ec2-54-243-69-6.compute-1.amazonaws.com/graffitimap.html?latitude=%f&longitude=%f";

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    [self reloadMapView];
}

- (IBAction)refreshButtonTapped:(UIBarButtonItem *)sender {
    [self reloadMapView];
}

- (void)reloadMapView
{
    float newLatitude = [LocationManager sharedInstance].latitude;
    float newLongitude = [LocationManager sharedInstance].longitude;
    
    if (newLatitude != self.latitude ||
        newLongitude != self.longitude) {
        NSString *urlString = [NSString stringWithFormat:kHeatmapUrlFormat, [LocationManager sharedInstance].latitude, [LocationManager sharedInstance].longitude];
        NSURLRequest *request = [[NSURLRequest alloc] initWithURL:[NSURL URLWithString:urlString]];
        [self.webView loadRequest:request];
        
        self.latitude = newLatitude;
        self.longitude = newLongitude;
    }
}

@end
