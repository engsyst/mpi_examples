#include <mpi.h>
#include <stdio.h>
#include "send_recv.h"

void send_recv_example() {
	int root = 0;
	int size, rank, code;
	code = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	code = MPI_Comm_size(MPI_COMM_WORLD, &size);
	if (rank == root) {
		printf_s("\n---= send_recv_example() =---\n");
	}

	// for debug only
	fflush(stdout);
	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Status status;
	int recv_rank;
	if (rank != 0) {
		code = MPI_Send(&rank, 1, MPI_INT, root, 0, MPI_COMM_WORLD);
		printf_s("Rank %d, code %d, send: %d", rank, code, rank);
	} else {
		for (int i = 1; i < size; i++) {
			code = MPI_Recv(&recv_rank, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			printf_s("Rank %d, code %d, recv: %d\n", rank, code, recv_rank);
			printf_s("Rank %d, code %d, MPI_ERROR %d, MPI_SOURCE %d, MPI_TAG %d\n",
				rank, code, status.MPI_ERROR, status.MPI_SOURCE, status.MPI_TAG);

		}
	}
}

void sendrecv_example() {
	int root = 0;
	int size, rank, code, prev, next;
	code = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	code = MPI_Comm_size(MPI_COMM_WORLD, &size);
	if (rank == root) {
		printf_s("\n---= sendrecv_example() =---\n");
	}

	// for debug only
	fflush(stdout);
	MPI_Barrier(MPI_COMM_WORLD);

	int recv_buf[2];
	MPI_Status status1;
	MPI_Status status2;
	prev = rank - 1;
	next = rank + 1;
	if (rank == 0) {
		prev = size - 1;
	}
	if (rank == size - 1) {
		next = 0;
	}
	MPI_Sendrecv(&rank, 1, MPI_INT, prev, 6, &recv_buf[0], 1, MPI_INT, next, 6, MPI_COMM_WORLD, &status2);
	MPI_Sendrecv(&rank, 1, MPI_INT, next, 5, &recv_buf[1], 1, MPI_INT, prev, 5, MPI_COMM_WORLD, &status1);
	printf_s("Rank %d, code %d, prev: %d, next: %d\n", rank, code, recv_buf[0], recv_buf[1]);
}