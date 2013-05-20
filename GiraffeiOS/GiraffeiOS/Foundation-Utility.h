//
//  Foundation-Utility.h
//  GiraffeiOS
//
//  Created by Kurtis Horimoto on 5/8/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSObject (Utility)

- (id)ifIsKindOfClass:(Class)aClass;

@end

#define NSDefaults [NSUserDefaults standardUserDefaults]