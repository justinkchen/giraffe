//
//  GiraffeSecondViewController.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/24/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "GiraffeMapViewController.h"
#import "GiraffeGraffitiViewController.h"
#import "LocationManager.h"
#import <MapKit/MapKit.h>
#import "Graffiti.h"
#import "SharedGraffitiData.h"

// Custom Map Pin Annotation with disclosure button
// Stores associated graffito
@interface GiraffeMapPinAnnotation : MKPointAnnotation

@property (nonatomic, retain) Graffiti *graffito;

@end

@implementation GiraffeMapPinAnnotation

@end

@interface GiraffeMapViewController () <MKMapViewDelegate>

@property (weak, nonatomic) IBOutlet MKMapView *mapView;
@property (nonatomic, retain) UIWebView *webView;

@property (nonatomic, assign) float latitude;
@property (nonatomic, assign) float longitude;

@end

@implementation GiraffeMapViewController

#pragma mark - View Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self.mapView setDelegate:self];
//    self.webView = [[UIWebView alloc] initWithFrame:self.view.bounds];
//    self.webView.delegate = self;
//    [self.view addSubview:self.webView];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

//NSString *const kHeatmapUrlFormat = @"http://ec2-54-243-69-6.compute-1.amazonaws.com/graffitimap.html?latitude=%f&longitude=%f";

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    [self reloadMapView];
}

- (IBAction)refreshButtonTapped:(UIBarButtonItem *)sender {
    [self reloadMapView];
}

- (void)reloadMapView
{
    float newLatitude = [LocationManager sharedInstance].latitude;
    float newLongitude = [LocationManager sharedInstance].longitude;
    
    if (newLatitude != self.latitude ||
        newLongitude != self.longitude) {
        self.mapView.showsUserLocation = YES;
        
        CLLocationCoordinate2D coordinates = (CLLocationCoordinate2D){newLatitude, newLongitude};
        MKCoordinateRegion viewRegion = MKCoordinateRegionMakeWithDistance(coordinates, 500.0, 500.0);
//        MKCoordinateRegion adjustedRegion = [self.mapView regionThatFits:viewRegion];
        [self.mapView setRegion:viewRegion];
        
        // Add annotations
        NSMutableArray *annotations = [NSMutableArray array];
        
        for (NSUInteger i = 0; i < [[SharedGraffitiData sharedData] count]; i++) {
            Graffiti *graffito = [[SharedGraffitiData sharedData] objectAtIndex:i];
            
            if (graffito.latitude && graffito.longitude) {
                GiraffeMapPinAnnotation *point = [[GiraffeMapPinAnnotation alloc] init];
                
                point.coordinate = (CLLocationCoordinate2D){graffito.latitude, graffito.longitude};
                point.title = graffito.user.username;
                point.subtitle = graffito.message;
                point.graffito = graffito;
                
                [annotations addObject:point];
            }
        }
        
        [self.mapView addAnnotations:annotations];
         
        self.latitude = newLatitude;
        self.longitude = newLongitude;
    }
}

#pragma mark - MKMapViewDelegate


- (MKAnnotationView *)mapView:(MKMapView *)mapView viewForAnnotation:(id <MKAnnotation>)annotation {
    if ([annotation isKindOfClass:[MKUserLocation class]]) return nil;
    
    MKAnnotationView *annotationView = [mapView dequeueReusableAnnotationViewWithIdentifier:@"MapPin"];
    if(!annotationView) {
        annotationView = [[MKPinAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:@"MapPin"];
        annotationView.rightCalloutAccessoryView = [UIButton buttonWithType:UIButtonTypeDetailDisclosure];
    }
    
    annotationView.enabled = YES;
    annotationView.canShowCallout = YES;
    
    return annotationView;
}

- (void)mapView:(MKMapView *)mapView annotationView:(MKAnnotationView *)view calloutAccessoryControlTapped:(UIControl *)control {
    // Go to edit view
    GiraffeGraffitiViewController *graffitiViewController = [GiraffeGraffitiViewController new];
    graffitiViewController.graffiti = ((GiraffeMapPinAnnotation *)view.annotation).graffito;
    [self.navigationController pushViewController:graffitiViewController animated:YES];
}

@end
