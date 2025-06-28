#include<boost/test/unit_test.hpp>
#include "funcs.h"
BOOST_AUTO_TEST_SUITE(funcs)

BOOST_AUTO_TEST_CASE(addition) {
  BOOST_CHECK(add(2,2) == 4);
//  BOOST_CHECK(add(3,3) == 8);

  BOOST_CHECK_EQUAL(add(2,2), 4);

  BOOST_CHECK_GE(add(2,2), 0);

  BOOST_CHECK_MESSAGE(add(2,2) == 4, "Adding 2 and 2 should give you 4...");
}

BOOST_AUTO_TEST_CASE(throwing) {
  BOOST_CHECK_THROW(throw_exception(), runtime_error);
}

bool is_my_exception(const runtime_error& ex)
{
  return strcmp(ex.what(),"EXCEPTION!!!!!") == 0;
}

BOOST_AUTO_TEST_CASE(exception) {
  BOOST_CHECK_EXCEPTION(throw_exception(), runtime_error, is_my_exception);
}

BOOST_AUTO_TEST_SUITE_END()
