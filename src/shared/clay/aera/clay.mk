$(TOP)/src/shared/clay/aera/generated.clay:$(TOP)/src/shared/plugin.h
	 clay-bindgen -I/usr/lib/clang/3.0/include $^ -o $@
