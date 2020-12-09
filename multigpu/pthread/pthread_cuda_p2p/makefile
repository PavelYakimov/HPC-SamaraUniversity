all: pthread_cuda_p2p

pthread_cuda_p2p: pthread_cuda_p2p.o pattern2d.o
	nvcc pthread_cuda_p2p.o pattern2d.o -o $@ -lpthread

pthread_cuda_p2p.o: pthread_cuda_p2p.c
	gcc -g -std=c99 -D_GNU_SOURCE -I/usr/local/cuda/include -I/opt/cuda/include -c $< -o $@

pattern2d.o: pattern2d.cu
	nvcc -g -c $< -o $@

clean:
	rm -rf *.o pthread_cuda_p2p

