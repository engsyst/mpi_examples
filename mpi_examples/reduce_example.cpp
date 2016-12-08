#include "arrayutils.h"
#include <mpi.h>
#include <stdio.h>
#include "reduce_example.h"
#include <math.h>

double max(double * d, int length) {
	double m = d[0];
	for (size_t i = 1; i < length; i++) {
		if (m < d[i]) {
			m = d[i];
		}
	}
	return m;
}

void reduce_example() {
	int root = 0;
	int size, rank, code;
	code = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	code = MPI_Comm_size(MPI_COMM_WORLD, &size);
	if (rank == root) {
		printf_s("\n---= reduce_example() =---\n");
	}

	// for debug only
	MPI_Barrier(MPI_COMM_WORLD);
	int data_size = 1001;
	int local_data_size = data_size / size;
	int last_local_data_size = data_size % size + local_data_size;
	if (rank == size - 1) {
		local_data_size = last_local_data_size;
	}
	printf_s("Rank %d, data_size: %d, local_data_size: %d\n", rank, data_size, local_data_size);

	double *data = NULL;
	double *local_buf = new double[local_data_size];

	int *sends = NULL;
	int *displaces = NULL;
	if (rank == root) {
		data = sequentalInit(data, data_size, 0);

		sends = new int[size];
		displaces = new int[size];
		for (size_t i = 0; i < size; i++) {
			sends[i] = (i == size - 1) ? last_local_data_size : local_data_size;
			displaces[i] = i * local_data_size;
			printf_s("Rank %d, sends[%d]: %d, displaces[%d]: %d\n", rank, i, sends[i], i, displaces[i]);
		}
	}

	MPI_Scatterv(data, sends, displaces, MPI_DOUBLE, local_buf, local_data_size, MPI_DOUBLE, root, MPI_COMM_WORLD);
	//printf_s("Rank %d, local_buf: ", rank);
	//print(local_buf, local_data_size);

	double localMax = max(local_buf, local_data_size);
	printf_s("Rank %d, localMax: %7.4f\n", rank, localMax);

	double totalMax = 0;
	MPI_Reduce(&localMax, &totalMax, 1, MPI_DOUBLE, MPI_MAX, root, MPI_COMM_WORLD);
	printf_s("Rank %d, TotalMax: %7.4f\n", rank, totalMax);
	printf_s("Rank %d, -------------------\n", rank);
}
