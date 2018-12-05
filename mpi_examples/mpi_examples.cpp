// mpi_examples.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <mpi.h>
#include <stdio.h>
#include <string>
#include "send_recv.h"
#include "arrayutils.h"
#include "reduce_example.h"
#include "topology_example.h"

using namespace std;

const char* i2s(int i) {
	const int bufsize = 11;
	string *s = new string();
	char *buf = new char[bufsize];
	sprintf_s(buf, bufsize, "%d", i);
	s->append(buf);
	return s->c_str();
}

int main(int argc, char *argv[]) {
	string *msg = new string();
	// Code without MPI
	MPI_Init(&argc, &argv);
	// Code with MPI
	int size, rank, code;
	code = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	code = MPI_Comm_size(MPI_COMM_WORLD, &size);
	if (rank == 0) {
		printf_s("Rank %d, MPI_COMM_WORLD size %d\n", rank, size);
	}

	// ======================================
	// For debbug
	// 1. set breakpoints
	// 2. run in debbug mode
	// 3. attach to processes 
	// 4. switch to mpiexec console and press enter
	// 5. switch to Visual Studio ...
	
	if (rank == 0) {
		getchar();
	}

	// ======================================
	// Debug only
	// wait while all processes call it
	MPI_Barrier(MPI_COMM_WORLD);
	// ======================================

	// call examples
	sendrecv_example();
	
	// Debug only
	MPI_Barrier(MPI_COMM_WORLD);

	reduce_example();
	
	// Debug only
	fflush(stdout);
	MPI_Barrier(MPI_COMM_WORLD);
	
	comm_cart_example();

	// Debug only
	fflush(stdout);
	MPI_Barrier(MPI_COMM_WORLD);

	comm_circle_example();
	
	// Debug only
	fflush(stdout);
	MPI_Barrier(MPI_COMM_WORLD);

	// ======================================

	MPI_Finalize();
	// Code without MPI
	return 0;
}

