//
//  CBEAttribute.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/23/19.
//

#import "CBEMain.h"

@class CBEAttribute;
@class CBEAttributeOperation;

@protocol CBEAttributeDelegate;










@interface CBAttribute (CBE)

@property (readonly) CBEAttributeOperation *nseOperation;

@end










@interface CBEAttribute : CBAttribute

@end










@protocol CBEAttributeDelegate <NSEObjectDelegate>

@end



@interface CBEAttributeOperation : NSEObjectOperation <CBEAttributeDelegate>

@property (weak, readonly) CBAttribute *object;

@end
