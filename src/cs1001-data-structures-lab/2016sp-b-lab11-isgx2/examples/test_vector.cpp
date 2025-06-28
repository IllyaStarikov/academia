#include<boost/test/unit_test.hpp>

#include<stdexcept>
#include"vector.h"
using namespace std;

BOOST_AUTO_TEST_SUITE(vector)

struct fixture {
  Vector<int> empty;
  Vector<int> v1;
  Vector<int> v2;

  fixture() {
    /*
    for(unsigned int i = 0; i < 10; i++) {
      v1.push_back(i);
    }

    for(unsigned int i = 0; i < 20; i++) {
      v2.push_back(i);
    }
    */
  }
};

BOOST_FIXTURE_TEST_CASE(constructor, fixture) {
  BOOST_CHECK_EQUAL(empty.size(), 4);
  BOOST_CHECK_EQUAL(empty.length(), 0);
}
/*
BOOST_FIXTURE_TEST_CASE(copy_constructor, fixture) {
  Vector<int> copy(v2);
  BOOST_CHECK_EQUAL(v2.size(), copy.size());
  BOOST_CHECK_EQUAL(v2.length(), copy.length());

  for(unsigned int i = 0; i < 20; i++) {
    BOOST_CHECK_EQUAL(v2[i], copy[i]);
  }
}

BOOST_FIXTURE_TEST_CASE(expanding, fixture) {
  BOOST_CHECK_EQUAL(v1.size(), 16);
  BOOST_CHECK_EQUAL(v2.size(), 32);
}

BOOST_FIXTURE_TEST_CASE(push_back, fixture) {
  for(unsigned int i = 0; i < 10; i++) {
    empty.push_back(i);
    BOOST_CHECK_EQUAL(empty.length(), i+1);
  }
}

BOOST_FIXTURE_TEST_CASE(accessor, fixture) {
  for(unsigned int i = 0; i < 20; i++) {
    BOOST_CHECK_EQUAL(v2[i], i);
  }
}

BOOST_FIXTURE_TEST_CASE(out_of_bounds, fixture) {
  BOOST_CHECK_THROW(empty[0], invalid_argument);
}
*/
BOOST_AUTO_TEST_SUITE_END()
