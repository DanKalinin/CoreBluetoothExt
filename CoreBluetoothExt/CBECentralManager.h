//
//  CBECentralManager.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/19/19.
//

#import "CBEManager.h"
#import "CBEPeripheral.h"

@class CBECentralManager;
@class CBECentralManagerDidDiscoverPeripheral;
@class CBECentralManagerOperation;

@protocol CBECentralManagerDelegate;










@interface CBCentralManager (CBE)

@property (readonly) CBECentralManagerOperation *nseOperation;

@end










@interface CBECentralManager : CBCentralManager

@end










@interface CBECentralManagerDidDiscoverPeripheral : NSEObject

@property (readonly) CBPeripheral *peripheral;
@property (readonly) CBEPeripheralAdvertisement *advertisement;
@property (readonly) NSNumber *rssi;

- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral advertisement:(CBEPeripheralAdvertisement *)advertisement rssi:(NSNumber *)rssi;

@end










@protocol CBECentralManagerDelegate <CBEManagerDelegate, CBEPeripheralDelegate>

@optional
- (void)cbeCentralManagerDidUpdateState:(CBCentralManager *)central;
- (void)cbeCentralManagerDidDiscoverPeripheral:(CBCentralManager *)central;

@end



@interface CBECentralManagerOperation : CBEManagerOperation <CBECentralManagerDelegate, CBCentralManagerDelegate>

@property (readonly) NSMutableOrderedSet<CBECentralManagerDelegate> *delegates;
@property (readonly) NSMutableSet<CBPeripheral *> *peripherals;

@property (weak, readonly) CBCentralManager *object;
@property (weak, readonly) CBECentralManagerDidDiscoverPeripheral *didDiscoverPeripheral;

- (void)connectPeripheral:(CBPeripheral *)peripheral options:(NSDictionary *)options;

@end
