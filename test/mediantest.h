#ifndef MEDIANTEST_H
#define MEDIANTEST_H

#include <vector>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class MedianTest: public CPPUNIT_NS::TestFixture
{
public:
    MedianTest(){}

    CPPUNIT_TEST_SUITE (MedianTest);
    CPPUNIT_TEST (quickMedianTest);
    CPPUNIT_TEST_SUITE_END ();

public:
    void setUp();
    void tearDown();

protected:
    void quickMedianTest();

private:
    void gen_data(std::vector<int> &vec, int start);

private:
    std::vector<int> vec10;
    std::vector<int> vec11;
};

#endif // MEDIANTEST_H
