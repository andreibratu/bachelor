#include <iostream>
#include <mpl.hpp>
#include "DSMSupervisor.h"
#include "DSMListener.h"
#include <unistd.h>

int main() {
    srand(0); // NOLINT(cert-msc51-cpp)
    const mpl::communicator &comm_world(mpl::environment::comm_world());

    if(comm_world.size() != 3) return 1;

    if(comm_world.rank() == 0) {
        DSMSupervisor<int> supervisor{comm_world, 2};
    }
    else if (comm_world.rank() == 1) {
        DSMListener<int> listener{comm_world};
        listener.write("foo", 5);
        for(int i = 0; i < 1000; i++) {
            listener.write("foo", rand() % 1000); // NOLINT(cert-msc50-cpp)
            sleep(1);
        }
    } else {
        DSMListener<int> listener{comm_world};
        sleep(10);
        listener.subscribe("foo");
    }
}
