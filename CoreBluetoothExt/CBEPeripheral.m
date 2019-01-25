//
//  CBEPeripheral.m
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/19/19.
//

#import "CBEPeripheral.h"
#import "CBECentralManager.h"










@implementation CBPeripheral (CBE)

@dynamic nseOperation;

- (Class)nseOperationClass {
    return CBEPeripheralOperation.class;
}

@end










@interface CBEPeripheral ()

@end



@implementation CBEPeripheral

@end










@interface CBEPeripheralAdvertisement ()

@property NSArray<CBUUID *> *serviceUUIDs;
@property BOOL isConnectable;

@end



@implementation CBEPeripheralAdvertisement

- (instancetype)initWithDictionary:(NSDictionary *)dictionary {
    self = [super initWithDictionary:dictionary];
    
    self.serviceUUIDs = dictionary[CBAdvertisementDataServiceUUIDsKey];
    self.isConnectable = [dictionary[CBAdvertisementDataIsConnectable] boolValue];
    
    return self;
}

@end










@interface CBEPeripheralDidDisconnect ()

@property NSError *error;

@end



@implementation CBEPeripheralDidDisconnect

- (instancetype)initWithError:(NSError *)error {
    self = super.init;
    
    self.error = error;
    
    return self;
}

@end










@interface CBEPeripheralConnection ()

@property NSDictionary *options;
@property CBEPeripheralDisconnection *disconnection;

@end



@implementation CBEPeripheralConnection

@dynamic parent;
@dynamic delegates;

- (instancetype)initWithOptions:(NSDictionary *)options timeout:(NSTimeInterval)timeout {
    self = [super initWithTimeout:timeout];
    
    self.options = options;
    
    return self;
}

- (void)updateState:(NSEOperationState)state {
    [super updateState:state];
    
    [self.delegates cbePeripheralConnectionDidUpdateState:self];
    if (state == NSEOperationStateDidStart) {
        [self.delegates cbePeripheralConnectionDidStart:self];
    } else if (state == NSEOperationStateDidCancel) {
        [self.delegates cbePeripheralConnectionDidCancel:self];
    } else if (state == NSEOperationStateDidFinish) {
        [self.delegates cbePeripheralConnectionDidFinish:self];
    }
}

- (void)updateProgress:(int64_t)completedUnitCount {
    [super updateProgress:completedUnitCount];
    
    [self.delegates cbePeripheralConnectionDidUpdateProgress:self];
}

#pragma mark - CBEPeripheralConnectionDelegate

- (void)cbePeripheralConnectionDidStart:(CBEPeripheralConnection *)connection {
    if (self.parent.object.state == CBPeripheralStateConnected) {
        [self finish];
    } else {
        self.parent.connection = self;
        
        if (self.parent.object.state == CBPeripheralStateConnecting) {
        } else {
            [self.parent.parent.object connectPeripheral:self.parent.object options:self.options];
        }
    }
}

- (void)cbePeripheralConnectionDidCancel:(CBEPeripheralConnection *)connection {
    self.disconnection = self.parent.disconnect;
    [self.disconnection.delegates addObject:self];
}

#pragma mark - CBEPeripheralDisconnectionDelegate

- (void)cbePeripheralDisconnectionDidFinish:(CBEPeripheralDisconnection *)disconnection {
    [self finish];
}

@end










@interface CBEPeripheralServicesDiscovery ()

@property NSArray<CBUUID *> *services;
@property CBEPeripheralDisconnection *disconnection;

@end



@implementation CBEPeripheralServicesDiscovery

@dynamic parent;
@dynamic delegates;

- (instancetype)initWithServices:(NSArray<CBUUID *> *)services timeout:(NSTimeInterval)timeout {
    self = [super initWithTimeout:timeout];
    
    self.services = services;
    
    return self;
}

- (void)updateState:(NSEOperationState)state {
    [super updateState:state];
    
    [self.delegates cbePeripheralServicesDiscoveryDidUpdateState:self];
    if (state == NSEOperationStateDidStart) {
        [self.delegates cbePeripheralServicesDiscoveryDidStart:self];
    } else if (state == NSEOperationStateDidCancel) {
        [self.delegates cbePeripheralServicesDiscoveryDidCancel:self];
    } else if (state == NSEOperationStateDidFinish) {
        [self.delegates cbePeripheralServicesDiscoveryDidFinish:self];
    }
}

- (void)updateProgress:(int64_t)completedUnitCount {
    [super updateProgress:completedUnitCount];
    
    [self.delegates cbePeripheralServicesDiscoveryDidUpdateProgress:self];
}

#pragma mark - CBEPeripheralServicesDiscoveryDelegate

- (void)cbePeripheralServicesDiscoveryDidStart:(CBEPeripheralServicesDiscovery *)discovery {
    NSArray *services = [self.parent retrieveServicesWithIdentifiers:self.services];
    if (services.count < self.services.count) {
        self.parent.servicesDiscovery = self;
        
        [self.parent.object discoverServices:self.services];
    } else {
        [self finish];
    }
}

- (void)cbePeripheralServicesDiscoveryDidCancel:(CBEPeripheralServicesDiscovery *)discovery {
    self.disconnection = self.parent.disconnect;
    [self.disconnection.delegates addObject:self];
}

#pragma mark - CBEPeripheralDisconnectionDelegate

- (void)cbePeripheralDisconnectionDidFinish:(CBEPeripheralDisconnection *)disconnection {
    [self finish];
}

@end










@interface CBEPeripheralOperation ()

@end



@implementation CBEPeripheralOperation

@dynamic parent;
@dynamic delegates;
@dynamic object;

- (instancetype)initWithObject:(CBPeripheral *)object {
    self = [super initWithObject:object];
    
    object.delegate = self;
    
    return self;
}

- (NSArray<CBService *> *)retrieveServicesWithIdentifiers:(NSArray<CBUUID *> *)identifiers {
    NSMutableArray *services = NSMutableArray.array;
    
    for (CBService *service in self.object.services) {
        [service.nseOperation.delegates addObject:self.delegates];
        
        if ([identifiers containsObject:service.UUID]) {
            [services addObject:service];
        }
    }
    
    return services;
}

- (CBEPeripheralDisconnection *)disconnect {
    CBEPeripheralDisconnection *disconnection = CBEPeripheralDisconnection.new;
    
    [self addOperation:disconnection];
    
    return disconnection;
}

- (CBEPeripheralDisconnection *)disconnectWithCompletion:(NSEBlock)completion {
    CBEPeripheralDisconnection *disconnection = self.disconnect;
    
    disconnection.completion = completion;
    
    return disconnection;
}

- (CBEPeripheralConnection *)connectWithOptions:(NSDictionary *)options timeout:(NSTimeInterval)timeout {
    [self.parent.peripherals addObject:self.object];
    
    CBEPeripheralConnection *connection = [CBEPeripheralConnection.alloc initWithOptions:options timeout:timeout];
    
    [self addOperation:connection];
    
    return connection;
}

- (CBEPeripheralConnection *)connectWithOptions:(NSDictionary *)options timeout:(NSTimeInterval)timeout completion:(NSEBlock)completion {
    CBEPeripheralConnection *connection = [self connectWithOptions:options timeout:timeout];
    
    connection.completion = completion;
    
    return connection;
}

- (CBEPeripheralServicesDiscovery *)discoverServices:(NSArray<CBUUID *> *)services timeout:(NSTimeInterval)timeout {
    CBEPeripheralServicesDiscovery *discovery = [CBEPeripheralServicesDiscovery.alloc initWithServices:services timeout:timeout];
    
    [self addOperation:discovery];
    
    return discovery;
}

- (CBEPeripheralServicesDiscovery *)discoverServices:(NSArray<CBUUID *> *)services timeout:(NSTimeInterval)timeout completion:(NSEBlock)completion {
    CBEPeripheralServicesDiscovery *discovery = [self discoverServices:services timeout:timeout];
    
    discovery.completion = completion;
    
    return discovery;
}

#pragma mark - CBPeripheralDelegate

- (void)peripheral:(CBPeripheral *)peripheral didDiscoverServices:(NSError *)error {
    if (error) {
        self.servicesDiscovery.error = error;
        [self.servicesDiscovery cancel];
    } else {
        NSArray *services = [self retrieveServicesWithIdentifiers:self.servicesDiscovery.services];
        if (services.count < self.servicesDiscovery.services.count) {
            self.servicesDiscovery.error = [NSError errorWithDomain:CBEErrorDomain code:CBEErrorLessAttributes userInfo:nil];
            [self.servicesDiscovery cancel];
        } else {
            [self.servicesDiscovery finish];
        }
    }
}

- (void)peripheral:(CBPeripheral *)peripheral didDiscoverCharacteristicsForService:(CBService *)service error:(NSError *)error {
    if (error) {
        service.nseOperation.characteristicsDiscovery.error = error;
        [service.nseOperation.characteristicsDiscovery finish];
    } else {
        NSArray *characteristics = [service.nseOperation retrieveCharacteristicsWithIdentifiers:service.nseOperation.characteristicsDiscovery.characteristics];
        if (characteristics.count < service.nseOperation.characteristicsDiscovery.characteristics.count) {
            service.nseOperation.characteristicsDiscovery.error = [NSError errorWithDomain:CBEErrorDomain code:CBEErrorLessAttributes userInfo:nil];
            [service.nseOperation.characteristicsDiscovery cancel];
        } else {
            [service.nseOperation.characteristicsDiscovery finish];
        }
    }
}

@end
