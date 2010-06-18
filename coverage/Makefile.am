coverage:
	$(LCOV) -d $(top_builddir) -c -o full.coverage && \
	$(LCOV) -e full.coverage *muParser* -o muparser.coverage && \
	$(GENHTML) --show-details -t "muParser Tests Coverage" --legend muparser.coverage -o coverage_report

clean-local:
	rm -rf coverage_report

CLEANFILES = \
	full.coverage \
	muparser.coverage

