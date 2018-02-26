//
//  interpolation-exception.h
//  exceptions
//
//  Illya Starikov, Section 1A, 18083141
//  cs5201 – Object Oriented Numerical Modeling
//

#ifndef interpolation_exception_h
#define interpolation_exception_h

#include <string>

/** @class ImproperDataset
 *
 *  @brief An error object to represent an improper dataset being fed into
 *         an interpolation.
 *
 **/

class ImproperDataset {
private:
    std::string errorMessage;

public:
    ImproperDataset(const std::string errorMessage);

    ImproperDataset() = delete;
    ImproperDataset(const ImproperDataset& other) = delete;
    ImproperDataset(const ImproperDataset&& other) = delete;
    ImproperDataset& operator=(const ImproperDataset& other) = delete;
    ImproperDataset& operator=(const ImproperDataset&& other) = delete;

    const std::string what() const;
};

#endif /* interpolation-exception_h */

