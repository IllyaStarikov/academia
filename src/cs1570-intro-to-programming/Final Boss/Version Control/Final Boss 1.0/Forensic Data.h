//
//  Forensic Data.h
//  Final Boss
//
//  Created by Illya Starikov on 4/20/15.
//  Copyright (c) 2015 Illya Starikov. All rights reserved.
//

#ifndef Final_Boss__Forensic_Data
#define Final_Boss__Forensic_Data

#include "Constants.h"

struct fingerPrint {
    char fingerPrintData[LENGTH_OF_FINGERPRINT_ARRAY][HEIGHT_OF_FINGERPRINT_ARRAY];
    int loops, arches, whirls;
};

struct forensicData {
    int hair;
    char DNA[LENGTH_OF_DNA + 1]; // +1 For Null Terminating Character
    fingerPrint forensicPrint;
};

#endif /* defined(Final_Boss__Forensic_Data) */
