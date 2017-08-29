//
//  LoadingGameViewController.m
//  Splatoonio
//
//  Created by Adam Evans on 8/24/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

#import "LoadingGameViewController.h"
#import "GameViewController.h"
#import "ServerAPI.h"


@implementation LoadingGameViewController


// =================================================================================
#pragma mark -						Loading States
// =================================================================================

- (void)loadGame
{
	game = [ServerAPI currentGame];
	
	[self loadingComplete];
}

// =================================================================================

- (void)loadingComplete
{
	[self performSegueWithIdentifier:@"LoadingGameToGame" sender:self];
}

// =================================================================================
#pragma mark -						UIViewController
// =================================================================================

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
	// only one segue to the game vc
	GameViewController* gamevc = (GameViewController*)[segue destinationViewController];
	gamevc.game = game;
}

// =================================================================================

- (void)viewDidLoad
{
    [super viewDidLoad];
	
	statusLabel.text = @"Loading Game";
	
	[self loadGame];
}

// =================================================================================

- (BOOL)prefersStatusBarHidden
{
	return YES;
}

// =================================================================================


@end
