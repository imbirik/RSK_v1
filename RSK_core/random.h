#pragma once

double rand01(double acc = 1e9);                             //Return real random number from [0, 1]
long randN(long);                            //Return integer random number from [0, N-1], where N is an argument     
void rand_arr(double*, size_t);             //Return an array of real random numbers form [0, 1] 