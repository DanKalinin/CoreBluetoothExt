//
//  CBEL2CAPChannel.m
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/28/19.
//

#import "CBEL2CAPChannel.h"










@implementation CBL2CAPChannel (CBE)

@dynamic cbeOperation;

- (Class)cbeOperationClass {
    return CBEL2CAPChannelOperation.class;
}

@end










@interface CBEL2CAPChannel ()

@end



@implementation CBEL2CAPChannel

@end










@interface CBEL2CAPChannelOperation ()

@property NSEStreams *streams;

@end



@implementation CBEL2CAPChannelOperation

@dynamic object;

- (instancetype)initWithObject:(CBL2CAPChannel *)object {
    self = [super initWithObject:object];
    
    self.streams = [NSEStreams.alloc initWithInputStream:object.inputStream outputStream:object.outputStream];
    [self.streams.delegates addObject:self.delegates];
    
    return self;
}

@end
