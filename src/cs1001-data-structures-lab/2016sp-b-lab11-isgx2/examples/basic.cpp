#define BOOST_TEST_MODULE "main"
#include<boost/test/included/unit_test.hpp>

int add(int x, int y) {
  return x + y;
}

BOOST_AUTO_TEST_CASE(addition) {
  BOOST_CHECK(add(3,3) == 6);
}