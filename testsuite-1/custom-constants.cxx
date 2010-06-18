#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <muParser/muParser.h>

#define _USE_MATH_DEFINES
#include <cmath>

class CustomConstantsTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE (CustomConstantsTest);
    CPPUNIT_TEST (testDefine);
    CPPUNIT_TEST (testQuery);
    CPPUNIT_TEST_SUITE_END ();

    void testDefine () {
        mu::Parser parser;
        double res;

        parser.DefineConst("sqrt1_2", M_SQRT1_2);

        parser.SetExpr ("sqrt1_2");
        res = parser.Eval ();
        CPPUNIT_ASSERT_DOUBLES_EQUAL (M_SQRT1_2, res, 0.000001);

        CPPUNIT_ASSERT_THROW (parser.DefineConst("!23", 0), mu::ParserError);
    }

    void testQuery () {
        mu::Parser parser;

        parser.DefineConst("sqrt1_2", M_SQRT1_2);
        CPPUNIT_ASSERT_THROW (parser.DefineConst("!23", 0), mu::ParserError);
        
        const mu::valmap_type& cmap = parser.GetConst ();
        CPPUNIT_ASSERT (cmap.size () > 0);
        mu::valmap_type::const_iterator iter;
        for (iter = cmap.begin (); iter != cmap.end (); ++iter) {
          if (iter->first == "_e")
            CPPUNIT_ASSERT_DOUBLES_EQUAL (M_E, iter->second, 0.00001);
          else if (iter->first == "_pi")
            CPPUNIT_ASSERT_DOUBLES_EQUAL (M_PI, iter->second, 0.00001);
          else if (iter->first == "sqrt1_2")
            CPPUNIT_ASSERT_DOUBLES_EQUAL (M_SQRT1_2, iter->second, 0.00001);
          else if (iter->first == "!23")
            CPPUNIT_ASSERT (iter->first != "!23");
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

