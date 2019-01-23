//
//  CBEService.m
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/23/19.
//

#import "CBEService.h"










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

@end



@implementation CBEServiceCharacteristicsDiscovery

- (instancetype)initWithCharacteristics:(NSArray<CBUUID *> *)characteristics timeout:(NSTimeInterval)timeout {
    self = [super initWithTimeout:timeout];
    
    self.characteristics = characteristics;
    
    return self;
}

@end










@interface CBEServiceOperation ()

@end



@implementation CBEServiceOperation

@dynamic object;

- (NSArray<CBCharacteristic *> *)retrieveCharacteristicsWithIdentifiers:(NSArray<CBUUID *> *)identifiers {
    NSMutableArray *characteristics = NSMutableArray.array;
    
    for (CBCharacteristic *characteristic in self.object.characteristics) {
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
