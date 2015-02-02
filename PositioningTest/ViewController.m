//
//  ViewController.m
//  PositioningTest
//
//  Created by Ruud Visser on 29-01-15.
//  Copyright (c) 2015 Nimble Devices. All rights reserved.
//

#import "ViewController.h"
#import <IndoorGuide/IGGuideManager.h>
#import <IndoorGuide/IGCoordinateConverter.h>
#import <CoreLocation/CoreLocation.h>

@interface ViewController () <IGDirectionsDelegate,IGPositioningDelegate>
{
    IGGuideManager *gm;
    IGCoordinateConverter *cc;
}

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [IGMapView class];
    
    // Do any additional setup after loading the view, typically from a nib.
    gm = [IGGuideManager sharedManager];
    CLLocationCoordinate2D coordinate1 = CLLocationCoordinate2DMake(60.187342, 24.814145);
    CLLocationCoordinate2D coordinate2 = CLLocationCoordinate2DMake(60.187336,24.816514);
    cc = [[IGCoordinateConverter alloc] initWithPoint1:CGPointMake(100, 100) point2:CGPointMake(0, 0) location1:coordinate1 location2:coordinate2];

    //[gm setPositioningDelegate:self];
    //[gm setDirectionsDelegate:self];
    NSString* nddFilePath = [[NSBundle mainBundle] pathForResource:@"eit" ofType:@"ndd"];
    
    [gm setNDDPath:nddFilePath];
    [self.mapView clearRoute];
    [self.mapView loadFromNDD];
    
    [gm startUpdates];
    
    NSDictionary *destinationsJson = [gm getNDDProperty:@"targets"];
    NSLog(@"Destinations: %@",destinationsJson);
    
    CLLocationCoordinate2D k1 = CLLocationCoordinate2DMake([[[gm getRoutingTargetCoordinate:@113] objectAtIndex:0] doubleValue], [[[gm getRoutingTargetCoordinate:@113] objectAtIndex:1] doubleValue]);
    CLLocationCoordinate2D k2 = CLLocationCoordinate2DMake([[[gm getRoutingTargetCoordinate:@123] objectAtIndex:0] doubleValue], [[[gm getRoutingTargetCoordinate:@123] objectAtIndex:1] doubleValue]);
    
    CGPoint point_k1 = [cc getPointForLocation:k1];
    CGPoint point_k2 = [cc getPointForLocation:k2];
    NSLog(@"Location kitchen 1: %f, %f",point_k1.x,point_k1.y);
    NSLog(@"Location kitchen 2: %f, %f",point_k2.x,point_k2.y);
}

- (void)guideManager:(IGGuideManager *)manager didUpdateToLocation:(CLLocation *)newLocation fromLocation:(CLLocation *)oldLocation
{
    [self.mapView setUserLocation:newLocation];
    NSLog(@"New location, lat: %f long:%f",newLocation.coordinate.latitude,newLocation.coordinate.longitude);
    
    CGPoint point = [cc getPointForLocation:newLocation.coordinate];
    NSLog(@"New X: %f, new Y: %f",point.x, point.y);
}

- (void)guideManager:(IGGuideManager *)manager didFailRoutingWithError:(NSError *)err{
    NSLog(@"Routing error!: %@",err);
}

- (void)guideManager:(IGGuideManager *)manager didCompleteRouting:(NSArray *)routepoints{
    NSLog(@"Completed routing");
}

- (void)guideManager:(IGGuideManager *)manager didUpdateRoutePosition:(CLLocationCoordinate2D)pos altitude:(CLLocationDistance)alt direction:(CLLocationDirection)direction distanceToChange:(CLLocationDistance)toChange distanceToGoal:(CLLocationDistance)toGoal{
    NSLog(@"New route position:");
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
