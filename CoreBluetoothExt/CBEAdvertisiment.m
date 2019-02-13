//
//  CBEAdvertisiment.m
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 2/13/19.
//

#import "CBEAdvertisiment.h"



@interface CBEAdvertisement ()

@property NSArray<CBUUID *> *serviceUUIDs;
@property BOOL isConnectable;

@end



@implementation CBEAdvertisement

- (instancetype)initWithDictionary:(NSDictionary *)dictionary {
    self = [super initWithDictionary:dictionary];
    
    self.serviceUUIDs = dictionary[CBAdvertisementDataServiceUUIDsKey];
    self.isConnectable = [dictionary[CBAdvertisementDataIsConnectable] boolValue];
    
    return self;
}

@end
