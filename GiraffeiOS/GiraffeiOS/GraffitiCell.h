//
//  GraffitiCell.h
//  GiraffeiOS
//
//  Created by Kurtis Horimoto on 5/6/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import <UIKit/UIKit.h>

@class Graffiti;

extern NSString *const kGraffitiCellIdentifier;

@interface GraffitiCell : UITableViewCell

@property (nonatomic, retain) Graffiti *graffiti;


@end
