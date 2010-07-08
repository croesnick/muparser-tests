TESTS = \
	test-buildin-functions \
	test-differentiate \
	test-custom-constants \
	test-custom-functions \
	test-custom-operators \
	test-custom-variables \
	test-custom-value-recognition

noinst_PROGRAMS = $(TESTS)

TESTS_CXXFLAGS = \
	$(CPPUNIT_CFLAGS) \
	-I$(top_srcdir)
TESTS_LDADD = \
	$(CPPUNIT_LIBS) \
	$(top_builddir)/muParser/libmuparser.la

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

test_custom_operators_SOURCES = custom-operators.cxx
test_custom_operators_CXXFLAGS = $(TESTS_CXXFLAGS)
test_custom_operators_LDADD = $(TESTS_LDADD)

test_custom_variables_SOURCES = custom-variables.cxx
test_custom_variables_CXXFLAGS = $(TESTS_CXXFLAGS)
test_custom_variables_LDADD = $(TESTS_LDADD)

test_custom_value_recognition_SOURCES = custom-value-recognition.cxx
test_custom_value_recognition_CXXFLAGS = $(TESTS_CXXFLAGS)
test_custom_value_recognition_LDADD = $(TESTS_LDADD)

include $(top_srcdir)/tests.mak

