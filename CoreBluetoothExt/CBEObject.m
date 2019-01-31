//
//  CBEObject.m
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/31/19.
//

#import "CBEObject.h"










@implementation NSObject (CBE)

- (Class)cbeOperationClass {
    return NSEObjectOperation.class;
}

- (NSEObjectOperation *)cbeOperation {
    NSEObjectOperation *operation = [self nseOperationForKey:@selector(cbeOperation) ofClass:self.cbeOperationClass];
    return operation;
}

@end










@interface CBEObject ()

@end



@implementation CBEObject

@end
