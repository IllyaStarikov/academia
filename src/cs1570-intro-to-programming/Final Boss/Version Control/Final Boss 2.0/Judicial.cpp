// Programmers: Illya Starikov and Alex Androff               Date: 04/17/15
// File: Judicial.cpp                                         Class: CS1570A
// Purpose: Write definitions of the Judicial Class

#include "Judicial.h"
#include "Functions.h"

Judicial::Judicial(std::string judgeName, int judgeConvictionRating) {
    name = judgeName;
    convictionRate = judgeConvictionRating;
    announceTheJudge();
}

bool Judicial::judgement(const std::string nameOfPrisoner) {
    bool isConvicted = randomArbitrary(0, 100) <= convictionRate;
    
    outcomeAnnouncement(isConvicted, nameOfPrisoner);
    
    return isConvicted;
}

void Judicial::outcomeAnnouncement(bool convictedToDeath, std::string nameOfPrisoner) {
    const int NUMBER_OF_RESPONSES = 3;
    int response = randomArbitrary(0, NUMBER_OF_RESPONSES - 1);
    
    if (convictedToDeath == false) {
        switch (response) {
            case 0:
                std::cout << "A good lawyer knows the law." << std::endl
                << "A great one knows the judge." << std::endl << std::endl
                << "And they did. Phew." << std:: endl;
                break;
                
            case 1:
                std::cout << "Off the hook, even though there was a good change he/she did it" << std::endl
                << "Haters gonna hate"<< std::endl;
                break;
                
            case 2:
                std::cout << "99 Problems. But his/her conviction isn't one. Got away squeaky clean" << std::endl
                << "At least it isn't JavaScript. Then it would be 99.0004 problems." << std::endl;
                break;
                
            default:
                std::cout << "He's free." << std::endl;
                break;
        }
    }
    else if (convictedToDeath == true) {
        switch (response) {
            // Batman references. Couldn't resist.
            case 0:
                std::cout << nameOfPrisoner<< " has been sentenced to death." << std::endl;
                break;
                
            case 1:
                std::cout << nameOfPrisoner << " has been sentenced to exile." << std::endl;
                break;
                
            case 2:
                std::cout << nameOfPrisoner << " has been sentenced to death by exile." << std::endl;
                break;
                
            default:
                std::cout << nameOfPrisoner << " is dead." << std::endl;
                break;
        }
    }
}

void Judicial::announceTheJudge() {
    std::cout << "All rise, this court is now in session. The honorable Judge " << name << " presiding." << std::endl;
    return;
}
