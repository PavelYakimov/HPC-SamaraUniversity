##
## MSU CUDA Course Examples and Exercises.
##
## Copyright (c) 2011 Dmitry Mikushin
##
## This software is provided 'as-is', without any express or implied warranty.
## In no event will the authors be held liable for any damages arising 
## from the use of this software.
## Permission is granted to anyone to use this software for any purpose, 
## including commercial applications, and to alter it and redistribute it freely,
## without any restrictons.
##

OPT = -O3

all: serial_cuda_driver_api.o pattern2d.o timing.o
	gcc serial_cuda_driver_api.o pattern2d.o timing.o -o serial_cuda_driver_api -L/opt/cuda/lib64 -lcuda -lcudart -lm -lrt

serial_cuda_driver_api.o: serial_cuda_driver_api.c timing.h pattern2d.h
	gcc -g $(OPT) -std=c99 -I/opt/cuda/include -c $< -o $@

pattern2d.o: pattern2d.cu pattern2d.h
	nvcc -g $(OPT) -c $< -o $@

timing.o: timing.c timing.h
	gcc -g $(OPT) -c $< -o $@

clean:
	rm -rf *.o serial_cuda_driver_api

