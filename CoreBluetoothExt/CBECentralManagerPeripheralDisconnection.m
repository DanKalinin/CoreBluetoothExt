//
//  CBECentralManagerPeripheralDisconnection.m
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/26/19.
//

#import "CBECentralManagerPeripheralDisconnection.h"
#import "CBECentralManager.h"



@interface CBECentralManagerPeripheralDisconnection ()

@property CBPeripheral *peripheral;

@end



@implementation CBECentralManagerPeripheralDisconnection

@dynamic parent;
@dynamic delegates;

- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral {
    self = super.init;
    
    self.peripheral = peripheral;
    
    return self;
}

- (void)updateState:(NSEOperationState)state {
    [super updateState:state];
    
    [self.delegates cbeCentralManagerPeripheralDisconnectionDidUpdateState:self];
    if (state == NSEOperationStateDidStart) {
        [self.delegates cbeCentralManagerPeripheralDisconnectionDidStart:self];
    } else if (state == NSEOperationStateDidCancel) {
        [self.delegates cbeCentralManagerPeripheralDisconnectionDidCancel:self];
    } else if (state == NSEOperationStateDidFinish) {
        [self.delegates cbeCentralManagerPeripheralDisconnectionDidFinish:self];
    }
}

- (void)updateProgress:(int64_t)completedUnitCount {
    [super updateProgress:completedUnitCount];
    
    [self.delegates cbeCentralManagerPeripheralDisconnectionDidUpdateProgress:self];
}

#pragma mark - CBECentralManagerPeripheralDisconnectionDelegate

- (void)cbeCentralManagerPeripheralDisconnectionDidStart:(CBECentralManagerPeripheralDisconnection *)disconnection {
    if (self.peripheral.state == CBPeripheralStateDisconnected) {
        [self finish];
    } else {
        if (self.peripheral.state == CBPeripheralStateDisconnecting) {
        } else {
            [self.parent.object cancelPeripheralConnection:self.peripheral];
        }
    }
}

@end
