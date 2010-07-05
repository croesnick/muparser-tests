TESTS = \
	test-builtin-constants \
	test-builtin-operators \
	test-builtin-functions \
	test-custom-constants \
	test-custom-variables \
	test-custom-operators \
	test-custom-functions \
	test-parser \
	test-differentiate

noinst_PROGRAMS = $(TESTS)

TESTS_CXXFLAGS = \
	$(CPPUNIT_CFLAGS) \
	-I$(top_srcdir)
TESTS_LDADD = \
	$(CPPUNIT_LIBS) \
	$(top_builddir)/muParser/libmuparser.la

test_builtin_constants_SOURCES = builtin-constants.cxx
test_builtin_constants_CXXFLAGS = $(TESTS_CXXFLAGS)
test_builtin_constants_LDADD = $(TESTS_LDADD)

test_builtin_operators_SOURCES = builtin-operators.cxx
test_builtin_operators_CXXFLAGS = $(TESTS_CXXFLAGS)
test_builtin_operators_LDADD = $(TESTS_LDADD)

test_builtin_functions_SOURCES = builtin-functions.cxx
test_builtin_functions_CXXFLAGS = $(TESTS_CXXFLAGS)
test_builtin_functions_LDADD = $(TESTS_LDADD)

test_custom_constants_SOURCES = custom-constants.cxx
test_custom_constants_CXXFLAGS = $(TESTS_CXXFLAGS)
test_custom_constants_LDADD = $(TESTS_LDADD)

test_custom_variables_SOURCES = custom-variables.cxx
test_custom_variables_CXXFLAGS = $(TESTS_CXXFLAGS)
test_custom_variables_LDADD = $(TESTS_LDADD)

test_custom_operators_SOURCES = custom-operators.cxx
test_custom_operators_CXXFLAGS = $(TESTS_CXXFLAGS)
test_custom_operators_LDADD = $(TESTS_LDADD)

test_custom_functions_SOURCES = custom-functions.cxx
test_custom_functions_CXXFLAGS = $(TESTS_CXXFLAGS)
test_custom_functions_LDADD = $(TESTS_LDADD)

test_parser_SOURCES = parser.cxx
test_parser_CXXFLAGS = $(TESTS_CXXFLAGS)
test_parser_LDADD = $(TESTS_LDADD)

test_differentiate_SOURCES = differentiate.cxx
test_differentiate_CXXFLAGS = $(TESTS_CXXFLAGS)
test_differentiate_LDADD = $(TESTS_LDADD)

include $(top_srcdir)/tests.mak

