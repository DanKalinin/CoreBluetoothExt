//
//  CBEAdvertisement.m
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/26/19.
//

#import "CBEAdvertisement.h"



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
