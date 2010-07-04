#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <limits>
#include <math.h>
#include <muParser/muParser.h>

class CustomConstantsTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE (CustomConstantsTest);
    CPPUNIT_TEST (testConstDefinition);
	CPPUNIT_TEST (testQueryConstants);
	CPPUNIT_TEST (testRemoveConstant);
    CPPUNIT_TEST_SUITE_END ();

	void testConstDefinition () {
		mu::Parser parser;
		
		// Check for empty names
		try {
			parser.DefineConst("", 1.0);
			CPPUNIT_ASSERT (false);
		}
		catch (...) { // What kind of error should be caught?
		}

		// Check for empty string names
		try {
			parser.DefineStrConst("", "it is empty");
			CPPUNIT_ASSERT (false);
		}
		catch (...) { // What kind of error should be caught?
		}

		// Define value constant _pi
		parser.DefineConst("_pi", (double) M_PI);
		// Re-defining value constant _pi by a "fake pi" :)
		parser.DefineConst("_pi", (double) M_E);

		// Define a string constant named strBuf
		parser.DefineStrConst("strBuf", "hello world");
		try {
			parser.DefineStrConst("strBuf", "howdy partner");
			CPPUNIT_ASSERT (false);
		}
		catch (...) { // What kind of error should be caught?
		}
	}

	void testQueryConstants () {
		mu::Parser parser;
		int initialNoConstants;
		int actualNoConstants = 0;
		int appearanceCounter[2] = {0, 0};

		// Get the map with the variables
		mu::valmap_type valmap = parser.GetConst ();
		initialNoConstants = (int) valmap.size ();

		// Adding a value constant and check if it is there
		try {
			parser.DefineConst ("valConst1", M_PI);
			//parser.DefineStrConst ("strConst1", "initial text");
			valmap = parser.GetConst ();
			CPPUNIT_ASSERT_EQUAL (initialNoConstants + 1, (int) valmap.size ());
			CPPUNIT_ASSERT (valmap.begin () != valmap.end ());

			mu::valmap_type::const_iterator items;
			for (items = valmap.begin(); items != valmap.end(); ++items, ++actualNoConstants) {
				if (items->first.compare ("valConst1") == 0) {
					appearanceCounter[0]++;
					CPPUNIT_ASSERT_EQUAL (M_PI, items->second);
				}
				//if (items->first.compare ("strConst1") == 0) {
				//	appearanceCounter[1]++;
				//	std::cout << items->second << std::endl;
				//	//CPPUNIT_ASSERT_EQUAL (0, items->second.compare ("initial text"));
				//}
			}
	
			CPPUNIT_ASSERT_EQUAL (initialNoConstants + 1, actualNoConstants);
			CPPUNIT_ASSERT_EQUAL (1, appearanceCounter[0]);
			//CPPUNIT_ASSERT_EQUAL (1, appearanceCounter[1]);
		}
		catch (mu::Parser::exception_type &e) {
			std::cerr << e.GetMsg() << std::endl;
			CPPUNIT_ASSERT (false);
		}

		// Try to re-define the constants
		try {
			parser.DefineConst ("valConst1", M_E);

			valmap = parser.GetConst ();
			CPPUNIT_ASSERT_EQUAL (initialNoConstants + 1, (int) valmap.size ());
			CPPUNIT_ASSERT (valmap.begin () != valmap.end ());

			mu::valmap_type::const_iterator items;
			for (items = valmap.begin(), actualNoConstants = 0, appearanceCounter[0] = 0; 
				items != valmap.end(); ++items, ++actualNoConstants) {
				if (items->first.compare ("valConst1") == 0) {
					appearanceCounter[0]++;
					CPPUNIT_ASSERT_EQUAL (M_E, items->second);
				}
			}
	
			CPPUNIT_ASSERT_EQUAL (initialNoConstants + 1, actualNoConstants);
			CPPUNIT_ASSERT_EQUAL (1, appearanceCounter[0]);
		}
		catch (mu::Parser::exception_type &e) { // What kind of error should be caught?
			std::cerr << e.GetMsg() << std::endl;
			CPPUNIT_ASSERT (false);
		}	
	}

	void testRemoveConstant () {
		mu::Parser parser;
		int initialNoConstants = 0;

		mu::valmap_type valmap = parser.GetConst ();
		initialNoConstants = (int) valmap.size ();

		try {
			parser.DefineConst ("varConst", M_PI);
			//parser.DefineStrConst ("strConst", "initial text");

			valmap = parser.GetConst ();
			CPPUNIT_ASSERT_EQUAL (initialNoConstants + 1, (int) valmap.size ());
		}
		catch (mu::Parser::exception_type &e) {
			std::cerr << e.GetMsg() << std::endl;
			CPPUNIT_ASSERT (false);
		}
		
		// Try treating a const as a variable -- should leave constant untouched
		try {
			parser.RemoveVar ("varConst");
			valmap = parser.GetConst ();
			CPPUNIT_ASSERT_EQUAL (initialNoConstants + 1, (int) valmap.size ());
		}
		catch (mu::Parser::exception_type &e) {
			std::cerr << e.GetMsg() << std::endl;
			CPPUNIT_ASSERT (false);
		}

		// Finally, remove the (all, resp.) constant
		try {
			parser.ClearConst ();
			valmap = parser.GetConst ();
			CPPUNIT_ASSERT_EQUAL (0, (int) valmap.size ());
		}
		catch (mu::Parser::exception_type &e) { 
			std::cerr << e.GetMsg() << std::endl;
			CPPUNIT_ASSERT (false);
		}
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION (CustomConstantsTest);

int main (int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry ();
    runner.addTest (registry.makeTest ());
    bool wasSuccessful = runner.run ("", false);
    return (wasSuccessful != 0) ? 0 : 1;
}

