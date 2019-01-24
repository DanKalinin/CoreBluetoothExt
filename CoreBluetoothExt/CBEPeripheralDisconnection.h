//
//  CBEPeripheralDisconnection.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/24/19.
//

#import "CBEMain.h"

@class CBEPeripheralDisconnection;
@class CBEPeripheralOperation;

@protocol CBEPeripheralDisconnectionDelegate;



@protocol CBEPeripheralDisconnectionDelegate <NSEOperationDelegate>

@optional
- (void)cbePeripheralDisconnectionDidUpdateState:(CBEPeripheralDisconnection *)disconnection;
- (void)cbePeripheralDisconnectionDidStart:(CBEPeripheralDisconnection *)disconnection;
- (void)cbePeripheralDisconnectionDidCancel:(CBEPeripheralDisconnection *)disconnection;
- (void)cbePeripheralDisconnectionDidFinish:(CBEPeripheralDisconnection *)disconnection;

- (void)cbePeripheralDisconnectionDidUpdateProgress:(CBEPeripheralDisconnection *)disconnection;

@end



@interface CBEPeripheralDisconnection : NSEOperation <CBEPeripheralDisconnectionDelegate>

@property (readonly) CBEPeripheralOperation *parent;
@property (readonly) NSMutableOrderedSet<CBEPeripheralDisconnectionDelegate> *delegates;

@end
