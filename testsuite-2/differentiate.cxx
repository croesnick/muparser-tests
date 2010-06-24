#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <limits>
#include <math.h>
#include <muParser/muParser.h>

class DifferentiateTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE (DifferentiateTest);
    CPPUNIT_TEST (testSimpleDiff);
	CPPUNIT_TEST (testSimpleDiffEpsilon);
    CPPUNIT_TEST_SUITE_END ();

	void testSimpleDiff () {
		mu::Parser parser;
		double x;
		double rval;
		double eps = (double) 0.00074;
		double inter;

		parser.DefineVar ("x", &x);
		parser.SetExpr ("x^2*cos(1/x)");
		rval = parser.Diff (&x, eps, 0);

		inter = 2 * eps * cos (1.0/eps) + sin (1.0/eps);
		CPPUNIT_ASSERT_DOUBLES_EQUAL (inter, rval, 1e-06);

		parser.SetExpr ("-0.5*x^3+exp(1)*x");
		rval = parser.Diff (&x, 0, 0);
		CPPUNIT_ASSERT_DOUBLES_EQUAL (M_E, rval, 1e-10);

		rval = parser.Diff (&x, M_PI, 1e-7 * M_PI);
		inter = -1.5 * pow (M_PI, 2) + exp (1);
		CPPUNIT_ASSERT_DOUBLES_EQUAL (inter, rval, 1e-7 * M_PI);
	}

	void testSimpleDiffEpsilon () {
		mu::Parser parser;
		double x;
		double rval;
		double eps = (double) 0.00074;
		double inter = 2 * eps * cos (1.0/eps) + sin (1.0/eps);

		parser.DefineVar ("x", &x);
		parser.SetExpr ("x^2*cos(1/x)");
	
		rval = parser.Diff (&x, eps, 1e-10);
		CPPUNIT_ASSERT_DOUBLES_EQUAL (inter, rval, 1e-07);
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

