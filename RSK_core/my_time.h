#pragma once

#include<ctime>

static double start_time;
double current_time;

void init_time()
{
	start_time = current_time = clock();
}

double full_exec_time()
{
	return (clock() - start_time) / 1000.0;
}

double part_exec_time()
{
	double ans = (clock() - current_time) / 1000.0;
	current_time = clock();
	return ans;
}

