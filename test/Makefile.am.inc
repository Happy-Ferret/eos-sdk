# Copyright 2013 Endless Mobile, Inc.

TEST_FLAGS = @EOS_SDK_CFLAGS@ -I$(builddir)/endless  -I$(top_srcdir) -DCOMPILING_EOS_SDK
TEST_LIBS = @EOS_SDK_LIBS@ $(top_builddir)/libendless-@EOS_SDK_API_VERSION@.la

noinst_PROGRAMS = \
	test/endless/run-tests \
	$(NULL)

test_endless_run_tests_SOURCES = \
	test/endless/run-tests.c \
	test/endless/run-tests.h \
	test/endless/test-init.c \
	test/endless/test-application.c \
	test/endless/test-page-manager.c \
	test/endless/test-window.c \
	test/endless/test-flexy-grid.c \
	test/endless/test-custom-container.c \
	test/endless/test-profile.c \
	$(NULL)
test_endless_run_tests_CPPFLAGS = $(TEST_FLAGS)
test_endless_run_tests_LDADD = $(TEST_LIBS)

credits_resource_files = \
	test/smoke-tests/images/test1.jpg \
	test/smoke-tests/images/test2.jpg \
	test/smoke-tests/images/test3.jpg \
	test/smoke-tests/images/attribution.json \
	$(NULL)
test/smoke-tests/images/credits.gresource: test/smoke-tests/images/credits.gresource.xml $(credits_resource_files)
	$(AM_V_GEN)$(MKDIR_P) $(@D) && \
	$(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=$(srcdir)/test/smoke-tests/images $<
dist_noinst_DATA += test/smoke-tests/images/credits.gresource
CLEANFILES += test/smoke-tests/images/credits.gresource
EXTRA_DIST += \
	test/smoke-tests/images/credits.gresource.xml \
	$(credits_resource_files) \
	$(NULL)

javascript_tests = \
	test/tools/eos-application-manifest/testInit.js \
	test/tools/testHtmlExtractor.js \
	test/endless/testCustomContainer.js \
	test/endless/testTopbarHomeButton.js \
	test/endless/testTopbarNavButton.js \
	$(NULL)
EXTRA_DIST += \
	$(javascript_tests) \
	test/tools/test.html \
	test/utils.js \
	$(NULL)

# Run tests when running 'make check'
TESTS = \
	test/endless/run-tests \
	$(javascript_tests) \
	run_coverage.coverage \
	$(NULL)
JS_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) $(top_srcdir)/tap-driver.sh
JS_LOG_DRIVER_FLAGS = --comments
TEST_EXTENSIONS = .js .coverage
JS_LOG_COMPILER = jasmine
AM_JS_LOG_FLAGS = \
	--include-path=$(top_srcdir) \
	--tap \
	@JASMINE_REPORT_ARGUMENT@ \
	--no-config \
	$(NULL)
LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) $(top_srcdir)/tap-driver.sh
LOG_COMPILER = $(top_srcdir)/test/tap-test.sh
EXTRA_DIST += \
	test/tap-test.sh \
	test/test-bus.conf \
	$(NULL)
CLEANFILES += stderr.log

# Use locally built versions of Endless-0.gir and libraries; this may need to be
# changed to AM_TESTS_ENVIRONMENT in a future version of Automake
# Set XDG_CONFIG_HOME so as to avoid cluttering the user's actual config
# directory with junk from the tests
TESTS_ENVIRONMENT = \
	export EOS_DISABLE_METRICS=1; \
	export NO_AT_BRIDGE=1; \
	export GI_TYPELIB_PATH="$(top_builddir)$${GI_TYPELIB_PATH:+:$$GI_TYPELIB_PATH}"; \
	export LD_LIBRARY_PATH="$(top_builddir)/.libs$${LD_LIBRARY_PATH:+:$$LD_LIBRARY_PATH}"; \
	export XDG_CONFIG_HOME=`mktemp -d $${TMPDIR:-/tmp}/sdktestconfig.XXXXXXXX`; \
	export TOP_SRCDIR="$(abs_top_srcdir)"; \
	export BUILDDIR="."; \
	$(DBUS_RUN_SESSION) --config-file=$(top_srcdir)/test/test-bus.conf
