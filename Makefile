dll:
	g++ -c -o wincppapi.o src/main.cpp --std=c++20 -Iinclude -D BUILD
	g++ -o bin/wincppapi.dll wincppapi.o -s -shared -Wl,--subsystem,windows,--out-implib,lib/libwincppapi.lib -Iinclude
	rm wincppapi.o
program:
	g++ -c -o test.o src/test.cpp --std=c++20 -Iinclude
	g++ -o test.exe -s test.o -Llib -lwincppapi -Iinclude
	rm test.o
	mv test.exe bin/test.exe