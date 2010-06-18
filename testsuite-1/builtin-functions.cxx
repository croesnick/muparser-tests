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

