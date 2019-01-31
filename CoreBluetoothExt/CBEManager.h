//
//  CBEManager.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/19/19.
//

#import "CBEObject.h"

@class CBEManager;
@class CBEManagerOperation;

@protocol CBEManagerDelegate;












@interface CBManager (CBE)

@property (readonly) CBEManagerOperation *cbeOperation;

@end










@interface CBEManager : CBManager

@end










@protocol CBEManagerDelegate <NSEObjectDelegate>

@end



@interface CBEManagerOperation : NSEObjectOperation <CBEManagerDelegate>

@property (weak, readonly) CBManager *object;

@end
