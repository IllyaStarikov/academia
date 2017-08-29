//
//  MenuViewController.m
//  Splatoonio
//
//  Created by Adam Evans on 8/24/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

#import "MenuViewController.h"


@implementation MenuViewController


// =================================================================================
#pragma mark -						UIViewController
// =================================================================================

- (void)viewDidLoad
{
	[super viewDidLoad];
	
	if (![CLLocationManager locationServicesEnabled])
	{
		UIAlertController* alert = [UIAlertController alertControllerWithTitle:@"Uh-oh"
																	   message:@"Turn on Location Services in Settings to play"
																preferredStyle:UIAlertControllerStyleAlert];
		[alert addAction:[UIAlertAction actionWithTitle:@"Okay" style:UIAlertActionStyleDefault handler:nil]];
		
		[self presentViewController:alert animated:YES completion:nil];
	}
	else
	{
		[[GPSManager defaultManager] turnOn];
	}
}

// =================================================================================

- (BOOL)prefersStatusBarHidden
{
	return TRUE;
}

// =================================================================================

@end
