//
//  CBEPeripheral.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/26/19.
//

#import "CBEPeer.h"
#import "CBECentralManagerPeripheralDisconnection.h"

@class CBEPeripheral;
@class CBEPeripheralAdvertisement;
@class CBEPeripheralServicesDiscovery;
@class CBEPeripheralOperation;
@class CBECentralManagerOperation;

@protocol CBEPeripheralDelegate;










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



@interface CBEPeripheralServicesDiscovery : NSETimeoutOperation <CBEPeripheralServicesDiscoveryDelegate, CBECentralManagerPeripheralDisconnectionDelegate>

@property (readonly) CBEPeripheralOperation *parent;
@property (readonly) NSMutableOrderedSet<CBEPeripheralServicesDiscoveryDelegate> *delegates;
@property (readonly) NSArray<CBUUID *> *services;

- (instancetype)initWithServices:(NSArray<CBUUID *> *)services timeout:(NSTimeInterval)timeout;

@end










@protocol CBEPeripheralDelegate <CBEPeerDelegate, CBEPeripheralServicesDiscoveryDelegate>

@end



@interface CBEPeripheralOperation : CBEPeerOperation <CBEPeripheralDelegate, CBPeripheralDelegate>

@property CBEPeripheralAdvertisement *advertisement;
@property NSNumber *rssi;

@property (readonly) CBECentralManagerOperation *parent;

@property (weak, readonly) CBPeripheral *object;

- (NSArray<CBService *> *)retrieveServicesWithIdentifiers:(NSArray<CBUUID *> *)identifiers;

@end
