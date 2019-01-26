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
@class CBEPeripheralOperation;

@protocol CBEPeripheralDelegate;
@protocol CBEPeripheralServicesDiscoveryDelegate;
@protocol CBEPeripheralCharacteristicsDiscoveryDelegate;










@interface CBPeripheral (CBE)

@property (readonly) CBEPeripheralOperation *nseOperation;

@end










@interface CBEPeripheral : CBPeripheral

@end










@interface CBEPeripheralAdvertisement : NSEDictionaryObject

@property (readonly) NSArray<CBUUID *> *serviceUUIDs;
@property (readonly) BOOL isConnectable;

@end










@protocol CBEPeripheralServicesDiscoveryDelegate <NSEOperationDelegate>

@optional
- (void)cbePeripheralServicesDiscoveryDidUpdateState:(CBEPeripheralServicesDiscovery *)discovery;
- (void)cbePeripheralServicesDiscoveryDidStart:(CBEPeripheralServicesDiscovery *)discovery;
- (void)cbePeripheralServicesDiscoveryDidCancel:(CBEPeripheralServicesDiscovery *)discovery;
- (void)cbePeripheralServicesDiscoveryDidFinish:(CBEPeripheralServicesDiscovery *)discovery;

- (void)cbePeripheralServicesDiscoveryDidUpdateProgress:(CBEPeripheralServicesDiscovery *)discovery;

@end



@interface CBEPeripheralServicesDiscovery : NSEOperation <CBEPeripheralServicesDiscoveryDelegate>

@property (readonly) CBEPeripheralOperation *parent;
@property (readonly) NSMutableOrderedSet<CBEPeripheralServicesDiscoveryDelegate> *delegates;
@property (readonly) NSArray<CBUUID *> *services;

- (instancetype)initWithServices:(NSArray<CBUUID *> *)services;

@end










@protocol CBEPeripheralCharacteristicsDiscoveryDelegate <NSEOperationDelegate>

@optional
- (void)cbePeripheralCharacteristicsDiscoveryDidUpdateState:(CBEPeripheralCharacteristicsDiscovery *)discovery;
- (void)cbePeripheralCharacteristicsDiscoveryDidStart:(CBEPeripheralCharacteristicsDiscovery *)discovery;
- (void)cbePeripheralCharacteristicsDiscoveryDidCancel:(CBEPeripheralCharacteristicsDiscovery *)discovery;
- (void)cbePeripheralCharacteristicsDiscoveryDidFinish:(CBEPeripheralCharacteristicsDiscovery *)discovery;

- (void)cbePeripheralCharacteristicsDiscoveryDidUpdateProgress:(CBEPeripheralCharacteristicsDiscovery *)discovery;

@end



@interface CBEPeripheralCharacteristicsDiscovery : NSEOperation <CBEPeripheralCharacteristicsDiscoveryDelegate>

@property (readonly) CBEPeripheralOperation *parent;
@property (readonly) NSMutableOrderedSet<CBEPeripheralCharacteristicsDiscoveryDelegate> *delegates;
@property (readonly) NSArray<CBUUID *> *characteristics;
@property (readonly) CBService *service;

- (instancetype)initWithCharacteristics:(NSArray<CBUUID *> *)characteristics service:(CBService *)service;

@end










@protocol CBEPeripheralCharacteristicValueReadingDelegate <NSEOperationDelegate>

@end



@interface CBEPeripheralCharacteristicValueReading : NSEOperation <CBEPeripheralCharacteristicValueReadingDelegate>

@property (readonly) CBEPeripheralOperation *parent;
@property (readonly) NSMutableOrderedSet<CBEPeripheralCharacteristicValueReadingDelegate> *delegates;
@property (readonly) CBCharacteristic *characteristic;

- (instancetype)initWithCharacteristic:(CBCharacteristic *)characteristic;

@end










@protocol CBEPeripheralDelegate <CBEPeerDelegate, CBEPeripheralServicesDiscoveryDelegate>

@end



@interface CBEPeripheralOperation : CBEPeerOperation <CBEPeripheralDelegate, CBPeripheralDelegate>

@property CBEPeripheralAdvertisement *advertisement;
@property NSNumber *rssi;

@property (weak, readonly) CBPeripheral *object;
@property (weak, readonly) CBEPeripheralServicesDiscovery *servicesDiscovery;
@property (weak, readonly) CBEPeripheralCharacteristicsDiscovery *characteristicsDiscovery;

- (NSArray<CBService *> *)retrieveServicesWithIdentifiers:(NSArray<CBUUID *> *)identifiers;

- (CBEPeripheralServicesDiscovery *)discoverServices:(NSArray<CBUUID *> *)services;
- (CBEPeripheralServicesDiscovery *)discoverServices:(NSArray<CBUUID *> *)services completion:(NSEBlock)completion;

- (CBEPeripheralCharacteristicsDiscovery *)discoverCharacteristics:(NSArray<CBUUID *> *)characteristics forService:(CBService *)service;
- (CBEPeripheralCharacteristicsDiscovery *)discoverCharacteristics:(NSArray<CBUUID *> *)characteristics forService:(CBService *)service completion:(NSEBlock)completion;

@end
