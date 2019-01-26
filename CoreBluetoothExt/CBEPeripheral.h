//
//  CBEPeripheral.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/26/19.
//

#import "CBEPeer.h"
#import "CBEDisconnection.h"

@class CBEPeripheral;
@class CBEPeripheralOperation;
@class CBECentralManagerOperation;

@protocol CBEPeripheralDelegate;










@interface CBPeripheral (CBE)

@property (readonly) CBEPeripheralOperation *nseOperation;

@end










@interface CBEPeripheral : CBPeripheral

@end










@protocol CBEPeripheralDelegate <CBEPeerDelegate>

@end



@interface CBEPeripheralOperation : CBEPeerOperation

@property (readonly) CBECentralManagerOperation *parent;

@property (weak, readonly) CBPeripheral *object;
@property (weak, readonly) CBEDisconnection *disconnection;

@end
