TESTS = \
	test-functions

noinst_PROGRAMS = $(TESTS)

TESTS_CXXFLAGS = \
	$(CPPUNIT_CFLAGS) \
	$(MUPARSER_CFLAGS)
TESTS_LDADD = \
	$(CPPUNIT_LIBS) \
	$(MUPARSER_LIBS)

test_functions_SOURCES = functions.cxx
test_functions_CXXFLAGS = $(TESTS_CXXFLAGS)
test_functions_LDADD = $(TESTS_LDADD)

include $(top_srcdir)/tests.mak

