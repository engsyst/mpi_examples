#include "arrayutils.h"
#include <mpi.h>
#include <stdio.h>
#include "reduce_example.h"
#include <math.h>

void comm_example() {
	int root = 0;
	int size, rank, code;
	code = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	code = MPI_Comm_size(MPI_COMM_WORLD, &size);

	MPI_Comm *comm = new int[size];
	MPI_Group *groups = new int[size];
	MPI_Group world_group;

	MPI_Comm_split(MPI_COMM_WORLD, size / 2 % rank, rank, comm);
	for (size_t i = 0; i < size; i++) {
		MPI_Comm_group(MPI_COMM_WORLD, &groups[i]);
	}

}