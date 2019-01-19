//
//  CBEPeripheral.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/19/19.
//

#import "CBEPeer.h"

@class CBEPeripheral;
@class CBEPeripheralOperation;

@protocol CBEPeripheralDelegate;










@interface CBPeripheral (CBE)

@property (readonly) CBEPeripheralOperation *nseOperation;

@end










@interface CBEPeripheral : CBPeripheral

@end










@interface CBEPeripheralDidDisconnect : NSEObject

@property (readonly) NSError *error;

- (instancetype)initWithError:(NSError *)error;

@end










@protocol CBEPeripheralDelegate <CBEPeerDelegate>

@optional
- (void)cbePeripheralDidConnect:(CBPeripheral *)peripheral;
- (void)cbePeripheralDidDisconnect:(CBPeripheral *)peripheral;
- (void)cbePeripheralDidCancelConnection:(CBPeripheral *)peripheral;

@end



@interface CBEPeripheralOperation : CBEPeerOperation <CBEPeripheralDelegate, CBPeripheralDelegate>

@property (weak) CBEPeripheralDidDisconnect *didDisconnect;

@property (readonly) NSMutableOrderedSet<CBEPeripheralDelegate> *delegates;

@property (weak, readonly) CBPeripheral *object;

@end
