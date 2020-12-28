#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
// Include below is actually required
#include <boost/serialization/utility.hpp>
#include <iostream>
#include "DSMSupervisor.h"
#include "DSMListener.h"
#include <unistd.h>
#include <future>

namespace mpi = boost::mpi;

int main() {
    mpi::environment env;
    mpi::communicator comm_world;
    srand(0); // NOLINT(cert-msc51-cpp)

    if(comm_world.size() != 3 && comm_world.rank() == 0) {
        std::cout << "Expected process count to be equal to 3, found " << comm_world.size() << '\n';
        return 1;
    }

    if(comm_world.rank() == 0) {
        DSMSupervisor supervisor{2};
        while(!supervisor.finished);
    }
    else if (comm_world.rank() == 1) {
        sleep(10);
        DSMListener listener;
        listener.write("foo", 5);
        for(int i = 0; i < 50; i++) {
            listener.update("foo", rand() % 1000); // NOLINT(cert-msc50-cpp)
            sleep(5);
        }
        while (true) {}
    } else {
        sleep(3);
//        DSMListener listener;
//        listener.subscribe("foo");
        while (true) {}
    }
}
