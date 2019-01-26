//
//  CBEDisconnection.m
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/26/19.
//

#import "CBEDisconnection.h"
#import "CBEPeripheral.h"



@interface CBEDisconnection ()

@end



@implementation CBEDisconnection

@dynamic parent;
@dynamic delegates;

- (void)updateState:(NSEOperationState)state {
    [super updateState:state];
    
    [self.delegates cbeDisconnectionDidUpdateState:self];
    if (state == NSEOperationStateDidStart) {
        [self.delegates cbeDisconnectionDidStart:self];
    } else if (state == NSEOperationStateDidCancel) {
        [self.delegates cbeDisconnectionDidCancel:self];
    } else if (state == NSEOperationStateDidFinish) {
        [self.delegates cbeDisconnectionDidFinish:self];
    }
}

- (void)updateProgress:(int64_t)completedUnitCount {
    [super updateProgress:completedUnitCount];
    
    [self.delegates cbeDisconnectionDidUpdateProgress:self];
}

#pragma mark - CBEDisconnectionDelegate

- (void)cbeDisconnectionDidStart:(CBEDisconnection *)disconnection {
    if (self.parent.object.state == CBPeripheralStateDisconnected) {
        [self finish];
    } else {
        
    }
}

@end
