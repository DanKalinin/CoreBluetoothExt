//
//  CBEPeripheral.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/19/19.
//

#import "CBEPeer.h"

@class CBEPeripheral;
@class CBEPeripheralAdvertisement;
@class CBEPeripheralDidDisconnect;
@class CBEPeripheralOperation;
@class CBECentralManagerOperation;

@protocol CBEPeripheralDelegate;










@interface CBPeripheral (CBE)

@property (readonly) CBEPeripheralOperation *nseOperation;

@end










@interface CBEPeripheral : CBPeripheral

@end










@interface CBEPeripheralAdvertisement : NSEDictionaryObject

@property (readonly) NSArray<CBUUID *> *serviceUUIDs;
@property (readonly) BOOL isConnectable;

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

@property CBEPeripheralAdvertisement *advertisement;
@property NSNumber *rssi;

@property (weak) CBEPeripheralDidDisconnect *didDisconnect;

@property (readonly) CBECentralManagerOperation *parent;
@property (readonly) NSMutableOrderedSet<CBEPeripheralDelegate> *delegates;

@property (weak, readonly) CBPeripheral *object;

@end
