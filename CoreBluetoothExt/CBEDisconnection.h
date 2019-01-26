//
//  CBEDisconnection.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 1/26/19.
//

#import "CBEMain.h"

@class CBEDisconnection;

@protocol CBEDisconnectionDelegate;



@protocol CBEDisconnectionDelegate <NSEOperationDelegate>

@end



@interface CBEDisconnection : NSEOperation <CBEDisconnectionDelegate>

@end
