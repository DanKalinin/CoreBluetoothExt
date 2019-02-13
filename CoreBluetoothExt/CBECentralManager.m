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
@property CBEAdvertisement *advertisement;
@property NSNumber *rssi;

@end



@implementation CBECentralManagerDidDiscoverPeripheral

- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral advertisement:(CBEAdvertisement *)advertisement rssi:(NSNumber *)rssi {
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










@interface CBECentralManagerDisconnection ()

@property CBPeripheral *peripheral;

@end



@implementation CBECentralManagerDisconnection

@dynamic parent;
@dynamic delegates;

- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral {
    self = super.init;
    
    self.peripheral = peripheral;
    
    return self;
}

- (void)updateState:(NSEOperationState)state {
    [super updateState:state];
    
    [self.delegates cbeCentralManagerDisconnectionDidUpdateState:self];
    if (state == NSEOperationStateDidStart) {
        [self.delegates cbeCentralManagerDisconnectionDidStart:self];
    } else if (state == NSEOperationStateDidCancel) {
        [self.delegates cbeCentralManagerDisconnectionDidCancel:self];
    } else if (state == NSEOperationStateDidFinish) {
        [self.delegates cbeCentralManagerDisconnectionDidFinish:self];
    }
}

- (void)updateProgress:(int64_t)completedUnitCount {
    [super updateProgress:completedUnitCount];
    
    [self.delegates cbeCentralManagerDisconnectionDidUpdateProgress:self];
}

#pragma mark - CBECentralManagerDisconnectionDelegate

- (void)cbeCentralManagerDisconnectionDidStart:(CBECentralManagerDisconnection *)disconnection {
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










@interface CBECentralManagerConnection ()

@property CBPeripheral *peripheral;
@property NSDictionary *options;
@property CBECentralManagerDisconnection *disconnection;

@end



@implementation CBECentralManagerConnection

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
    
    [self.delegates cbeCentralManagerConnectionDidUpdateState:self];
    if (state == NSEOperationStateDidStart) {
        [self.delegates cbeCentralManagerConnectionDidStart:self];
    } else if (state == NSEOperationStateDidCancel) {
        [self.delegates cbeCentralManagerConnectionDidCancel:self];
    } else if (state == NSEOperationStateDidFinish) {
        [self.delegates cbeCentralManagerConnectionDidFinish:self];
    }
}

- (void)updateProgress:(int64_t)completedUnitCount {
    [super updateProgress:completedUnitCount];
    
    [self.delegates cbeCentralManagerConnectionDidUpdateProgress:self];
}

#pragma mark - CBECentralManagerConnectionDelegate

- (void)cbeCentralManagerConnectionDidStart:(CBECentralManagerConnection *)connection {
    if (self.peripheral.state == CBPeripheralStateConnected) {
        [self finish];
    } else {
        if (self.peripheral.state == CBPeripheralStateConnecting) {
        } else {
            [self.parent.object connectPeripheral:self.peripheral options:self.options];
        }
    }
}

- (void)cbeCentralManagerConnectionDidCancel:(CBECentralManagerConnection *)connection {
    self.disconnection = [self.parent disconnectPeripheral:self.peripheral];
    [self.disconnection.delegates addObject:self];
}

#pragma mark - CBECentralManagerDisconnectionDelegate

- (void)cbeCentralManagerDisconnectionDidFinish:(CBECentralManagerDisconnection *)disconnection {
    [self finish];
}

@end










@interface CBECentralManagerOperation ()

@property NSMutableSet<CBPeripheral *> *peripherals;

@property (weak) CBECentralManagerDidDiscoverPeripheral *didDiscoverPeripheral;
@property (weak) CBECentralManagerDidDisconnectPeripheral *didDisconnectPeripheral;
@property (weak) CBECentralManagerDisconnection *disconnection;
@property (weak) CBECentralManagerConnection *connection;

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

- (CBECentralManagerDisconnection *)disconnectPeripheral:(CBPeripheral *)peripheral {
    self.disconnection = [CBECentralManagerDisconnection.alloc initWithPeripheral:peripheral].nseAutorelease;
    
    [self addOperation:self.disconnection];
    
    return self.disconnection;
}

- (CBECentralManagerDisconnection *)disconnectPeripheral:(CBPeripheral *)peripheral completion:(NSEBlock)completion {
    CBECentralManagerDisconnection *disconnection = [self disconnectPeripheral:peripheral];
    
    disconnection.completion = completion;
    
    return disconnection;
}

- (CBECentralManagerConnection *)connectPeripheral:(CBPeripheral *)peripheral options:(NSDictionary *)options timeout:(NSTimeInterval)timeout {
    self.connection = [CBECentralManagerConnection.alloc initWithPeripheral:peripheral options:options timeout:timeout].nseAutorelease;
    
    [self addOperation:self.connection];
    
    return self.connection;
}

- (CBECentralManagerConnection *)connectPeripheral:(CBPeripheral *)peripheral options:(NSDictionary *)options timeout:(NSTimeInterval)timeout completion:(NSEBlock)completion {
    CBECentralManagerConnection *connection = [self connectPeripheral:peripheral options:options timeout:timeout];
    
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
    CBEAdvertisement *advertisement = [CBEAdvertisement.alloc initWithDictionary:advertisementData];
    
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
    [self.connection finish];
}

- (void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error {
    if (error) {
        self.didDisconnectPeripheral = [CBECentralManagerDidDisconnectPeripheral.alloc initWithPeripheral:peripheral error:error].nseAutorelease;
        [self.delegates cbeCentralManagerDidDisconnectPeripheral:central];
    } else {
        [self.disconnection finish];
    }
    
    [self.peripherals removeObject:peripheral];
    
    [peripheral.nseOperation.l2capChannels removeAllObjects];
}

@end
