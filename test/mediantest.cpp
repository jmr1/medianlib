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
    const auto ret10 = medianlib::QuickMedian<vec10_type>::find(&vec10[0], vec10.size());
    CPPUNIT_ASSERT_EQUAL(ret10, static_cast<decltype(ret10)>(49.5));

    const auto ret11 = medianlib::QuickMedian<vec11_type>::find(&vec11[0], vec11.size());
    CPPUNIT_ASSERT_EQUAL(ret11, static_cast<decltype(ret11)>(1050));
}

void MedianTest::quickSelectMedianTest()
{
    const auto ret10 = medianlib::QuickSelectMedian<vec10_type>::find(&vec10[0], vec10.size());
    CPPUNIT_ASSERT_EQUAL(ret10, static_cast<decltype(ret10)>(49.5));

    const auto ret11 = medianlib::QuickSelectMedian<vec11_type>::find(&vec11[0], vec11.size());
    CPPUNIT_ASSERT_EQUAL(ret11, static_cast<decltype(ret11)>(1050));
}

void MedianTest::streamHeapMedianTest()
{
    std::vector<int> tmp11;
    medianlib::StreamHeapMedian<vec11_type> sh_m11(vec11.size()/2+1);
    for(const auto &x : vec11)
    {
        tmp11.push_back(x);
        const auto median = sh_m11.find(x);

        auto first = tmp11.begin();
        auto last = tmp11.end();
        auto middle = first + (last - first) / 2;
        auto middle2 = first + (last - first) / 2 - 1;
        if(tmp11.size() % 2)
        {
            std::nth_element(first, middle, last);
            CPPUNIT_ASSERT_EQUAL(static_cast<decltype(median)>(*middle), median);
        }
        else
        {
            std::nth_element(first, middle, last);
            std::nth_element(first, middle2, last);
            const auto averaged_median = medianlib::average(*middle, *middle2);
            CPPUNIT_ASSERT_EQUAL(averaged_median, median);
        }
    }
}
