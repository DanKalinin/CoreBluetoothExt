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

@dynamic parent;
@dynamic delegates;

- (instancetype)initWithOptions:(NSDictionary *)options timeout:(NSTimeInterval)timeout {
    self = [super initWithTimeout:timeout];
    
    self.options = options;
    
    return self;
}

- (void)updateState:(NSEOperationState)state {
    [super updateState:state];
    
    [self.delegates cbePeripheralConnectionDidUpdateState:self];
    if (state == NSEOperationStateDidStart) {
        [self.delegates cbePeripheralConnectionDidStart:self];
    } else if (state == NSEOperationStateDidCancel) {
        [self.delegates cbePeripheralConnectionDidCancel:self];
    } else if (state == NSEOperationStateDidFinish) {
        [self.delegates cbePeripheralConnectionDidFinish:self];
    }
}

- (void)updateProgress:(int64_t)completedUnitCount {
    [super updateProgress:completedUnitCount];
    
    [self.delegates cbePeripheralConnectionDidUpdateProgress:self];
}

#pragma mark - CBEPeripheralConnectionDelegate

- (void)cbePeripheralConnectionDidStart:(CBEPeripheralConnection *)connection {
    if (self.parent.object.state == CBPeripheralStateConnected) {
        [self finish];
    } else {
        self.parent.connection = self;
        
        if (self.parent.object.state == CBPeripheralStateConnecting) {
        } else {
            [self.parent.parent.object connectPeripheral:self.parent.object options:self.options];
        }
    }
}

- (void)cbePeripheralConnectionDidCancel:(CBEPeripheralConnection *)connection {
    
}

@end










@interface CBEPeripheralDisconnection ()

@end



@implementation CBEPeripheralDisconnection

@dynamic parent;
@dynamic delegates;

- (void)updateState:(NSEOperationState)state {
    [super updateState:state];
    
    [self.delegates cbePeripheralDisconnectionDidUpdateState:self];
    if (state == NSEOperationStateDidStart) {
        [self.delegates cbePeripheralDisconnectionDidStart:self];
    } else if (state == NSEOperationStateDidCancel) {
        [self.delegates cbePeripheralDisconnectionDidCancel:self];
    } else if (state == NSEOperationStateDidFinish) {
        [self.delegates cbePeripheralDisconnectionDidFinish:self];
    }
}

- (void)updateProgress:(int64_t)completedUnitCount {
    [super updateProgress:completedUnitCount];
    
    [self.delegates cbePeripheralDisconnectionDidUpdateProgress:self];
}

#pragma mark - CBEPeripheralDisconnectionDelegate

- (void)cbePeripheralDisconnectionDidStart:(CBEPeripheralDisconnection *)disconnection {
    if (self.parent.object.state == CBPeripheralStateDisconnected) {
        [self finish];
    } else {
        self.parent.disconnection = self;
        
        if (self.parent.object.state == CBPeripheralStateDisconnecting) {
        } else {
            [self.parent.parent.object cancelPeripheralConnection:self.parent.object];
        }
    }
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
    [self.parent.peripherals addObject:self.object];
    
    CBEPeripheralConnection *connection = [CBEPeripheralConnection.alloc initWithOptions:options timeout:timeout];
    
    [self addOperation:connection];
    
    return connection;
}

- (CBEPeripheralConnection *)connectWithOptions:(NSDictionary *)options timeout:(NSTimeInterval)timeout completion:(NSEBlock)completion {
    CBEPeripheralConnection *connection = [self connectWithOptions:options timeout:timeout];
    
    connection.completion = completion;
    
    return connection;
}

- (CBEPeripheralDisconnection *)disconnect {
    CBEPeripheralDisconnection *disconnection = CBEPeripheralDisconnection.new;
    
    [self addOperation:disconnection];
    
    return disconnection;
}

- (CBEPeripheralDisconnection *)disconnectWithCompletion:(NSEBlock)completion {
    CBEPeripheralDisconnection *disconnection = self.disconnect;
    
    disconnection.completion = completion;
    
    return disconnection;
}

@end
