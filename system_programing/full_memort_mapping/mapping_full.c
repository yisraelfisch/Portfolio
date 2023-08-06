#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
void FunctionFromSharedLib();
void FunctionFromStaticLib();

static int StaticFunction()
{
	printf("StaticFunction: %p\n", StaticFunction);
	return 1;
}

extern int ExternFunction()
{
	printf("ExternFunction: %p\n", ExternFunction);
	return 2;
}

int FunctionForLocalVar()
{
	const int const_local_var = 1;
	const static int const_static_local_var = 2;
	
	int non_const_local_var = 1;
	static int non_const_static_local_var = 2;

	char *string_literal_pointer_local = "abc";
	char string_literal_array_local[] = "abc";

	int *heap_var_local = (int *)malloc(sizeof(int) * 10);

	printf("FunctionForLocalVar: %p\n", FunctionForLocalVar);
	printf("const_local_var: %p\n", &const_local_var);
	printf("const_static_local_var: %p\n", &const_static_local_var);
	printf("non_const_local_var: %p\n", &non_const_local_var);
	printf("non_const_static_local_var: %p\n", &non_const_static_local_var);
	printf("string_literal_pointer_local: %p\n", &string_literal_pointer_local);
	printf("string_literal_pointer_local: %p\n", string_literal_pointer_local);
	printf("string_literal_array_local: %p\n", &string_literal_array_local);
	printf("string_literal_array_local: %p\n", string_literal_array_local);
	printf("heap_var_local: %p\n", &heap_var_local);
	
	free(heap_var_local);

	return 3;
}

const int const_global_var = 1;
const static int const_static_global_var = 2;
	
int non_const_global_var = 1;
static int non_const_static_global_var = 2;

char *string_literal_pointer_global = "abc";
char string_literal_array_global[] = "abc";

int RecursiveFunction(int x)
{
	int auto_local_rec = 1;
	static int static_local_var_rec = 1;

	int *heap_var_local_rec1 = (int *)malloc(sizeof(int) * 10);
	int *heap_var_local_rec2 = (int *)malloc(sizeof(int) * 10);
	int *heap_var_local_rec3 = (int *)malloc(sizeof(int) * 10);

	char local_arr1[100];
	char local_arr2[100];
	char local_arr3[100];

	if(x == 10)
	{
		return x;
	}

	printf("heap_var_local_rec1: %p\n", heap_var_local_rec1);
	printf("heap_var_local_rec2: %p\n", heap_var_local_rec2);
	printf("heap_var_local_rec3: %p\n", heap_var_local_rec3);
	printf("local_arr1: %p\n", local_arr1);
	printf("local_arr2: %p\n", local_arr2);
	printf("local_arr3: %p\n", local_arr3);

	free(heap_var_local_rec1);
	free(heap_var_local_rec2);
	free(heap_var_local_rec3);

	printf("This is the %d call\n", x);
	
	return (RecursiveFunction(x + 1));
}

int main(int argc, char **argv, char **envp)
{
	void *handle = NULL;
	void(*foo)();

	char *enviroment_var = *envp; /*  */
	char *command_line_argv = *argv;
	int command_line_argc = argc;

	printf("argc: %p\n", &argc);
	printf("argv: %p\n", argv);
	printf("envp: %p\n", envp);
	printf("*argv: %p\n", *argv);
	printf("*envp: %p\n", *envp);

	printf("const_global_var: %p\n", &const_global_var);
	printf("const_static_global_var: %p\n", &const_static_global_var);
	printf("non_const_global_var: %p\n", &non_const_global_var);
	printf("string_literal_pointer_global: %p\n", &string_literal_pointer_global);
	printf("string_literal_pointer_global: %p\n", string_literal_pointer_global);
	printf("string_literal_array_global: %p\n", &string_literal_array_global);
 	printf("string_literal_array_global: %p\n", string_literal_array_global);
	handle = dlopen("./libdyn.so", RTLD_LAZY);
	*(void **)(&foo) = dlsym(handle, "FunctionFromSharedLib");
	(*foo)();
	printf("FunctionFromSharedLib - explicit: %p\n", foo);
	dlclose(handle);

	FunctionForLocalVar();
	FunctionFromSharedLib();
	FunctionFromStaticLib();
	printf("FunctionFromSharedLib - implicit: %p\n", FunctionFromSharedLib);
	printf("FunctionFromStaticLib: %p\n", FunctionFromStaticLib);
	StaticFunction();
	ExternFunction();
	RecursiveFunction(1);
	
	return 0;
}
