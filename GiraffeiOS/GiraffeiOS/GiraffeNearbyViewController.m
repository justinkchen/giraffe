//
//  GiraffeFirstViewController.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/24/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "GiraffeNearbyViewController.h"
#import "GiraffeProfileViewController.h"
#import "Graffiti.h"
#import "InstagramGraffiti.h"
#import "TwitterGraffiti.h"
#import "User.h"
#import "GraffitiCell.h"
#import "GiraffeClient.h"
#import "InstagramClient.h"
#import "TwitterClient.h"
#import "LocationManager.h"
#import "RankingAlgorithm.h"
#import "UIKit-Utility.h"
#import "Toast+UIView.h"
#import "Foundation-Utility.h"

@interface GiraffeNearbyViewController () <UITableViewDataSource, UITableViewDelegate>

@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (nonatomic, retain) NSArray *graffiti;

@end

@implementation GiraffeNearbyViewController

#pragma mark - View Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    NSLog(@"location %f %f", [LocationManager sharedInstance].latitude, [LocationManager sharedInstance].longitude);
    
    [self requestGraffitiFromServer];
}

#pragma mark - Accessors

- (void)setGraffiti:(NSMutableArray *)graffiti
{
    if (![_graffiti isEqualToArray:graffiti]) {
        _graffiti = graffiti;
        [self.tableView reloadData];
    }
}

#pragma mark - Utility

- (void)requestGraffitiFromServer
{
    [self.view makeToastActivity];
    
    CGFloat latitude = [LocationManager sharedInstance].latitude;
    CGFloat longitude = [LocationManager sharedInstance].longitude;
    
    // Kick off load request
    [[GiraffeClient sharedClient] beginGraffitiNearbyGetWithLatitude:latitude
                                                           longitude:longitude success:^(AFHTTPRequestOperation *operation, id responseObject) {
                                                               [self.view hideToastActivity];
                                                               NSLog(@"got response %@", responseObject);
                                                               
                                                               [self graffitiRequestFinishedWithDictionary:[responseObject ifIsKindOfClass:[NSDictionary class]]];
                                                           } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
                                                               [self.view hideToastActivity];
                                                               [self.view makeToast:[error localizedDescription] duration:1.5f position:@"top"];
                                                           }];
    if (latitude && longitude) {
        [self instagramRequestBeginWithLatitude:latitude longitude:longitude];
        
        [[TwitterClient sharedClient] beginTwitterNearbyGetWithLatitude:latitude
                                                              longitude:longitude
                                                                success:^(AFHTTPRequestOperation *operation, id responseObject) {
                                                                    [self.view hideToastActivity];
                                                                    NSLog(@"got twitter response %@", responseObject);
                                                                    
                                                                    [self twitterRequestFinishedWithDictionary:[responseObject ifIsKindOfClass:[NSDictionary class]]];
                                                                }
                                                                failure:^(AFHTTPRequestOperation *operation, NSError *error) {
                                                                    [self.view hideToastActivity];
                                                                    [self.view makeToast:[error localizedDescription] duration:1.5f position:@"top"];
                                                                }];
    }
}

- (void)graffitiRequestFinishedWithDictionary:(NSDictionary *)dictionary
{
    NSArray *graffitiDicts = [dictionary objectForKey:kParamNameGraffiti];
    NSMutableArray *newGraffiti = [NSMutableArray new];
    for (NSDictionary *graffitiDict in graffitiDicts) {
        Graffiti *graffiti = [[Graffiti alloc] initWithDictionary:graffitiDict];
        [newGraffiti addObject:graffiti];
    }
    self.graffiti = newGraffiti;
}

- (void)instagramRequestBeginWithLatitude:(CGFloat)latitude
                                longitude:(CGFloat)longitude
{
    [[InstagramClient sharedClient] beginInstagramNearbyGetWithLatitude:latitude
                                                              longitude:longitude
                                                                success:^(AFHTTPRequestOperation *operation, id responseObject) {
                                                                    [self.view hideToastActivity];
                                                                    NSLog(@"got instagram response %@", responseObject);
                                                                    
                                                                    [self instagramRequestFinishedWithDictionary:[responseObject ifIsKindOfClass:[NSDictionary class]]];
                                                                }
                                                                failure:^(AFHTTPRequestOperation *operation, NSError *error) {
                                                                    NSLog(@"retrying to connect w/ instagram");
                                                                    [self instagramRequestBeginWithLatitude:latitude longitude:longitude];
//                                                                    [self.view hideToastActivity];
//                                                                    [self.view makeToast:[error localizedDescription] duration:1.5f position:@"top"];
                                                                     }];
}
         
- (void)instagramRequestFinishedWithDictionary:(NSDictionary *)dictionary
{
    NSArray *instagramDicts = [dictionary objectForKey:kParamNameInstagramData];
    NSMutableArray *newGraffiti = [NSMutableArray arrayWithArray:self.graffiti];
    for (NSDictionary *instagramDict in instagramDicts) {
        InstagramGraffiti *graffiti = [[InstagramGraffiti alloc] initWithDictionary:instagramDict];
        [newGraffiti addObject:graffiti];
    }
    self.graffiti = [RankingAlgorithm sortGraffiti:newGraffiti];
}

- (void)twitterRequestFinishedWithDictionary:(NSDictionary *)dictionary
{
    NSArray *twitterDicts = [dictionary objectForKey:kParamNameTwitterResults];
    NSMutableArray *newGraffiti = [NSMutableArray arrayWithArray:self.graffiti];
    for (NSDictionary *twitterDict in twitterDicts) {
        TwitterGraffiti *graffiti = [[TwitterGraffiti alloc] initWithDictionary:twitterDict];
        [newGraffiti addObject:graffiti];
    }
    self.graffiti = [RankingAlgorithm sortGraffiti:newGraffiti];
}



- (IBAction)refreshButtonTapped:(UIBarButtonItem *)sender {
    [self requestGraffitiFromServer];
}

#pragma mark - UITableViewDelegate

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return [[self tableView:tableView cellForRowAtIndexPath:indexPath] sizeThatFits:tableView.frameSize].height;
}

- (void)viewProfile:(id)sender
{
    UIButton *usernameButton = (UIButton *)sender;
    GraffitiCell *cell = (GraffitiCell *)[usernameButton superview];
    
    NSLog(@"view profile %d", cell.graffiti.user.identifier);
    GiraffeProfileViewController *profileViewController = [[UIStoryboard storyboardWithName:@"MainStoryboard_iPhone" bundle:nil] instantiateViewControllerWithIdentifier:@"profile"];
    profileViewController.user = cell.graffiti.user;
    
    [self.navigationController pushViewController:profileViewController animated:YES];
}

- (void)likeGraffiti:(id)sender
{
    // Check to make sure user logged in
    if (![User currentUser].identifier) {
        [self.view makeToast:@"Please log in to like graffiti." duration:1.5f position:@"top"];
        return;
    };
    
    UIButton *likeButton = (UIButton *)sender;
    GraffitiCell *cell = (GraffitiCell *)[likeButton superview];
    
    cell.graffiti.isLiked = !cell.graffiti.isLiked;
    if (cell.graffiti.isLiked) cell.graffiti.likes++;
    else cell.graffiti.likes--;
    
    // update cell
    [self.tableView beginUpdates];
    [self.tableView reloadRowsAtIndexPaths:[NSArray arrayWithObject:[self.tableView indexPathForCell:cell]] withRowAnimation:UITableViewRowAnimationNone];
    [self.tableView endUpdates];
    
    [[GiraffeClient sharedClient] beginGraffitiLikePostWithGraffiti:cell.graffiti success:^(AFHTTPRequestOperation *operation, id responseObject) {
        // todo check for error / blah
        // if error revert cell and isLiked
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        // todo print error
        // if error revert cell and isLiked
        [self.view makeToast:[error localizedDescription] duration:1.5f position:@"top"];
    }];
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
