//
//  InstagramGraffiti.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 5/23/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "InstagramGraffiti.h"

NSString *const kParamNameInstagramData = @"data";
NSString *const kParamNameInstagramId = @"id";
NSString *const kParamNameInstagramCaption = @"caption";
NSString *const kParamNameInstagramCaptionText = @"text";
NSString *const kParamNameInstagramImages = @"images";
NSString *const kParamNameInstagramImagesStandard = @"standard_resolution";
NSString *const kParamNameInstagramLocation = @"location";
NSString *const kParamNameInstagramLatitude = @"latitude";
NSString *const kParamNameInstagramLongitude = @"longitude";
NSString *const kParamNameInstagramDateCreated = @"created_time";
NSString *const kParamNameInstagramUser = @"user";
NSString *const kParamNameInstagramUserId = @"id";
NSString *const kParamNameInstagramUserUsername = @"username";
NSString *const kParamNameInstagramUserAvatarUrl = @"profile_picture";

NSString *const kParamNameInstagramLikes = @"likes";
NSString *const kParamNameInstagramLikesCount = @"count";

NSString *const kParamNameInstagramLink = @"link";

@implementation InstagramGraffiti

- (void)updateWithDictionary:(NSDictionary *)dictionary
{
    if ([dictionary objectForKey:kParamNameInstagramId]) {
        self.identifier = [[dictionary objectForKey:kParamNameInstagramId] intValue];
    }
    
    if (![[dictionary objectForKey:kParamNameInstagramCaption] isKindOfClass:[NSNull class]]) {
        NSDictionary *captionDictionary = [dictionary objectForKey:kParamNameInstagramCaption];
        if ([captionDictionary objectForKey:kParamNameInstagramCaptionText]) {
            self.message = [captionDictionary objectForKey:kParamNameInstagramCaptionText];
        }
    }
    
    if (![[dictionary objectForKey:kParamNameInstagramImages]isKindOfClass:[NSNull class]]) {
        NSDictionary *imagesDictionary = [dictionary objectForKey:kParamNameInstagramImages];
        
        if ([imagesDictionary objectForKey:kParamNameInstagramImagesStandard]) {
            self.imageUrl = [[imagesDictionary objectForKey:kParamNameInstagramImagesStandard] objectForKey:@"url"];
        }
        
        if ([self.imageUrl isKindOfClass:[NSNull class]]) {
            self.imageUrl = nil;
        }
    }
    
    if (![[dictionary objectForKey:kParamNameInstagramLocation] isKindOfClass:[NSNull class]]) {
        NSDictionary *locationDictionary = [dictionary objectForKey:kParamNameInstagramLocation];
        if ([locationDictionary objectForKey:kParamNameInstagramLatitude]) {
            self.latitude = [[locationDictionary objectForKey:kParamNameInstagramLatitude] floatValue];
        }
        
        if ([locationDictionary objectForKey:kParamNameInstagramLongitude]) {
            self.longitude = [[locationDictionary objectForKey:kParamNameInstagramLongitude] floatValue];
        }
    }
    
    // TODO: Assign to some const?
    self.radius = 500.0;
    
    // x, y, z positions
    
    if (![[dictionary objectForKey:kParamNameInstagramUser] isKindOfClass:[NSNull class]]) {
        NSDictionary *userDictionary = [dictionary objectForKey:kParamNameInstagramUser];
        self.user = [[User alloc] initWithDictionary:@{kParamNameUserId: [userDictionary objectForKey:kParamNameInstagramUserId],
                      kParamNameUserUsername: [userDictionary objectForKey:kParamNameInstagramUserUsername],
                     kParamNameUserAvatarUrl: [userDictionary objectForKey:kParamNameInstagramUserAvatarUrl]}];
    }
    
    if ([dictionary objectForKey:kParamNameInstagramDateCreated]) {
        self.dateCreated = [NSDate dateWithTimeIntervalSince1970:[[dictionary objectForKey:kParamNameInstagramDateCreated] doubleValue]];
    }
    
    if (![[dictionary objectForKey:kParamNameInstagramLikes] isKindOfClass:[NSNull class]]) {
        NSDictionary *likesDictionary = [dictionary objectForKey:kParamNameInstagramLikes];
        if ([likesDictionary objectForKey:kParamNameInstagramLikesCount]) {
            self.likes = [[likesDictionary objectForKey:kParamNameInstagramLikesCount] intValue];
        }
    }
    
    // disable this feature until signing in allowed?
    self.isLiked = false;
    
    // todo link to instagram page
    
    self.platform = @"instagram";
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
