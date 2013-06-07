//
//  GiraffeFilterViewController.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 6/7/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "GiraffeFilterViewController.h"

@interface GiraffeFilterViewController ()

@property (weak, nonatomic) IBOutlet UITextField *query;
@property (weak, nonatomic) IBOutlet UISwitch *facebookSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *twitterSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *instagramSwitch;

@end

@implementation GiraffeFilterViewController

NSString *const kQueryFilterKey = @"queryFilter";
NSString *const kFacebookFeedKey = @"facebookFeed";
NSString *const kTwitterFeedKey = @"twitterFeed";
NSString *const kInstagramFeedKey = @"instagramFeed";

- (id)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
 
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
    
    // set the switches based on nsdefaults
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    self.query.text = [userDefaults objectForKey:kQueryFilterKey] != nil ? [userDefaults objectForKey:kQueryFilterKey] : @"";
    [self.facebookSwitch setOn:[userDefaults objectForKey:kFacebookFeedKey] != nil ? [userDefaults boolForKey:kFacebookFeedKey] : YES];
    [self.twitterSwitch setOn:[userDefaults objectForKey:kTwitterFeedKey] != nil ? [userDefaults boolForKey:kTwitterFeedKey] : YES];
    [self.instagramSwitch setOn:[userDefaults objectForKey:kInstagramFeedKey] != nil ? [userDefaults boolForKey:kInstagramFeedKey] : YES];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)applyFilter:(UIBarButtonItem *)sender {
    // save the filter choices into NSDefaults
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    [userDefaults setObject:self.query.text forKey:kQueryFilterKey];
    [userDefaults setBool:self.facebookSwitch.isOn forKey:kFacebookFeedKey];
    [userDefaults setBool:self.twitterSwitch.isOn forKey:kTwitterFeedKey];
    [userDefaults setBool:self.instagramSwitch.isOn forKey:kInstagramFeedKey];
    
    [self.presentingViewController dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction)cancelFilter:(UIBarButtonItem *)sender {
    // close window
    [self.presentingViewController dismissViewControllerAnimated:YES completion:nil];
}

#pragma mark - Table view data source
/*
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
#warning Potentially incomplete method implementation.
    // Return the number of sections.
    return 0;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
#warning Incomplete method implementation.
    // Return the number of rows in the section.
    return 0;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier forIndexPath:indexPath];
    
    // Configure the cell...
    
    return cell;
}
*/
/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/

/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
    }   
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath
{
}
*/

/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Navigation logic may go here. Create and push another view controller.
    /*
     <#DetailViewController#> *detailViewController = [[<#DetailViewController#> alloc] initWithNibName:@"<#Nib name#>" bundle:nil];
     // ...
     // Pass the selected object to the new view controller.
     [self.navigationController pushViewController:detailViewController animated:YES];
     */
}

@end
