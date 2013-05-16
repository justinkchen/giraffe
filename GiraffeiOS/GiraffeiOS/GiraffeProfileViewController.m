//
//  GiraffeProfileViewController.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/28/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "GiraffeProfileViewController.h"
#import "UIImageView+AFNetworking.h"
#import "GiraffeClient.h"
#import "Graffiti.h"
#import "GraffitiCell.h"
#import "User.h"
#import "Foundation-Utility.h"
#import "UIKit-Utility.h"

@interface GiraffeProfileViewController ()

@property (weak, nonatomic) IBOutlet UILabel *usernameLabel;
@property (weak, nonatomic) IBOutlet UIImageView *avatarView;
@property (weak, nonatomic) IBOutlet UILabel *graffitiCountLabel;
@property (weak, nonatomic) IBOutlet UILabel *likesCountLabel;
@property (weak, nonatomic) IBOutlet UILabel *badgesCountLabel;
@property (weak, nonatomic) IBOutlet UITableView *userGraffitiTableView;

@property (nonatomic, strong) NSArray *graffiti;

@end

@implementation GiraffeProfileViewController

@synthesize usernameLabel = _usernameLabel;
@synthesize avatarView = _avatarView;
@synthesize graffitiCountLabel = _graffitiCountLabel;
@synthesize likesCountLabel = _likesCountLabel;
@synthesize badgesCountLabel = _badgesCountLabel;
@synthesize userGraffitiTableView = _userGraffitiTableView;
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
    
    [[GiraffeClient sharedClient] beginUserGraffitiGetWithId:[User currentUser].identifier success:^(AFHTTPRequestOperation *operation, id responseObject) {
        NSLog(@"yay %@", responseObject);
        [self graffitiRequestFinishedWithDictionary:[responseObject ifIsKindOfClass:[NSDictionary class]]];
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        // print error
    }];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Accessors

- (void)setGraffiti:(NSMutableArray *)graffiti
{
    if (![_graffiti isEqualToArray:graffiti]) {
        _graffiti = graffiti;
        [self.userGraffitiTableView reloadData];
    }
}

#pragma mark - Utility

- (void)graffitiRequestFinishedWithDictionary:(NSDictionary *)dictionary
{
    NSArray *graffitiDicts = [dictionary objectForKey:kParamNameGraffiti];
    if ([graffitiDicts count] > 0) {
        NSMutableArray *newGraffiti = [NSMutableArray new];
        for (NSDictionary *graffitiDict in graffitiDicts) {
            Graffiti *graffiti = [[Graffiti alloc] initWithDictionary:graffitiDict];
            [newGraffiti addObject:graffiti];
        }
        self.graffiti = newGraffiti;
    }
}

#pragma mark - UITableViewDelegate

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return [[self tableView:tableView cellForRowAtIndexPath:indexPath] sizeThatFits:tableView.frameSize].height;
}

#pragma mark - UITableViewDatasource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [self.graffiti count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    GraffitiCell *cell = [[tableView dequeueReusableCellWithIdentifier:kGraffitiCellIdentifier] ifIsKindOfClass:[GraffitiCell class]];
    if (!cell) {
        cell = [[GraffitiCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kGraffitiCellIdentifier];
    }
    cell.graffiti = [self.graffiti objectAtIndex:indexPath.row];
    return cell;
}

@end
