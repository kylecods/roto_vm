prac-win:
	x86_64-w64-mingw32-g++ -o sb.exe sb_test.cpp -static-libstdc++ 
vm-win:
	x86_64-w64-mingw32-gcc -o roto.exe main.c vm.c chunk.c value.c -Wall -Wextra -std=c99
vm-linux:
	clang -o roto-lin main.c vm.c chunk.c value.c -Wall -Wextra -std=c11
