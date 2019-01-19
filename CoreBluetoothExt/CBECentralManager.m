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

@end










@interface CBECentralManagerDidDiscoverPeripheral ()

@property CBPeripheral *peripheral;
@property NSDictionary *advertisementData;
@property NSNumber *rssi;

@end



@implementation CBECentralManagerDidDiscoverPeripheral

- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary *)advertisementData rssi:(NSNumber *)rssi {
    self = super.init;
    
    self.peripheral = peripheral;
    self.advertisementData = advertisementData;
    self.rssi = rssi;
    
    return self;
}

@end










@interface CBECentralManagerOperation ()

@property (weak) CBECentralManagerDidDiscoverPeripheral *didDiscoverPeripheral;

@end



@implementation CBECentralManagerOperation

@dynamic delegates;
@dynamic object;

- (instancetype)initWithObject:(CBCentralManager *)object {
    self = [super initWithObject:object];
    
    object.delegate = self;
    
    return self;
}

#pragma mark - CBCentralManagerDelegate

- (void)centralManagerDidUpdateState:(CBCentralManager *)central {
    [self.delegates cbeCentralManagerDidUpdateState:central];
}

- (void)centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary<NSString *,id> *)advertisementData RSSI:(NSNumber *)RSSI {
    self.didDiscoverPeripheral = [CBECentralManagerDidDiscoverPeripheral.alloc initWithPeripheral:peripheral advertisementData:advertisementData rssi:RSSI].nseAutorelease;
    [self.delegates cbeCentralManagerDidDiscoverPeripheral:central];
}

@end
