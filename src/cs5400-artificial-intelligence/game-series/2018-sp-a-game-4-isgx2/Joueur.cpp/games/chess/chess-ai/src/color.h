//
//  color.h
//  src
//
//  Created by Illya Starikov on 03/02/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef color_h
#define color_h

namespace ChessEngine {
    /** @enum Color
     *
     *  @brief A enum to represent the two apposing colors, white and black.
     *
     **/

    enum Color {
        white, black
    };
}

namespace std {
    template <>
    struct hash<ChessEngine::Color> {
        size_t operator()(const ChessEngine::Color& color) const {
            return static_cast<int>(color);
        }
    };
}
    
#endif /* color_h */

