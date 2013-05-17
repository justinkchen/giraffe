//
//  GiraffeShareViewController.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/28/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "GiraffeShareViewController.h"
#import "GiraffeShareView.h"
#import "UserLoginController.h"
#import "UIKit-Utility.h"

@interface GiraffeShareViewController () <GiraffeShareViewDelegate>

@property (nonatomic, retain) GiraffeShareView *shareView;

@end

@implementation GiraffeShareViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.shareView = [GiraffeShareView new];
    self.shareView.backgroundColor = [UIColor whiteColor];
    self.shareView.frame = self.view.bounds;
    self.shareView.delegate = self;
    [self.view addSubview:self.shareView];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    
    [self.shareView updateMapView];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - GiraffeShareViewDelegate

- (void)postButtonTappedWithGraffiti:(Graffiti *)graffiti
{
    // Post graffiti to server
    [[GiraffeClient sharedClient] beginGraffitiNewPostWithGraffiti:graffiti success:^(AFHTTPRequestOperation *operation, id responseObject) {
        // display responseObject
        // redirect to nearby page if successful?
        NSLog(@"successful post to server!");
        [[self.view.subviews objectAtIndex:0] resetView];
        
        // Navigate to the 1st tab
        self.tabBarController.selectedViewController = [self.tabBarController.viewControllers objectAtIndex:0];
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        // display error message
    }];
}

- (void)showUserLogin
{
    // Show user login screen
    UserLoginController *loginController = [UserLoginController new];
    UINavigationController *navController = [[UINavigationController alloc] initWithRootViewController:loginController];
    navController.modalPresentationStyle = UIModalPresentationFullScreen;
    navController.modalTransitionStyle = UIModalTransitionStyleCoverVertical;
    [self presentViewController:navController animated:YES completion:nil];
}

@end
