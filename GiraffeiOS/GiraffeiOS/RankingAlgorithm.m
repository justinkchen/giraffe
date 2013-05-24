//
//  RankingAlgorithm.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 5/23/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "RankingAlgorithm.h"
#import <math.h>
#import "Graffiti.h"

@implementation RankingAlgorithm

+ (NSArray *)sortGraffiti:(NSArray *)graffiti
{
    NSSortDescriptor *scoreSortDescriptor = [NSSortDescriptor sortDescriptorWithKey: @"score" ascending: NO];
    
    return [graffiti sortedArrayUsingDescriptors:[NSArray arrayWithObject:scoreSortDescriptor]];
}

@end
