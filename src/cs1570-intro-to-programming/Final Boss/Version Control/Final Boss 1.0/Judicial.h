//
//  Judicial.h
//  Final Boss
//
//  Created by Illya Starikov on 4/25/15.
//  Copyright (c) 2015 Illya Starikov. All rights reserved.
//

#ifndef __Final_Boss__Judicial__
#define __Final_Boss__Judicial__


#include <iostream>

#include "Constants.h"

class Judicial {
public:
    Judicial(std::string judgeName, int judgeConvictionRating = DEFAULT_CONVICTION_RATE);
    void judgement()const;
    void outcomeAnnouncement(std::string nameOfPerson, bool convictedToDeath)const;
    
private:
    std::string name;
    int convictionRate;
};
#endif /* defined(__Final_Boss__Judicial__) */
