//
//  GiraffeClient.h
//  GiraffeiOS
//
//  Created by Bryan Cheng on 5/6/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AFHTTPClient.h"

@interface GiraffeClient : AFHTTPClient

+ (GiraffeClient *)getGiraffeClient;

@end
