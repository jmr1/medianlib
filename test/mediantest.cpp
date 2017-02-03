#include "mediantest.h"

#include <numeric>
#include <algorithm>

#include <medianlib/median.h>

CPPUNIT_TEST_SUITE_REGISTRATION(MedianTest);

void MedianTest::gen_data(std::vector<int> &vec, int start)
{
    std::iota(std::begin(vec), std::end(vec), start);
    std::shuffle(std::begin(vec), std::end(vec), std::mt19937{std::random_device{}()});
}

void MedianTest::setUp()
{
    vec10.resize(100);
    gen_data(vec10, 0);

    vec11.resize(101);
    gen_data(vec11, 1000);
}

void MedianTest::tearDown()
{
}

void MedianTest::quickMedianTest()
{
    using vec10_type = std::remove_reference<decltype(vec10[0])>::type;
    const auto ret10 = medianlib::QuickMedian<vec10_type>::find(&vec10[0], vec10.size());
    CPPUNIT_ASSERT_EQUAL(ret10, static_cast<decltype(ret10)>(49.5));

    using vec11_type = std::remove_reference<decltype(vec11[0])>::type;
    const auto ret11 = medianlib::QuickMedian<vec11_type>::find(&vec11[0], vec11.size());
    CPPUNIT_ASSERT_EQUAL(ret11, static_cast<decltype(ret11)>(1050));
}

void MedianTest::quickSelectMedianTest()
{
    using vec10_type = std::remove_reference<decltype(vec10[0])>::type;
    const auto ret10 = medianlib::QuickSelectMedian<vec10_type>::find(&vec10[0], vec10.size());
    CPPUNIT_ASSERT_EQUAL(ret10, static_cast<decltype(ret10)>(49.5));

    using vec11_type = std::remove_reference<decltype(vec11[0])>::type;
    const auto ret11 = medianlib::QuickSelectMedian<vec11_type>::find(&vec11[0], vec11.size());
    CPPUNIT_ASSERT_EQUAL(ret11, static_cast<decltype(ret11)>(1050));
}
