#define BOOST_TEST_MODULE "main"
#include<boost/test/included/unit_test.hpp>

int add(int x, int y) {
  return x + y;
}

BOOST_AUTO_TEST_CASE(addition) {
  BOOST_CHECK(add(3,3) == 6);
  BOOST_CHECK_EQUAL(add(3,3), 42);
}

BOOST_AUTO_TEST_CASE(universe_is_sane) {
  BOOST_CHECK_GT(5,4);
  BOOST_CHECK_LE(3,65);
}
