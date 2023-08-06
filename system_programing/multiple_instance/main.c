#include <dlfcn.h>
void Foo1();
void Foo2();
void PrintGlobalVariableAddress();

int main()
{
	/*void *handle1;
	void *handle2;

	void(*foo1)();
	void(*foo2)();

	handle1 = dlopen("libex1.so", RTLD_LAZY);

	*(void **)(&foo1) = dlsym(handle1, "Foo1");

	(*foo1)();

	handle2 = dlopen("libex2.so", RTLD_LAZY);

	*(void **)(&foo2) = dlsym(handle2, "Foo2");
	
	(*foo2)();
	dlclose(handle1);
	dlclose(handle2);*/
	PrintGlobalVariableAddress();

	Foo1();
	Foo2();


	return 0;
}
/*

Creating static library:
gd -c -fpic global.c
ar rcs libglobal.a global.o

creating two dynamic library:
gd -c -fpic Ex1.c
gd -c -fpic Ex2.c
gd -shared -o libex1.so Ex1.o libglobal.a 
gd -shared -o libex2.so Ex2.o libglobal.a 

compiling with linking:
pwd
gd -L/home/yaakov/git/system_programming/multiple_instances_of_a_global_variable -Wl,-rpath=/home/yaakov/git/system_programming/multiple_instances_of_a_global_variable main.c libglobal.a 

*/