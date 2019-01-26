//
//  CBEPeripheral.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/26/19.
//

#import "CBEPeer.h"

@class CBEPeripheral;
@class CBEPeripheralAdvertisement;
@class CBEPeripheralServicesDiscovery;
@class CBEPeripheralCharacteristiscDiscovery;
@class CBEPeripheralOperation;

@protocol CBEPeripheralDelegate;
@protocol CBEPeripheralServicesDiscoveryDelegate;
@protocol CBEPeripheralCharacteristiscDiscoveryDelegate;










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










@protocol CBEPeripheralCharacteristiscDiscoveryDelegate <NSETimeoutOperationDelegate>

@end



@interface CBEPeripheralCharacteristiscDiscovery : NSETimeoutOperation <CBEPeripheralCharacteristiscDiscoveryDelegate>

@property (readonly) CBEPeripheralOperation *parent;
@property (readonly) NSMutableOrderedSet<CBEPeripheralCharacteristiscDiscoveryDelegate> *delegates;

@end










@protocol CBEPeripheralDelegate <CBEPeerDelegate, CBEPeripheralServicesDiscoveryDelegate>

@end



@interface CBEPeripheralOperation : CBEPeerOperation <CBEPeripheralDelegate, CBPeripheralDelegate>

@property CBEPeripheralAdvertisement *advertisement;
@property NSNumber *rssi;

@property (weak, readonly) CBPeripheral *object;
@property (weak, readonly) CBEPeripheralServicesDiscovery *servicesDiscovery;

- (NSArray<CBService *> *)retrieveServicesWithIdentifiers:(NSArray<CBUUID *> *)identifiers;

- (CBEPeripheralServicesDiscovery *)discoverServices:(NSArray<CBUUID *> *)services;
- (CBEPeripheralServicesDiscovery *)discoverServices:(NSArray<CBUUID *> *)services completion:(NSEBlock)completion;

@end
