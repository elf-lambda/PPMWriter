// main.cpp
#include "PPMWriter.hh"

int main() {
    PPMWriter ppm{R"(C:\Users\elff\CLionProjects\learn01\input.txt)", "output.ppm"};
    ppm.generate();
}
