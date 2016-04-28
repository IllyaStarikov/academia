//
//  CloseCent.hpp
//  Source Code
//
//  Created by Timothy Ott on 4/27/16.
//  Copyright © 2016 Timothy Ott. All rights reserved.
//

#ifndef CloseCent_hpp
#define CloseCent_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>

#include <vector>
#include <map>
#include <tuple>

#include "Constants.h"

void CloseCent(const VectArray & input);

void CloseGraph(const vector<double> & Close);

void AllCloseCent(VectArray & UWUDshort, VectArray & UWDshort, VectArray & WUDshort, VectArray & WDshort);

#endif /* CloseCent_hpp */