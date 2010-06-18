#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <muParser/muParser.h>

#include <limits>
#define _USE_MATH_DEFINES
#include <cmath>

class BuiltinFunctionsTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE (BuiltinFunctionsTest);
    CPPUNIT_TEST (testSinCosTan);
    CPPUNIT_TEST (testArcusSinCosTan);
    CPPUNIT_TEST (testHyperbolicSinCosTan);
    CPPUNIT_TEST (testArcusHyperbolicSinCosTan);
    CPPUNIT_TEST (testExp);
    CPPUNIT_TEST (testSqrt);
    CPPUNIT_TEST (testSignAbs);
    CPPUNIT_TEST (testRint);
    CPPUNIT_TEST (testIf);
    CPPUNIT_TEST (testMinMax);
    CPPUNIT_TEST (testSum);
    CPPUNIT_TEST (testAvg);
    CPPUNIT_TEST_SUITE_END ();

    void testSinCosTan () {
        mu::Parser parser;
        double res;

        parser.SetExpr ("sin(0)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);

        parser.SetExpr ("cos(0)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res, 0.000001);

        parser.SetExpr ("tan(0)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);

        parser.SetExpr ("sin(_pi / 2)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res, 0.000001);

        parser.SetExpr ("cos(_pi / 2)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);

        parser.SetExpr ("tan(_pi / 2)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (tan (M_PI / 2), res, 0.000001);

        parser.SetExpr ("sin(_pi)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);

        parser.SetExpr ("cos(_pi)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-1.0, res, 0.000001);

        parser.SetExpr ("tan(_pi)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);

        parser.SetExpr ("sin(_pi + _pi / 2)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-1.0, res, 0.000001);

        parser.SetExpr ("cos(_pi + _pi / 2)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);

        parser.SetExpr ("tan(_pi + _pi / 2)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (tan (M_PI + M_PI / 2), res, 0.000001);

        parser.SetExpr ("sin(4214.3213)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (sin (4214.3213), res, 0.000001);

        parser.SetExpr ("cos(4214.3213)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (cos (4214.3213), res, 0.000001);

        parser.SetExpr ("tan(4214.3213)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (tan (4214.3213), res, 0.000001);
    }

    void testArcusSinCosTan () {
        mu::Parser parser;
        double res;

        parser.SetExpr ("asin(0)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0, res, 0.000001);

        parser.SetExpr ("acos(0)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (M_PI / 2, res, 0.000001);

        parser.SetExpr ("atan(0)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0, res, 0.000001);

        parser.SetExpr ("asin(1)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (M_PI / 2, res, 0.000001);

        parser.SetExpr ("acos(1)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0, res, 0.000001);

        parser.SetExpr ("atan(1)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (M_PI / 4, res, 0.000001);

        parser.SetExpr ("asin(-1)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-M_PI / 2, res, 0.000001);

        parser.SetExpr ("acos(-1)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (M_PI, res, 0.000001);

        parser.SetExpr ("atan(-1)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-M_PI / 4, res, 0.000001);

        parser.SetExpr ("asin(0.43212313)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (asin (0.43212313), res, 0.000001);

        parser.SetExpr ("acos(0.43212313)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (acos (0.43212313), res, 0.000001);

        parser.SetExpr ("atan(4321.2313)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (atan (4321.2313), res, 0.000001);
    }

    void testHyperbolicSinCosTan () {
        mu::Parser parser;
        double res;

        parser.SetExpr ("sinh(0)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);

        parser.SetExpr ("cosh(0)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res, 0.000001);

        parser.SetExpr ("tanh(0)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);

        parser.SetExpr ("sinh(-20)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (sinh (-20), res, 0.000001);

        parser.SetExpr ("cosh(-20)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (cosh (-20), res, 0.000001);

        parser.SetExpr ("tanh(-20)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (tanh (-20), res, 0.000001);

        parser.SetExpr ("sinh(20)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (sinh (20), res, 0.000001);

        parser.SetExpr ("cosh(20)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (cosh (20), res, 0.000001);

        parser.SetExpr ("tanh(20)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (tanh (20), res, 0.000001);
    }

    void testArcusHyperbolicSinCosTan () {
        mu::Parser parser;
        double res;

        parser.SetExpr ("asinh(0)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);

        parser.SetExpr ("acosh(1)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);

        parser.SetExpr ("atanh(0)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);

        parser.SetExpr ("asinh(-20)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (asinh (-20), res, 0.000001);

        parser.SetExpr ("atanh(-0.9)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (atanh (-0.9), res, 0.000001);

        parser.SetExpr ("asinh(20)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (asinh (20), res, 0.000001);

        parser.SetExpr ("acosh(20)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (acosh (20), res, 0.000001);

        parser.SetExpr ("atanh(0.9)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (atanh (0.9), res, 0.000001);
    }

    void testExp () {
        mu::Parser parser;
        double res;

        parser.SetExpr ("exp(0)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res, 0.000001);

        parser.SetExpr ("ln(1)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);

        parser.SetExpr ("log2(1)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);

        parser.SetExpr ("log10(1)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);

        parser.SetExpr ("exp(1)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (M_E, res, 0.000001);

        parser.SetExpr ("ln(_e)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res, 0.000001);

        parser.SetExpr ("log2(2)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res, 0.000001);

        parser.SetExpr ("log10(10)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res, 0.000001);

        parser.SetExpr ("exp(-1)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1/M_E, res, 0.000001);

        parser.SetExpr ("ln(1/_e)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-1.0, res, 0.000001);

        parser.SetExpr ("log2(0.5)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-1.0, res, 0.000001);

        parser.SetExpr ("log10(0.1)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-1.0, res, 0.000001);

        parser.SetExpr ("log2(1024)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (10.0, res, 0.000001);

        parser.SetExpr ("log10(10000000000)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (10.0, res, 0.000001);
    }

    void testSqrt () {
        mu::Parser parser;
        double res;

        parser.SetExpr ("sqrt(0)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);

        parser.SetExpr ("sqrt(2)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (M_SQRT2, res, 0.000001);

        parser.SetExpr ("sqrt(0.5)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (M_SQRT1_2, res, 0.000001);

        parser.SetExpr ("sqrt(4)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (2, res, 0.000001);
    }

    void testSignAbs () {
        mu::Parser parser;
        double res;

        parser.SetExpr ("sign(0)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);

        parser.SetExpr ("sign(1)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res, 0.000001);

        parser.SetExpr ("sign(-1)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-1.0, res, 0.000001);

        parser.SetExpr ("sign(100.2)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res, 0.000001);

        parser.SetExpr ("sign(-100.2)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-1.0, res, 0.000001);

        parser.SetExpr ("abs(0)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);
        
        parser.SetExpr ("abs(1)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res, 0.000001);

        parser.SetExpr ("abs(-1)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res, 0.000001);

        parser.SetExpr ("abs(10.123)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (10.123, res, 0.000001);

        parser.SetExpr ("abs(-10.123)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (10.123, res, 0.000001);
    }

    void testRint () {
        mu::Parser parser;
        double res;

        parser.SetExpr ("rint(0)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0, res, 0.000001);

        parser.SetExpr ("rint(0.5)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res, 0.000001);

        parser.SetExpr ("rint(1)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res, 0.000001);

        parser.SetExpr ("rint(0.96)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res, 0.000001);

        parser.SetExpr ("rint(0.123)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);

        parser.SetExpr ("rint(-0.5)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);

        parser.SetExpr ("rint(-1)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-1.0, res, 0.000001);

        parser.SetExpr ("rint(-0.96)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-1.0, res, 0.000001);

        parser.SetExpr ("rint(-0.123)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, res, 0.000001);
    }

    void testIf () {
        mu::Parser parser;
        double res;

        parser.SetExpr ("if(1 < 2, 10, 5)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (10, res, 0.000001);

        parser.SetExpr ("if(1 > 2, 10, 5)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (5, res, 0.000001);
    }

    void testMinMax () {
        mu::Parser parser;
        double res;

        parser.SetExpr ("min(-1, 2, 10)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-1, res, 0.000001);

        parser.SetExpr ("min(-1)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-1, res, 0.000001);

        parser.SetExpr ("min(6, 3, 5, 1, 7, 3)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1, res, 0.000001);

        parser.SetExpr ("max(-1, 2, 10)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (10, res, 0.000001);

        parser.SetExpr ("max(-1)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-1, res, 0.000001);

        parser.SetExpr ("max(6, 3, 5, 1, 7, 3)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (7, res, 0.000001);
    }

    void testSum () {
        mu::Parser parser;
        double res;

        parser.SetExpr ("sum(-1, 2, 10)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (11, res, 0.000001);

        parser.SetExpr ("sum(10)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (10, res, 0.000001);

        parser.SetExpr ("sum(10, 31, 3, 5, 2)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (51, res, 0.000001);
    }

    void testAvg () {
        mu::Parser parser;
        double res;

        parser.SetExpr ("avg(1, 2, 3)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (2, res, 0.000001);

        parser.SetExpr ("avg(1, 2)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1.5, res, 0.000001);

        parser.SetExpr ("avg(1)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (1, res, 0.000001);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION (BuiltinFunctionsTest);

int main (int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry ();
    runner.addTest (registry.makeTest ());
    bool wasSuccessful = runner.run ("", false);
    return (wasSuccessful != 0) ? 0 : 1;
}

