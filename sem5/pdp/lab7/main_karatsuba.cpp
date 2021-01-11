#include <iostream>
#include "utils.h"
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#import "karatsuba_polynomial_multiplication.h"

namespace mpi = boost::mpi;

int main() {
    Polynomial p0 = getRandomPolynomial(12, 1, 60);
    Polynomial p1 = getRandomPolynomial(12, 1, 60);
    Polynomial result;

    mpi::environment env;
    mpi::communicator comm_world;
    int numWorkers = comm_world.size() - 1;

    if (numWorkers != 3) comm_world.abort(EXIT_FAILURE);

    if (comm_world.rank() == 0) {
        multiplyKaratsubaParallelMainEntrypoint(p0, p1, comm_world);
    }
    else {
        multiplyKaratsubaWorkerEntrypoint(comm_world);
    }
}
