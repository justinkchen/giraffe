//
//  RankingAlgorithm.h
//  GiraffeiOS
//
//  Created by Bryan Cheng on 5/23/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Graffiti.h"

@interface RankingAlgorithm : NSObject

+ (NSArray *)sortGraffiti:(NSArray *)graffiti;
+ (NSArray *)insertGraffito:(Graffiti *)graffito
                       into:(NSArray *)graffitiList;

@end
