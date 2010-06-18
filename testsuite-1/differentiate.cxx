#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <muParser/muParser.h>

#define _USE_MATH_DEFINES
#include <cmath>

class DifferentiateTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE (DifferentiateTest);
    CPPUNIT_TEST (testDiffX2);
    CPPUNIT_TEST (testDiffExp);
    CPPUNIT_TEST_SUITE_END ();

    void testDiffX2 () {
        mu::Parser parser;
        double res, x;

        parser.DefineVar("x", &x);

        parser.SetExpr ("x^2");

        res = parser.Diff (&x, 0, 0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);

        res = parser.Diff (&x, 2, 0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL (4.0, res, 0.000001);
    }

    void testDiffExp () {
        mu::Parser parser;
        double res, x;

        parser.DefineVar("x", &x);

        parser.SetExpr ("exp(x)");

        res = parser.Diff (&x, 0, 0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res, 0.000001);

        res = parser.Diff (&x, 1, 0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL (M_E, res, 0.000001);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION (DifferentiateTest);

int main (int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry ();
    runner.addTest (registry.makeTest ());
    bool wasSuccessful = runner.run ("", false);
    return (wasSuccessful != 0) ? 0 : 1;
}

