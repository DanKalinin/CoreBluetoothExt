//
//  CBEService.m
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/23/19.
//

#import "CBEService.h"
#import "CBEPeripheral.h"










@implementation CBService (CBE)

@dynamic nseOperation;

- (Class)nseOperationClass {
    return CBEServiceOperation.class;
}

@end










@interface CBEService ()

@end



@implementation CBEService

@end










@interface CBEServiceCharacteristicsDiscovery ()

@property NSArray<CBUUID *> *characteristics;
@property CBEPeripheralDisconnection *disconnection;

@end



@implementation CBEServiceCharacteristicsDiscovery

@dynamic parent;
@dynamic delegates;

- (instancetype)initWithCharacteristics:(NSArray<CBUUID *> *)characteristics timeout:(NSTimeInterval)timeout {
    self = [super initWithTimeout:timeout];
    
    self.characteristics = characteristics;
    
    return self;
}

- (void)updateState:(NSEOperationState)state {
    [super updateState:state];
    
    [self.delegates cbeServiceCharacteristicsDiscoveryDidUpdateState:self];
    if (state == NSEOperationStateDidStart) {
        [self.delegates cbeServiceCharacteristicsDiscoveryDidStart:self];
    } else if (state == NSEOperationStateDidCancel) {
        [self.delegates cbeServiceCharacteristicsDiscoveryDidCancel:self];
    } else if (state == NSEOperationStateDidFinish) {
        [self.delegates cbeServiceCharacteristicsDiscoveryDidFinish:self];
    }
}

- (void)updateProgress:(int64_t)completedUnitCount {
    [super updateProgress:completedUnitCount];
    
    [self.delegates cbeServiceCharacteristicsDiscoveryDidUpdateProgress:self];
}

#pragma mark - CBEServiceCharacteristicsDiscoveryDelegate

- (void)cbeServiceCharacteristicsDiscoveryDidStart:(CBEServiceCharacteristicsDiscovery *)discovery {
    NSArray *characteristics = [self.parent retrieveCharacteristicsWithIdentifiers:self.characteristics];
    if (characteristics.count < self.characteristics.count) {
        self.parent.characteristicsDiscovery = self;
        
        [self.parent.parent.object discoverCharacteristics:self.characteristics forService:self.parent.object];
    } else {
        [self finish];
    }
}

- (void)cbeServiceCharacteristicsDiscoveryDidCancel:(CBEServiceCharacteristicsDiscovery *)discovery {
    self.disconnection = self.parent.parent.disconnect;
    [self.disconnection.delegates addObject:self];
}

#pragma mark - CBEPeripheralDisconnectionDelegate

- (void)cbePeripheralDisconnectionDidFinish:(CBEPeripheralDisconnection *)disconnection {
    [self finish];
}

@end










@interface CBEServiceOperation ()

@end



@implementation CBEServiceOperation

@dynamic parent;
@dynamic delegates;
@dynamic object;

- (NSArray<CBCharacteristic *> *)retrieveCharacteristicsWithIdentifiers:(NSArray<CBUUID *> *)identifiers {
    NSMutableArray *characteristics = NSMutableArray.array;
    
    for (CBCharacteristic *characteristic in self.object.characteristics) {
        [characteristic.nseOperation.delegates addObject:self.delegates];
        
        if ([identifiers containsObject:characteristic.UUID]) {
            [characteristics addObject:characteristic];
        }
    }
    
    return characteristics;
}

- (CBEServiceCharacteristicsDiscovery *)discoverCharacteristics:(NSArray<CBUUID *> *)characteristics timeout:(NSTimeInterval)timeout {
    CBEServiceCharacteristicsDiscovery *discovery = [CBEServiceCharacteristicsDiscovery.alloc initWithCharacteristics:characteristics timeout:timeout];
    
    [self addOperation:discovery];
    
    return discovery;
}

- (CBEServiceCharacteristicsDiscovery *)discoverCharacteristics:(NSArray<CBUUID *> *)characteristics timeout:(NSTimeInterval)timeout completion:(NSEBlock)completion {
    CBEServiceCharacteristicsDiscovery *discovery = [self discoverCharacteristics:characteristics timeout:timeout];
    
    discovery.completion = completion;
    
    return discovery;
}

@end
