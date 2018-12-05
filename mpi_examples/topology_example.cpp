#include "arrayutils.h"
#include <mpi.h>
#include <stdio.h>
#include "reduce_example.h"
#include <math.h>
#include <string>
#include "topology_example.h"

using namespace std;

void comm_cart_example() {
	int root = 0;
	int size, rank, code;
	code = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	code = MPI_Comm_size(MPI_COMM_WORLD, &size);

	// for debug only
	fflush(stdout);
	MPI_Barrier(MPI_COMM_WORLD);

	if (rank == root) {
		printf_s("\n---= comm_cart_example() =---\n");
	}

	int ndims = 2;
	int* dims = new int[ndims];
	int* periods = new int[ndims];
	
	// size MUST be 4, 16, 32 ...
	int processesPerDim = sqrtf(size);
	for (size_t i = 0; i < ndims; i++) {
		dims[i] = processesPerDim;
		periods[i] = 1;
	}
	MPI_Comm* cart_comm = new MPI_Comm;
	MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, 1, cart_comm);
	int cart_rank = 0;
	MPI_Comm_rank(*cart_comm, &cart_rank);
	printf_s("Rank %d, Cart_rank: %d\n", rank, cart_rank);

	int left, right, top, bottom;
	MPI_Cart_shift(*cart_comm, 0, 1, &left, &right);
	MPI_Cart_shift(*cart_comm, 1, 1, &top, &bottom);
	printf_s("Rank %d, left: %d, right: %d, top: %d, bottom: %d\n", rank, left, right, top, bottom);

}

void comm_circle_example() {
	int root = 0;
	int size, rank, code;
	code = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	code = MPI_Comm_size(MPI_COMM_WORLD, &size);

	// for debug only
	fflush(stdout);
	MPI_Barrier(MPI_COMM_WORLD);

	if (rank == root) {
		printf_s("\n---= comm_circle_example() =---\n");
	}

	int ndims = 1;
	int dims[] = { size };
	int periods[] = { 1 };

	MPI_Comm* cart_comm = new MPI_Comm;
	MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, 1, cart_comm);
	int cart_rank = 0;
	MPI_Comm_rank(*cart_comm, &cart_rank);
	printf_s("Rank %d, Cart_rank: %d\n", rank, cart_rank);

	int left, right;
	MPI_Cart_shift(*cart_comm, 0, 1, &left, &right);
	printf_s("Rank %d, left: %d, right: %d\n", rank, left, right);

}