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

- (NSArray<CBPeripheral *> *)retrievePeripheralsWithIdentifiers:(NSArray<NSUUID *> *)identifiers {
    NSArray *peripherals = [self.object retrievePeripheralsWithIdentifiers:identifiers];
    
    for (CBPeripheral *peripheral in peripherals) {
        [peripheral.nseOperation.delegates addObject:self.delegates];
    }
    
    return peripherals;
}

- (NSArray<CBPeripheral *> *)retrieveConnectedPeripheralsWithServices:(NSArray<CBUUID *> *)serviceUUIDs {
    NSArray *peripherals = [self.object retrieveConnectedPeripheralsWithServices:serviceUUIDs];
    
    for (CBPeripheral *peripheral in peripherals) {
        [peripheral.nseOperation.delegates addObject:self.delegates];
    }
    
    return peripherals;
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
    [peripheral.nseOperation.delegates addObject:self.delegates];
    
    CBEAdvertisement *advertisement = [CBEAdvertisement.alloc initWithDictionary:advertisementData];
    
    self.didDiscoverPeripheral = [CBECentralManagerDidDiscoverPeripheral.alloc initWithPeripheral:peripheral advertisement:advertisement rssi:RSSI].nseAutorelease;
    [self.delegates cbeCentralManagerDidDiscoverPeripheral:central];
}

@end
