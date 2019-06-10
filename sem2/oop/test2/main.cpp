#include <iostream>
#include "Person.h"
#include "Controller.h"
#include "UI.h"

int main() {
    Person p{"Mary"};
    Controller c{p};
    UI ui{c};

    ui.loop();

    return 0;
}