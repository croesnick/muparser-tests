#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <muParser/muParser.h>

#define _USE_MATH_DEFINES
#include <cmath>

class CustomFunctionsTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE (CustomFunctionsTest);
    CPPUNIT_TEST (testUnary);
    CPPUNIT_TEST (testBinary);
    CPPUNIT_TEST (testTernary);
    CPPUNIT_TEST (testFourary);
    CPPUNIT_TEST (testFiveary);
    CPPUNIT_TEST_SUITE_END ();

    static double _unaryFunc (double arg) {
        return arg*arg;
    }

    static double _binaryFunc (double arg1, double arg2) {
        return arg1*arg2;
    }

    static double _ternaryFunc (double arg1, double arg2, double arg3) {
        return (arg1*arg2) / arg3;
    }

    static double _fouraryFunc (double arg1, double arg2, double arg3, double arg4) {
        return (arg1 * arg3) / (arg2 * arg4);
    }

    static double _fivearyFunc (double arg1, double arg2, double arg3, double arg4, double arg5) {
        return arg1 + arg2 + arg3 + arg4 + arg5;
    }

    void testUnary () {
        mu::Parser parser;
        double res;

        parser.DefineFun ("square", &_unaryFunc);

        parser.SetExpr ("square(2)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (4, res, 0.000001);
    }

    void testBinary () {
        mu::Parser parser;
        double res;

        parser.DefineFun ("mul", &_binaryFunc);

        parser.SetExpr ("mul(2, 2)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (4, res, 0.000001);
    }

    void testTernary () {
        mu::Parser parser;
        double res;

        parser.DefineFun ("scale", &_ternaryFunc);

        parser.SetExpr ("scale(1, 6, 5)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1.2, res, 0.000001);
    }

    void testFourary () {
        mu::Parser parser;
        double res;

        parser.DefineFun ("mult", &_fouraryFunc);

        parser.SetExpr ("mult(2, 3, 3, 2)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1, res, 0.000001);
    }

    void testFiveary () {
        mu::Parser parser;
        double res;

        parser.DefineFun ("add", &_fivearyFunc);

        parser.SetExpr ("add(1, 2, 3, 4, 5)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (15, res, 0.000001);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION (CustomFunctionsTest);

int main (int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry ();
    runner.addTest (registry.makeTest ());
    bool wasSuccessful = runner.run ("", false);
    return (wasSuccessful != 0) ? 0 : 1;
}

