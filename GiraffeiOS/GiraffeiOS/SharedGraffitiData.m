//
//  SharedGraffitiData.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 6/4/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "SharedGraffitiData.h"

@interface SharedGraffitiData ()

@end

@implementation SharedGraffitiData

+ (NSMutableArray *)sharedData
{
    // Create Singleton
    static NSMutableArray *sharedGraffiti = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedGraffiti = [NSMutableArray array];
    });
    
    return sharedGraffiti;
}

@end
