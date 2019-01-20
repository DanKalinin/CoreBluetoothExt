//
//  CBEPeripheral.m
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/19/19.
//

#import "CBEPeripheral.h"
#import "CBECentralManager.h"










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










@interface CBEPeripheralAdvertisement ()

@property NSArray<CBUUID *> *serviceUUIDs;
@property BOOL isConnectable;

@end



@implementation CBEPeripheralAdvertisement

- (instancetype)initWithDictionary:(NSDictionary *)dictionary {
    self = [super initWithDictionary:dictionary];
    
    self.serviceUUIDs = dictionary[CBAdvertisementDataServiceUUIDsKey];
    self.isConnectable = [dictionary[CBAdvertisementDataIsConnectable] boolValue];
    
    return self;
}

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










@interface CBEPeripheralConnection ()

@property NSDictionary *options;

@end



@implementation CBEPeripheralConnection

- (instancetype)initWithOptions:(NSDictionary *)options timeout:(NSTimeInterval)timeout {
    self = [super initWithTimeout:timeout];
    
    self.options = options;
    
    return self;
}

@end










@interface CBEPeripheralOperation ()

@end



@implementation CBEPeripheralOperation

@dynamic parent;
@dynamic delegates;
@dynamic object;

- (instancetype)initWithObject:(CBPeripheral *)object {
    self = [super initWithObject:object];
    
    object.delegate = self;
    
    return self;
}

- (CBEPeripheralConnection *)connectWithOptions:(NSDictionary *)options timeout:(NSTimeInterval)timeout {
    CBEPeripheralConnection *connection = [CBEPeripheralConnection.alloc initWithOptions:options timeout:timeout];
    
    [self addOperation:connection];
    
    return connection;
}

- (CBEPeripheralConnection *)connectWithOptions:(NSDictionary *)options timeout:(NSTimeInterval)timeout completion:(NSEBlock)completion {
    CBEPeripheralConnection *connection = [self connectWithOptions:options timeout:timeout];
    
    connection.completion = completion;
    
    return connection;
}

@end
