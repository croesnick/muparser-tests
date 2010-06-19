#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <muParser/muParser.h>

#define _USE_MATH_DEFINES
#include <cmath>

class CustomVariablesTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE (CustomVariablesTest);
    CPPUNIT_TEST (testDefine);
    CPPUNIT_TEST (testAssign);
    CPPUNIT_TEST (testQueryRemove);
    CPPUNIT_TEST (testImplicit);
    CPPUNIT_TEST_SUITE_END ();

    void testDefine () {
        mu::Parser parser;
        double res, x;

        parser.DefineVar("x", &x);

        x = 2.5;
        parser.SetExpr ("sqrt(x*x)");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (x, res, 0.000001);

        x = 10;
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (x, res, 0.000001);
    }

    void testAssign () {
        mu::Parser parser;
        double res, x;

        parser.DefineVar("x", &x);
        parser.SetExpr ("x = _pi");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (M_PI, x, 0.000001);
        CPPUNIT_ASSERT_DOUBLES_EQUAL (x, res, 0.000001);
    }


    void testQueryRemove () {
        mu::Parser parser;
        double x;

        parser.DefineVar("x", &x);
        
        const mu::varmap_type& vmap = parser.GetVar ();
        CPPUNIT_ASSERT (vmap.size () > 0);
        mu::varmap_type::const_iterator iter;
        for (iter = vmap.begin (); iter != vmap.end (); ++iter) {
          if (iter->first == "x")
            CPPUNIT_ASSERT_EQUAL (&x, iter->second);
        }

        parser.RemoveVar("x");
        CPPUNIT_ASSERT (parser.GetVar ().size () == 0);
    }

    static double * variable_x (const char *name, void *data) {
      static double val = M_PI;

      CPPUNIT_ASSERT (data != NULL);
      if (strcmp (name, "x") == 0) {
        int *variable_x_called = (int *) data;
        *variable_x_called = *variable_x_called + 1;
        return &val;
      }

      return NULL;
    }

    void testImplicit () {
        mu::Parser parser;
        double res;
        int variable_x_called = 0;

        parser.SetVarFactory(&variable_x, &variable_x_called);

        parser.SetExpr ("x");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (M_PI, res, 0.000001);
        CPPUNIT_ASSERT_EQUAL (1, variable_x_called);
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

