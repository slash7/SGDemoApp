//
// SGLayer.h
// CCLocatorServices
//
// Created by Derek Smith on 9/15/09.
// Copyright 2010 SimpleGeo. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SGLocationTypes.h"
#import "SGLocationService.h"

@protocol SGRecordAnnotation;


/*!
* @class SGLayer 
* @abstract Updates and retrieves records that are within a layer.
* @discussion A layer object has the ability to update and retrieve 
* records that are already registered with the object. By adding the layer as a delegate
* to the @link //simplegeo/ooc/cl/SGLocationService SGLocationService @/link, the layer will do its best
* to update the record once information is recieved about it. If the layer
* recieves a record that isn't already registered, it will call @link recordAnnotationFromGeoJSONObject: recordAnnotationFromGeoJSONObject: @/link.
* If the record is already registered, then the layer object will attempt to call 
* @link //simplegeo/ooc/instm/SGRecordAnnotation/updateRecordWithGeoJSONObject: updateRecordWithGeoJSONObject: @link if
* the object implements it.
*
* The layer object does not handle errors generated by the @link //simplegeo/ooc/cl/SGLocationService SGLocationService @/link.
* If an error is incurred, it is up to the other delegates to handle the error.
*/
@interface SGLayer : NSObject <SGLocationServiceDelegate> {
 
    NSString* layerId;
    
 
}

/*!
* @property The name of the layer.
* @abstract The layerId is the name of the layer used in SimpleGeo. A common convention
* used in naming a layer is a reverse URL. (e.g. "com.simplegeo.spatula").
*/
@property (nonatomic, readonly) NSString* layerId;

/*!
* @method initWithLayerName:
* @abstract ￼Initialize a new SGLayer object with a layer name.
* @discussion See @link layerId layerId @/link
* @param layerId ￼The name of the layer.
* @result ￼A initialized SGLayer object.
*/
- (id) initWithLayerName:(NSString*)layerId;

/*!
* @method recordAnnotationFromGeoJSONObject:
* @abstract ￼Creates a new record from the given dictionary.
* @discussion ￼This method is called when the layer finds an unregistered record. The default implementation
* of this method creates a new instance of @link //simplegeo/ooc/cl/SGRecord SGRecord @/link and calls
* @link //simplegeo/ooc/instm/SGRecord/updateRecordWithGeoJSONObject: updateRecordWithGeoJSONObject: @/link.
* If subclasses wish to do any manipulation to a record after it is retrieved from SimpleGeo, they are encouraged to
* override this method.
* @param geoJSONObject The GeoJSON dictionary representation of the new record. ￼
* @result ￼The @link //simplegeo/ooc/instp/SGRecordAnnotation SGRecordAnnotation @/link of the GeoJSON dictionary.
*/
- (id<SGRecordAnnotation>) recordAnnotationFromGeoJSONObject:(NSDictionary*)geoJSONObject;

#pragma mark -
#pragma mark Register Record with Layer 

/*!
* @method recordAnnotations
* @result ￼All the @link //simplegeo/ooc/cl/SGRecordAnnotaiton SGRecordAnntations @/link registered with the SGLayer object.
*/
- (NSArray*) recordAnnotations;

/*!
* @method removeAllRecordAnnotations
* @abstract ￼ Removes all @link //simplegeo/ooc/cl/SGRecordAnnotation SGRecordAnnotations @/link registered with the SGLayer object.
*/
- (void) removeAllRecordAnnotations;

/*!
* @method addRecordAnnotation:
* @abstract ￼ Adds a @link //simplegeo/ooc/intf/SGRecordAnnotation SGRecordAnnotation @/link to the layer.
* @discussion When a record is added, the @link //simplegeo/ooc/instp/SGRecordAnnotation/layer layer @/link of the record
* is changed to reflect the @link layerId layerId @/link.
* @param recordAnnotation The record annotation to add.￼
*/
- (void) addRecordAnnotation:(id<SGRecordAnnotation>)recordAnnotation;

/*!
* @method addRecordAnnotations:
* @abstract ￼Adds an array of @link //simplegeo/ooc/intf/SGRecordAnnotation SGRecordAnnotations @/link to the SGLayer object.
* @discussion See @link addRecord: addRecord: @/link
* @param recordAnnotations ￼The array of record annotations to add.
*/
- (void) addRecordAnnotations:(NSArray*)recordAnnotations;

/*!
* @method removeRecordAnnotationAtIndex:
* @abstract ￼Remove a @link //simplegeo/ooc/intf/SGRecordAnnotation SGRecordAnnotation @/link registed with the SGLayer object.
* @param recordAnnotation The record annotation to remove.
*/
- (void) removeRecordAnnotation:(id<SGRecordAnnotation>)recordAnnotation;

/*!
* @method removeRecordAnnotationAtIndex:
* @abstract ￼Remove a @link //simplegeo/ooc/intf/SGRecordAnnotation SGRecordAnnotation @/link registed with the SGLayer object.
* @param recordAnnotation The array of record annotations to remove.
*/
- (void) removeRecordAnnotations:(NSArray*)recordAnnotations;


/*!
* @method recordAnnotationCount
* @abstract ￼ Get the amount of @link //simplegeo/ooc/intf/SGRecordAnnotation SGRecordAnnotations @/link registered with the SGLayer object.
* @result ￼ The amount of records registerd with the SGLayer object.
*/
- (NSInteger) recordAnnotationCount;

#pragma mark -
#pragma mark SGLocationService methods 
 
/*!
* @method updateAllRecords
* @abstract ￼ Updates or adds all records registered with the SGLayer object to SimpleGeo.
* @discussion See @link updateRecordsFromIndex:toIndex: updateRecordsFromIndex:toIndex: @/link
* @result ￼ A request identifier that can be used to analyze the response object returned to
* the @link //simplegeo/ooc/cl/SGLocationServiceDelegate SGLocationServiceDelegate @/link
*/
- (NSString*) updateAllRecords;

/*!
* @method retrieveAllRecords
* @abstract ￼ Retrieves all records that are registered with the SGLayer object from SimpleGeo.
* @discussion See @link updateRecordsFromIndex:toIndex: updateRecordsFromIndex:toIndex: @/link
* @result ￼ A request identifier that can be used to analyze the response object returned to
* the @link //simplegeo/ooc/cl/SGLocationServiceDelegate SGLocationServiceDelegate @/link
*/
- (NSString*) retrieveAllRecords;

/*!
* @method updateRecordsFromIndex:toIndex:
* @abstract ￼ Updates or adds all registered records within a range from this SGLayer object to SimpleGeo.
* @discussion ￼ Currently, there is no way to update ALL records in a single PUT request. Each
* record creates a HTTP request so if there are 300 records registered with the SGLayer object,
* then it might be a minute in order to recieve a response back saying all records have been updated. 
* As soon as a request returns, the next request is loaded. If at any time a request fails,
* all delegates registered with @link //simplegeo/ooc/cl/SGLocationService SGLocationService @/link
* are notified with the initial request identifier and the proper NSError.
* 
* Records are updated in order. If a record update fails at n + 1, then all records 0 <= n will
* have been updated.
* @param recordAnnotations The annotations to update.
* @result ￼ A request identifier that can be used to analyze the response object returned to
* the @link //simplegeo/ooc/cl/SGLocationServiceDelegate SGLocationServiceDelegate @/link
*/
- (NSString*) updateRecordAnnotations:(NSArray*)recordAnnotations;

/*!
* @method retrieveRecordsFromIndex:toIndex:
* @abstract ￼ Retrieves all registered records within a range from this layer that are in SimpleGeo.
* @discussion ￼ Currently, there is no way to retrieve ALL records in a single GET request. Each
* record creates a HTTP request so if there are 300 records register with the SGLayer object,
* then it might be a minute in order to recieve a response back. As soon as a request returns,
* the record is immediately updated and the next request is sent. If at any time a request fails,
* all delegates registered with @link //simplegeo/ooc/cl/SGLocationService SGLocationService @/link
* are notified with the response identifier.
* 
* Records are retrieved in order. If record retrieval fails at n + 1, then all records 0 <= n will
* be retrieved.
* @param recordAnnotations The annotations to retrieve.
* @result ￼ A request identifier that can be used to analyze the response object returned to
* the @link //simplegeo/ooc/cl/SGLocationServiceDelegate SGLocationServiceDelegate @/link
*/
- (NSString*) retrieveRecordAnnotations:(NSArray*)recordAnnoations;

/*!
* @method retrieveRecordsForGeohash:types:limit:
* @abstract Retrieves records within the given geohash from SimpleGeo.
* @param geohash The geohash to search in.
* @param types The types of objects to retrieve. ￼
* @param limit The amount of objects to retrieve.
* @result ￼ A request identifier that can be used to analyze the response object returned to
* the @link //simplegeo/ooc/intf/SGLocationServiceDelegate SGLocationServiceDelegate @/link
*/
- (NSString*) retrieveRecordsForGeohash:(SGGeohash)region types:(NSArray*)types limit:(NSInteger)limit;

/*!
* @method retrieveRecordsForCoordinate:radius:types:limit:
* @abstract ￼Retrieves records within from an origin with a desired radius from SimpleGeo.
* @param coord The lat/lon coordinates that declare the origin of the search space.
* @param radius The radius of the circle.
* @param types The types of objects to retrieve. ￼
* @param limit The amount of objects to retrieve.
* @result ￼ A request identifier that can be used to analyze the response object returned to
* the @link //simplegeo/ooc/intf/SGLocationServiceDelegate SGLocationServiceDelegate @/link
*/
- (NSString*) retrieveRecordsForCoordinate:(CLLocationCoordinate2D)coord 
                                    radius:(double)radius
                                     types:(NSArray*)types
                                     limit:(NSInteger)limit;

@end
