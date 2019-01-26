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

@end
