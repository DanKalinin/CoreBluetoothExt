//
//  CBEPeer.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/19/19.
//

#import "CBEMain.h"

@class CBEPeer;
@class CBEPeerOperation;

@protocol CBEPeerDelegate;










@interface CBPeer (CBE)

@property (readonly) CBEPeerOperation *nseOperation;

@end










@interface CBEPeer : CBPeer

@end










@protocol CBEPeerDelegate <NSEObjectDelegate>

@end



@interface CBEPeerOperation : NSEObjectOperation <CBEPeerDelegate>

@property (weak, readonly) CBPeer *object;

@end
