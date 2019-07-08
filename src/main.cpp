#include "main.hpp"


int main(int argc, char const *argv[]) {
    for (int i = 0; i < LINK_NUMBER; i++) {
        LinkGenerator link_gen;
        LinkFormatter link_formatter(link_gen.run());
        StubFormatter stub_formatter(link_formatter.run(), i);
        CoordinateCorrector coordinate_corrector(stub_formatter.run());
        coordinate_corrector.run();
    }

    Geometry g;
    g.getData();
    g.getModules()[0].print();

    return 0;
}
