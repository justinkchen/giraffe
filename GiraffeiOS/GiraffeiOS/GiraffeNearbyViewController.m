//
//  GiraffeFirstViewController.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/24/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "GiraffeNearbyViewController.h"
#import "Graffiti.h"
#import "User.h"
#import "GraffitiCell.h"
#import "GiraffeClient.h"
#import "LocationManager.h"
#import "UIKit-Utility.h"
#import "Foundation-Utility.h"

@interface GiraffeNearbyViewController () <UITableViewDataSource, UITableViewDelegate>

@property (nonatomic, retain) UITableView *tableView;
@property (nonatomic, retain) NSMutableArray *graffiti;

@end

@implementation GiraffeNearbyViewController

#pragma mark - View Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.tableView = [[UITableView alloc] initWithFrame:self.view.bounds style:UITableViewStylePlain];
    self.tableView.delegate = self;
    self.tableView.dataSource = self;
    [self.view addSubview:self.tableView];
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
    
    // Kick off load request
    [[GiraffeClient sharedClient] beginGraffitiNearbyGetWithLatitude:[LocationManager sharedInstance].latitude
                                                           longitude:[LocationManager sharedInstance].longitude success:^(AFHTTPRequestOperation *operation, id responseObject) {
                                                               NSLog(@"got response %@", responseObject);
                                                               
                                                               [self graffitiRequestFinishedWithDictionary:[responseObject ifIsKindOfClass:[NSDictionary class]]];
                                                                                                                          } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
                                                               NSLog(@"Graffiti request failed with error: %@", [error localizedDescription]);
                                                           }];
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

- (void)likeGraffiti:(id)sender
{
    // Check to make sure user logged in
    if (![User currentUser].identifier) return;
    
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
