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

@property (weak, nonatomic) IBOutlet UILabel *usernameLabel;
@property (weak, nonatomic) IBOutlet UIImageView *avatarView;
@property (weak, nonatomic) IBOutlet UILabel *graffitiCountLabel;
@property (weak, nonatomic) IBOutlet UILabel *likesCountLabel;
@property (weak, nonatomic) IBOutlet UILabel *badgesCountLabel;
@property (weak, nonatomic) IBOutlet UITableView *userGraffitiTable;

@property (nonatomic, strong) NSArray *graffiti;

@end

@implementation GiraffeProfileViewController

@synthesize usernameLabel = _usernameLabel;
@synthesize avatarView = _avatarView;
@synthesize graffitiCountLabel = _graffitiCountLabel;
@synthesize likesCountLabel = _likesCountLabel;
@synthesize badgesCountLabel = _badgesCountLabel;
@synthesize userGraffitiTable = _userGraffitiTable;
@synthesize graffiti = _graffiti;

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
    [self.avatarView setImageWithURL:[NSURL URLWithString:@"http://www.thegiraffeapp.com/images/user/d6a49c99211136c42557c3ae966ae155c929c71b97a269531af541bdb84a6edc.jpg"]];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark UITableViewDelegateMethods

//-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
//    
//}

#pragma mark UITableViewDataSourceMethods

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [self.graffiti count];
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"UserGraffitiCell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier forIndexPath:indexPath];
    cell.textLabel.text = @"yay";
    return cell;
}

@end
