//
//  Judicial.cpp
//  Final Boss
//
//  Created by Illya Starikov on 4/25/15.
//  Copyright (c) 2015 Illya Starikov. All rights reserved.
//

#include "Judicial.h"
#include "Functions.h"

Judicial::Judicial(std::string judgeName, int judgeConvictionRating) {
    name = judgeName;
    convictionRate = judgeConvictionRating;
}

void Judicial::judgement()const {
    bool isConvicted = randomArbitrary(0, 100) <= convictionRate;
    
    outcomeAnnouncement(name, isConvicted);
    
    return;
}

void Judicial::outcomeAnnouncement(std::string nameOfPerson, bool convictedToDeath)const {
    const int NUMBER_OF_RESPONSES = 3;
    int response = randomArbitrary(0, NUMBER_OF_RESPONSES - 1);
    if (convictedToDeath == false) {
        switch (response) {
            case 0:
                std::cout << "A good lawyer knows the law." << std::endl
                << "A great one knows the judge." << std::endl << std::endl
                << "And his/her did. Phew." << std:: endl;
                break;
                
            case 1:
                std::cout << "Off the hook, even though there was a good change he/she did it" << std::endl
                << "Haters gonna hate"<< std::endl;
                break;
                
            case 2:
                std::cout << "99 Problems. But his/her conviction isn't one. Got away squeeky clean" << std::endl
                << "At least it isn't JavaScript. Then it would be 99.0004 problems." << std::endl;
                break;
                
            default:
                std::cout << "He's free." << std::endl;
                break;
        }
        if (convictedToDeath == true) {
            switch (response) {
                // Batman references. Couldn't resist.s
                case 0:
                    std::cout << "Sentenced to death." << std::endl;
                    break;
                    
                case 1:
                    std::cout << "Sentenced to exile." << std::endl;
                    break;
                    
                case 2:
                    std::cout << "Sentenced to death by exile." << std::endl;
                    break;
                    
                default:
                    std::cout << "He's dead." << std::endl;
                    break;
            }
        }
        
    }
}