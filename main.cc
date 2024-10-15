// main.cpp
#include "PPMWriter.hh"

int main() {
    PPMWriter ppm{"..\\input.txt", "output.ppm"};
    ppm.generate();
}
