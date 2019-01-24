//
//  CBEPeripheralDisconnection.m
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/24/19.
//

#import "CBEPeripheralDisconnection.h"
#import "CBECentralManager.h"



@interface CBEPeripheralDisconnection ()

@end



@implementation CBEPeripheralDisconnection

@dynamic parent;
@dynamic delegates;

- (void)updateState:(NSEOperationState)state {
    [super updateState:state];
    
    [self.delegates cbePeripheralDisconnectionDidUpdateState:self];
    if (state == NSEOperationStateDidStart) {
        [self.delegates cbePeripheralDisconnectionDidStart:self];
    } else if (state == NSEOperationStateDidCancel) {
        [self.delegates cbePeripheralDisconnectionDidCancel:self];
    } else if (state == NSEOperationStateDidFinish) {
        [self.delegates cbePeripheralDisconnectionDidFinish:self];
    }
}

- (void)updateProgress:(int64_t)completedUnitCount {
    [super updateProgress:completedUnitCount];
    
    [self.delegates cbePeripheralDisconnectionDidUpdateProgress:self];
}

#pragma mark - CBEPeripheralDisconnectionDelegate

- (void)cbePeripheralDisconnectionDidStart:(CBEPeripheralDisconnection *)disconnection {
    if (self.parent.object.state == CBPeripheralStateDisconnected) {
        [self finish];
    } else {
        self.parent.disconnection = self;
        
        if (self.parent.object.state == CBPeripheralStateDisconnecting) {
        } else {
            [self.parent.parent.object cancelPeripheralConnection:self.parent.object];
        }
    }
}

@end
