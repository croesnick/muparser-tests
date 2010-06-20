#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <limits>
#include <muParser/muParser.h>

class FunctionTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE (FunctionTest);
    CPPUNIT_TEST (testFunctionSign);
    CPPUNIT_TEST_SUITE_END ();

	void testFunctionSign () {
		mu::Parser parser;

		parser.DefineConst ("z", (double)  0.0);
		parser.DefineConst ("p", (double)  0.00074);
		parser.DefineConst ("n", (double) -0.00074);

		parser.SetExpr ("1*sign(z) + 2*sign(p) + 4*sign(n)");

		int rval = 0;
		try
		{
			rval = parser.Eval ();
			CPPUNIT_ASSERT (rval == -2);
		}
		catch (mu::Parser::exception_type &e)
		{
			std::cout << e.GetMsg() << std::endl;
		}
		
/*
		// Why can't I use numerical_limits?
		parser.DefineConst ("positive", (double)  std::numerical_limits<double>::epsilon( ));
		parser.DefineConst ("negative", (double) -std::numerical_limits<double>::epsilon( ));
*/
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

