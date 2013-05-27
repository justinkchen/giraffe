//
//  FacebookGraffiti.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 5/26/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "FacebookGraffiti.h"
#import "NSDate+TimeAgo.h"

NSString *const kParamNameFacebookId = @"id";

NSString *const kParamNameFacebookName = @"name";
NSString *const kParamNameFacebookMessage = @"message";

NSString *const kParamNameFacebookPicture = @"source";

NSString *const kParamNameFacebookPlace = @"place";
NSString *const kParamNameFacebookPlaceName = @"name";
NSString *const kParamNameFacebookLocation = @"location";
NSString *const kParamNameFacebookLatitude = @"latitude";
NSString *const kParamNameFacebookLongitude = @"longitude";
NSString *const kParamNameFacebookDateCreated = @"created_time";
NSString *const kParamNameFacebookDateUpdated = @"updated_time";

NSString *const kParamNameFacebookFrom = @"from";
NSString *const kParamNameFacebookUserId = @"id";
NSString *const kParamNameFacebookUserUsername = @"name";
NSString *const kParamNameFacebookUserAvatarUrlFormat = @"https://graph.facebook.com/%@/picture";

NSString *const kParamNameFacebookLikes = @"likes";
NSString *const kParamNameFacebookLikesData = @"data";


@implementation FacebookGraffiti

- (void)updateWithDictionary:(NSDictionary *)dictionary
{
    if ([dictionary objectForKey:kParamNameFacebookId]) {
        self.identifier = [[dictionary objectForKey:kParamNameFacebookId] intValue];
    }
    
    if ([dictionary objectForKey:kParamNameFacebookName]) {
        self.message = [dictionary objectForKey:kParamNameFacebookName];
    } else if ([dictionary objectForKey:kParamNameFacebookMessage]) {
        self.message = [dictionary objectForKey:kParamNameFacebookMessage];
    }
    
    if ([dictionary objectForKey:kParamNameFacebookPicture]) {
        self.imageUrl = [dictionary objectForKey:kParamNameFacebookPicture];
    } else {
        self.imageUrl = nil;
    }
    
    if (![[dictionary objectForKey:kParamNameFacebookPlace] isKindOfClass:[NSNull class]]) {
        NSDictionary *placeDictionary = [dictionary objectForKey:kParamNameFacebookPlace];
        if (!self.message && [placeDictionary objectForKey:kParamNameFacebookPlaceName]) {
            self.message = [placeDictionary objectForKey:kParamNameFacebookPlaceName];
        }
        
        if ([placeDictionary objectForKey:kParamNameFacebookLocation]) {
            NSDictionary *locationDictionary = [placeDictionary objectForKey:kParamNameFacebookLocation];
            self.latitude = [[locationDictionary objectForKey:kParamNameFacebookLatitude] floatValue];
            self.longitude = [[locationDictionary objectForKey:kParamNameFacebookLongitude] floatValue];
        }
    }
    
    // TODO: Assign to some const?
    self.radius = 500.0;
    
    // x, y, z positions
    
    if ([dictionary objectForKey:kParamNameFacebookFrom]) {
        NSDictionary *userDictionary = [dictionary objectForKey:kParamNameFacebookFrom];
        self.user = [[User alloc] initWithDictionary:@{kParamNameUserId: [userDictionary objectForKey:kParamNameFacebookUserId],
                              kParamNameUserUsername: [userDictionary objectForKey:kParamNameFacebookUserUsername],
                             kParamNameUserAvatarUrl: [NSString stringWithFormat:kParamNameFacebookUserAvatarUrlFormat, [userDictionary objectForKey:kParamNameFacebookUserId]]}];
    }
    
    if ([dictionary objectForKey:kParamNameFacebookDateCreated]) {
        self.dateCreated = [[FacebookGraffiti sharedDateFormatter] dateFromString:[dictionary objectForKey:kParamNameFacebookDateCreated]];
    } else if ([dictionary objectForKey:kParamNameFacebookDateUpdated]) {
        self.dateCreated = [[FacebookGraffiti sharedDateFormatter] dateFromString:[dictionary objectForKey:kParamNameFacebookDateUpdated]];
    }
    
    if (![[dictionary objectForKey:kParamNameFacebookLikes] isKindOfClass:[NSNull class]]) {
        NSDictionary *likesDictionary = [dictionary objectForKey:kParamNameFacebookLikes];
        if ([likesDictionary objectForKey:kParamNameFacebookLikesData]) {
            self.likes = [[likesDictionary objectForKey:kParamNameFacebookLikesData] count];
        }
    }
    
    // disable this feature until signing in allowed?
    self.isLiked = false;
    
    // todo link to facebook? page
    
    self.platform = @"facebook";
}

- (id)initWithDictionary:(NSDictionary *)dictionary
{
    self = [super init];
    if (self) {
        [self updateWithDictionary:dictionary];
    }
    return self;
}

+ (NSDateFormatter *)sharedDateFormatter
{
    // Create Singleton
    static NSDateFormatter *sharedDateFormatter = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedDateFormatter = [[NSDateFormatter alloc] init];
        [sharedDateFormatter setDateFormat:@"yyyy-MM-dd'T'HH:mm:ssZ"];
        [sharedDateFormatter setTimeZone:[NSTimeZone timeZoneWithAbbreviation:@"GMT"]];
        //        NSLog(@"time zone%@", [NSTimeZone systemTimeZone]);
    });
    
    return sharedDateFormatter;
}

@end
