// Copyright (c) 2012-2015 The Bitcoin Core developers 
// Copyright (c) 2017 IoP Ventures LLC

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "compat/sanity.h"
#include "key.h"
#include "test/test_IoP.h"

#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(sanity_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(basic_sanity)
{
  BOOST_CHECK_MESSAGE(glibc_sanity_test() == true, "libc sanity test");
  BOOST_CHECK_MESSAGE(glibcxx_sanity_test() == true, "stdlib sanity test");
  BOOST_CHECK_MESSAGE(ECC_InitSanityCheck() == true, "openssl ECC test");
}

BOOST_AUTO_TEST_SUITE_END()
