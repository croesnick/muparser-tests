#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <limits>
#include <math.h>
#include <muParser/muParser.h>

// For fixed number of arguments
double valFun1 (double a) {
	if (a <= 0) throw int(1);
	return log(a);
};
double valFun2 (double a, double b) {
	return valFun1 (a+b);
};
double valFun3 (double a, double b, double c) {
	if ((b-c) < 0) throw int(3);
	return valFun2 (a, sqrt(b-c));
};
double valFun4 (double a, double b, double c, double d) {
	return valFun3 (a, b*c, d);
} 
double valFun5 (double a, double b, double c, double d, double e) {
	return (log(e + sqrt(e * e - 1)) == valFun4 (a, b, c, d));
} 

// for a variable number of arguments
//   first arg:   pointer to the arguments
//   second arg:  number of arguments
double valFunArb (const double * pArgs, int noArgs) {
	if (noArgs != 4) throw int(0);
	double inter = pArgs[1]*pArgs[2]-pArgs[3];
	if (inter < 0) throw int(1);
	inter = pArgs[0]+sqrt(inter);
	if (inter <= 0) throw int(2);
	return log(inter);
};

// for functions taking a single string plus up to two numeric values
double strFun0 (const char * str);
double strFun1 (const char * str, double a);
double strFun2 (const char * str, double a, double b);

class CustomFunctionsTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE (CustomFunctionsTest);
    CPPUNIT_TEST (testDefineValFctConst);
	CPPUNIT_TEST (testDefineValFctArb);
	CPPUNIT_TEST (testDefineStrFctConst);
	CPPUNIT_TEST (testOverwriteExistingFct);
    CPPUNIT_TEST_SUITE_END ();

	// Define value functions with constant number of arguments
	void testDefineValFctConst () {
		// Simulating acosh ("log(v + sqrt(v * v - 1))")
		mu::Parser parser;
		double rval;
		
		parser.DefineFun ("valfun1", valFun1);
		parser.DefineFun ("valfun2", valFun2);
		parser.DefineFun ("valfun3", valFun3);
		parser.DefineFun ("valfun4", valFun4);
		parser.DefineFun ("valfun5", valFun5);

		try {
			parser.DefineConst ("eps", std::numeric_limits<double>::epsilon ());
			parser.SetExpr ("valfun1(eps)-ln(eps)");
			rval = parser.Eval ();
			CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, rval, 0.0);

			parser.DefineConst ("eps", std::numeric_limits<double>::epsilon ());
			parser.SetExpr ("valfun2(eps,2*eps)-ln(eps+eps+eps)");
			rval = parser.Eval ();
			CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, rval, 0.0);
	
			parser.SetExpr ("acosh(3.14)-valfun4(3.14,3.14,3.14,1)");
			rval = parser.Eval ();
			CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, rval, 0.0);

			parser.SetExpr ("valfun5(3.14, 3.14, 3.14, 1, 3.14)");
			rval = parser.Eval ();
			CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, rval, 0.0);
		}
		catch (const int &e) {
			std::cerr << "Function 'valFun" << e << "' caused an error." << std::endl;
			CPPUNIT_ASSERT (false);
		}
		catch (mu::Parser::exception_type &e) {
			std::cerr << e.GetMsg() << std::endl;
			CPPUNIT_ASSERT (false);
		}
	}

	// Define value function with arbitrarily many arguments
	void testDefineValFctArb () {
		mu::Parser parser;
		double rval;

		parser.DefineFun ("valfunArb", valFunArb);
		parser.DefineConst ("eps", std::numeric_limits<double>::epsilon ());

		// Try to use three instead of the required four arguments
		try {
			parser.SetExpr ("valfunArb(1, 2, 3)");
			parser.Eval ();
		}
		catch (const int &e) {
			CPPUNIT_ASSERT_EQUAL (0, e);
		}

		// Use exactly four arguments, but produce exception '1' by passing
		// parameters that are outside the function's range
		try {
			parser.SetExpr ("valfunArb(eps, eps, eps, 1)-acosh(eps)");
			rval = parser.Eval ();
			CPPUNIT_ASSERT (false);
		}
		catch (const int &e) {
			CPPUNIT_ASSERT_EQUAL (1, e);
		}

		// Use exactly four arguments, but produce exception '2' by passing
		// parameters causing an intermediate value outside ln's range
		try {
			parser.SetExpr ("valfunArb(-0.316227767, 2, 3, 5.9)");
			rval = parser.Eval ();
			CPPUNIT_ASSERT (false);
		}
		catch (const int &e) {
			CPPUNIT_ASSERT_EQUAL (2, e);
		}

		// Use exactly four arguments -- correctly :)
		try {
			parser.SetExpr ("valfunArb(3.14, 3.14, 3.14, 1)-acosh(3.14)");
			rval = parser.Eval ();
			CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, rval, 0.0);
		}
		catch (const int &e) {
			std::cerr << "Cought exception '" << e << "'." << std::endl;
			CPPUNIT_ASSERT (false);
		}

		// Try to use five instead of the required four arguments
		try {
			parser.SetExpr ("valfunArb(1, 2, 3, 4, 5)");
			parser.Eval ();
		}
		catch (const int &e) {
			CPPUNIT_ASSERT_EQUAL (0, e);
		}
	}

	// Define string functions, taking up to two numerical parameters
	void testDefineStrFctConst () {
		// TODO
	}

	// Try to overwrite existing functions
	void testOverwriteExistingFct () {
		mu::Parser parser;

		parser.DefineFun ("valfun1", valFun1);
		try {
			parser.SetExpr ("valfun1(3.14)");
			parser.Eval ();
		}
		catch (...) {
			CPPUNIT_ASSERT (false);
		}

		parser.DefineFun ("valfun1", valFun2);
		try {
			parser.SetExpr ("valfun1(3.14, 2.72)");
			parser.Eval ();
		}
		catch (...) {
			CPPUNIT_ASSERT (false);
		}
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

