//
//  CBECentralManager.m
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/19/19.
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

- (void)connectPeripheral:(CBPeripheral *)peripheral options:(NSDictionary *)options {
    [super connectPeripheral:peripheral options:options];
    
    [self.nseOperation connectPeripheral:peripheral options:options];
}

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










@interface CBECentralManagerOperation ()

@property NSMutableSet<CBPeripheral *> *peripherals;

@property (weak) CBECentralManagerDidDiscoverPeripheral *didDiscoverPeripheral;

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

- (void)connectPeripheral:(CBPeripheral *)peripheral options:(NSDictionary *)options {
    [self.peripherals addObject:peripheral];
    
    [peripheral.nseOperation.delegates addObject:self.delegates];
}

#pragma mark - CBCentralManagerDelegate

- (void)centralManagerDidUpdateState:(CBCentralManager *)central {
    [self.delegates cbeCentralManagerDidUpdateState:central];
    
    if (central.state == CBManagerStatePoweredOn) {
    } else {
        [self.peripherals removeAllObjects];
    }
}

- (void)centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary<NSString *,id> *)advertisementData RSSI:(NSNumber *)RSSI {
    CBEPeripheralAdvertisement *advertisement = [CBEPeripheralAdvertisement.alloc initWithDictionary:advertisementData];
    
    peripheral.nseOperation.advertisement = advertisement;
    peripheral.nseOperation.rssi = RSSI;
    
    self.didDiscoverPeripheral = [CBECentralManagerDidDiscoverPeripheral.alloc initWithPeripheral:peripheral advertisement:advertisement rssi:RSSI].nseAutorelease;
    [self.delegates cbeCentralManagerDidDiscoverPeripheral:central];
}

- (void)centralManager:(CBCentralManager *)central didConnectPeripheral:(CBPeripheral *)peripheral {
    [peripheral.nseOperation.delegates cbePeripheralDidConnect:peripheral];
}

- (void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error {
    if (error) {
        peripheral.nseOperation.didDisconnect = [CBEPeripheralDidDisconnect.alloc initWithError:error].nseAutorelease;
        [peripheral.nseOperation.delegates cbePeripheralDidDisconnect:peripheral];
    } else {
        [peripheral.nseOperation.delegates cbePeripheralDidCancelConnection:peripheral];
    }
}

@end
