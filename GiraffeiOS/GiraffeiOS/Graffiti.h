//
//  Graffiti.h
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/28/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import <Foundation/Foundation.h>

@class User;

@interface Graffiti : NSObject

extern NSString *const kParamNameGraffiti;
extern NSString *const kParamNameGraffitiId;
extern NSString *const kParamNameGraffitiMessage;
extern NSString *const kParamNameGraffitiImageUrl;
extern NSString *const kParamNameGraffitiLatitude;
extern NSString *const kParamNameGraffitiLongitude;
extern NSString *const kParamNameGraffitiRadius;
extern NSString *const kParamNameGraffitiDirectionX;
extern NSString *const kParamNameGraffitiDirectionY;
extern NSString *const kParamNameGraffitiDirectionZ;
//extern NSString *const kParamNameGraffitiLikeCount;
extern NSString *const kParamNameGraffitiFlagged;
extern NSString *const kParamNameGraffitiDateCreated;
extern NSString *const kParamNameGraffitiUserId;
extern NSString *const kParamNameGraffitiUserUsername;
extern NSString *const kParamNameGraffitiUserAvatarUrl;
extern NSString *const kParamNameGraffitiLikes;
extern NSString *const kParamNameGraffitiIsLiked;

@property (nonatomic, assign) int identifier;
@property (nonatomic, retain) NSString *message;
@property (nonatomic, retain) NSString *imageUrl;
@property (nonatomic, assign) float latitude;
@property (nonatomic, assign) float longitude;
@property (nonatomic, assign) float radius;
@property (nonatomic, assign) float directionX;
@property (nonatomic, assign) float directionY;
@property (nonatomic, assign) float directionZ;
//@property (nonatomic, assign) NSUInteger likeCount;
@property (nonatomic, assign) BOOL flagged;
@property (nonatomic, retain) NSDate *dateCreated;
@property (nonatomic, retain) User *user;
@property (nonatomic, assign) int likes;
@property (nonatomic, assign) BOOL isLiked;
@property (nonatomic, retain) NSString *platform;

- (NSDictionary *)parameterDictionary;
- (void)updateWithDictionary:(NSDictionary *)dictionary;
- (id)initWithDictionary:(NSDictionary *)dictionary;

@end
