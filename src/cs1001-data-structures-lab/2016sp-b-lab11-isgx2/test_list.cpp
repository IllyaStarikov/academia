#include <boost/test/unit_test.hpp>
#include <stdexcept>

#include "list.h"

BOOST_AUTO_TEST_SUITE(list)
struct fixture {
    List<int> empty;
    List<int> huge;
    List<int> small;

    fixture() {
        for (int i = 0; i < 10; i++) {
            small.append(i);
        }

        for (int i = 0; i < 100; i++) {
            huge.append(i);
        }
    }
};

BOOST_FIXTURE_TEST_CASE(constructor, fixture) {
    BOOST_CHECK_EQUAL(empty.length(), 0);
    BOOST_CHECK_EQUAL(small.length(), 10);
    BOOST_CHECK_EQUAL(huge.length(), 100);
}

BOOST_FIXTURE_TEST_CASE(prepend, fixture) {
    for (int i = 0; i < 100; huge.prepend(++i)) {
        BOOST_CHECK_EQUAL(i, huge.head());
    }
}

BOOST_FIXTURE_TEST_CASE(empty, fixture) {
    // Length will not work here :(
    for (unsigned i = 0; i < 10; i++) {
        small.pop();
    }

    BOOST_CHECK_EQUAL(small.empty(), true);
}


// BOOST_FIXTURE_TEST_CASE(append, fixture) {


//     for (int i = 0; i < 100; i++) {

//         BOOST_CHECK_EQUAL(, huge.tail());
//     }
// }

BOOST_AUTO_TEST_SUITE_END()