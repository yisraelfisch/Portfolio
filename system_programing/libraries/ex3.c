#include <dlfcn.h>

int main()
{
	void *handle;
	void (*foo)(int);

	handle = dlopen("libfoo.so", RTLD_NOW | RTLD_LOCAL);
	foo = (void (*)(int)) dlsym(handle,"foo");
	if (foo)
	{
		foo(5);
	} 

	dlclose(handle);
	

	return 0;
}