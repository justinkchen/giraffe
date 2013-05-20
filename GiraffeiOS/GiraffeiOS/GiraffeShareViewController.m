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

@interface GiraffeShareViewController () <GiraffeShareViewDelegate, UINavigationControllerDelegate, UIActionSheetDelegate, UIImagePickerControllerDelegate>

@property (nonatomic, retain) GiraffeShareView *shareView;

@property (nonatomic, retain) UIImage *graffitiImage;

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
    
    self.graffitiImage = nil;
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
    NSLog(@"graffiti image %@", self.graffitiImage);
    [[GiraffeClient sharedClient] beginGraffitiNewPostWithGraffiti:graffiti image:self.graffitiImage success:^(AFHTTPRequestOperation *operation, id responseObject) {
        // display responseObject
        // redirect to nearby page if successful?
        NSLog(@"successful post to server!");
        
        self.graffitiImage = nil;
        [[self.view.subviews objectAtIndex:0] resetView];
        
        // Navigate to the 1st tab
        self.tabBarController.selectedViewController = [self.tabBarController.viewControllers objectAtIndex:0];
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        // display error message
    }];
}

- (void)imageButtonTapped
{
    UIActionSheet *actionSheet = nil;
    if ([UIImagePickerController isCameraDeviceAvailable:UIImagePickerControllerCameraDeviceRear]) {
        actionSheet = [[UIActionSheet alloc] initWithTitle:nil
                                                  delegate:self
                                         cancelButtonTitle:@"Cancel"
                                    destructiveButtonTitle:nil
                                         otherButtonTitles:@"Take Photo", @"Choose Existing", nil];
    } else {
        actionSheet = [[UIActionSheet alloc] initWithTitle:nil
                                                  delegate:self
                                         cancelButtonTitle:@"Cancel"
                                    destructiveButtonTitle:nil
                                         otherButtonTitles:@"Choose Existing", nil];
    }
    [actionSheet showInView:self.parentViewController.view];
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

#pragma mark - Action sheet

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    NSString *buttonTitle = [actionSheet buttonTitleAtIndex:buttonIndex];
    if (![buttonTitle isEqualToString:@"Cancel"]) {
        UIImagePickerController *imagePickerController = [UIImagePickerController new];
        imagePickerController.delegate = self;
        if ([buttonTitle isEqualToString:@"Take Photo"]) {
            imagePickerController.sourceType = UIImagePickerControllerSourceTypeCamera;
        } else if ([buttonTitle isEqualToString:@"Choose Existing"]) {
            imagePickerController.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
        }
        [self presentViewController:imagePickerController animated:YES completion:nil];
    }
}

#pragma mark - UIImagePickerControllerDelegate

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    NSString *mediaType = [info objectForKey:UIImagePickerControllerMediaType];
    
    if ([mediaType isEqualToString:@"public.image"]) {
        self.graffitiImage = [info objectForKey:UIImagePickerControllerOriginalImage];
        
        // TODO mark image included
        NSLog(@"image attached %@", self.graffitiImage);
        
        [picker dismissViewControllerAnimated:YES completion:^{
            // do nothing
        }];
    }
}

@end
