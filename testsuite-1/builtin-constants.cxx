#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <muParser/muParser.h>

#define _USE_MATH_DEFINES
#include <cmath>

class BuiltinConstantsTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE (BuiltinConstantsTest);
    CPPUNIT_TEST (testEuler);
    CPPUNIT_TEST (testPi);
    CPPUNIT_TEST_SUITE_END ();

    void testEuler () {
        mu::Parser parser;
        double res;

        parser.SetExpr ("_e");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (M_E, res, 0.0);
    }

    void testPi () {
        mu::Parser parser;
        double res;

        parser.SetExpr ("_pi");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (M_PI, res, 0.0);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION (BuiltinConstantsTest);

int main (int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry ();
    runner.addTest (registry.makeTest ());
    bool wasSuccessful = runner.run ("", false);
    return (wasSuccessful != 0) ? 0 : 1;
}

