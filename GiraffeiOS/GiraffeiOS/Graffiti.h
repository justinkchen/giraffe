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
extern NSString *const kParamNameGraffitiText;
extern NSString *const kParamNameGraffitiImageUrl;
extern NSString *const kParamNameGraffitiLongitude;
extern NSString *const kParamNameGraffitiLatitude;
extern NSString *const kParamNameGraffitiDirectionX;
extern NSString *const kParamNameGraffitiDirectionY;
extern NSString *const kParamNameGraffitiDirectionZ;
extern NSString *const kParamNameGraffitiRadius;
extern NSString *const kParamNameGraffitiLikeCount;
extern NSString *const kParamNameGraffitiFlagged;
extern NSString *const kParamNameGraffitiDateCreated;
extern NSString *const kParamNameGraffitiAuthor;

@property (nonatomic, retain) NSString *text;
@property (nonatomic, retain) NSString *imageUrl;
@property (nonatomic, assign) float longitude;
@property (nonatomic, assign) float latitute;
@property (nonatomic, assign) float directionX;
@property (nonatomic, assign) float directionY;
@property (nonatomic, assign) float directionZ;
@property (nonatomic, assign) float radius;
@property (nonatomic, assign) NSUInteger likeCount;
@property (nonatomic, assign) BOOL flagged;
@property (nonatomic, retain) NSDate *dateCreated;
@property (nonatomic, retain) User *author;

- (NSDictionary *)parameterDictionary;
- (void)updateWithDictionary:(NSDictionary *)dictionary;

@end
