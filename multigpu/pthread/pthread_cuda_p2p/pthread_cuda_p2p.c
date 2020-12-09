/*
 * MSU CUDA Course Examples and Exercises.
 *
 * Copyright (c) 2011 Dmitry Mikushin
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising 
 * from the use of this software.
 * Permission is granted to anyone to use this software for any purpose, 
 * including commercial applications, and to alter it and redistribute it freely,
 * without any restrictons.
 */

#include "pattern2d.h"

#include <cuda_runtime.h>
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct thread_params_t
{
	int ithread, nthreads;
	int n, npasses;
	size_t size;

	float *din1, *din2, *dout;

	pthread_t handle;
	pthread_barrier_t* barrier;

	struct thread_params_t* prev;
};

void* thread_func(void* arg)
{
	// Get the current thread params from arg.
	struct thread_params_t* current =
		(struct thread_params_t*)arg;

        // Assign unique device to each POSIX thread.
	cudaError_t status = cudaSetDevice(current->ithread);
	if (status != cudaSuccess)
	{
		fprintf(stderr, "Cannot set CUDA device by process d, status= %s\n",
			current->ithread, cudaGetErrorString(status));
		pthread_exit(NULL);
	}

	// Create two device input buffers.
	status = cudaMalloc((void**)&current->din1, current->size);
	if (status != cudaSuccess)
	{
		fprintf(stderr, "Cannot allocate input device buffer by process %d, status = %s\n",
			current->ithread, cudaGetErrorString(status));
		pthread_exit(NULL);
	}
	status = cudaMalloc((void**)&current->din2, current->size);
	if (status != cudaSuccess)
	{
		fprintf(stderr, "Cannot allocate input device buffer by process %d, status = %s\n",
			current->ithread, cudaGetErrorString(status));
		pthread_exit(NULL);
	}
	
	// Create device output buffer.
	float* dout;
	status = cudaMalloc((void**)&current->dout, current->size);
	if (status != cudaSuccess)
	{
		fprintf(stderr, "Cannot allocate output device buffer by process %d, status = %s\n",
			current->ithread, cudaGetErrorString(status));
		pthread_exit(NULL);
	}

	float* hin = (float*)malloc(current->size);
	float* hout = (float*)malloc(current->size);
	
	// Generate random input data.
	double dinvrmax = 1.0 / RAND_MAX;
	for (int i = 0; i < current->n * current->n; i++)
	{
		for (int j = 0; j < current->ithread + 1; j++)
			hin[i] += rand() * dinvrmax;
		hin[i] /= current->ithread + 1;
	}
	
	// Copy input data generated on host to device buffer.
	status = cudaMemcpy(current->din1, hin, current->size, cudaMemcpyHostToDevice); 
	if (status != cudaSuccess)
	{
		fprintf(stderr, "Cannot copy input data from host to device by process %d, status = %s\n",
			current->ithread, cudaGetErrorString(status));
		pthread_exit(NULL);
	}

	// Synchronize threads after allocations.
	pthread_barrier_wait(current->barrier);
	
	// Perform the specified number of processing passes.
	for (int ipass = 0; ipass < current->npasses; ipass++)
	{
		// Fill output device buffer will zeros.
		status = cudaMemset(current->dout, 0, current->size);
		if (status != cudaSuccess)
		{
			fprintf(stderr, "Cannot fill output device buffer with zeros by process %d, status = %s\n",
				current->ithread, cudaGetErrorString(status));
			pthread_exit(NULL);
		}

		// Process data on GPU.
		pattern2d_gpu(1, current->n, 1, 1, current->n, 1, current->din1, current->dout);

		// Wait for GPU kernels to finish processing.
		status = cudaThreadSynchronize();
		if (status != cudaSuccess)
		{
			fprintf(stderr, "Cannot synchronize GPU kernel by process %d, status = %s\n",
				current->ithread, cudaGetErrorString(status));
			pthread_exit(NULL);
		}
	
		// Copy output data back from device to host.
		status = cudaMemcpy(hout, current->dout, current->size, cudaMemcpyDeviceToHost); 
		if (status != cudaSuccess)
		{
			fprintf(stderr, "Cannot copy output data from device to host by process %d, status = %s\n",
				current->ithread, cudaGetErrorString(status));
			pthread_exit(NULL);
		}
	
		// Output average value of the resulting field.
		float avg = 0.0;
		for (int i = 0; i < current->n * current->n; i++)
			avg += hout[i];
		avg /= current->n * current->n;

		printf("Receiving thread %d resulting field with average = %f by thread %d\n",
			current->prev->ithread, avg, current->ithread);
	
		// Pass entire process input device buffer directly to input device buffer
		// of next process.
		status = cudaMemcpyPeer(current->din2, current->ithread,
			current->prev->din1, current->prev->ithread, current->prev->size);
		if (status != cudaSuccess)
		{
			fprintf(stderr, "Cannot start peer to peer transfer between device %d and %d: %s\n",
				current->ithread, current->prev->ithread, cudaGetErrorString(status));
			pthread_exit(NULL);
		}

		status = cudaDeviceSynchronize();
		if (status != cudaSuccess)
		{
			fprintf(stderr, "Cannot synchronize after peer to peer transfer between device %d and %d: %s\n",
				current->ithread, current->prev->ithread, cudaGetErrorString(status));
			pthread_exit(NULL);
		}

		// Synchronize after iteration.
		pthread_barrier_wait(current->barrier);
		
		// Swap buffers.
		float* swap = current->din1;
		current->din1 = current->din2;
		current->din2 = swap;
	}
	
	status = cudaFree(current->din1);
	if (status != cudaSuccess)
	{
		fprintf(stderr, "Cannot free input device buffer by process %d, status = %d\n",
			current->ithread, cudaGetErrorString(status));
		pthread_exit(NULL);
	}

	status = cudaFree(current->din2);
	if (status != cudaSuccess)
	{
		fprintf(stderr, "Cannot free input device buffer by process %d, status = %d\n",
			current->ithread, cudaGetErrorString(status));
		pthread_exit(NULL);
	}

	status = cudaFree(current->dout);
	if (status != cudaSuccess)
	{
		fprintf(stderr, "Cannot free output device buffer by process d, status = %d\n",
			current->ithread, cudaGetErrorString(status));
		pthread_exit(NULL);
	}

	free(hin);
	free(hout);	

	pthread_exit(NULL);

	return NULL;
}

int main(int argc, char* argv[])
{
	// Get problem size from the command line.
	if (argc != 4)
	{
		printf("Usage: %s <nthreads> <n> <npasses>\n", argv[0]);
		return 0;
	}

	int nthreads = atoi(argv[1]);
	int n = atoi(argv[2]);
	int npasses = atoi(argv[3]);
	size_t size = n * n * sizeof(float);
	
	if ((nthreads <= 0) || (n <= 0) || (npasses <= 0)) return 0;

	int ndevices = 0;
	cudaError_t status = cudaGetDeviceCount(&ndevices);
	if (status != cudaSuccess)
	{
		fprintf(stderr, "Cannot get the cuda device count, status = %s\n",
			cudaGetErrorString(status));
		return 1;
	}

	if (ndevices < nthreads)
	{
		fprintf(stderr, "There are less devices than working threads requested\n");
		return 1;
	}
	
	// Create containers for threads parameters.
	struct thread_params_t* thread_params =
		(struct thread_params_t*)malloc(
			sizeof(struct thread_params_t) * nthreads);

	// Initialize threads barrier.
	pthread_barrier_t barrier;
	if (pthread_barrier_init(&barrier, NULL, nthreads))
	{
		fprintf(stderr, "Cannot initialize pthread barrier\n");
		return 1;
	}
	
	// Start threads.
	for (int ithread = 0; ithread < nthreads; ithread++)
	{
		struct thread_params_t* t = thread_params + ithread;
		t->ithread = ithread;
		t->nthreads = nthreads;
		t->n = n; t->npasses = npasses; t->size = size;
		t->prev = thread_params + ithread - 1;
		t->prev += ithread ? 0 : nthreads;
		t->barrier = &barrier;
		
		if (pthread_create(&thread_params[ithread].handle, NULL,
			thread_func, &thread_params[ithread]))
		{
			fprintf(stderr, "Cannot create pthread thread\n");
			return 1;
		}
	}
	
	// Wait for threads completion.
	for (int ithread = 0; ithread < nthreads; ithread++)
	{
		if (pthread_join(thread_params[ithread].handle, NULL))
		{
			fprintf(stderr, "Cannot join pthread thread\n");
			return 1;
		}
	}
	
	free(thread_params);

	if (pthread_barrier_destroy(&barrier))
	{
		fprintf(stderr, "Cannot destroy pthread barrier\n");
		return 1;
	}
	
	return 0;
}

