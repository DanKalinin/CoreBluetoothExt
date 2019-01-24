//
//  CBEService.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/23/19.
//

#import "CBEAttribute.h"

@class CBEService;
@class CBEServiceCharacteristicsDiscovery;
@class CBEServiceOperation;
@class CBEPeripheralDisconnection;
@class CBEPeripheralOperation;

@protocol CBEServiceDelegate;
@protocol CBEServiceCharacteristicsDiscoveryDelegate;
@protocol CBEPeripheralDisconnectionDelegate;










@interface CBService (CBE)

@property (readonly) CBEServiceOperation *nseOperation;

@end










@interface CBEService : CBService

@end










@protocol CBEServiceCharacteristicsDiscoveryDelegate <NSETimeoutOperationDelegate>

@optional
- (void)cbeServiceCharacteristicsDiscoveryDidUpdateState:(CBEServiceCharacteristicsDiscovery *)discovery;
- (void)cbeServiceCharacteristicsDiscoveryDidStart:(CBEServiceCharacteristicsDiscovery *)discovery;
- (void)cbeServiceCharacteristicsDiscoveryDidCancel:(CBEServiceCharacteristicsDiscovery *)discovery;
- (void)cbeServiceCharacteristicsDiscoveryDidFinish:(CBEServiceCharacteristicsDiscovery *)discovery;

- (void)cbeServiceCharacteristicsDiscoveryDidUpdateProgress:(CBEServiceCharacteristicsDiscovery *)discovery;

@end



@interface CBEServiceCharacteristicsDiscovery : NSETimeoutOperation <CBEServiceCharacteristicsDiscoveryDelegate, CBEPeripheralDisconnectionDelegate>

@property (readonly) CBEServiceOperation *parent;
@property (readonly) NSMutableOrderedSet<CBEServiceCharacteristicsDiscoveryDelegate> *delegates;
@property (readonly) NSArray<CBUUID *> *characteristics;
@property (readonly) CBEPeripheralDisconnection *disconnection;

- (instancetype)initWithCharacteristics:(NSArray<CBUUID *> *)characteristics timeout:(NSTimeInterval)timeout;

@end










@protocol CBEServiceDelegate <CBEAttributeDelegate, CBEServiceCharacteristicsDiscoveryDelegate>

@end



@interface CBEServiceOperation : CBEAttributeOperation <CBEServiceDelegate>

@property (weak) CBEServiceCharacteristicsDiscovery *characteristicsDiscovery;

@property (readonly) CBEPeripheralOperation *parent;
@property (readonly) NSMutableOrderedSet<CBEServiceDelegate> *delegates;

@property (weak, readonly) CBService *object;

- (NSArray<CBCharacteristic *> *)retrieveCharacteristicsWithIdentifiers:(NSArray<CBUUID *> *)identifiers;

- (CBEServiceCharacteristicsDiscovery *)discoverCharacteristics:(NSArray<CBUUID *> *)characteristics timeout:(NSTimeInterval)timeout;
- (CBEServiceCharacteristicsDiscovery *)discoverCharacteristics:(NSArray<CBUUID *> *)characteristics timeout:(NSTimeInterval)timeout completion:(NSEBlock)completion;

@end
