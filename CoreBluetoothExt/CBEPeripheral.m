//
//  CBEPeripheral.m
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/19/19.
//

#import "CBEPeripheral.h"










@implementation CBPeripheral (CBE)

@dynamic nseOperation;

- (Class)nseOperationClass {
    return CBEPeripheralOperation.class;
}

@end










@interface CBEPeripheral ()

@end



@implementation CBEPeripheral

@end










@interface CBEPeripheralDidDisconnect ()

@property NSError *error;

@end



@implementation CBEPeripheralDidDisconnect

- (instancetype)initWithError:(NSError *)error {
    self = super.init;
    
    self.error = error;
    
    return self;
}

@end










@interface CBEPeripheralOperation ()

@end



@implementation CBEPeripheralOperation

@dynamic object;

- (instancetype)initWithObject:(CBPeripheral *)object {
    self = [super initWithObject:object];
    
    object.delegate = self;
    
    return self;
}

@end
