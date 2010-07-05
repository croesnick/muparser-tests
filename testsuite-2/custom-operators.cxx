#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <limits>
#include <math.h>
#include <muParser/muParser.h>

double infixOp1 (double v) {
	return (v-floor(v));
};
double infixOp2 (double v) {
	return floor (v);
};
double postfixOp1 (double v) {
	return v*1000.0;
};
double postfixOp2 (double v) {
	int result = static_cast<int>(v/360.0);
	float mod = v - static_cast<float>(result)*360.0;
	return (mod/360.0)*2.0*M_PI;
};
double postfixOp3 (double v) {
	int result = static_cast<int>(v/(2.0*M_PI));
	float mod = v - static_cast<float>(result)*(2.0*M_PI);
	return (mod/(2.0*M_PI))*360.0;
};
double binaryOp1 (double v, double w) {
	return (v==w);
};
double binaryOp2 (double v, double w) {
	return v > w ? v : w;
};
double binaryOp3 (double v, double w) {
	return v < w ? v : w;
};
double binaryOp4 (double v, double w) {
	return (v+w)/2.0;
};
double binaryOp5 (double v, double w) {
	return (v-w);
};

class CustomOperatorsTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE (CustomOperatorsTest);
    CPPUNIT_TEST (testDefineInfixOp);
	CPPUNIT_TEST (testDefinePostfixOp);
	CPPUNIT_TEST (testDefineBinaryOp);
	CPPUNIT_TEST (testInfixPostfixInteraction);
    CPPUNIT_TEST_SUITE_END ();

	void testDefineInfixOp () {
		mu::Parser parser;
		double rval;

		parser.DefineInfixOprtChars("/+-*^?<>=#!$%&~'_");
		try {
			parser.DefineInfixOprt ("|", infixOp1);
			CPPUNIT_ASSERT (false);
		}
		catch (...) { }

		parser.DefineInfixOprtChars("/+-*^?<>=#!$%&|~'_");
		try {
			
			parser.DefineInfixOprt ("|", infixOp1);
			parser.DefineInfixOprt ("#", infixOp2);

			parser.DefineConst ("apple", M_PI);
			parser.SetExpr ("apple-(#apple+|apple)");
		
			rval = parser.Eval ();
			CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, rval, 0.0);
		}
		catch (mu::Parser::exception_type &e) {
			std::cerr << e.GetMsg() << std::endl;
			CPPUNIT_ASSERT (false);
		}
	}

	void testDefinePostfixOp () {
		mu::Parser parser;
		double rval;

		parser.DefinePostfixOprt ("rad", postfixOp2);
		parser.DefinePostfixOprt ("grad", postfixOp3);
		parser.DefineOprt ("AND", binaryOp1);

		parser.DefineConst ("apple", M_PI);
		parser.SetExpr ("(360rad == 0) AND (90rad == apple/2.0)");
		rval = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, rval, 0.0);

		parser.SetExpr ("(sqrt(2)grad)rad - sqrt(2)");
		rval = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, rval, 1e-07);
	}

	void testDefineBinaryOp () {
		mu::Parser parser;
		double rval;

		parser.EnableBuiltInOprt (false);
		parser.DefineOprt ("-", binaryOp5, 0); // simply minus
		parser.DefineOprt ("^", binaryOp2, 3); // max
		parser.DefineOprt ("_", binaryOp3, 3); // min
		parser.DefineOprt ("~", binaryOp4, 6); // average

		parser.SetExpr ("(1_2^3)-((1_2)^3)");
		rval = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, rval, 0.0);

		parser.SetExpr ("(1_2~3)-((1_2)~3)");
		rval = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (-1.0, rval, 0.0);
	}

	void testInfixPostfixInteraction () {
		mu::Parser parser;
		double rval;

		parser.DefineInfixOprt ("|", infixOp1);
		parser.DefineInfixOprt ("#", infixOp2);
		parser.DefinePostfixOprt ("K", postfixOp1);
		parser.DefineOprt ("AND", binaryOp1);

		parser.DefineConst ("PiOverTen", M_PI/10.0);

		parser.SetExpr ("(#(PiOverTen)K==314)AND(#(PiOverTen)K==#((PiOverTen)K))");
		rval = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, rval, 0.0);
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

