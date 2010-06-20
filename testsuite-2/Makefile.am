TESTS = \
	test-functions

noinst_PROGRAMS = $(TESTS)

TESTS_CXXFLAGS = \
	$(CPPUNIT_CFLAGS) \
	-I$(top_srcdir)
TESTS_LDADD = \
	$(CPPUNIT_LIBS) \
	$(top_builddir)/muParser/libmuparser.la

test_functions_SOURCES = functions.cxx
test_functions_CXXFLAGS = $(TESTS_CXXFLAGS)
test_functions_LDADD = $(TESTS_LDADD)

include $(top_srcdir)/tests.mak

