//
//  CBEPeripheral.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/19/19.
//

#import "CBEPeer.h"
#import "CBEPeripheralDisconnection.h"
#import "CBEService.h"

@class CBEPeripheral;
@class CBEPeripheralAdvertisement;
@class CBEPeripheralDidDisconnect;
@class CBEPeripheralConnection;
@class CBEPeripheralServicesDiscovery;
@class CBEPeripheralOperation;
@class CBECentralManagerOperation;

@protocol CBEPeripheralDelegate;
@protocol CBEPeripheralConnectionDelegate;
@protocol CBEPeripheralServicesDiscoveryDelegate;










@interface CBPeripheral (CBE)

@property (readonly) CBEPeripheralOperation *nseOperation;

@end










@interface CBEPeripheral : CBPeripheral

@end










@interface CBEPeripheralAdvertisement : NSEDictionaryObject

@property (readonly) NSArray<CBUUID *> *serviceUUIDs;
@property (readonly) BOOL isConnectable;

@end










@interface CBEPeripheralDidDisconnect : NSEObject

@property (readonly) NSError *error;

- (instancetype)initWithError:(NSError *)error;

@end










@protocol CBEPeripheralConnectionDelegate <NSETimeoutOperationDelegate>

@optional
- (void)cbePeripheralConnectionDidUpdateState:(CBEPeripheralConnection *)connection;
- (void)cbePeripheralConnectionDidStart:(CBEPeripheralConnection *)connection;
- (void)cbePeripheralConnectionDidCancel:(CBEPeripheralConnection *)connection;
- (void)cbePeripheralConnectionDidFinish:(CBEPeripheralConnection *)connection;

- (void)cbePeripheralConnectionDidUpdateProgress:(CBEPeripheralConnection *)connection;

@end



@interface CBEPeripheralConnection : NSETimeoutOperation <CBEPeripheralConnectionDelegate, CBEPeripheralDisconnectionDelegate>

@property (readonly) CBEPeripheralOperation *parent;
@property (readonly) NSMutableOrderedSet<CBEPeripheralConnectionDelegate> *delegates;
@property (readonly) NSDictionary *options;
@property (readonly) CBEPeripheralDisconnection *disconnection;

- (instancetype)initWithOptions:(NSDictionary *)options timeout:(NSTimeInterval)timeout;

@end










@protocol CBEPeripheralServicesDiscoveryDelegate <NSETimeoutOperationDelegate>

@optional
- (void)cbePeripheralServicesDiscoveryDidUpdateState:(CBEPeripheralServicesDiscovery *)discovery;
- (void)cbePeripheralServicesDiscoveryDidStart:(CBEPeripheralServicesDiscovery *)discovery;
- (void)cbePeripheralServicesDiscoveryDidCancel:(CBEPeripheralServicesDiscovery *)discovery;
- (void)cbePeripheralServicesDiscoveryDidFinish:(CBEPeripheralServicesDiscovery *)discovery;

- (void)cbePeripheralServicesDiscoveryDidUpdateProgress:(CBEPeripheralServicesDiscovery *)discovery;

@end



@interface CBEPeripheralServicesDiscovery : NSETimeoutOperation <CBEPeripheralServicesDiscoveryDelegate, CBEPeripheralDisconnectionDelegate>

@property (readonly) CBEPeripheralOperation *parent;
@property (readonly) NSMutableOrderedSet<CBEPeripheralServicesDiscoveryDelegate> *delegates;
@property (readonly) NSArray<CBUUID *> *services;
@property (readonly) CBEPeripheralDisconnection *disconnection;

- (instancetype)initWithServices:(NSArray<CBUUID *> *)services timeout:(NSTimeInterval)timeout;

@end










@protocol CBEPeripheralDelegate <CBEPeerDelegate, CBEPeripheralDisconnectionDelegate, CBEPeripheralConnectionDelegate, CBEPeripheralServicesDiscoveryDelegate>

@optional
- (void)cbePeripheralDidDisconnect:(CBPeripheral *)peripheral;

@end



@interface CBEPeripheralOperation : CBEPeerOperation <CBEPeripheralDelegate, CBPeripheralDelegate>

@property CBEPeripheralAdvertisement *advertisement;
@property NSNumber *rssi;

@property (weak) CBEPeripheralDidDisconnect *didDisconnect;
@property (weak) CBEPeripheralConnection *connection;
@property (weak) CBEPeripheralDisconnection *disconnection;
@property (weak) CBEPeripheralServicesDiscovery *servicesDiscovery;

@property (readonly) CBECentralManagerOperation *parent;
@property (readonly) NSMutableOrderedSet<CBEPeripheralDelegate> *delegates;

@property (weak, readonly) CBPeripheral *object;

- (NSArray<CBService *> *)retrieveServicesWithIdentifiers:(NSArray<CBUUID *> *)identifiers;

- (CBEPeripheralDisconnection *)disconnect;
- (CBEPeripheralDisconnection *)disconnectWithCompletion:(NSEBlock)completion;

- (CBEPeripheralConnection *)connectWithOptions:(NSDictionary *)options timeout:(NSTimeInterval)timeout;
- (CBEPeripheralConnection *)connectWithOptions:(NSDictionary *)options timeout:(NSTimeInterval)timeout completion:(NSEBlock)completion;

- (CBEPeripheralServicesDiscovery *)discoverServices:(NSArray<CBUUID *> *)services timeout:(NSTimeInterval)timeout;
- (CBEPeripheralServicesDiscovery *)discoverServices:(NSArray<CBUUID *> *)services timeout:(NSTimeInterval)timeout completion:(NSEBlock)completion;

@end
