#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <muParser/muParser.h>

#define _USE_MATH_DEFINES
#include <cmath>

class CustomOperatorsTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE (CustomOperatorsTest);
    CPPUNIT_TEST (testUnaryInfix);
    CPPUNIT_TEST (testUnaryPostfix);
    CPPUNIT_TEST (testBinary);
    CPPUNIT_TEST_SUITE_END ();

    static double _unaryInfixFunc (double arg) {
        return 1.0 / arg;
    }

    static double _unaryPostfixFunc (double arg) {
        double ret = 1.0;

        for (int i = 1.0; i <= arg; i++)
          ret *= i;

        return ret;
    }

    static double _binaryFunc (double arg1, double arg2) {
        return arg1 + arg2;
    }

    static double _binary2Func (double arg1, double arg2) {
        return arg1 * arg2;
    }

    void testUnaryInfix () {
        mu::Parser parser;
        double res;

        parser.DefineInfixOprt ("^", &_unaryInfixFunc);

        parser.SetExpr ("^2");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.5, res, 0.000001);
    }

    void testUnaryPostfix () {
        mu::Parser parser;
        double res;

        parser.DefinePostfixOprt ("!", &_unaryPostfixFunc);

        parser.SetExpr ("2!");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (2, res, 0.000001);

        parser.SetExpr ("6!");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (720, res, 0.000001);
    }

    void testBinary () {
        mu::Parser parser;
        double res;

        parser.DefineOprt ("add", &_binaryFunc, 0);
        parser.DefineOprt ("mul", &_binary2Func, 1);

        parser.SetExpr ("2 add 3");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (5, res, 0.000001);

        parser.SetExpr ("2 mul 3");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (6, res, 0.000001);

        parser.SetExpr ("2 mul 3 add 4");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (10, res, 0.000001);

        parser.SetExpr ("2 add 3 mul 4");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (14, res, 0.000001);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION (CustomOperatorsTest);

int main (int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry ();
    runner.addTest (registry.makeTest ());
    bool wasSuccessful = runner.run ("", false);
    return (wasSuccessful != 0) ? 0 : 1;
}

