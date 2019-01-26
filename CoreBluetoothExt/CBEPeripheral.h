//
//  CBEPeripheral.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/26/19.
//

#import "CBEPeer.h"
#import "CBEService.h"

@class CBEPeripheral;
@class CBEPeripheralAdvertisement;
@class CBEPeripheralServicesDiscovery;
@class CBEPeripheralCharacteristicsDiscovery;
@class CBEPeripheralCharacteristicValueReading;
@class CBEPeripheralOperation;

@protocol CBEPeripheralDelegate;
@protocol CBEPeripheralServicesDiscoveryDelegate;
@protocol CBEPeripheralCharacteristicsDiscoveryDelegate;
@protocol CBEPeripheralCharacteristicValueReadingDelegate;










@interface CBPeripheral (CBE)

@property (readonly) CBEPeripheralOperation *nseOperation;

@end










@interface CBEPeripheral : CBPeripheral

@end










@interface CBEPeripheralAdvertisement : NSEDictionaryObject

@property (readonly) NSArray<CBUUID *> *serviceUUIDs;
@property (readonly) BOOL isConnectable;

@end










@protocol CBEPeripheralServicesDiscoveryDelegate <NSETimeoutOperationDelegate>

@optional
- (void)cbePeripheralServicesDiscoveryDidUpdateState:(CBEPeripheralServicesDiscovery *)discovery;
- (void)cbePeripheralServicesDiscoveryDidStart:(CBEPeripheralServicesDiscovery *)discovery;
- (void)cbePeripheralServicesDiscoveryDidCancel:(CBEPeripheralServicesDiscovery *)discovery;
- (void)cbePeripheralServicesDiscoveryDidFinish:(CBEPeripheralServicesDiscovery *)discovery;

- (void)cbePeripheralServicesDiscoveryDidUpdateProgress:(CBEPeripheralServicesDiscovery *)discovery;

@end



@interface CBEPeripheralServicesDiscovery : NSETimeoutOperation <CBEPeripheralServicesDiscoveryDelegate>

@property (readonly) CBEPeripheralOperation *parent;
@property (readonly) NSMutableOrderedSet<CBEPeripheralServicesDiscoveryDelegate> *delegates;
@property (readonly) NSArray<CBUUID *> *services;

- (instancetype)initWithServices:(NSArray<CBUUID *> *)services timeout:(NSTimeInterval)timeout;

@end










@protocol CBEPeripheralCharacteristicsDiscoveryDelegate <NSETimeoutOperationDelegate>

@optional
- (void)cbePeripheralCharacteristicsDiscoveryDidUpdateState:(CBEPeripheralCharacteristicsDiscovery *)discovery;
- (void)cbePeripheralCharacteristicsDiscoveryDidStart:(CBEPeripheralCharacteristicsDiscovery *)discovery;
- (void)cbePeripheralCharacteristicsDiscoveryDidCancel:(CBEPeripheralCharacteristicsDiscovery *)discovery;
- (void)cbePeripheralCharacteristicsDiscoveryDidFinish:(CBEPeripheralCharacteristicsDiscovery *)discovery;

- (void)cbePeripheralCharacteristicsDiscoveryDidUpdateProgress:(CBEPeripheralCharacteristicsDiscovery *)discovery;

@end



@interface CBEPeripheralCharacteristicsDiscovery : NSETimeoutOperation <CBEPeripheralCharacteristicsDiscoveryDelegate>

@property (readonly) CBEPeripheralOperation *parent;
@property (readonly) NSMutableOrderedSet<CBEPeripheralCharacteristicsDiscoveryDelegate> *delegates;
@property (readonly) NSArray<CBUUID *> *characteristics;
@property (readonly) CBService *service;

- (instancetype)initWithCharacteristics:(NSArray<CBUUID *> *)characteristics service:(CBService *)service timeout:(NSTimeInterval)timeout;

@end










@protocol CBEPeripheralCharacteristicValueReadingDelegate <NSETimeoutOperationDelegate>

@optional
- (void)cbePeripheralCharacteristicValueReadingDidUpdateState:(CBEPeripheralCharacteristicValueReading *)reading;
- (void)cbePeripheralCharacteristicValueReadingDidStart:(CBEPeripheralCharacteristicValueReading *)reading;
- (void)cbePeripheralCharacteristicValueReadingDidCancel:(CBEPeripheralCharacteristicValueReading *)reading;
- (void)cbePeripheralCharacteristicValueReadingDidFinish:(CBEPeripheralCharacteristicValueReading *)reading;

- (void)cbePeripheralCharacteristicValueReadingDidUpdateProgress:(CBEPeripheralCharacteristicValueReading *)reading;

@end



@interface CBEPeripheralCharacteristicValueReading : NSETimeoutOperation <CBEPeripheralCharacteristicValueReadingDelegate>

@property (readonly) CBEPeripheralOperation *parent;
@property (readonly) NSMutableOrderedSet<CBEPeripheralCharacteristicValueReadingDelegate> *delegates;
@property (readonly) CBCharacteristic *characteristic;

- (instancetype)initWithCharacteristic:(CBCharacteristic *)characteristic timeout:(NSTimeInterval)timeout;

@end










@protocol CBEPeripheralDelegate <CBEPeerDelegate, CBEPeripheralServicesDiscoveryDelegate>

@end



@interface CBEPeripheralOperation : CBEPeerOperation <CBEPeripheralDelegate, CBPeripheralDelegate>

@property CBEPeripheralAdvertisement *advertisement;
@property NSNumber *rssi;

@property (weak, readonly) CBPeripheral *object;
@property (weak, readonly) CBEPeripheralServicesDiscovery *servicesDiscovery;
@property (weak, readonly) CBEPeripheralCharacteristicsDiscovery *characteristicsDiscovery;
@property (weak, readonly) CBEPeripheralCharacteristicValueReading *characteristicValueReading;

- (NSArray<CBService *> *)retrieveServicesWithIdentifiers:(NSArray<CBUUID *> *)identifiers;

- (CBEPeripheralServicesDiscovery *)discoverServices:(NSArray<CBUUID *> *)services timeout:(NSTimeInterval)timeout;
- (CBEPeripheralServicesDiscovery *)discoverServices:(NSArray<CBUUID *> *)services timeout:(NSTimeInterval)timeout completion:(NSEBlock)completion;

- (CBEPeripheralCharacteristicsDiscovery *)discoverCharacteristics:(NSArray<CBUUID *> *)characteristics forService:(CBService *)service timeout:(NSTimeInterval)timeout;
- (CBEPeripheralCharacteristicsDiscovery *)discoverCharacteristics:(NSArray<CBUUID *> *)characteristics forService:(CBService *)service timeout:(NSTimeInterval)timeout completion:(NSEBlock)completion;

- (CBEPeripheralCharacteristicValueReading *)readValueForCharacteristic:(CBCharacteristic *)characteristic timeout:(NSTimeInterval)timeout;
- (CBEPeripheralCharacteristicValueReading *)readValueForCharacteristic:(CBCharacteristic *)characteristic timeout:(NSTimeInterval)timeout completion:(NSEBlock)completion;

@end
