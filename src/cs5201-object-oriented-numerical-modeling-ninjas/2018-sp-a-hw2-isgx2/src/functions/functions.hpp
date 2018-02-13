//
//  functions.hpp
//  functions
//
//  Created by Illya Starikov on 02/02/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef functions_hpp
#define functions_hpp

template<typename R, typename Theta>
std::vector<PolarPair<R, Theta>> parseFileContents(const std::string& fileContents) {
    auto fileSplitOnNewline = split(fileContents, '\n');
    auto polarPairs = std::vector<PolarPair<R, Theta>>();

    R radius;
    Theta azimuth;

    try {
        auto numberOfParameter = stringToInt(fileSplitOnNewline[0]);

        // Static cast to get ride of unsigned int/int comparison warning
        if (numberOfParameter < static_cast<int>(fileSplitOnNewline.size()) - 1) {
            displayErrorAndQuit("Not enough polar pairs in input file. Terminating.");
        }

        for (int i = 1; i < numberOfParameter; i++) {
            auto inputSplit = split(fileSplitOnNewline[i], ' ');

            // This just removes any newlines, usually occurs when there are
            // multiple spaces between input entries (i.e., 42     82).
            std::remove_if(inputSplit.begin(), inputSplit.end(), [](std::string string) { return string == ""; });

            if (inputSplit.size() < 2) throw std::logic_error("Freaking too little input");

            inputSplit[0] = (inputSplit[0][0] == '.') ? '0' + inputSplit[0] : inputSplit[0];
            inputSplit[1] = (inputSplit[1][0] == '.') ? '0' + inputSplit[1] : inputSplit[1];

            if (std::is_same<R, int>::value) {
                radius = stringToInt(inputSplit[0]);
            } else {
                radius = stringToDouble(inputSplit[0]);
            }

            if (std::is_same<Theta, int>::value) {
                azimuth = stringToInt(inputSplit[1]);
            } else {
                azimuth = stringToDouble(inputSplit[1]);
            }

            polarPairs.push_back(PolarPair<R, Theta>(radius, azimuth));
        }
    } catch(const std::logic_error error) {
        displayErrorAndQuit("Data is not in proper format. Terminating.");
    }

    return polarPairs;
}

#endif /* functions_hpp */
