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
    
    NSString *urlString = [NSString stringWithFormat:kHeatmapUrlFormat, [LocationManager sharedInstance].latitude, [LocationManager sharedInstance].longitude];
    NSURLRequest *request = [[NSURLRequest alloc] initWithURL:[NSURL URLWithString:urlString]];
    [self.webView loadRequest:request];
}

@end
