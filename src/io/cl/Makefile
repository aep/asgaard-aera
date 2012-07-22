../../../plugins/libaera1.io.csv.so:main.clay aera/generated.clay aera/aera.clay aera/primitives.clay
	clay -g -shared main.clay -o $@
aera/generated.clay:../../shared/plugin.h
	clay-bindgen -I/usr/lib/clang/3.0/include $^ -o $@

