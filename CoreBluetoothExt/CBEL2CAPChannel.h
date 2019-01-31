//
//  CBEL2CAPChannel.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/28/19.
//

#import "CBEObject.h"

@class CBEL2CAPChannel;
@class CBEL2CAPChannelOperation;

@protocol CBEL2CAPChannelDelegate;










@interface CBL2CAPChannel (CBE)

@property (readonly) CBEL2CAPChannelOperation *cbeOperation;

@end










@interface CBEL2CAPChannel : CBL2CAPChannel

@end










@protocol CBEL2CAPChannelDelegate <NSEObjectDelegate, NSEStreamsDelegate>

@end



@interface CBEL2CAPChannelOperation : NSEObjectOperation <CBEL2CAPChannelDelegate>

@property (readonly) NSEStreams *streams;

@property (weak, readonly) CBL2CAPChannel *object;

@end
