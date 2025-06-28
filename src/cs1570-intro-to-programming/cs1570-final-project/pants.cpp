//
//  pants.cpp
//  homework-10
//
//  Created by Illya Starikov on 4/13/17.
//  Copyright © 2017 Illya Starikov. All rights reserved.
//

#include "pants.hpp"

Pants::Pants() {
    location = Point(-1 , -1);
}

void Pants::placeMe(Town& town) {
    location = town.findRandomEmptySpot();

    town.setElement(location.y, location.x, PANTS_CHAR);
}

void Pants::chase(Tailor& tailor, Town& town) {
    Point newLocation = location, tailorLocation = tailor.getLocation();

    if (tailorLocation.x > location.x && town.getElement(newLocation.y, newLocation.x + 1) == EMPTY_SPACE) {
        newLocation.x++;
    } else if (tailorLocation.x < location.x && town.getElement(newLocation.y, newLocation.x - 1) == EMPTY_SPACE) {
        newLocation.x--;
    } else if (tailorLocation.y > location.y && town.getElement(newLocation.y + 1, newLocation.x) == EMPTY_SPACE) {
        newLocation.y++;
    } else if (tailorLocation.y < location.y && town.getElement(newLocation.y - 1, newLocation.x) == EMPTY_SPACE) {
        newLocation.y--;
    }

    if (town.getElement(newLocation.y, newLocation.x) == EMPTY_SPACE) {
        town.setElement(location.y, location.x, ' ');
        town.setElement(newLocation.y, newLocation.x, PANTS_CHAR);

        location = newLocation;
    }
}

void Pants::kill(Tailor& tailor) const {
    tailor.kill();
    cout << "The phantom pants killed " << tailor.getName() << "!\n";
}
