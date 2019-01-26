//
//  CBEPeripheral.m
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/26/19.
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










@interface CBEPeripheralServicesDiscovery ()

@property NSArray<CBUUID *> *services;
@property CBECentralManagerPeripheralDisconnection *disconnection;

@end



@implementation CBEPeripheralServicesDiscovery

@dynamic parent;
@dynamic delegates;

- (instancetype)initWithServices:(NSArray<CBUUID *> *)services {
    self = super.init;
    
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
        [self.parent.object discoverServices:self.services];
    } else {
        [self finish];
    }
}

@end










@interface CBEPeripheralCharacteristicsDiscovery ()

@property NSArray<CBUUID *> *characteristics;
@property CBService *service;

@end



@implementation CBEPeripheralCharacteristicsDiscovery

@dynamic parent;
@dynamic delegates;

- (instancetype)initWithCharacteristics:(NSArray<CBUUID *> *)characteristics service:(CBService *)service {
    self = super.init;
    
    self.characteristics = characteristics;
    self.service = service;
    
    return self;
}

- (void)updateState:(NSEOperationState)state {
    [super updateState:state];
    
    [self.delegates cbePeripheralCharacteristicsDiscoveryDidUpdateState:self];
    if (state == NSEOperationStateDidStart) {
        [self.delegates cbePeripheralCharacteristicsDiscoveryDidStart:self];
    } else if (state == NSEOperationStateDidCancel) {
        [self.delegates cbePeripheralCharacteristicsDiscoveryDidCancel:self];
    } else if (state == NSEOperationStateDidFinish) {
        [self.delegates cbePeripheralCharacteristicsDiscoveryDidFinish:self];
    }
}

- (void)updateProgress:(int64_t)completedUnitCount {
    [super updateProgress:completedUnitCount];
    
    [self.delegates cbePeripheralCharacteristicsDiscoveryDidUpdateProgress:self];
}

#pragma mark - CBEPeripheralCharacteristicsDiscoveryDelegate

- (void)cbePeripheralCharacteristicsDiscoveryDidStart:(CBEPeripheralCharacteristicsDiscovery *)discovery {
    
}

@end










@interface CBEPeripheralOperation ()

@property (weak) CBEPeripheralServicesDiscovery *servicesDiscovery;
@property (weak) CBEPeripheralCharacteristicsDiscovery *characteristicsDiscovery;

@end



@implementation CBEPeripheralOperation

@dynamic parent;
@dynamic object;

- (instancetype)initWithObject:(CBPeripheral *)object {
    self = [super initWithObject:object];
    
    object.delegate = self;
    
    return self;
}

- (NSArray<CBService *> *)retrieveServicesWithIdentifiers:(NSArray<CBUUID *> *)identifiers {
    NSMutableArray *services = NSMutableArray.array;
    
    for (CBService *service in self.object.services) {
        if ([identifiers containsObject:service.UUID]) {
            [services addObject:service];
        }
    }
    
    return services;
}

- (CBEPeripheralServicesDiscovery *)discoverServices:(NSArray<CBUUID *> *)services {
    self.servicesDiscovery = [CBEPeripheralServicesDiscovery.alloc initWithServices:services].nseAutorelease;
    
    [self addOperation:self.servicesDiscovery];
    
    return self.servicesDiscovery;
}

- (CBEPeripheralServicesDiscovery *)discoverServices:(NSArray<CBUUID *> *)services completion:(NSEBlock)completion {
    CBEPeripheralServicesDiscovery *discovery = [self discoverServices:services];
    
    discovery.completion = completion;
    
    return discovery;
}

- (CBEPeripheralCharacteristicsDiscovery *)discoverCharacteristics:(NSArray<CBUUID *> *)characteristics forService:(CBService *)service {
    self.characteristicsDiscovery = [CBEPeripheralCharacteristicsDiscovery.alloc initWithCharacteristics:characteristics service:service].nseAutorelease;
    
    [self addOperation:self.characteristicsDiscovery];
    
    return self.characteristicsDiscovery;
}

- (CBEPeripheralCharacteristicsDiscovery *)discoverCharacteristics:(NSArray<CBUUID *> *)characteristics forService:(CBService *)service completion:(NSEBlock)completion {
    CBEPeripheralCharacteristicsDiscovery *discovery = [self discoverCharacteristics:characteristics forService:service];
    
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
        self.characteristicsDiscovery.error = error;
        [self.characteristicsDiscovery finish];
    } else {
//        NSArray *characteristics = [service.nseOperation retrieveCharacteristicsWithIdentifiers:service.nseOperation.characteristicsDiscovery.characteristics];
//        if (characteristics.count < service.nseOperation.characteristicsDiscovery.characteristics.count) {
//            service.nseOperation.characteristicsDiscovery.error = [NSError errorWithDomain:CBEErrorDomain code:CBEErrorLessAttributes userInfo:nil];
//            [service.nseOperation.characteristicsDiscovery cancel];
//        } else {
//            [service.nseOperation.characteristicsDiscovery finish];
//        }
    }
}

@end
