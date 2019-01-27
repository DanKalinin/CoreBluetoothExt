//
//  CBECentralManager.m
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/26/19.
//

#import "CBECentralManager.h"










@implementation CBCentralManager (CBE)

@dynamic nseOperation;

- (Class)nseOperationClass {
    return CBECentralManagerOperation.class;
}

@end










@interface CBECentralManager ()

@end



@implementation CBECentralManager

@end










@interface CBECentralManagerDidDiscoverPeripheral ()

@property CBPeripheral *peripheral;
@property CBEPeripheralAdvertisement *advertisement;
@property NSNumber *rssi;

@end



@implementation CBECentralManagerDidDiscoverPeripheral

- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral advertisement:(CBEPeripheralAdvertisement *)advertisement rssi:(NSNumber *)rssi {
    self = super.init;
    
    self.peripheral = peripheral;
    self.advertisement = advertisement;
    self.rssi = rssi;
    
    return self;
}

@end










@interface CBECentralManagerDidDisconnectPeripheral ()

@property CBPeripheral *peripheral;
@property NSError *error;

@end



@implementation CBECentralManagerDidDisconnectPeripheral

- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral error:(NSError *)error {
    self = super.init;
    
    self.peripheral = peripheral;
    self.error = error;
    
    return self;
}

@end










@interface CBECentralManagerPeripheralDisconnection ()

@property CBPeripheral *peripheral;

@end



@implementation CBECentralManagerPeripheralDisconnection

@dynamic parent;
@dynamic delegates;

- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral {
    self = super.init;
    
    self.peripheral = peripheral;
    
    return self;
}

- (void)updateState:(NSEOperationState)state {
    [super updateState:state];
    
    [self.delegates cbeCentralManagerPeripheralDisconnectionDidUpdateState:self];
    if (state == NSEOperationStateDidStart) {
        [self.delegates cbeCentralManagerPeripheralDisconnectionDidStart:self];
    } else if (state == NSEOperationStateDidCancel) {
        [self.delegates cbeCentralManagerPeripheralDisconnectionDidCancel:self];
    } else if (state == NSEOperationStateDidFinish) {
        [self.delegates cbeCentralManagerPeripheralDisconnectionDidFinish:self];
    }
}

- (void)updateProgress:(int64_t)completedUnitCount {
    [super updateProgress:completedUnitCount];
    
    [self.delegates cbeCentralManagerPeripheralDisconnectionDidUpdateProgress:self];
}

#pragma mark - CBECentralManagerPeripheralDisconnectionDelegate

- (void)cbeCentralManagerPeripheralDisconnectionDidStart:(CBECentralManagerPeripheralDisconnection *)disconnection {
    if (self.peripheral.state == CBPeripheralStateDisconnected) {
        [self finish];
    } else {
        if (self.peripheral.state == CBPeripheralStateDisconnecting) {
        } else {
            [self.parent.object cancelPeripheralConnection:self.peripheral];
        }
    }
}

@end










@interface CBECentralManagerPeripheralConnection ()

@property CBPeripheral *peripheral;
@property NSDictionary *options;
@property CBECentralManagerPeripheralDisconnection *disconnection;

@end



@implementation CBECentralManagerPeripheralConnection

@dynamic parent;
@dynamic delegates;

- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral options:(NSDictionary *)options timeout:(NSTimeInterval)timeout {
    self = [super initWithTimeout:timeout];
    
    self.peripheral = peripheral;
    self.options = options;
    
    return self;
}

- (void)updateState:(NSEOperationState)state {
    [super updateState:state];
    
    [self.delegates cbeCentralManagerPeripheralConnectionDidUpdateState:self];
    if (state == NSEOperationStateDidStart) {
        [self.delegates cbeCentralManagerPeripheralConnectionDidStart:self];
    } else if (state == NSEOperationStateDidCancel) {
        [self.delegates cbeCentralManagerPeripheralConnectionDidCancel:self];
    } else if (state == NSEOperationStateDidFinish) {
        [self.delegates cbeCentralManagerPeripheralConnectionDidFinish:self];
    }
}

- (void)updateProgress:(int64_t)completedUnitCount {
    [super updateProgress:completedUnitCount];
    
    [self.delegates cbeCentralManagerPeripheralConnectionDidUpdateProgress:self];
}

#pragma mark - CBECentralManagerPeripheralConnectionDelegate

- (void)cbeCentralManagerPeripheralConnectionDidStart:(CBECentralManagerPeripheralConnection *)connection {
    if (self.peripheral.state == CBPeripheralStateConnected) {
        [self finish];
    } else {
        if (self.peripheral.state == CBPeripheralStateConnecting) {
        } else {
            [self.parent.object connectPeripheral:self.peripheral options:self.options];
        }
    }
}

- (void)cbeCentralManagerPeripheralConnectionDidCancel:(CBECentralManagerPeripheralConnection *)connection {
    self.disconnection = [self.parent disconnectPeripheral:self.peripheral];
    [self.disconnection.delegates addObject:self];
}

#pragma mark - CBECentralManagerPeripheralDisconnectionDelegate

- (void)cbeCentralManagerPeripheralDisconnectionDidFinish:(CBECentralManagerPeripheralDisconnection *)disconnection {
    [self finish];
}

@end










@interface CBECentralManagerOperation ()

@property NSMutableSet<CBPeripheral *> *peripherals;

@property (weak) CBECentralManagerDidDiscoverPeripheral *didDiscoverPeripheral;
@property (weak) CBECentralManagerDidDisconnectPeripheral *didDisconnectPeripheral;
@property (weak) CBECentralManagerPeripheralDisconnection *disconnection;
@property (weak) CBECentralManagerPeripheralConnection *connection;

@end



@implementation CBECentralManagerOperation

@dynamic delegates;
@dynamic object;

- (instancetype)initWithObject:(CBCentralManager *)object {
    self = [super initWithObject:object];
    
    object.delegate = self;
    
    self.peripherals = NSMutableSet.set;
    
    return self;
}

- (CBECentralManagerPeripheralDisconnection *)disconnectPeripheral:(CBPeripheral *)peripheral {
    self.disconnection = [CBECentralManagerPeripheralDisconnection.alloc initWithPeripheral:peripheral].nseAutorelease;
    
    [self addOperation:self.disconnection];
    
    return self.disconnection;
}

- (CBECentralManagerPeripheralDisconnection *)disconnectPeripheral:(CBPeripheral *)peripheral completion:(NSEBlock)completion {
    CBECentralManagerPeripheralDisconnection *disconnection = [self disconnectPeripheral:peripheral];
    
    disconnection.completion = completion;
    
    return disconnection;
}

- (CBECentralManagerPeripheralConnection *)connectPeripheral:(CBPeripheral *)peripheral options:(NSDictionary *)options timeout:(NSTimeInterval)timeout {
    self.connection = [CBECentralManagerPeripheralConnection.alloc initWithPeripheral:peripheral options:options timeout:timeout].nseAutorelease;
    
    [self addOperation:self.connection];
    
    return self.connection;
}

- (CBECentralManagerPeripheralConnection *)connectPeripheral:(CBPeripheral *)peripheral options:(NSDictionary *)options timeout:(NSTimeInterval)timeout completion:(NSEBlock)completion {
    CBECentralManagerPeripheralConnection *connection = [self connectPeripheral:peripheral options:options timeout:timeout];
    
    connection.completion = completion;
    
    return connection;
}

#pragma mark - CBCentralManagerDelegate

- (void)centralManagerDidUpdateState:(CBCentralManager *)central {
    [self.delegates cbeCentralManagerDidUpdateState:central];
    
    if (central.state == CBManagerStatePoweredOn) {
    } else {
        [self.peripherals removeAllObjects];
    }
}

- (void)centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)RSSI {
    CBEPeripheralAdvertisement *advertisement = [CBEPeripheralAdvertisement.alloc initWithDictionary:advertisementData];
    
    peripheral.nseOperation.advertisement = advertisement;
    peripheral.nseOperation.rssi = RSSI;
    
    self.didDiscoverPeripheral = [CBECentralManagerDidDiscoverPeripheral.alloc initWithPeripheral:peripheral advertisement:advertisement rssi:RSSI].nseAutorelease;
    [self.delegates cbeCentralManagerDidDiscoverPeripheral:central];
}

- (void)centralManager:(CBCentralManager *)central didConnectPeripheral:(CBPeripheral *)peripheral {
    [self.connection finish];
    
    [self.peripherals addObject:peripheral];
    
    [peripheral.nseOperation.delegates addObject:self.delegates];
}

- (void)centralManager:(CBCentralManager *)central didFailToConnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error {
    self.connection.error = error;
    [self.connection cancel];
}

- (void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error {
    if (error) {
        self.didDisconnectPeripheral = [CBECentralManagerDidDisconnectPeripheral.alloc initWithPeripheral:peripheral error:error].nseAutorelease;
        [self.delegates cbeCentralManagerDidDisconnectPeripheral:central];
    } else {
        [self.disconnection finish];
    }
    
    [self.peripherals removeObject:peripheral];
    
    [peripheral.nseOperation.channels removeAllObjects];
}

@end
