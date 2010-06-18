#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <muParser/muParser.h>

#include <limits>

class BuiltinOperatorsTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE (BuiltinOperatorsTest);
    CPPUNIT_TEST (testUnaryMinus);
    CPPUNIT_TEST (testAdd);
    CPPUNIT_TEST (testSubtract);
    CPPUNIT_TEST (testMultiply);
    CPPUNIT_TEST (testDivide);
    CPPUNIT_TEST (testPower);
    CPPUNIT_TEST_SUITE_END ();

    void testUnaryMinus () {
        mu::Parser parser;
        double res;

        parser.SetExpr ("-1");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-1.0, res, 0.0);

        parser.SetExpr ("-0");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.0);

        parser.SetExpr ("-0.5");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-0.5, res, 0.0);

        parser.SetExpr ("-(2)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-2.0, res, 0.0);

        parser.SetExpr ("-(-2)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (2.0, res, 0.0);
    }

    void testAdd () {
        mu::Parser parser;
        double res;

        parser.SetExpr ("2 + 2");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (4.0, res, 0.0);

        parser.SetExpr ("2.5 + 2.5");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (5.0, res, 0.0);

        parser.SetExpr ("2.5 + (-2.5)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.0);

        parser.SetExpr ("2.5 + -2.5");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.0);

        parser.SetExpr ("2 + 3 + 4");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (9.0, res, 0.0);

        parser.SetExpr ("-2 + 3 + 4");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (5.0, res, 0.0);
    }

    void testSubtract () {
        mu::Parser parser;
        double res;

        parser.SetExpr ("2 - 2");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.0);

        parser.SetExpr ("2.5 - 2.5");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.0);

        parser.SetExpr ("2.5 - (-2.5)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (5.0, res, 0.0);

        parser.SetExpr ("2.5 - -2.5");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (5.0, res, 0.0);

        parser.SetExpr ("2 - 3 + 4");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (3.0, res, 0.0);

        parser.SetExpr ("-2 + 3 - 4");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-3.0, res, 0.0);
    }

    void testMultiply () {
        mu::Parser parser;
        double res;

        parser.SetExpr ("2 * 2");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (4.0, res, 0.0);

        parser.SetExpr ("2.5 * 2");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (5.0, res, 0.0);

        parser.SetExpr ("2.5 * (-2)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-5.0, res, 0.0);

        parser.SetExpr ("-2.5 * -2");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (5.0, res, 0.0);

        parser.SetExpr ("2 * 3 * 4");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (24.0, res, 0.0);

        parser.SetExpr ("-2 * 3 * 4");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-24.0, res, 0.0);
    }

    void testDivide () {
        mu::Parser parser;
        double res;

        parser.SetExpr ("2 / 2");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res, 0.0);

        parser.SetExpr ("2.5 / 2");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1.25, res, 0.0);

        parser.SetExpr ("2.5 / (-2)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-1.25, res, 0.0);

        parser.SetExpr ("2 / 3 / 4");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.1666666666, res, 0.0001);

        parser.SetExpr ("2 / 0");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (std::numeric_limits<double>::infinity (), res, 0.0);
    }

    void testPower () {
        mu::Parser parser;
        double res;

        parser.SetExpr ("2^2");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (4.0, res, 0.0);

        parser.SetExpr ("4^0.5");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (2, res, 0.0);
        
        parser.SetExpr ("4^0.5^3");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (8, res, 0.0);

        parser.SetExpr ("4^(-2)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0625, res, 0.0);

        parser.SetExpr ("4^(2)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (16, res, 0.0);

        parser.SetExpr ("(-3)^2");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (9.0, res, 0.0);

        parser.SetExpr ("(-3)^3");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-27.0, res, 0.0);

        parser.SetExpr ("27^(1/3)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (3, res, 0.0);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION (BuiltinOperatorsTest);

int main (int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry ();
    runner.addTest (registry.makeTest ());
    bool wasSuccessful = runner.run ("", false);
    return (wasSuccessful != 0) ? 0 : 1;
}

