//
//  ItemPickerView.m
//  Splatoonio
//
//  Created by Adam Evans on 8/25/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

#import "ItemPickerView.h"


// UI constants
#define ICON_SIZE		40
#define MULTIPLICITY_LABEL_OFFSET_X		(ICON_SIZE / 2)			// offset of the label center from the icon center
#define MULTIPLICITY_LABEL_OFFSET_Y		(ICON_SIZE / 2)			// offset of the label center from the icon center
#define MULTIPLICITY_LABEL_WIDTH		30
#define MULTIPLICITY_LABEL_HEIGHT		30
#define MULTIPLICITY_LABEL_FONT_SIZE	15


@implementation ItemPickerView


@synthesize selectedType;


// =================================================================================
#pragma mark -						Touch Functions
// =================================================================================

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
	CGPoint loc = [[touches anyObject] locationInView:self];
	CGFloat slotWidth = self.frame.size.width / nslots;
	int slot = (int)loc.x / slotWidth;
	
	// show the selectionBox
	selectedType = -1;
	int slotCount = 0;
	
	while (slotCount <= slot)		// no need for bounds check b/c internal consistency
	{
		selectedType++;
		
		if (itemCounts[selectedType] > 0)
		{
			slotCount++;
		}
	}
	
	[self refreshList];
}

// =================================================================================
#pragma mark -						Normal Functions
// =================================================================================

- (void)addItems:(NSArray<Item*>*)newItems
{
	for (int i = 0; i < [newItems count]; i++)
	{
		itemCounts[[newItems objectAtIndex:i].type]++;
	}
	
	[self refreshList];
}

// =================================================================================

- (void)addItem:(ItemType)type
{
	itemCounts[type]++;
	[self refreshList];
}

// =================================================================================

- (void)removeItem:(ItemType)type
{
	if (itemCounts[type] > 0)
	{
		itemCounts[type]--;
		[self refreshList];
	}
}

// =================================================================================
#pragma mark -						Private Functions
// =================================================================================
// Updates the UI to display the correct items in the correct number of slots with the selection box
// The selection box can 
- (void)refreshList
{
	// figure out how many different item "slots" we need to show
	nslots = 0;
	
	for (int i = 0; i < ITEM_TYPE_COUNT; i++)
	{
		if (itemCounts[i] != 0)
		{
			nslots++;
		}
	}
	
	CGFloat SIDE_PADDING = 0;
	CGFloat slotWidth = (self.frame.size.width - (2 * SIDE_PADDING)) / nslots;
	
	// ------------------------------------
	// setup selection
	if (itemCounts[selectedType] == 0)
	{
		selectedType = ITEM_TYPE_NONE;
	}
	
	if (selectedType == ITEM_TYPE_NONE)
	{
		selectionBox.hidden = YES;
	}
	else
	{
		int selectedSlot = 0;
		
		// figure out which slot has the items of the selected type
		for (int i = 0; i < selectedType; i++)
		{
			if (itemCounts[i] > 0)
			{
				selectedSlot++;
			}
		}
		
		// configure the selection box
		selectionBox.hidden = NO;
		selectionBox.frame = CGRectMake(slotWidth * selectedSlot, 0, slotWidth, self.frame.size.height);
	}
	
	// ------------------------------------
	// put all the UI components where they need to go
	CGFloat x = SIDE_PADDING;
	CGFloat iconCentery = self.frame.size.height / 2;
	
	for (int i = 0; i < ITEM_TYPE_COUNT; i++)
	{
		// handle different counts of each type
		if (itemCounts[i] == 0)
		{
			itemIcons[i].hidden = YES;
			multiplicityLabels[i].hidden = YES;
			continue;
		}
		else if (itemCounts[i] == 1)
		{
			multiplicityLabels[i].hidden = YES;
		}
		else
		{
			multiplicityLabels[i].hidden = NO;
			multiplicityLabels[i].text = [NSString stringWithFormat:@"x%d", itemCounts[i]];
			[multiplicityLabels[i] sizeToFit];
			multiplicityLabels[i].center = CGPointMake(itemIcons[i].center.x + MULTIPLICITY_LABEL_OFFSET_X,
													   itemIcons[i].center.y + MULTIPLICITY_LABEL_OFFSET_Y);
		}
		
		// configure this item slot
		itemIcons[i].hidden = NO;
		itemIcons[i].center = CGPointMake(x + (slotWidth / 2), iconCentery);
		
		// prepare for the next item
		x += slotWidth;
	}
}

// =================================================================================
#pragma mark -						Initializers
// =================================================================================

- (id)initWithCoder:(NSCoder *)aDecoder
{
	self = [super initWithCoder:aDecoder];
	
	if (self != nil)
	{
		[self initialize];
	}
	
	return self;
}

// =================================================================================

- (id)initWithFrame:(CGRect)frame
{
	self = [super initWithFrame:frame];
	
	if (self != nil)
	{
		[self initialize];
	}
	
	return self;
}

// =================================================================================

- (void)initialize
{
	selectedType = ITEM_TYPE_NONE;
	
	memset(&itemCounts[0], 0, sizeof(itemCounts));
	
	selectionBox = [[UIView alloc] init];
	selectionBox.backgroundColor = UIColor.blackColor;
	selectionBox.alpha = 0.2;
	[self addSubview:selectionBox];
	
	// add all the views for the item slots
	for (int i = 0; i < ITEM_TYPE_COUNT; i++)
	{
		itemCounts[i] = 0;
		
		itemIcons[i] = [[UIImageView alloc] initWithImage:[Item imageForItemOfType:i]];
		itemIcons[i].frame = CGRectMake(0, 0, ICON_SIZE, ICON_SIZE);
		[self addSubview:itemIcons[i]];
		
		multiplicityLabels[i] = [[UILabel alloc] init];
		multiplicityLabels[i].hidden = YES;
		multiplicityLabels[i].frame = CGRectMake(0, 0, MULTIPLICITY_LABEL_WIDTH, MULTIPLICITY_LABEL_HEIGHT);
		multiplicityLabels[i].font = [UIFont systemFontOfSize:MULTIPLICITY_LABEL_FONT_SIZE];
		[self addSubview:multiplicityLabels[i]];
	}
}

// =================================================================================

@end









