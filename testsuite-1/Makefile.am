TESTS = \
	test-allocate \
	test-builtin-constants \
	test-builtin-operators \
	test-builtin-functions

noinst_PROGRAMS = $(TESTS)

TESTS_CXXFLAGS = \
	$(CPPUNIT_CFLAGS) \
	-I$(top_srcdir)
TESTS_LDADD = \
	$(CPPUNIT_LIBS) \
	$(top_builddir)/muParser/libmuparser.la

test_allocate_SOURCES = allocate.cxx
test_allocate_CXXFLAGS = $(TESTS_CXXFLAGS)
test_allocate_LDADD = $(TESTS_LDADD)

test_builtin_constants_SOURCES = builtin-constants.cxx
test_builtin_constants_CXXFLAGS = $(TESTS_CXXFLAGS)
test_builtin_constants_LDADD = $(TESTS_LDADD)

test_builtin_operators_SOURCES = builtin-operators.cxx
test_builtin_operators_CXXFLAGS = $(TESTS_CXXFLAGS)
test_builtin_operators_LDADD = $(TESTS_LDADD)

test_builtin_functions_SOURCES = builtin-functions.cxx
test_builtin_functions_CXXFLAGS = $(TESTS_CXXFLAGS)
test_builtin_functions_LDADD = $(TESTS_LDADD)

include $(top_srcdir)/tests.mak

