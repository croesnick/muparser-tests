TESTS = \
	test-allocate

noinst_PROGRAMS = $(TESTS)

TESTS_CXXFLAGS = \
	$(CPPUNIT_CFLAGS) \
	$(MUPARSER_CFLAGS)
TESTS_LDADD = \
	$(CPPUNIT_LIBS) \
	$(MUPARSER_LIBS)

test_allocate_SOURCES = allocate.cxx
test_allocate_CXXFLAGS = $(TESTS_CXXFLAGS)
test_allocate_LDADD = $(TESTS_LDADD)

include $(top_srcdir)/tests.mak

