//
//  GiraffeFirstViewController.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/24/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "GiraffeNearbyViewController.h"
#import "GiraffeProfileViewController.h"
#import "GiraffeGraffitiViewController.h"
#import "Graffiti.h"
#import "SharedGraffitiData.h"
#import "InstagramGraffiti.h"
#import "TwitterGraffiti.h"
#import "FacebookGraffiti.h"
#import "User.h"
#import "GraffitiCell.h"
#import "GiraffeClient.h"
#import "InstagramClient.h"
#import "TwitterClient.h"
#import "FacebookClient.h"
#import "LocationManager.h"
#import "RankingAlgorithm.h"
#import "UIKit-Utility.h"
#import "Toast+UIView.h"
#import "Foundation-Utility.h"
#import <FacebookSDK/FacebookSDK.h>

@interface GiraffeNearbyViewController () <UITableViewDataSource, UITableViewDelegate, LocationManagerDelegate>

@property (weak, nonatomic) IBOutlet UITableView *tableView;
//@property (nonatomic, retain) NSArray *graffiti;

@end

@implementation GiraffeNearbyViewController

#pragma mark - View Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [LocationManager sharedInstance].delegate = self;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    [self requestGraffitiFromServer];
}

#pragma mark - Accessors

- (void)setGraffiti:(NSMutableArray *)graffiti
{
    if (![[SharedGraffitiData sharedData] isEqualToArray:graffiti]) {
        [[SharedGraffitiData sharedData] setArray:graffiti];
        [self.tableView reloadData];
    }
}

#pragma mark - Utility

- (void)requestGraffitiFromServer
{
    CGFloat latitude = [LocationManager sharedInstance].latitude;
    CGFloat longitude = [LocationManager sharedInstance].longitude;
    // Find current location
    
    if (latitude == 0 && longitude == 0) return;
    
    [self.view makeToastActivity];
    
    if (latitude && longitude) {
        [[SharedGraffitiData sharedData] setArray:[NSArray new]];
        [self giraffeRequestBeginWithLatitude:latitude longitude:longitude];
        
        NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
        if ([userDefaults objectForKey:@"instagramFeed"] != nil ? [userDefaults boolForKey:@"instagramFeed"] : YES) {
            [self instagramRequestBeginWithLatitude:latitude longitude:longitude];
        }
        
        if ([userDefaults objectForKey:@"twitterFeed"] != nil ? [userDefaults boolForKey:@"twitterFeed"] : YES) {
            [self twitterRequestBeginWithLatitude:latitude longitude:longitude];
        }
        
        
        if ([userDefaults objectForKey:@"facebookFeed"] != nil ? [userDefaults boolForKey:@"facebookFeed"] : YES) {
            [self facebookRequestBeginWithLatitude:latitude longitude:longitude];
        }
    }
}

- (void)giraffeRequestBeginWithLatitude:(CGFloat)latitude
                              longitude:(CGFloat)longitude
{
    // Kick off load request
    [[GiraffeClient sharedClient] beginGraffitiNearbyGetWithLatitude:latitude
                                                           longitude:longitude success:^(AFHTTPRequestOperation *operation, id responseObject) {
                                                               [self.view hideToastActivity];
                                                               //                                                               NSLog(@"got response %@", responseObject);
                                                               
                                                               [self graffitiRequestFinishedWithDictionary:[responseObject ifIsKindOfClass:[NSDictionary class]]];
                                                           } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
                                                               [self.view hideToastActivity];
                                                               [self.view makeToast:[error localizedDescription] duration:1.5f position:@"top"];
                                                           }];
}

- (void)graffitiRequestFinishedWithDictionary:(NSDictionary *)dictionary
{
    NSArray *graffitiDicts = [dictionary objectForKey:kParamNameGraffiti];
    NSMutableArray *newGraffiti = [NSMutableArray arrayWithArray:[SharedGraffitiData sharedData]];
    for (NSDictionary *graffitiDict in graffitiDicts) {
        Graffiti *graffiti = [[Graffiti alloc] initWithDictionary:graffitiDict];
        
        // filter response
        NSString *query = [[NSUserDefaults standardUserDefaults] objectForKey:@"queryFilter"];
        if (query == nil || [query isEqualToString:@""] || [graffiti.message rangeOfString:query options:NSCaseInsensitiveSearch].location != NSNotFound) {
            [newGraffiti addObject:graffiti];
        }
    }
    
    [[SharedGraffitiData sharedData] setArray:[RankingAlgorithm sortGraffiti:newGraffiti]];
    [self.tableView reloadData];
}

- (void)instagramRequestBeginWithLatitude:(CGFloat)latitude
                                longitude:(CGFloat)longitude
{
    [[InstagramClient sharedClient] beginInstagramNearbyGetWithLatitude:latitude
                                                              longitude:longitude
                                                                success:^(AFHTTPRequestOperation *operation, id responseObject) {
                                                                    [self.view hideToastActivity];
//                                                                    NSLog(@"got instagram response %@", responseObject);
                                                                    
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
    NSMutableArray *newGraffiti = [NSMutableArray arrayWithArray:[SharedGraffitiData sharedData]];
    for (NSDictionary *instagramDict in instagramDicts) {
        InstagramGraffiti *graffiti = [[InstagramGraffiti alloc] initWithDictionary:instagramDict];
        
        // filter response
        NSString *query = [[NSUserDefaults standardUserDefaults] objectForKey:@"queryFilter"];
        if (query == nil || [query isEqualToString:@""] || (graffiti.message != nil && [graffiti.message rangeOfString:query options:NSCaseInsensitiveSearch].location != NSNotFound)) {
            [newGraffiti addObject:graffiti];
        }
    }
    
    [[SharedGraffitiData sharedData] setArray:[RankingAlgorithm sortGraffiti:newGraffiti]];
    [self.tableView reloadData];
}

- (void)twitterRequestBeginWithLatitude:(CGFloat)latitude
                              longitude:(CGFloat)longitude
{
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

- (void)twitterRequestFinishedWithDictionary:(NSDictionary *)dictionary
{
    NSArray *twitterDicts = [dictionary objectForKey:kParamNameTwitterResults];
    NSMutableArray *newGraffiti = [NSMutableArray arrayWithArray:[SharedGraffitiData sharedData]];
    for (NSDictionary *twitterDict in twitterDicts) {
        TwitterGraffiti *graffiti = [[TwitterGraffiti alloc] initWithDictionary:twitterDict];
        
        // filter response
        NSString *query = [[NSUserDefaults standardUserDefaults] objectForKey:@"queryFilter"];
        if (query == nil || [query isEqualToString:@""] || [graffiti.message rangeOfString:query options:NSCaseInsensitiveSearch].location != NSNotFound) {
            [newGraffiti addObject:graffiti];
        }
    }
    
    [[SharedGraffitiData sharedData] setArray:[RankingAlgorithm sortGraffiti:newGraffiti]];
    [self.tableView reloadData];
}

- (void)facebookRequestBeginWithLatitude:(CGFloat)latitude
                               longitude:(CGFloat)longitude
{
    if (FBSession.activeSession.isOpen) {
        [[FacebookClient sharedClient] beginFacebookNearbyGetWithLatitude:latitude longitude:longitude success:^(FBRequestConnection *connection, id result) {
            //                NSLog(@"facebook post %@", result);
            [self facebookRequestFinishedWithDictionary:[result ifIsKindOfClass:[NSDictionary class]]];
        } failure:^(FBRequestConnection *connection, id result, NSError *error) {
            [self.view hideToastActivity];
            [self.view makeToast:[error localizedDescription] duration:1.5f position:@"top"];
        }];
    }
}

- (void)facebookRequestFinishedWithDictionary:(NSDictionary *)dictionary
{
    FacebookGraffiti *graffiti = [[FacebookGraffiti alloc] initWithDictionary:dictionary];
    
    // filter response
    NSString *query = [[NSUserDefaults standardUserDefaults] objectForKey:@"queryFilter"];
    if (query == nil || [query isEqualToString:@""] || [graffiti.message rangeOfString:query options:NSCaseInsensitiveSearch].location != NSNotFound) {
        [[SharedGraffitiData sharedData] setArray:[RankingAlgorithm insertGraffito:graffiti into:[SharedGraffitiData sharedData]]];
        [self.tableView reloadData];
    }
}

- (IBAction)refreshButtonTapped:(UIBarButtonItem *)sender {
    [self requestGraffitiFromServer];
}

#pragma mark - UITableViewDelegate

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return [[self tableView:tableView cellForRowAtIndexPath:indexPath] sizeThatFits:tableView.frameSize].height;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    GraffitiCell *cell = (GraffitiCell *)[self tableView:tableView cellForRowAtIndexPath:indexPath];
    
    GiraffeGraffitiViewController *graffitiViewController = [GiraffeGraffitiViewController new];
    graffitiViewController.graffiti = cell.graffiti;
    
    [self.navigationController pushViewController:graffitiViewController animated:YES];
}

- (void)viewProfile:(id)sender
{
    UIButton *usernameButton = (UIButton *)sender;
    GraffitiCell *cell = (GraffitiCell *)[usernameButton superview];
    
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
    return [[SharedGraffitiData sharedData] count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    GraffitiCell *cell = [[tableView dequeueReusableCellWithIdentifier:kGraffitiCellIdentifier] ifIsKindOfClass:[GraffitiCell class]];
    if (!cell) {
        cell = [[GraffitiCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kGraffitiCellIdentifier];
    }
    cell.graffiti = [[SharedGraffitiData sharedData] objectAtIndex:indexPath.row];
    return cell;
}

#pragma mark - LocationManagerDelegate

- (void)locationFound
{
    [self requestGraffitiFromServer];
}

@end