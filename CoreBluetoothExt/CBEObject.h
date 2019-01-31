//
//  CBEObject.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/31/19.
//

#import "CBEMain.h"

@class CBEObject;










@interface NSObject (CBE)

@property (readonly) Class cbeOperationClass;
@property (readonly) NSEObjectOperation *cbeOperation;

@end










@interface CBEObject : NSObject

@end
