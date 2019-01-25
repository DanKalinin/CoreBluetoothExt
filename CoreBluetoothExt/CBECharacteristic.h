//
//  CBECharacteristic.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/25/19.
//

#import "CBEAttribute.h"
#import "CBEPeripheralDisconnection.h"

@class CBECharacteristic;
@class CBECharacteristicValueReading;
@class CBECharacteristicOperation;
@class CBEServiceOperation;

@protocol CBECharacteristicDelegate;
@protocol CBECharacteristicValueReadingDelegate;










@interface CBCharacteristic (CBE)

@property (readonly) CBECharacteristicOperation *nseOperation;

@end










@interface CBECharacteristic : CBCharacteristic

@end










@protocol CBECharacteristicValueReadingDelegate <NSETimeoutOperationDelegate>

@optional
- (void)cbeCharacteristicValueReadingDidUpdateState:(CBECharacteristicValueReading *)reading;
- (void)cbeCharacteristicValueReadingDidStart:(CBECharacteristicValueReading *)reading;
- (void)cbeCharacteristicValueReadingDidCancel:(CBECharacteristicValueReading *)reading;
- (void)cbeCharacteristicValueReadingDidFinish:(CBECharacteristicValueReading *)reading;

- (void)cbeCharacteristicValueReadingDidUpdateProgress:(CBECharacteristicValueReading *)reading;

@end



@interface CBECharacteristicValueReading : NSETimeoutOperation <CBECharacteristicValueReadingDelegate, CBEPeripheralDisconnectionDelegate>

@property (readonly) CBECharacteristicOperation *parent;
@property (readonly) NSMutableOrderedSet<CBECharacteristicValueReadingDelegate> *delegates;
@property (readonly) CBEPeripheralDisconnection *disconnection;

@end










@protocol CBECharacteristicDelegate <CBEAttributeDelegate, CBECharacteristicValueReadingDelegate>

@end



@interface CBECharacteristicOperation : CBEAttributeOperation <CBECharacteristicDelegate>

@property (weak) CBECharacteristicValueReading *valueReading;

@property (readonly) CBEServiceOperation *parent;

@property (weak, readonly) CBCharacteristic *object;

@end
