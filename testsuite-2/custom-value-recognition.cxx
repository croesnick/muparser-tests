#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <limits>
#include <math.h>
#include <muParser/muParser.h>

int isOctVal (const char *expr, int *pos, double *val) {
	if (expr[0] != 'o') return false;
	if (expr[1] == '\0') return false;

	// TODO: Prevent overflows
	unsigned int i;
	double rval = 0.0;
	for (i = 0; ((0x30 <= expr[i+1]) && (expr[i+1] <= 0x37)); i++) {
		rval = (8*rval)+(expr[i+1]-0x30);
	}

	if (i == 0) return false;
	
	*val = rval;
  	*pos += i+1;

	return true;
}

int isBinVal (const char *expr, int *pos, double *val) {
	if (expr[0] != 'b') return false;

	unsigned i;
	unsigned iVal = 0, iBits = sizeof(iVal)*8;
	for (i = *pos; (expr[i+1]=='0'||expr[i+1]=='1')&& i<iBits; ++i) {
		iVal |= (int)(expr[i+1]=='1') << ((iBits-1)-i);
	}

	if (i==0) return false;
	if (i==iBits)
		throw int(-1);

	*val = (unsigned)(iVal >> (iBits-i) );
	*pos += i+1;

	return true;
}

class CustomValueRecognitionTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE (CustomValueRecognitionTest);
    CPPUNIT_TEST (testValueRecognitionOctal);
    CPPUNIT_TEST_SUITE_END ();

	void testValueRecognitionOctal () {
		mu::Parser parser;
		double rval;

		parser.AddValIdent (&isOctVal);
		parser.AddValIdent (&isBinVal);

		parser.SetExpr ("0");
		rval = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (0.0, rval, 0.0);

		try {
			parser.SetExpr ("0x32");
			rval = parser.Eval ();
			CPPUNIT_ASSERT (false);
		}
        catch (mu::Parser::exception_type &e) { }

		try {
			parser.SetExpr ("o");
			rval = parser.Eval ();
			CPPUNIT_ASSERT (false);
		}
        catch (mu::Parser::exception_type &e) { }

		try {
			parser.SetExpr ("o.");
			rval = parser.Eval ();
			CPPUNIT_ASSERT (false);
		}
        catch (mu::Parser::exception_type &e) { }

		try {
			parser.SetExpr ("o8");
			rval = parser.Eval ();
			CPPUNIT_ASSERT (false);
		}
        catch (mu::Parser::exception_type &e) { }

		parser.SetExpr ("o2");
		rval = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (2, rval, 0.0);

		parser.SetExpr ("o23");
		rval = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (19, rval, 0.0);

		parser.SetExpr ("b1001");
		rval = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (9, rval, 0.0);

		// Actually, I tried to test (b101010 - o32) [causing -16 -- why?]
		// and finally sqrt(((b00101010-o32)*o34)/b00000111) == 8.
		try {
			parser.SetExpr ("b00101010 - o32");
			rval = parser.Eval ();
			CPPUNIT_ASSERT_DOUBLES_EQUAL (16, rval, 1e-10);
		} catch (mu::Parser::exception_type &e) {
			std::cerr << e.GetMsg() << std::endl;
			CPPUNIT_ASSERT (false);
		} 
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION (CustomValueRecognitionTest);

int main (int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry ();
    runner.addTest (registry.makeTest ());
    bool wasSuccessful = runner.run ("", false);
    return (wasSuccessful != 0) ? 0 : 1;
}

