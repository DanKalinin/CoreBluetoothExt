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

@protocol CBEServiceDelegate;
@protocol CBEServiceCharacteristicsDiscoveryDelegate;










@interface CBService (CBE)

@property (readonly) CBEServiceOperation *nseOperation;

@end










@interface CBEService : CBService

@end










@protocol CBEServiceCharacteristicsDiscoveryDelegate <NSETimeoutOperationDelegate>

@end



@interface CBEServiceCharacteristicsDiscovery : NSETimeoutOperation <CBEServiceCharacteristicsDiscoveryDelegate>

@property (readonly) NSArray<CBUUID *> *characteristics;

- (instancetype)initWithCharacteristics:(NSArray<CBUUID *> *)characteristics timeout:(NSTimeInterval)timeout;

@end










@protocol CBEServiceDelegate <CBEAttributeDelegate>

@end



@interface CBEServiceOperation : CBEAttributeOperation <CBEServiceDelegate>

@property (weak, readonly) CBService *object;

- (NSArray<CBCharacteristic *> *)retrieveCharacteristicsWithIdentifiers:(NSArray<CBUUID *> *)identifiers;

- (CBEServiceCharacteristicsDiscovery *)discoverCharacteristics:(NSArray<CBUUID *> *)characteristics timeout:(NSTimeInterval)timeout;
- (CBEServiceCharacteristicsDiscovery *)discoverCharacteristics:(NSArray<CBUUID *> *)characteristics timeout:(NSTimeInterval)timeout completion:(NSEBlock)completion;

@end
