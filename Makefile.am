ACLOCAL_AMFLAGS = -I m4

SUBDIRS = testsuite-1 testsuite-2 testsuite-3

check:
	$(MAKE) -C testsuite-1 check
	$(MAKE) -C testsuite-2 check
	$(MAKE) -C testsuite-3 check

check-valgrind:
	$(MAKE) -C testsuite-1 check-valgrind
	$(MAKE) -C testsuite-2 check-valgrind
	$(MAKE) -C testsuite-3 check-valgrind

