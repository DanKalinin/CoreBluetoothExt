//
//  CBEPeripheral.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/26/19.
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










@protocol CBEPeripheralDelegate <CBEPeerDelegate>

@end



@interface CBEPeripheralOperation : CBEPeerOperation

@property (weak, readonly) CBPeripheral *object;

@end
