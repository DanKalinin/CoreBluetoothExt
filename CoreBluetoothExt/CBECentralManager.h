//
//  CBECentralManager.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/19/19.
//

#import "CBEManager.h"

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
@property (readonly) NSDictionary *advertisementData;
@property (readonly) NSNumber *rssi;

- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary *)advertisementData rssi:(NSNumber *)rssi;

@end










@protocol CBECentralManagerDelegate <CBEManagerDelegate>

@optional
- (void)cbeCentralManagerDidUpdateState:(CBCentralManager *)central;
- (void)cbeCentralManagerDidDiscoverPeripheral:(CBCentralManager *)central;

@end



@interface CBECentralManagerOperation : CBEManagerOperation <CBECentralManagerDelegate, CBCentralManagerDelegate>

@property (readonly) NSMutableOrderedSet<CBECentralManagerDelegate> *delegates;

@property (weak, readonly) CBCentralManager *object;
@property (weak, readonly) CBECentralManagerDidDiscoverPeripheral *didDiscoverPeripheral;

@end
