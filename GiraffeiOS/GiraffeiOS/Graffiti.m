//
//  Graffiti.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/28/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "Graffiti.h"

@implementation Graffiti

NSString *const kParamNameGraffiti = @"graffiti";
NSString *const kParamNameGraffitiText = @"id";
NSString *const kParamNameGraffitiImageUrl = @"imageUrl";
NSString *const kParamNameGraffitiLongitude = @"longitude";
NSString *const kParamNameGraffitiLatitude = @"latitude";
NSString *const kParamNameGraffitiDirectionX = @"directionX";
NSString *const kParamNameGraffitiDirectionY = @"directionY";
NSString *const kParamNameGraffitiDirectionZ = @"directionZ";
NSString *const kParamNameGraffitiRadius = @"radius";
NSString *const kParamNameGraffitiLikeCount = @"likeCount";
NSString *const kParamNameGraffitiFlagged = @"flagged";
NSString *const kParamNameGraffitiDateCreated = @"dateCreated";
NSString *const kParamNameGraffitiAuthor = @"author";

- (NSDictionary *)parameterDictionary
{
    // Create dictionary with expected parameter names
    return nil;
}

- (void)updateWithDictionary:(NSDictionary *)dictionary
{
    // Perform reverse of paramterDictionary...unpack json into properties
}

- (id)initWithDictionary:(NSDictionary *)dictionary
{
    self = [super init];
    if (self) {
        [self updateWithDictionary:dictionary];
    }
    return self;
}

@end
