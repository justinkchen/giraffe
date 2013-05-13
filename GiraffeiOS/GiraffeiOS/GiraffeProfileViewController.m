//
//  GiraffeProfileViewController.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/28/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "GiraffeProfileViewController.h"
#import "UIImageView+AFNetworking.h"

@interface GiraffeProfileViewController ()

@end

@implementation GiraffeProfileViewController

@synthesize avatar = _avatar;

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
    
    //[self.avatar setImageWithURL:[NSURL URLWithString:@"http://www.thegiraffeapp.com/images/user/d6a49c99211136c42557c3ae966ae155c929c71b97a269531af541bdb84a6edc.jpg"] placeholderImage:[UIImage imageNamed:@"first.png"]];
    [self.avatar setImageWithURL:[NSURL URLWithString:@"http://www.thegiraffeapp.com/images/user/d6a49c99211136c42557c3ae966ae155c929c71b97a269531af541bdb84a6edc.jpg"]];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
