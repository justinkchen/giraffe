//
//  Foundation-Utility.m
//  GiraffeiOS
//
//  Created by Kurtis Horimoto on 5/8/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "Foundation-Utility.h"

@implementation NSObject (Utility)

- (id)ifIsKindOfClass:(Class)aClass
{
    if ([self isKindOfClass:aClass]) {
        return self;
    }
    
    return nil;
}

@end
