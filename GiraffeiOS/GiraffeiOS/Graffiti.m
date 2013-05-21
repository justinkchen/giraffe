//
//  Graffiti.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/28/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "Graffiti.h"
#import "User.h"
#import "NSDate+TimeAgo.h"

@implementation Graffiti

NSString *const kParamNameGraffiti = @"graffiti";
NSString *const kParamNameGraffitiId = @"id";
NSString *const kParamNameGraffitiMessage = @"message";
NSString *const kParamNameGraffitiImageUrl = @"imageUrl";
NSString *const kParamNameGraffitiLatitude = @"latitude";
NSString *const kParamNameGraffitiLongitude = @"longitude";
NSString *const kParamNameGraffitiRadius = @"radius";
NSString *const kParamNameGraffitiDirectionX = @"directionX";
NSString *const kParamNameGraffitiDirectionY = @"directionY";
NSString *const kParamNameGraffitiDirectionZ = @"directionZ";
//NSString *const kParamNameGraffitiLikeCount = @"likeCount";
NSString *const kParamNameGraffitiFlagged = @"flagged";
NSString *const kParamNameGraffitiDateCreated = @"dateCreated";
NSString *const kParamNameGraffitiUserId = @"userId";
NSString *const kParamNameGraffitiUserUsername = @"username";
NSString *const kParamNameGraffitiUserAvatarUrl = @"avatarUrl";
NSString *const kParamNameGraffitiLikes = @"likes";
NSString *const kParamNameGraffitiIsLiked = @"isLiked";

- (NSDictionary *)parameterDictionary
{
    // Create dictionary with expected parameter names
    return @{kParamNameGraffitiId: @(self.identifier),
             kParamNameGraffitiMessage: self.message,
             kParamNameGraffitiLatitude: @(self.latitude),
             kParamNameGraffitiLongitude: @(self.longitude),
             kParamNameGraffitiRadius: @(self.radius),
             kParamNameGraffitiUserId: @(self.user.identifier),
             kParamNameGraffitiIsLiked: @(self.isLiked)};
}

- (void)updateWithDictionary:(NSDictionary *)dictionary
{
    // Perform reverse of paramterDictionary...unpack json into properties
    if ([dictionary objectForKey:kParamNameGraffitiId]) {
        self.identifier = [[dictionary objectForKey:kParamNameGraffitiId] intValue];
    }
    
    if ([dictionary objectForKey:kParamNameGraffitiMessage]) {
        self.message = [dictionary objectForKey:kParamNameGraffitiMessage];
    }
    
    if ([dictionary objectForKey:kParamNameGraffitiImageUrl]) {
        self.imageUrl = [dictionary objectForKey:kParamNameGraffitiImageUrl];
        
        if ([self.imageUrl isKindOfClass:[NSNull class]]) {
            self.imageUrl = nil;
        }
    }
    
    if ([dictionary objectForKey:kParamNameGraffitiLatitude]) {
        self.latitude = [[dictionary objectForKey:kParamNameGraffitiLatitude] floatValue];
    }
    
    if ([dictionary objectForKey:kParamNameGraffitiLongitude]) {
        self.longitude = [[dictionary objectForKey:kParamNameGraffitiLongitude] floatValue];
    }
    
    if ([dictionary objectForKey:kParamNameGraffitiRadius]) {
        self.radius = [[dictionary objectForKey:kParamNameGraffitiRadius] floatValue];
    }
    
    // x, y, z positions
    
    if ([dictionary objectForKey:kParamNameGraffitiUserId]) {
        self.user = [[User alloc] initWithDictionary:@{kParamNameUserId: [dictionary objectForKey:kParamNameGraffitiUserId],
                      kParamNameGraffitiUserUsername: [dictionary objectForKey:kParamNameGraffitiUserUsername],
                     kParamNameGraffitiUserAvatarUrl: [dictionary objectForKey:kParamNameGraffitiUserAvatarUrl]}];
    }
    
    if ([dictionary objectForKey:kParamNameGraffitiDateCreated]) {
                
        self.dateCreated = [[NSDateFormatter sharedDateFormatter] dateFromString:[dictionary objectForKey:kParamNameGraffitiDateCreated]];
    }
    
    if ([dictionary objectForKey:kParamNameGraffitiLikes]) {
        self.likes = [[dictionary objectForKey:kParamNameGraffitiLikes] intValue];
    }
    
    if ([dictionary objectForKey:kParamNameGraffitiIsLiked]) {
        self.isLiked = [[dictionary objectForKey:kParamNameGraffitiIsLiked] boolValue];
    }
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
