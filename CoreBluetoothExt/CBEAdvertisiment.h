//
//  CBEAdvertisiment.h
//  CoreBluetoothExt
//
//  Created by Dan Kalinin on 2/13/19.
//

#import "CBEMain.h"



@interface CBEAdvertisement : NSEDictionaryObject

@property (readonly) NSArray<CBUUID *> *serviceUUIDs;
@property (readonly) BOOL isConnectable;

@end
