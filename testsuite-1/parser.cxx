#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <muParser/muParser.h>

#define _USE_MATH_DEFINES
#include <cmath>

class ParserTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE (ParserTest);
    CPPUNIT_TEST (testCustomValueRecognition);
    CPPUNIT_TEST (testPrecedence);
    CPPUNIT_TEST (testParenthesis);
    CPPUNIT_TEST_SUITE_END ();

    static int _hexValRecognition(const char *expr, int *pos, double *val) {
      if (expr[0]!='#') 
        return 0;
      
      double ret = 0;
      int c, i;

      for (i=0; ((expr[i+1]>='0'&& expr[i+1]<='9') || (expr[i+1]>='a'&& expr[i+1]<='f') || (expr[i+1]>='A'&& expr[i+1]<='F')); ++i) {
        if (expr[i + 1] >= '0' && expr[i + 1] <= '9')
          c = expr[i + 1] - '0';
        else if (expr[i + 1] >= 'a' && expr[i + 1] <= 'f')
          c = expr[i + 1] - 'a' + 10;
        else if (expr[i + 1] >= 'A' && expr[i + 1] <= 'F')
          c = expr[i + 1] - 'A' + 10;
        ret = (ret * 16) + c;
      }
      
      if (i==0)
        return 0;
      
      *val = ret;
      *pos += i + 1;
      
      return 1;
    }

    void testCustomValueRecognition () {
        mu::Parser parser;
        double res;

        parser.AddValIdent(&_hexValRecognition);

        parser.SetExpr ("2");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (2, res, 0.000001);

        parser.SetExpr ("#10");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (16, res, 0.000001);

        parser.SetExpr ("#10 + 1");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (17, res, 0.000001);

        parser.SetExpr ("#ff");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (255, res, 0.000001);

        parser.SetExpr ("#Ff");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (255, res, 0.000001);

        parser.SetExpr ("#F0");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (240, res, 0.000001);
    }

    void testPrecedence () {
        mu::Parser parser;
        double res, x = 2;

        parser.DefineVar("x", &x);

        parser.SetExpr ("x = x + 3 * 4 - (x + 3) * 4");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-6, res, 0.000001);
        CPPUNIT_ASSERT_DOUBLES_EQUAL (-6, x, 0.000001);
    }

    void testParenthesis () {
        mu::Parser parser;
        double res;

        parser.SetExpr ("sqrt((-((((2 - 1) * 3) + (2 / 3.) * 4) - 2 * 3 * (3 + 4) + 1 - 2 / 3)))");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (6, res, 0.000001);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION (ParserTest);

int main (int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry ();
    runner.addTest (registry.makeTest ());
    bool wasSuccessful = runner.run ("", false);
    return (wasSuccessful != 0) ? 0 : 1;
}

