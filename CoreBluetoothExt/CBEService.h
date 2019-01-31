//
//  CBEService.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/23/19.
//

#import "CBEAttribute.h"

@class CBEService;
@class CBEServiceOperation;

@protocol CBEServiceDelegate;










@interface CBService (CBE)

@property (readonly) CBEServiceOperation *nseOperation;

@end










@interface CBEService : CBService

@end










@protocol CBEServiceDelegate <CBEAttributeDelegate>

@end



@interface CBEServiceOperation : CBEAttributeOperation <CBEServiceDelegate>

@property (weak, readonly) CBService *object;

- (NSArray<CBCharacteristic *> *)retrieveCharacteristicsWithIdentifiers:(NSArray<CBUUID *> *)identifiers;

@end
