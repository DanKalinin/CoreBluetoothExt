//
//  CBECentralManagerPeripheralDisconnection.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/26/19.
//

#import "CBEMain.h"

@class CBECentralManagerPeripheralDisconnection;
@class CBECentralManagerOperation;

@protocol CBECentralManagerPeripheralDisconnectionDelegate;



@protocol CBECentralManagerPeripheralDisconnectionDelegate <NSEOperationDelegate>

@optional
- (void)cbeCentralManagerPeripheralDisconnectionDidUpdateState:(CBECentralManagerPeripheralDisconnection *)disconnection;
- (void)cbeCentralManagerPeripheralDisconnectionDidStart:(CBECentralManagerPeripheralDisconnection *)disconnection;
- (void)cbeCentralManagerPeripheralDisconnectionDidCancel:(CBECentralManagerPeripheralDisconnection *)disconnection;
- (void)cbeCentralManagerPeripheralDisconnectionDidFinish:(CBECentralManagerPeripheralDisconnection *)disconnection;

- (void)cbeCentralManagerPeripheralDisconnectionDidUpdateProgress:(CBECentralManagerPeripheralDisconnection *)disconnection;

@end



@interface CBECentralManagerPeripheralDisconnection : NSEOperation <CBECentralManagerPeripheralDisconnectionDelegate>

@property (readonly) CBECentralManagerOperation *parent;
@property (readonly) NSMutableOrderedSet<CBECentralManagerPeripheralDisconnectionDelegate> *delegates;
@property (readonly) CBPeripheral *peripheral;

- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral;

@end
