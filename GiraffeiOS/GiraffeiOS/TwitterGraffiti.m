//
//  TwitterGraffiti.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 5/24/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "TwitterGraffiti.h"
#import "NSDate+TimeAgo.h"

NSString *const kParamNameTwitterResults = @"results";
NSString *const kParamNameTwitterId = @"id";
NSString *const kParamNameTwitterText = @"text";

NSString *const kParamNameTwitterEntities = @"entities";
NSString *const kParamNameTwitterMedia = @"media";
NSString *const kParamNameTwitterImageUrl = @"media_url";

NSString *const kParamNameTwitterGeocode = @"geo";
NSString *const kParamNameTwitterCoordinates = @"coordinates";
NSString *const kParamNameTwitterDateCreated = @"created_at";

NSString *const kParamNameTwitterUserId = @"from_user_id";
NSString *const kParamNameTwitterUserUsername = @"from_user";
NSString *const kParamNameTwitterUserAvatarUrl = @"profile_image_url";

NSString *const kParamNameTwitterMetadata = @"metadata";
NSString *const kParamNameTwitterRetweets = @"retweets";

//NSString *const kParamNameTwitterLink = @"link";

@implementation TwitterGraffiti

- (void)updateWithDictionary:(NSDictionary *)dictionary
{
    if ([dictionary objectForKey:kParamNameTwitterId]) {
        self.identifier = [[dictionary objectForKey:kParamNameTwitterId] intValue];
    }
    
    if ([dictionary objectForKey:kParamNameTwitterText]) {
        self.message = [dictionary objectForKey:kParamNameTwitterText];
    }
    
    if (![[dictionary objectForKey:kParamNameTwitterEntities]isKindOfClass:[NSNull class]]) {
        NSDictionary *entitiesDictionary = [dictionary objectForKey:kParamNameTwitterEntities];
        
        if (![[entitiesDictionary objectForKey:kParamNameTwitterMedia] isKindOfClass:[NSNull class]]) {
            
            NSDictionary *mediaDictionary = [entitiesDictionary objectForKey:kParamNameTwitterMedia];
            
            if ([mediaDictionary objectForKey:kParamNameTwitterImageUrl]) {
                self.imageUrl = [mediaDictionary objectForKey:kParamNameTwitterImageUrl];
            }
        }
        
        if ([self.imageUrl isKindOfClass:[NSNull class]]) {
            self.imageUrl = nil;
        }
    }
    
    if (![[dictionary objectForKey:kParamNameTwitterGeocode] isKindOfClass:[NSNull class]]) {
        NSDictionary *geocodeDictionary = [dictionary objectForKey:kParamNameTwitterGeocode];
        if ([geocodeDictionary objectForKey:kParamNameTwitterCoordinates]) {    
            NSArray *coordinates = [geocodeDictionary objectForKey:kParamNameTwitterCoordinates];
            self.latitude = [[coordinates objectAtIndex:0] floatValue];
            self.longitude = [[coordinates objectAtIndex:1] floatValue];
        }
    }
    
    // TODO: Assign to some const?
    self.radius = 500.0;
    
    // x, y, z positions
    
    if ([dictionary objectForKey:kParamNameTwitterUserId]) {
        self.user = [[User alloc] initWithDictionary:@{kParamNameUserId: [dictionary objectForKey:kParamNameTwitterUserId],
                              kParamNameUserUsername: [dictionary objectForKey:kParamNameTwitterUserUsername],
                             kParamNameUserAvatarUrl: [dictionary objectForKey:kParamNameTwitterUserAvatarUrl]}];
    }
    
    if ([dictionary objectForKey:kParamNameTwitterDateCreated]) {
        self.dateCreated = [[NSDateFormatter sharedTwitterDateFormatter] dateFromString:[dictionary objectForKey:kParamNameTwitterDateCreated]];
        
//        [dateFormatter dateFromString:[currentDict objectForKey:@"created_at"]];
    }
    
    if (![[dictionary objectForKey:kParamNameTwitterMetadata] isKindOfClass:[NSNull class]]) {
        NSDictionary *metadataDictionary = [dictionary objectForKey:kParamNameTwitterMetadata];
        if ([metadataDictionary objectForKey:kParamNameTwitterRetweets]) {
            self.likes = [[metadataDictionary objectForKey:kParamNameTwitterRetweets] intValue];
        }
    }
    
    // disable this feature until signing in allowed?
    self.isLiked = false;
    
    // todo link to twitter? page
    
    self.platform = @"twitter";
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
