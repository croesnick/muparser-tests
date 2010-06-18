#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <muParser/muParser.h>

class AllocateTest : public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE (AllocateTest);
    CPPUNIT_TEST (testAllocateStack);
    CPPUNIT_TEST (testAllocateDynamic);
    CPPUNIT_TEST_SUITE_END ();

    void testAllocateStack () {
        mu::Parser parser;
    }

    void testAllocateDynamic () {
        mu::Parser *parser = new mu::Parser ();
        CPPUNIT_ASSERT (parser != NULL);
        delete parser;
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION (AllocateTest);

int main (int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry ();
    runner.addTest (registry.makeTest ());
    bool wasSuccessful = runner.run ("", false);
    return (wasSuccessful != 0) ? 0 : 1;
}

