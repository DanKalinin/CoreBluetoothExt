//
//  CBECentralManager.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/26/19.
//

#import "CBEManager.h"
#import "CBEPeripheral.h"

@class CBECentralManager;
@class CBECentralManagerDidDiscoverPeripheral;
@class CBECentralManagerPeripheralDisconnection;
@class CBECentralManagerPeripheralConnection;
@class CBECentralManagerOperation;

@protocol CBECentralManagerDelegate;
@protocol CBECentralManagerPeripheralDisconnectionDelegate;
@protocol CBECentralManagerPeripheralConnectionDelegate;










@interface CBCentralManager (CBE)

@property (readonly) CBECentralManagerOperation *nseOperation;

@end










@interface CBECentralManager : CBCentralManager

@end










@interface CBECentralManagerDidDiscoverPeripheral : NSEObject

@property (readonly) CBPeripheral *peripheral;
@property (readonly) CBEPeripheralAdvertisement *advertisement;
@property (readonly) NSNumber *rssi;

- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral advertisement:(CBEPeripheralAdvertisement *)advertisement rssi:(NSNumber *)rssi;

@end










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










@protocol CBECentralManagerPeripheralConnectionDelegate <NSETimeoutOperationDelegate>

@optional
- (void)cbeCentralManagerPeripheralConnectionDidUpdateState:(CBECentralManagerPeripheralConnection *)connection;
- (void)cbeCentralManagerPeripheralConnectionDidStart:(CBECentralManagerPeripheralConnection *)connection;
- (void)cbeCentralManagerPeripheralConnectionDidCancel:(CBECentralManagerPeripheralConnection *)connection;
- (void)cbeCentralManagerPeripheralConnectionDidFinish:(CBECentralManagerPeripheralConnection *)connection;

- (void)cbeCentralManagerPeripheralConnectionDidUpdateProgress:(CBECentralManagerPeripheralConnection *)connection;

@end



@interface CBECentralManagerPeripheralConnection : NSETimeoutOperation <CBECentralManagerPeripheralConnectionDelegate>

@property (readonly) CBECentralManagerOperation *parent;
@property (readonly) NSMutableOrderedSet<CBECentralManagerPeripheralConnectionDelegate> *delegates;
@property (readonly) CBPeripheral *peripheral;
@property (readonly) NSDictionary *options;

- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral options:(NSDictionary *)options timeout:(NSTimeInterval)timeout;

@end










@protocol CBECentralManagerDelegate <CBEManagerDelegate, CBEPeripheralDelegate>

@optional
- (void)cbeCentralManagerDidUpdateState:(CBCentralManager *)central;
- (void)cbeCentralManagerDidDiscoverPeripheral:(CBCentralManager *)central;

@end



@interface CBECentralManagerOperation : CBEManagerOperation <CBECentralManagerDelegate, CBCentralManagerDelegate>

@property (readonly) NSMutableOrderedSet<CBECentralManagerDelegate> *delegates;
@property (readonly) NSMutableSet<CBPeripheral *> *peripherals;

@property (weak, readonly) CBCentralManager *object;
@property (weak, readonly) CBECentralManagerDidDiscoverPeripheral *didDiscoverPeripheral;
@property (weak, readonly) CBECentralManagerPeripheralDisconnection *disconnection;

- (CBECentralManagerPeripheralDisconnection *)disconnectPeripheral:(CBPeripheral *)peripheral;
- (CBECentralManagerPeripheralDisconnection *)disconnectPeripheral:(CBPeripheral *)peripheral completion:(NSEBlock)completion;

@end
