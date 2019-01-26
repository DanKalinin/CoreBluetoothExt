//
//  CBEPeripheral.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/26/19.
//

#import "CBEPeer.h"

@class CBEPeripheral;
@class CBEPeripheralAdvertisement;
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










@interface CBEPeripheralServicesDiscovery : NSETimeoutOperation

@end










@protocol CBEPeripheralDelegate <CBEPeerDelegate>

@end



@interface CBEPeripheralOperation : CBEPeerOperation

@property CBEPeripheralAdvertisement *advertisement;
@property NSNumber *rssi;

@property (readonly) CBECentralManagerOperation *parent;

@property (weak, readonly) CBPeripheral *object;

@end
