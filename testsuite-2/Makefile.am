TESTS = \
	test-buildin-functions \
	test-differentiate \
	test-custom-constants \
	test-custom-functions \
	test-custom-variables

noinst_PROGRAMS = $(TESTS)

TESTS_CXXFLAGS = \
	$(CPPUNIT_CFLAGS) \
	$(MUPARSER_CFLAGS)
TESTS_LDADD = \
	$(CPPUNIT_LIBS) \
	$(MUPARSER_LIBS)

test_buildin_functions_SOURCES = buildin-functions.cxx
test_buildin_functions_CXXFLAGS = $(TESTS_CXXFLAGS)
test_buildin_functions_LDADD = $(TESTS_LDADD)

test_differentiate_SOURCES = differentiate.cxx
test_differentiate_CXXFLAGS = $(TESTS_CXXFLAGS)
test_differentiate_LDADD = $(TESTS_LDADD)

test_custom_constants_SOURCES = custom-constants.cxx
test_custom_constants_CXXFLAGS = $(TESTS_CXXFLAGS)
test_custom_constants_LDADD = $(TESTS_LDADD)

test_custom_functions_SOURCES = custom-functions.cxx
test_custom_functions_CXXFLAGS = $(TESTS_CXXFLAGS)
test_custom_functions_LDADD = $(TESTS_LDADD)

test_custom_variables_SOURCES = custom-variables.cxx
test_custom_variables_CXXFLAGS = $(TESTS_CXXFLAGS)
test_custom_variables_LDADD = $(TESTS_LDADD)

include $(top_srcdir)/tests.mak

