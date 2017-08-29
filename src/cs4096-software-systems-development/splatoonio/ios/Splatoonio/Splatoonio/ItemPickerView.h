//
//  ItemPickerView.h
//  Splatoonio
//
//  Created by Adam Evans on 8/25/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Player.h"			// for max items constant
#import "Item.h"


#define ITEM_PICKER_INDEX_NONE		-1


@interface ItemPickerView : UIView
{
	int nslots;
	
	int				itemCounts[ITEM_TYPE_COUNT];			// how many of each item we are displaying
	UILabel*		multiplicityLabels[ITEM_TYPE_COUNT];	// label with "x2" or what ever to indicate the multiplicity of same-type items
	UIImageView*	itemIcons[ITEM_TYPE_COUNT];
	UIButton*		itemButtons[ITEM_TYPE_COUNT];
	
	UIView*	selectionBox;
}

@property (readonly) ItemType selectedType;

- (void)addItem:(ItemType)type;
- (void)removeItem:(ItemType)type;

@end
