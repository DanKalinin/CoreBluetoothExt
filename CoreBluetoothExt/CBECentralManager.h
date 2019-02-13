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
@class CBECentralManagerDidDisconnectPeripheral;
@class CBECentralManagerDisconnection;
@class CBECentralManagerConnection;
@class CBECentralManagerOperation;

@protocol CBECentralManagerDelegate;
@protocol CBECentralManagerDisconnectionDelegate;
@protocol CBECentralManagerConnectionDelegate;










@interface CBCentralManager (CBE)

@property (readonly) CBECentralManagerOperation *nseOperation;

@end










@interface CBECentralManager : CBCentralManager

@end










@interface CBECentralManagerDidDiscoverPeripheral : NSEObject

@property (readonly) CBPeripheral *peripheral;
@property (readonly) CBEAdvertisement *advertisement;
@property (readonly) NSNumber *rssi;

- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral advertisement:(CBEAdvertisement *)advertisement rssi:(NSNumber *)rssi;

@end










@interface CBECentralManagerDidDisconnectPeripheral : NSEObject

@property (readonly) CBPeripheral *peripheral;
@property (readonly) NSError *error;

- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral error:(NSError *)error;

@end










@protocol CBECentralManagerDisconnectionDelegate <NSEOperationDelegate>

@optional
- (void)cbeCentralManagerDisconnectionDidUpdateState:(CBECentralManagerDisconnection *)disconnection;
- (void)cbeCentralManagerDisconnectionDidStart:(CBECentralManagerDisconnection *)disconnection;
- (void)cbeCentralManagerDisconnectionDidCancel:(CBECentralManagerDisconnection *)disconnection;
- (void)cbeCentralManagerDisconnectionDidFinish:(CBECentralManagerDisconnection *)disconnection;

- (void)cbeCentralManagerDisconnectionDidUpdateProgress:(CBECentralManagerDisconnection *)disconnection;

@end



@interface CBECentralManagerDisconnection : NSEOperation <CBECentralManagerDisconnectionDelegate>

@property (readonly) CBECentralManagerOperation *parent;
@property (readonly) NSMutableOrderedSet<CBECentralManagerDisconnectionDelegate> *delegates;
@property (readonly) CBPeripheral *peripheral;

- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral;

@end










@protocol CBECentralManagerConnectionDelegate <NSETimeoutOperationDelegate>

@optional
- (void)cbeCentralManagerConnectionDidUpdateState:(CBECentralManagerConnection *)connection;
- (void)cbeCentralManagerConnectionDidStart:(CBECentralManagerConnection *)connection;
- (void)cbeCentralManagerConnectionDidCancel:(CBECentralManagerConnection *)connection;
- (void)cbeCentralManagerConnectionDidFinish:(CBECentralManagerConnection *)connection;

- (void)cbeCentralManagerConnectionDidUpdateProgress:(CBECentralManagerConnection *)connection;

@end



@interface CBECentralManagerConnection : NSETimeoutOperation <CBECentralManagerConnectionDelegate, CBECentralManagerDisconnectionDelegate>

@property (readonly) CBECentralManagerOperation *parent;
@property (readonly) NSMutableOrderedSet<CBECentralManagerConnectionDelegate> *delegates;
@property (readonly) CBPeripheral *peripheral;
@property (readonly) NSDictionary *options;
@property (readonly) CBECentralManagerDisconnection *disconnection;

- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral options:(NSDictionary *)options timeout:(NSTimeInterval)timeout;

@end










@protocol CBECentralManagerDelegate <CBEManagerDelegate, CBEPeripheralDelegate, CBECentralManagerDisconnectionDelegate, CBECentralManagerConnectionDelegate>

@optional
- (void)cbeCentralManagerDidUpdateState:(CBCentralManager *)central;
- (void)cbeCentralManagerDidDiscoverPeripheral:(CBCentralManager *)central;
- (void)cbeCentralManagerDidDisconnectPeripheral:(CBCentralManager *)central;

@end



@interface CBECentralManagerOperation : CBEManagerOperation <CBECentralManagerDelegate, CBCentralManagerDelegate>

@property (readonly) NSMutableOrderedSet<CBECentralManagerDelegate> *delegates;
@property (readonly) NSMutableSet<CBPeripheral *> *peripherals;

@property (weak, readonly) CBCentralManager *object;
@property (weak, readonly) CBECentralManagerDidDiscoverPeripheral *didDiscoverPeripheral;
@property (weak, readonly) CBECentralManagerDidDisconnectPeripheral *didDisconnectPeripheral;
@property (weak, readonly) CBECentralManagerDisconnection *disconnection;
@property (weak, readonly) CBECentralManagerConnection *connection;

- (CBECentralManagerDisconnection *)disconnectPeripheral:(CBPeripheral *)peripheral;
- (CBECentralManagerDisconnection *)disconnectPeripheral:(CBPeripheral *)peripheral completion:(NSEBlock)completion;

- (CBECentralManagerConnection *)connectPeripheral:(CBPeripheral *)peripheral options:(NSDictionary *)options timeout:(NSTimeInterval)timeout;
- (CBECentralManagerConnection *)connectPeripheral:(CBPeripheral *)peripheral options:(NSDictionary *)options timeout:(NSTimeInterval)timeout completion:(NSEBlock)completion;

@end
