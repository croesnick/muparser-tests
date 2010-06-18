ACLOCAL_AMFLAGS = -I m4

SUBDIRS = muParser testsuite-1 testsuite-2 testsuite-3 coverage

check: all
	$(MAKE) -C testsuite-1 check
	$(MAKE) -C testsuite-2 check
	$(MAKE) -C testsuite-3 check

check-valgrind: all
	$(MAKE) -C testsuite-1 check-valgrind
	$(MAKE) -C testsuite-2 check-valgrind
	$(MAKE) -C testsuite-3 check-valgrind

if ENABLE_COVERAGE
%.coverage: all
	-find $(top_builddir) -name *.gcda | xargs rm
	$(MAKE) -C $* check
	$(MAKE) -C coverage coverage
endif

clean-local:
	-find $(top_builddir) -name *.gcda -or -name *.gcno | xargs rm

