#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <limits>
#include <math.h>
#include <muParser/muParser.h>

double * addVariableManually (const char * pName, void * pUserData) {
	static double dValBuf[10];
	static int iVal = 0;

	dValBuf[iVal++] = 0;
	if (iVal >= 9)
		throw mu::Parser::exception_type("Variable buffer overflow.");

	return &dValBuf[iVal];
}
/*
double * addVariableFactory (const char * pName, void * pUserData) {
	mu::MyFactory *pFactory = (mu::MyFactory*) pUserData;
	pFactory->CreateNewVariable (pName);
}
*/
class CustomVariablesTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE (CustomVariablesTest);
    CPPUNIT_TEST (testExplicitVariableDefinition);
	CPPUNIT_TEST (testImplicitVariableDefinition);
	CPPUNIT_TEST (testQueryParserVariables);
	CPPUNIT_TEST (testQueryExpressionVariables);
	CPPUNIT_TEST (testRemoveVariables);
    CPPUNIT_TEST_SUITE_END ();

	void testExplicitVariableDefinition () {
		mu::Parser parser;
		double * pfval = NULL;
		double fval = M_PI;

		// Checking the case "a_pVar==0"
		try {
			parser.DefineVar ("a", pfval);
			CPPUNIT_ASSERT (false);
		}
		catch (...) { // What kind of error should be caught?
		}

		// Check for invalid signs in variable name
		parser.DefineNameChars("abcdefghijklmnopqrstuvwxyz");
		try {
			parser.DefineVar ("inValid", &fval);
			CPPUNIT_ASSERT (false);
		}
		catch (...) { // What kind of error should be caught?
		}

		// Now, try to set a variable correctly
		parser.DefineNameChars("abcdefghijklmnopqrstuvwxyz");
		try {
			parser.DefineVar ("x", &fval);
		}
		catch (...) {
			CPPUNIT_ASSERT (false);
		}

		// Try to define a variable twice
		try {
			parser.DefineVar ("x", &fval);
			CPPUNIT_ASSERT (false);
		}
		catch (...) { // What kind of error should be caught?h
		}
	}

	void testImplicitVariableDefinition () {
		mu::Parser parser;

		// Manually adding variables
		parser.SetVarFactory (addVariableManually, &parser);
		parser.SetExpr ("longvariable=1234567890");
		try {
			parser.Eval ();
			CPPUNIT_ASSERT (true);
		}
		catch (...) {
			CPPUNIT_ASSERT (false);
		}
	}

	void testQueryParserVariables () {
		mu::Parser parser;
		double fval1 = M_PI, fval2 = M_E;

		// Get the map with the variables
		mu::varmap_type varmap = parser.GetVar ();
		CPPUNIT_ASSERT_EQUAL ((int) varmap.size (), 0);
		CPPUNIT_ASSERT (varmap.begin () == varmap.end ());

		// Adding a variable and check if it is there
		try {
			parser.DefineVar ("simpleVariable", &fval1);
			varmap = parser.GetVar ();
			CPPUNIT_ASSERT_EQUAL ((int) varmap.size (), 1);
			CPPUNIT_ASSERT (varmap.begin () != varmap.end ());

			mu::varmap_type::const_iterator items = varmap.begin ();
			CPPUNIT_ASSERT_EQUAL (items->first.compare ("simpleVariable"), 0);
		}
		catch (mu::Parser::exception_type &e) {
			std::cerr << e.GetMsg() << std::endl;
			CPPUNIT_ASSERT (false);
		}

		// Try to define a variable twice and re-check the number of variables
		try {
			parser.DefineVar ("simpleVariable", &fval2);
			CPPUNIT_ASSERT (false);
		}
		catch (...) { // What kind of error should be caught?
			varmap = parser.GetVar ();
			CPPUNIT_ASSERT_EQUAL ((int) varmap.size (), 1);
			CPPUNIT_ASSERT (varmap.begin () != varmap.end ());
		}
	}

	void testQueryExpressionVariables () {
		mu::Parser parser;
		double fval1 = M_PI;

		// Get the map with the variables (should be empty right now)
		parser.SetExpr ("0");
		mu::varmap_type varmap = parser.GetUsedVar ();
		CPPUNIT_ASSERT_EQUAL ((int) varmap.size (), 0);
		CPPUNIT_ASSERT (varmap.begin () == varmap.end ());

		// Adding two variables (explicitly, implicitly) and check if it is there
		try {
			int itemCounter = 0, appearanceCounter[2] = {0, 0};

			parser.DefineVar ("varExplicit", &fval1);
			parser.SetExpr ("varImplicit=2*varExplicit");
			varmap = parser.GetUsedVar ();
			CPPUNIT_ASSERT_EQUAL ((int) varmap.size (), 2);
			CPPUNIT_ASSERT (varmap.begin () != varmap.end ());

			mu::varmap_type::const_iterator items = varmap.begin ();
			for (; items != varmap.end(); ++items, ++itemCounter) {
				if (items->first.compare ("varExplicit") == 0)
					appearanceCounter[0]++;
				if (items->first.compare ("varImplicit") == 0)
					appearanceCounter[1]++;
			}
			CPPUNIT_ASSERT_EQUAL ((int) varmap.size (), itemCounter);
			CPPUNIT_ASSERT_EQUAL (appearanceCounter[0], 1);
			CPPUNIT_ASSERT_EQUAL (appearanceCounter[1], 1);
		}
		catch (mu::Parser::exception_type &e) {
			std::cerr << e.GetMsg() << std::endl;
			CPPUNIT_ASSERT (false);
		}

		// Check multiple usage of variables in expressions
		try {
			int itemCounter = 0;

			parser.SetExpr ("varExplicit=4*varExplicit");
			varmap = parser.GetUsedVar ();
			CPPUNIT_ASSERT_EQUAL ((int) varmap.size (), 1);
			CPPUNIT_ASSERT (varmap.begin () != varmap.end ());

			mu::varmap_type::const_iterator items = varmap.begin ();
			for (; items != varmap.end(); ++items, ++itemCounter) 
				CPPUNIT_ASSERT_EQUAL (items->first.compare ("varExplicit"), 0);

			CPPUNIT_ASSERT_EQUAL ((int) varmap.size (), itemCounter);
		}
		catch (mu::Parser::exception_type &e) {
			std::cerr << e.GetMsg() << std::endl;
			CPPUNIT_ASSERT (false);
		}
	}

	void testRemoveVariables () {
		mu::Parser parser;
		int itemCounter = 0;
		double fval1 = M_PI;

		try {
			parser.DefineVar ("varExplicit", &fval1);
			parser.SetVarFactory (addVariableManually, &parser);
			parser.SetExpr ("varImplicit=2*varExplicit");
			parser.Eval ();

			mu::varmap_type varmap = parser.GetVar ();
			CPPUNIT_ASSERT_EQUAL ((int) varmap.size (), 2);
			CPPUNIT_ASSERT (varmap.begin () != varmap.end ());

			mu::varmap_type::const_iterator items = varmap.begin ();
			for (; items != varmap.end(); ++items, ++itemCounter);

			CPPUNIT_ASSERT_EQUAL ((int) varmap.size (), itemCounter);
		}
		catch (mu::Parser::exception_type &e) {
			std::cerr << e.GetMsg() << std::endl;
			CPPUNIT_ASSERT (false);
		}

		try {
			parser.RemoveVar ("varExplicit");
			mu::varmap_type varmap = parser.GetVar ();
			CPPUNIT_ASSERT_EQUAL ((int) varmap.size (), 1);
			CPPUNIT_ASSERT (varmap.begin () != varmap.end ());

			parser.RemoveVar ("varImplicit");
			varmap = parser.GetVar ();
			CPPUNIT_ASSERT_EQUAL ((int) varmap.size (), 0);
		}
		catch (mu::Parser::exception_type &e) {
			std::cerr << e.GetMsg() << std::endl;
			CPPUNIT_ASSERT (false);
		}

		try {
			parser.RemoveVar ("aVarThatNeverExisted");
			CPPUNIT_ASSERT (false);
		}
		catch (...) { }
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION (CustomVariablesTest);

int main (int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry ();
    runner.addTest (registry.makeTest ());
    bool wasSuccessful = runner.run ("", false);
    return (wasSuccessful != 0) ? 0 : 1;
}

