//
//  CBEPeripheral.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/26/19.
//

#import "CBEPeer.h"
#import "CBEAdvertisiment.h"
#import "CBEService.h"
#import "CBEL2CAPChannel.h"

@class CBEPeripheral;
@class CBEPeripheralServicesDiscovery;
@class CBEPeripheralCharacteristicsDiscovery;
@class CBEPeripheralCharacteristicReading;
@class CBEPeripheralL2CAPOpening;
@class CBEPeripheralOperation;

@protocol CBEPeripheralDelegate;
@protocol CBEPeripheralServicesDiscoveryDelegate;
@protocol CBEPeripheralCharacteristicsDiscoveryDelegate;
@protocol CBEPeripheralCharacteristicReadingDelegate;
@protocol CBEPeripheralL2CAPOpeningDelegate;










@interface CBPeripheral (CBE)

@property (readonly) CBEPeripheralOperation *nseOperation;

@end










@interface CBEPeripheral : CBPeripheral

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










@protocol CBEPeripheralCharacteristicReadingDelegate <NSETimeoutOperationDelegate>

@optional
- (void)cbePeripheralCharacteristicReadingDidUpdateState:(CBEPeripheralCharacteristicReading *)reading;
- (void)cbePeripheralCharacteristicReadingDidStart:(CBEPeripheralCharacteristicReading *)reading;
- (void)cbePeripheralCharacteristicReadingDidCancel:(CBEPeripheralCharacteristicReading *)reading;
- (void)cbePeripheralCharacteristicReadingDidFinish:(CBEPeripheralCharacteristicReading *)reading;

- (void)cbePeripheralCharacteristicReadingDidUpdateProgress:(CBEPeripheralCharacteristicReading *)reading;

@end



@interface CBEPeripheralCharacteristicReading : NSETimeoutOperation <CBEPeripheralCharacteristicReadingDelegate>

@property (readonly) CBEPeripheralOperation *parent;
@property (readonly) NSMutableOrderedSet<CBEPeripheralCharacteristicReadingDelegate> *delegates;
@property (readonly) CBCharacteristic *characteristic;

- (instancetype)initWithCharacteristic:(CBCharacteristic *)characteristic timeout:(NSTimeInterval)timeout;

@end










@protocol CBEPeripheralL2CAPOpeningDelegate <NSETimeoutOperationDelegate>

@optional
- (void)cbePeripheralL2CAPOpeningDidUpdateState:(CBEPeripheralL2CAPOpening *)opening;
- (void)cbePeripheralL2CAPOpeningDidStart:(CBEPeripheralL2CAPOpening *)opening;
- (void)cbePeripheralL2CAPOpeningDidCancel:(CBEPeripheralL2CAPOpening *)opening;
- (void)cbePeripheralL2CAPOpeningDidFinish:(CBEPeripheralL2CAPOpening *)opening;

- (void)cbePeripheralL2CAPOpeningDidUpdateProgress:(CBEPeripheralL2CAPOpening *)opening;

@end



@interface CBEPeripheralL2CAPOpening : NSETimeoutOperation <CBEPeripheralL2CAPOpeningDelegate>

@property (readonly) CBEPeripheralOperation *parent;
@property (readonly) NSMutableOrderedSet<CBEPeripheralL2CAPOpeningDelegate> *delegates;
@property (readonly) CBL2CAPPSM psm;

- (instancetype)initWithPSM:(CBL2CAPPSM)psm timeout:(NSTimeInterval)timeout;

@end










@protocol CBEPeripheralDelegate <CBEPeerDelegate, CBEL2CAPChannelDelegate, CBEPeripheralServicesDiscoveryDelegate, CBEPeripheralCharacteristicsDiscoveryDelegate, CBEPeripheralCharacteristicReadingDelegate, CBEPeripheralL2CAPOpeningDelegate>

@end



@interface CBEPeripheralOperation : CBEPeerOperation <CBEPeripheralDelegate, CBPeripheralDelegate>

@property CBEAdvertisement *advertisement;
@property NSNumber *rssi;

@property (readonly) NSMutableDictionary<NSNumber *, CBL2CAPChannel *> *l2capChannels;

@property (weak, readonly) CBPeripheral *object;
@property (weak, readonly) CBEPeripheralServicesDiscovery *servicesDiscovery;
@property (weak, readonly) CBEPeripheralCharacteristicsDiscovery *characteristicsDiscovery;
@property (weak, readonly) CBEPeripheralCharacteristicReading *characteristicReading;
@property (weak, readonly) CBEPeripheralL2CAPOpening *l2capOpening;

- (NSArray<CBService *> *)retrieveServicesWithIdentifiers:(NSArray<CBUUID *> *)identifiers;

- (CBEPeripheralServicesDiscovery *)discoverServices:(NSArray<CBUUID *> *)services timeout:(NSTimeInterval)timeout;
- (CBEPeripheralServicesDiscovery *)discoverServices:(NSArray<CBUUID *> *)services timeout:(NSTimeInterval)timeout completion:(NSEBlock)completion;

- (CBEPeripheralCharacteristicsDiscovery *)discoverCharacteristics:(NSArray<CBUUID *> *)characteristics forService:(CBService *)service timeout:(NSTimeInterval)timeout;
- (CBEPeripheralCharacteristicsDiscovery *)discoverCharacteristics:(NSArray<CBUUID *> *)characteristics forService:(CBService *)service timeout:(NSTimeInterval)timeout completion:(NSEBlock)completion;

- (CBEPeripheralCharacteristicReading *)readValueForCharacteristic:(CBCharacteristic *)characteristic timeout:(NSTimeInterval)timeout;
- (CBEPeripheralCharacteristicReading *)readValueForCharacteristic:(CBCharacteristic *)characteristic timeout:(NSTimeInterval)timeout completion:(NSEBlock)completion;

- (CBEPeripheralL2CAPOpening *)openL2CAPChannel:(CBL2CAPPSM)psm timeout:(NSTimeInterval)timeout;
- (CBEPeripheralL2CAPOpening *)openL2CAPChannel:(CBL2CAPPSM)psm timeout:(NSTimeInterval)timeout completion:(NSEBlock)completion;

@end
