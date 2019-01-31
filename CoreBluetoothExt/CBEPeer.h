//
//  CBEPeer.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/19/19.
//

#import "CBEObject.h"

@class CBEPeer;
@class CBEPeerOperation;

@protocol CBEPeerDelegate;










@interface CBPeer (CBE)

@property (readonly) CBEPeerOperation *cbeOperation;

@end










@interface CBEPeer : CBPeer

@end










@protocol CBEPeerDelegate <NSEObjectDelegate>

@end



@interface CBEPeerOperation : NSEObjectOperation <CBEPeerDelegate>

@property (weak, readonly) CBPeer *object;

@end
