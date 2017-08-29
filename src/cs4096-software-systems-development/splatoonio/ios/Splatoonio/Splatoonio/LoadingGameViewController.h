//
//  LoadingGameViewController.h
//  Splatoonio
//
//  Created by Adam Evans on 8/24/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Game.h"


@interface LoadingGameViewController : UIViewController
{
	Game* game;
	
	IBOutlet UILabel* statusLabel;
}


@end
