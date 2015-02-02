/**
  IGGuideManager.h
  IGObjectiveGuideDemo

  Created by Mikko Virkkilä on 21.9.2013.
  Copyright (c) 2013-2014 Nimble Devices. All rights reserved.
 
 
 The following frameworks must be linked in to the app  : 
  - CoreBluetooth
  - CoreLocation (set target membership to optional for iOS6 support)
  - CoreMotion
 
*/

#import <Foundation/Foundation.h>
#import "IGPositioningDelegate.h"
#import "IGDirectionsDelegate.h"


@interface IGGuideManager : NSObject

/**
 * Allows adding an offset to compass measurements
 */
@property (assign, atomic) CLLocationDirection compassDirectionOffset;

/**
 * This delegate receives updates about location and heading updates.
 */
@property(assign, nonatomic) id<IGPositioningDelegate> positioningDelegate;

/**
 *  This delegate receives updates about routing directions.
 */
@property(assign, nonatomic) id<IGDirectionsDelegate> directionsDelegate;


/**
 *  When a route target is set and routing fails, for example due to the person
 * going too far from the route, an automatic re-routing can be attempted. By
 * setting this key to YES, the automatic re-routing is not done and instead a 
 * routing did fail gets triggered.
 * 
 * Deprecated: Set routing timeout to zero instead.
 */
@property(assign, nonatomic) BOOL preventRerouting;

/**
 *
 * Default: -1 meaning try rerouting infitely
 */
@property(assign, nonatomic) NSTimeInterval routingTimeout;

/**
 * The device's accelerometer can be used to significantly improve the accuracy
 * of pedestrian positioning. If it is known that the user is not a pedestrian, then
 * the use of the Accelerometer will decrease accuracy. By default it is assumed that
 * the user is a pdestrian and hence this setting will be set to YES.
 */
@property(assign, nonatomic) BOOL useAccelerometer;


/**
 * The device's compass together with the accelerometer will significantly improve
 * the accuracy of pedestrian positioning. If you don't use the compass, you should
 * also turn off the Accelerometer and the DeviceMotion heading imporvement. If you
 * have to turn off the Compass we'd be interested in hearing why. By default this is
 * set to YES.
 */
@property(assign, nonatomic) BOOL useCompass;


/**
 * The device's sensors such as gyro can be used to improve accuracy of positioning 
 * and compass heading. By default this will be set to NO as the feature is not
 * required on iOS.
 */
@property(assign, nonatomic) BOOL useDeviceMotion;

/**
 * The absolute positioning accuracy is based on Bluetooth beacons. This is YES by
 * default.
 */
@property(assign, nonatomic) BOOL useBluetooth;

/**
 * iBeacons provide coarse range information that can be used for positioning instead
 * of or in addition to other beacons. They can also be used for movable beacon zones.
 *
 * If you need to use iBeacons instead of normal infrastructure/positioning beacons
 * please specify the iBeacon UUID of your iBeacons here. The NimbleDevice's iBeacon 
 * configuration application NimbleTweak uses the UUID of 5EC0AE91-3CF2-D989-E311-192F98DADD45.
 *
 * This is set to nil by default and can be left as nil when normal positioning is used.
 */
@property(retain, nonatomic) NSUUID* useIBeaconUUID;

@property(assign, nonatomic) BOOL useIBeaconRangingInBackground;


/**
 *  Obtain the IGGuideManager. In order for it to do anything useful
 *  the data file needs to be provided using setNDDUrl.
 *
 *  @return a shared instance of IGGuideManager
 */
+ (id)sharedManager;


/**
 * Set the data file used for positioning.
 * All the data used by the library is encapsulated in a data file. The data file can
 * be changed during runtime using this method.
 *
 * @param url is loaded using NSData dataContentsOfUrl:
 */
- (void)setNDDUrl:(NSURL*)url;

/**
 * Set the data file used for positioning.
 * All the data used by the library is encapsulated in a data file. The data file can
 * be changed during runtime using this method.
 *
 * @param path data is loaded using NSData dataContentsOfFile:
 */
- (void)setNDDPath:(NSString*)path;

/**
 * Set the data file used for positioning.
 * All the data used by the library is encapsulated in a data file. The data file can
 * be changed during runtime using this method.
 *
 * @param data ndd file contents
 */
- (void)setNDDData:(NSData*)data;


/**
 * Fetch information of a property in the NDD file. Examples of NDD properties are:
 *  - map: A complex object describing features of the map. GuideDemo has an example of its use.
 *  - targets: A dictionary where the keys are keywords for targets and the values are a list of target_id:s for that keyword.
 *
 * @param name The key of the property to fetch.
 *
 * @return A dictionary which is the value of the property.
 */
- (NSDictionary*) getNDDProperty:(NSString *)name;

/**
 *    After this method is called, location updates will be sent to the delegate.
 */
- (void) startUpdates;

/**
 *    After this method is called, location updates will cease to the delegate.
 */
- (void) stopUpdates;


- (void) setImmediateLocation:(CLLocation *)location;


/**
 *  Searches the map data for routing targets matching the given keyword.
 *
 *  @param keyword for matching the routing target
 *
 *  @return a list of target ids matching the keyword
 */
-(NSArray *) findRoutingTargets:(NSString*)keyword;

/**
 *  Allows retrieving the coordinate and altitude of a given routing target.
 *
 *  @param target  The id of the target
 *
 *  @return latitude, longitude and altitude of the target
 */
-(NSArray*) getRoutingTargetCoordinate:(NSNumber*)target;

/**
 *  Perform a routing calculation to the given target.
 *
 *  @param target The id of the target that the route should be calculated to.
 */
-(void) startRoutingToTarget:(NSNumber*)target;


/**
 * Perform the routing calculation to a target. The target is found by performing
 * a keyword search of the map data's route targets and selecting the first one.
 *
 *  @param keyword Search keyword to find the target point.
 */
-(void) startRoutingToName:(NSString*)keyword;


/**
 * Stop updating the routing information to the directionsDelegate.
 */
- (void) stopRouting;


/* Debugging only */
-(void)setDebugHandler:(void (^)(int, NSString*))block;
-(const uint16_t*)getDebuggingGridWidth:(uint16_t *)width height:(uint16_t *)height lat:(double *)lat lon:(double *)lon;
- (void) startStreamingTo:(NSString*)destination;
- (void) stopStreaming;


@end
