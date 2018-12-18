mod_foo.la: mod_foo.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_foo.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_foo.la
