//
//  RankingAlgorithm.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 5/23/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "RankingAlgorithm.h"
#import <math.h>

@implementation RankingAlgorithm

+ (NSArray *)sortGraffiti:(NSArray *)graffiti
{
    NSSortDescriptor *scoreSortDescriptor = [NSSortDescriptor sortDescriptorWithKey: @"score" ascending: NO];
    
    return [graffiti sortedArrayUsingDescriptors:[NSArray arrayWithObject:scoreSortDescriptor]];
}

+ (NSArray *)insertGraffito:(Graffiti *)graffito
                       into:(NSArray *)graffitiList
{
    NSMutableArray *newGraffitiList = [NSMutableArray arrayWithArray:graffitiList];
    
    NSComparator graffitiComparator = ^(Graffiti *g1, Graffiti *g2) {
        if (g1.score > g2.score) {
            return (NSComparisonResult)NSOrderedAscending;
        }
        
        if (g1.score < g2.score) {
            return (NSComparisonResult)NSOrderedDescending;
        }
        
        return (NSComparisonResult)NSOrderedSame;
    };
    
    NSUInteger newIndex = [newGraffitiList indexOfObject:graffito
                                    inSortedRange:(NSRange){0, [newGraffitiList count]}
                                          options:NSBinarySearchingInsertionIndex
                                  usingComparator:graffitiComparator];
    
    [newGraffitiList insertObject:graffito atIndex:newIndex];
    
    return newGraffitiList;
}

@end
