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
        sleep(10);
        listener.write("foo", 5);
        sleep(4);
        for(int i = 0; i < 5; i++) {
            listener.update("foo", rand() % 1000); // NOLINT(cert-msc50-cpp)
            sleep(4);
        }
        std::cout << "RANK 1 DONE\n";
        while (true) {}
    } else {
        sleep(10);
        DSMListener listener;
//        Delayed start
        sleep(10);
        listener.subscribe("foo");
        while (true) {}
    }
}
