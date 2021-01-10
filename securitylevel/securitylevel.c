#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "securitylevel.h"
#include <stdlib.h>

int set_security_level(int pid, int new_level) {


	long int set = syscall(335, pid, new_level);
	return set;
}

int get_security_level(int pid) {

	long int get = syscall(336, pid);
	return get;
}

int* retrieve_set_security_params(int pid, int new_level) {

	int *set = malloc(sizeof(int)*4);
	set[0] = 335; set[1] = 2; set[2] = pid; set[3] = new_level;
	return set;
}


int* retrieve_get_security_params(int pid) {

        int *get = malloc(sizeof(int)*4);
        get[0] = 336; get[1] = 1; get[2] = pid;
        return get;
}

int interpret_set_security_result(int ret_value) {

	return ret_value;
}

int interpret_get_security_result(int ret_value) {

	return ret_value;
}
