//
//  CBECharacteristic.m
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/25/19.
//

#import "CBECharacteristic.h"
#import "CBEPeripheral.h"










@implementation CBCharacteristic (CBE)

@dynamic nseOperation;

- (Class)nseOperationClass {
    return CBECharacteristicOperation.class;
}

@end










@interface CBECharacteristic ()

@end



@implementation CBECharacteristic

@end










@interface CBECharacteristicValueReading ()

@property CBEPeripheralDisconnection *disconnection;

@end



@implementation CBECharacteristicValueReading

@dynamic parent;
@dynamic delegates;

- (void)updateState:(NSEOperationState)state {
    [super updateState:state];
    
    [self.delegates cbeCharacteristicValueReadingDidUpdateState:self];
    if (state == NSEOperationStateDidStart) {
        [self.delegates cbeCharacteristicValueReadingDidStart:self];
    } else if (state == NSEOperationStateDidCancel) {
        [self.delegates cbeCharacteristicValueReadingDidCancel:self];
    } else if (state == NSEOperationStateDidFinish) {
        [self.delegates cbeCharacteristicValueReadingDidFinish:self];
    }
}

- (void)updateProgress:(int64_t)completedUnitCount {
    [super updateProgress:completedUnitCount];
    
    [self.delegates cbeCharacteristicValueReadingDidUpdateProgress:self];
}

#pragma mark - CBECharacteristicValueReadingDelegate

- (void)cbeCharacteristicValueReadingDidStart:(CBECharacteristicValueReading *)reading {
    self.parent.valueReading = self;
    
    [self.parent.parent.parent.object readValueForCharacteristic:self.parent.object];
}

- (void)cbeCharacteristicValueReadingDidCancel:(CBECharacteristicValueReading *)reading {
    self.disconnection = self.parent.parent.parent.disconnect;
    [self.disconnection.delegates addObject:self];
}

#pragma mark - CBEPeripheralDisconnectionDelegate

- (void)cbePeripheralDisconnectionDidFinish:(CBEPeripheralDisconnection *)disconnection {
    [self finish];
}

@end










@interface CBECharacteristicOperation ()

@end



@implementation CBECharacteristicOperation

@dynamic parent;
@dynamic object;

@end
