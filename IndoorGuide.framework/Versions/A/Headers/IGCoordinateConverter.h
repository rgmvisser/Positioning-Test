/**
 * Used to facilitate conversions between "GPS" coordinates and for example a raster
 * image of the floor plan. The converter is initialized by specifying two cordinates
 * in GPS and their corresponding coordinates in an XY coordinate system. After that the
 * methods can be used to convert between the two coordinate systems. All rotations, scalings
 * and translations between the coordinate systems are done by the library.
 *
 * This library does a simplistic mercator style projection around the center point of the
 * two GPS coordinates. In practice this means that the accuracy is good in small areas of
 * less than a kilometer.
 */
#import <CoreGraphics/CGGeometry.h>
#import <CoreLocation/CoreLocation.h>

@interface IGCoordinateConverter : NSObject

/**
 *  Initializes the converter object to perform conversion between GPS compatible coordinates
 *  and coordinates in a carthesian XY coordinate system. 
 *
 *  @param point1    The first point in the XY coordinate system
 *  @param point2    The first point in the XY coordinate system
 *  @param location1 The GPS coordinate that corresponds to point1
 *  @param location2 The GPS coordinate that corresponds to point2
 *
 *  @return The conversion object
 */
-(id) initWithPoint1:(const CGPoint)point1 point2:(const CGPoint)point2 location1:(const CLLocationCoordinate2D)location1 location2:(const CLLocationCoordinate2D)location2;

- (void)dealloc;

/**
 *  Projects a GPS coordinates to carthesian XY coordinates
 *
 *  @param location The latitude and longitude pair to convert
 *
 *  @return A newly created point in the XY coordinate system
 */
- (CGPoint) getPointForLocation:(const CLLocationCoordinate2D)location;

/**
 *  Creates a GPS coordinate object that corresponds to the given point.
 *
 *  @param point The point used as input for the conversion
 *
 *  @return The GPS coordinates that correspond to the XY point.
 */
- (CLLocationCoordinate2D) getLocationForPoint:(const CGPoint)point;

/**
 * @return in radians
 */
- (CGFloat) getRotationForDirection:(CLLocationDirection) direction;

+(void) testIt;

@end
