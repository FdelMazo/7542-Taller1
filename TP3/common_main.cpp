#include <iostream>
#include "server_HoneyPot.h"
int main(int argc, char *argv[]) {
    HoneyPot hp("config.cfg");
    std::string buff, arg;
    while (true) {
        std::cin >> buff >> arg;
        std::cout << hp.runCommand(buff, arg) << "\n";
    }
    return 0;
}
