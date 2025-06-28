#define BOOST_TEST_MODULE "main"
#include<boost/test/included/unit_test.hpp>
#include<stdexcept>
using namespace std;

BOOST_AUTO_TEST_CASE(throw_exception) {
  BOOST_CHECK_THROW(throw runtime_error("whoops"),
      runtime_error);
}

bool check_error(const runtime_error& ex) {
  return strcmp(ex.what(), "whoops") == 0;
}

BOOST_AUTO_TEST_CASE(check_exception) {
  BOOST_CHECK_EXCEPTION(throw runtime_error("whoops"),
      runtime_error, check_error);
}