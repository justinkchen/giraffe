//
//  GiraffeGraffitiViewController.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 6/4/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "GiraffeGraffitiViewController.h"
#import "GiraffeGraffitiView.h"
#import "UIKit-Utility.h"
#import <MapKit/MapKit.h>

@interface GiraffeGraffitiViewController () <UIScrollViewDelegate>

@property (nonatomic, retain) GiraffeGraffitiView *graffitiView;

@end

@implementation GiraffeGraffitiViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
    self.view.frameHeight = self.navigationController.view.frame.size.height - self.tabBarController.tabBar.frame.size.height;
    
    self.graffitiView = [GiraffeGraffitiView new];
    self.graffitiView.backgroundColor = [UIColor whiteColor];
    self.graffitiView.frame = self.view.bounds;
    self.graffitiView.delegate = self;
    self.graffitiView.graffiti = self.graffiti;
    
    [self.view addSubview:self.graffitiView];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}



@end
