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

@interface GiraffeProfileViewController () <UINavigationControllerDelegate,UIActionSheetDelegate, UIImagePickerControllerDelegate>

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
    
    [self setUserContent];

    UITapGestureRecognizer *singleTap = [[UITapGestureRecognizer alloc]
                                         initWithTarget:self
                                         action:@selector(handleAvatarImageTouched:)];
    [singleTap setNumberOfTapsRequired:1];
    self.avatarView.userInteractionEnabled = YES;
    [self.avatarView addGestureRecognizer:singleTap];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateUserContent:) name:@"userUpdated" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateUserStats:) name:@"userStatsUpdated" object:nil];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    [[GiraffeClient sharedClient] beginUserGraffitiGetWithId:[User currentUser].identifier success:^(AFHTTPRequestOperation *operation, id responseObject) {
        [self graffitiRequestFinishedWithDictionary:[responseObject ifIsKindOfClass:[NSDictionary class]]];
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        // print error
    }];
    
    [[GiraffeClient sharedClient] beginUserStatsGetWithId:[User currentUser].identifier success:^(AFHTTPRequestOperation *operation, id responseObject) {
        if ([responseObject objectForKey:@"error"]) {
            NSLog(@"%@", [responseObject objectForKey:@"error"]);
            return;
        }
        
        [[User currentUser] updateStatsWithDictionary:[responseObject objectForKey:@"stats"]];
        [self setUserStats];
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
    } else {
        self.graffiti = [NSArray array];
    }
}

- (void)updateUserContent:(NSNotification *)notification
{
    NSLog(@"updated!");
    [self setUserContent];
}

- (void)setUserContent
{
    User *user = [User currentUser];
    
    self.usernameLabel.text = user.username;
    
    if (user.avatarUrl) {
        [self.avatarView setImageWithURL:[NSURL URLWithString:[NSString stringWithFormat:@"%@%@", kBaseURL, user.avatarUrl]]];
    } else {
        [self.avatarView setImage:nil];
    }
}

- (void)setUserStats
{
    User *user = [User currentUser];
    
    self.graffitiCountLabel.text = [NSString stringWithFormat:@"%i", user.graffitiCount];
    self.likesCountLabel.text = [NSString stringWithFormat:@"%i", user.likeCount];
    self.badgesCountLabel.text = [NSString stringWithFormat:@"%i", user.badgeCount];
}

- (void)updateCurrentUserWithDictionary:(id)dictionary
{
    NSLog(@"received user data");
    NSDictionary *userDict = [[dictionary ifIsKindOfClass:[NSDictionary class]] objectForKey:kParamNameUser];
    [[User currentUser] updateWithDictionary:userDict];
}

#pragma mark - Buttons

- (void)handleAvatarImageTouched:(UIGestureRecognizer*)recognizer
{
    if ([self.avatarView isEqual:recognizer.view]) {
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
        [actionSheet showInView:self.parentViewController.tabBarController.view];
    }
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
        [[GiraffeClient sharedClient] beginUserAvatarUpdatePutWithImage:[info objectForKey:UIImagePickerControllerOriginalImage] success:^(AFHTTPRequestOperation *operation, id responseObject) {
            // if no error
            NSLog(@"response %@", responseObject);
            if ([responseObject objectForKey:@"error"]) {
                // todo print error
                return;
            }
            NSLog(@"after it");
            [self updateCurrentUserWithDictionary:responseObject];
        } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
            // todo print error
        }];
//        [self.avatarView setImage:[info objectForKey:kUIImagePickerImageKey]];
        [picker dismissViewControllerAnimated:YES completion:^{
            // do nothing
        }];
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
    [self.userGraffitiTableView beginUpdates];
    [self.userGraffitiTableView reloadRowsAtIndexPaths:[NSArray arrayWithObject:[self.userGraffitiTableView indexPathForCell:cell]] withRowAnimation:UITableViewRowAnimationNone];
    [self.userGraffitiTableView endUpdates];
    
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
