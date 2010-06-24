#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <cstdlib>
#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>

#include <muParser/muParser.h>

class FunctionTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE (FunctionTest);
    CPPUNIT_TEST (testFunctionSign);
	CPPUNIT_TEST (testFunctionRoundInt);
	CPPUNIT_TEST (testFunctionAreaHyperbolicusSinCosTan);
	CPPUNIT_TEST (testFunctionIf);
	CPPUNIT_TEST (testFunctionAverage);
    CPPUNIT_TEST_SUITE_END ();

	void testFunctionSign () {
		mu::Parser parser;

		parser.DefineConst ("z", (double)  0.0);
		parser.DefineConst ("p", (double)  std::numeric_limits<double>::epsilon());
		parser.DefineConst ("n", (double) -std::numeric_limits<double>::epsilon());

		parser.SetExpr ("1*sign(z) + 2*sign(p) + 4*sign(n)");

		int rval = 0;
		try
		{
			rval = parser.Eval ();
			CPPUNIT_ASSERT_DOUBLES_EQUAL (-2, rval, 0.0);
		}
		catch (mu::Parser::exception_type &e)
		{
			std::cout << e.GetMsg() << std::endl;
		}
	}

	void testFunctionRoundInt () {
		mu::Parser parser;

		int base = (rand () % 1023);
		double rval = 0;		
		double epsilon = 2.0 * std::numeric_limits<double>::epsilon();

		parser.DefineConst ("base", (double) base);
		parser.DefineConst ("eps", (double) epsilon);

		parser.SetExpr ("rint(base+(0.5-eps)) - base+rint(0.5-eps)");
		rval = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, rval, 0.0);

		parser.SetExpr ("rint(base+0.5-eps)+2*rint(base+0.5)+4*rint(base+0.5+eps)");
		rval = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL ((base + (2+4)*(base+1)), rval, 0.0);
	}

	void testFunctionAreaHyperbolicusSinCosTan () {
		mu::Parser parser;
        double rval;
		
		double arsinhMin = -(std::fabs( std::numeric_limits<double>::min() / 2.0 ) - 1);
		double arsinhMax =  (sqrt( std::numeric_limits<double>::max() ) - 1) / 2.0;

		parser.DefineConst ("arsinhMin", arsinhMin);
		parser.DefineConst ("arsinhMax", arsinhMax);

        parser.SetExpr ("asinh(arsinhMax)");
        rval = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (log(arsinhMax + sqrt(pow (arsinhMax, 2) + 1)), rval, 1e-07);

		parser.SetExpr ("asinh(arsinhMin)");
        rval = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (log(arsinhMin + sqrt(pow (arsinhMin, 2) + 1)), rval, 1e-07);

		parser.SetExpr ("asinh(0)");
        rval = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, rval, 0);

		//-----

		double arcosMax = sqrt( std::numeric_limits<double>::max() ) / 2.0;
		parser.DefineConst ("arcoshMax", arcosMax);

		parser.SetExpr ("acosh(1)");
        rval = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, rval, 0);

		parser.SetExpr ("acosh(arcoshMax)");
        rval = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (log(arcosMax + sqrt(pow (arcosMax, 2) + 1)), rval, 1e-07);

		//-----

		double eps = std::numeric_limits<double>::epsilon();
		double artanhMin = -1.0 + eps;
		double artanhMax =  1.0 - eps;

		parser.DefineConst ("artanhMin", artanhMin);
		parser.DefineConst ("artanhMax", artanhMax);

		parser.SetExpr ("atanh(artanhMin)");
        rval = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.5 * log((1 + artanhMin) / (1 - artanhMin)), rval, 1e-07);

		parser.SetExpr ("atanh(0)");
        rval = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, rval, 0);

		parser.SetExpr ("atanh(artanhMax)");
        rval = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.5 * log((1 + artanhMax) / (1 - artanhMax)), rval, 1e-07);
	}

	void testFunctionIf () {
		mu::Parser parser;
		double dvar, rval;

		parser.DefineConst( "pi", (double) M_PI);

		parser.DefineVar ("x", &dvar);
		// Important: Leave no space between 'if' and the leading parenthesis
		parser.SetExpr ("if((x == pi), 2.0, if((x < pi), 1.0, 3.0))");

		dvar = M_PI;
		rval = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (2.0, rval, 0.0);

		dvar = M_PI - 2.0 * std::numeric_limits<double>::epsilon ();
		rval = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, rval, 0.0);

		dvar = M_PI + 2.0 * std::numeric_limits<double>::epsilon ();
		rval = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (3.0, rval, 0.0);
	}

	void testFunctionAverage () {
		mu::Parser parser;
		double dvar, rval;

		dvar = std::numeric_limits<double>::epsilon ();
		parser.DefineVar ("x", &dvar);

		parser.SetExpr ("avg(x)");
		rval = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (dvar, rval, 0.0);

		parser.SetExpr ("avg(x,2*x)");
		rval = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (1.5*dvar, rval, 0.5*std::numeric_limits<double>::epsilon());
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION (FunctionTest);

int main (int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry ();
    runner.addTest (registry.makeTest ());
    bool wasSuccessful = runner.run ("", false);
    return (wasSuccessful != 0) ? 0 : 1;
}

