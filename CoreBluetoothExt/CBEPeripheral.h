//
//  CBEPeripheral.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/26/19.
//

#import "CBEPeer.h"
#import "CBEService.h"
#import "CBEL2CAPChannel.h"

@class CBEPeripheral;
@class CBEPeripheralAdvertisement;
@class CBEPeripheralServicesDiscovery;
@class CBEPeripheralCharacteristicsDiscovery;
@class CBEPeripheralCharacteristicValueReading;
@class CBEPeripheralL2CAPChannelOpening;
@class CBEPeripheralOperation;

@protocol CBEPeripheralDelegate;
@protocol CBEPeripheralServicesDiscoveryDelegate;
@protocol CBEPeripheralCharacteristicsDiscoveryDelegate;
@protocol CBEPeripheralCharacteristicValueReadingDelegate;
@protocol CBEPeripheralL2CAPChannelOpeningDelegate;










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










@protocol CBEPeripheralL2CAPChannelOpeningDelegate <NSETimeoutOperationDelegate>

@optional
- (void)cbePeripheralL2CAPChannelOpeningDidUpdateState:(CBEPeripheralL2CAPChannelOpening *)opening;
- (void)cbePeripheralL2CAPChannelOpeningDidStart:(CBEPeripheralL2CAPChannelOpening *)opening;
- (void)cbePeripheralL2CAPChannelOpeningDidCancel:(CBEPeripheralL2CAPChannelOpening *)opening;
- (void)cbePeripheralL2CAPChannelOpeningDidFinish:(CBEPeripheralL2CAPChannelOpening *)opening;

- (void)cbePeripheralL2CAPChannelOpeningDidUpdateProgress:(CBEPeripheralL2CAPChannelOpening *)opening;

@end



@interface CBEPeripheralL2CAPChannelOpening : NSETimeoutOperation <CBEPeripheralL2CAPChannelOpeningDelegate>

@property (readonly) CBEPeripheralOperation *parent;
@property (readonly) NSMutableOrderedSet<CBEPeripheralL2CAPChannelOpeningDelegate> *delegates;
@property (readonly) CBL2CAPPSM psm;

- (instancetype)initWithPSM:(CBL2CAPPSM)psm timeout:(NSTimeInterval)timeout;

@end










@protocol CBEPeripheralDelegate <CBEPeerDelegate, CBEPeripheralServicesDiscoveryDelegate>

@end



@interface CBEPeripheralOperation : CBEPeerOperation <CBEPeripheralDelegate, CBPeripheralDelegate>

@property CBEPeripheralAdvertisement *advertisement;
@property NSNumber *rssi;

@property (readonly) NSMutableDictionary<NSNumber *, CBL2CAPChannel *> *l2capChannels;

@property (weak, readonly) CBPeripheral *object;
@property (weak, readonly) CBEPeripheralServicesDiscovery *servicesDiscovery;
@property (weak, readonly) CBEPeripheralCharacteristicsDiscovery *characteristicsDiscovery;
@property (weak, readonly) CBEPeripheralCharacteristicValueReading *characteristicValueReading;
@property (weak, readonly) CBEPeripheralL2CAPChannelOpening *l2capChannelOpening;

- (NSArray<CBService *> *)retrieveServicesWithIdentifiers:(NSArray<CBUUID *> *)identifiers;

- (CBEPeripheralServicesDiscovery *)discoverServices:(NSArray<CBUUID *> *)services timeout:(NSTimeInterval)timeout;
- (CBEPeripheralServicesDiscovery *)discoverServices:(NSArray<CBUUID *> *)services timeout:(NSTimeInterval)timeout completion:(NSEBlock)completion;

- (CBEPeripheralCharacteristicsDiscovery *)discoverCharacteristics:(NSArray<CBUUID *> *)characteristics forService:(CBService *)service timeout:(NSTimeInterval)timeout;
- (CBEPeripheralCharacteristicsDiscovery *)discoverCharacteristics:(NSArray<CBUUID *> *)characteristics forService:(CBService *)service timeout:(NSTimeInterval)timeout completion:(NSEBlock)completion;

- (CBEPeripheralCharacteristicValueReading *)readValueForCharacteristic:(CBCharacteristic *)characteristic timeout:(NSTimeInterval)timeout;
- (CBEPeripheralCharacteristicValueReading *)readValueForCharacteristic:(CBCharacteristic *)characteristic timeout:(NSTimeInterval)timeout completion:(NSEBlock)completion;

- (CBEPeripheralL2CAPChannelOpening *)openL2CAPChannel:(CBL2CAPPSM)psm timeout:(NSTimeInterval)timeout;
- (CBEPeripheralL2CAPChannelOpening *)openL2CAPChannel:(CBL2CAPPSM)psm timeout:(NSTimeInterval)timeout completion:(NSEBlock)completion;

@end
