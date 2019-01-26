//
//  CBEDisconnection.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/26/19.
//

#import "CBEMain.h"

@class CBEDisconnection;
@class CBEPeripheralOperation;

@protocol CBEDisconnectionDelegate;



@protocol CBEDisconnectionDelegate <NSEOperationDelegate>

@optional
- (void)cbeDisconnectionDidUpdateState:(CBEDisconnection *)disconnection;
- (void)cbeDisconnectionDidStart:(CBEDisconnection *)disconnection;
- (void)cbeDisconnectionDidCancel:(CBEDisconnection *)disconnection;
- (void)cbeDisconnectionDidFinish:(CBEDisconnection *)disconnection;

- (void)cbeDisconnectionDidUpdateProgress:(CBEDisconnection *)disconnection;

@end



@interface CBEDisconnection : NSEOperation <CBEDisconnectionDelegate>

@property (readonly) CBEPeripheralOperation *parent;
@property (readonly) NSMutableOrderedSet<CBEDisconnectionDelegate> *delegates;

@end
