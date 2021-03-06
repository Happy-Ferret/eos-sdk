## Process this file with automake to produce Makefile.in

# The name of the module, e.g. 'glib'.
DOC_MODULE=endless

# Uncomment for versioned docs and specify the version of the module, e.g. '2'.
DOC_MODULE_VERSION=@EOS_SDK_API_VERSION@

# The top-level SGML file. You can change this if you want to.
DOC_MAIN_SGML_FILE=$(DOC_MODULE)-docs.xml

# Directories containing the source code.
# gtk-doc will search all .c and .h files beneath these paths
# for inline comments documenting functions and macros.
# e.g. DOC_SOURCE_DIR=$(top_srcdir)/gtk $(top_srcdir)/gdk
DOC_SOURCE_DIR = \
	$(top_srcdir)/endless \
	$(top_builddir)/endless \
	$(NULL)

# Extra options to pass to gtkdoc-scangobj. Not normally needed.
SCANGOBJ_OPTIONS= \
    --query-child-properties=gtk_container_class_list_child_properties

# Extra options to supply to gtkdoc-scan.
# e.g. SCAN_OPTIONS=--deprecated-guards="GTK_DISABLE_DEPRECATED"
SCAN_OPTIONS=--rebuild-types

# Extra options to supply to gtkdoc-mkdb.
# e.g. MKDB_OPTIONS=--xml-mode --output-format=xml
MKDB_OPTIONS=--xml-mode --output-format=xml

# Extra options to supply to gtkdoc-mktmpl
# e.g. MKTMPL_OPTIONS=--only-section-tmpl
MKTMPL_OPTIONS=

# Extra options to supply to gtkdoc-mkhtml
MKHTML_OPTIONS=

# Extra options to supply to gtkdoc-fixxref. Not normally needed.
# e.g. FIXXREF_OPTIONS=--extra-dir=../gdk-pixbuf/html --extra-dir=../gdk/html
FIXXREF_OPTIONS=

# Used for dependencies. The docs will be rebuilt if any of these change.
BUILT_HFILES = $(top_builddir)/endless/eosversion.h
HFILE_GLOB=$(top_srcdir)/endless/*.h
CFILE_GLOB=$(top_srcdir)/endless/*.c

# Extra header to include when scanning, which are not under DOC_SOURCE_DIR
# e.g. EXTRA_HFILES=$(top_srcdir)/contrib/extra.h
EXTRA_HFILES=

# Header files or dirs to ignore when scanning. Use base file/dir names
# e.g. IGNORE_HFILES=gtkdebug.h gtkintl.h private_code
IGNORE_HFILES= eosapiversion.h \
               eosinit-private.h \
               eosresource-private.h \
               eostopbar-private.h \
               eosmainarea-private.h \
               eosactionmenu-private.h \
               eospagemanager-private.h \
               eosflexygrid-private.h \
               eosattribution-private.h \
               eoscellrendererpixbuflink-private.h \
               eoscellrenderertextlink-private.h \
	       eosprofile-private.h \
	       gvdb \
               $(NULL)

# Images to copy into HTML directory.
# e.g. HTML_IMAGES=$(top_srcdir)/gtk/stock-icons/stock_about_24.png
HTML_IMAGES=

# Extra SGML files that are included by $(DOC_MAIN_SGML_FILE).
# e.g. content_files=running.sgml building.sgml changes-2.0.sgml
content_files=\
	eos-profile.xml \
	$(NULL)

# SGML files where gtk-doc abbrevations (#GtkWidget) are expanded
# These files must be listed here *and* in content_files
# e.g. expand_content_files=running.sgml
expand_content_files=

# CFLAGS and LDFLAGS for compiling gtkdoc-scangobj with your library.
# Only needed if you are using gtkdoc-scangobj to dynamically query widget
# signals and properties.
GTKDOC_CFLAGS=-I$(top_srcdir) -I$(top_builddir) @EOS_SDK_CFLAGS@
GTKDOC_LIBS=$(top_builddir)/libendless-@EOS_SDK_API_VERSION@.la @EOS_SDK_LIBS@

# This includes the standard gtk-doc make rules, copied by gtkdocize.
include $(top_srcdir)/gtk-doc.make

# Other files to distribute
# e.g. EXTRA_DIST += version.xml.in
EXTRA_DIST +=

# Files not to distribute
# for --rebuild-types in $(SCAN_OPTIONS), e.g. $(DOC_MODULE).types
# for --rebuild-sections in $(SCAN_OPTIONS) e.g. $(DOC_MODULE)-sections.txt
#DISTCLEANFILES +=

if ENABLE_GTK_DOC
TESTS_ENVIRONMENT = \
	export DOC_MODULE=$(DOC_MODULE); \
	export DOC_MAIN_SGML_FILE=$(DOC_MAIN_SGML_FILE); \
	export SRCDIR=$(abs_srcdir); \
	export BUILDDIR=$(abs_builddir);
TESTS = $(GTKDOC_CHECK)
endif

man_MANS =

if ENABLE_MAN

man_MANS += \
	eos-profile.1 \
	$(NULL)

XSLTPROC_FLAGS = \
	--nonet \
	--stringparam man.output.quietly 1 \
	--stringparam funcsynopsis.style ansi \
	--stringparam man.th.extra1.suppress 1 \
	--stringparam man.authors.section.enabled 0 \
	--stringparam man.copyright.section.enabled 1 \
	$(NULL)

.xml.1:
	$(AM_V_GEN) $(XSLTPROC) $(XSLTPROC_FLAGS) http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $<

endif

CLEANFILES ?=
CLEANFILES += $(man_MANS)
EXTRA_DIST += $(man_MANS)
