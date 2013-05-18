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
    
    //[self.avatar setImageWithURL:[NSURL URLWithString:@"http://www.thegiraffeapp.com/images/user/d6a49c99211136c42557c3ae966ae155c929c71b97a269531af541bdb84a6edc.jpg"] placeholderImage:[UIImage imageNamed:@"first.png"]];
    [self setUserContent];

//    [self.avatarView addTarget:self action:@selector(handleAvatarImageTapped:) forControlEvents:UIControlEventTouchUpInside];
    UITapGestureRecognizer *singleTap = [[UITapGestureRecognizer alloc]
                                         initWithTarget:self
                                         action:@selector(handleAvatarImageTouched:)];
    [singleTap setNumberOfTapsRequired:1];
    self.avatarView.userInteractionEnabled = YES;
    [self.avatarView addGestureRecognizer:singleTap];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateUserContent:) name:@"userUpdated" object:nil];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
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
        [actionSheet showInView:self.view];
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
        [self showImagePicker:imagePickerController];
    }
}

- (void)showImagePicker:(UIImagePickerController *)imagePicker
{
    [self presentViewController:imagePicker animated:YES completion:nil];
}

#pragma mark - UIImagePickerControllerDelegate

NSString *const kUIImagePickerImageKey = @"UIImagePickerControllerOriginalImage";

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    // figure out which image to use here and submit it to the db
    if ([info objectForKey:kUIImagePickerImageKey]) {
        [[GiraffeClient sharedClient] beginUserAvatarUpdatePutWithImage:[info objectForKey:kUIImagePickerImageKey] success:^(AFHTTPRequestOperation *operation, id responseObject) {
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
    
    Graffiti *graffiti = ((GraffitiCell *)[likeButton superview]).graffiti;
    graffiti.isLiked = !graffiti.isLiked;
    // update cell
    
    NSLog(@"%@", graffiti.message);
    [[GiraffeClient sharedClient] beginGraffitiLikePostWithGraffiti:graffiti success:^(AFHTTPRequestOperation *operation, id responseObject) {
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
        [cell setSelectionStyle:UITableViewCellSelectionStyleNone];
    }
    cell.graffiti = [self.graffiti objectAtIndex:indexPath.row];
    return cell;
}

@end
