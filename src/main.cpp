#include "main.hpp"


int main(int argc, char const *argv[]) {
    Geometry g;
    g.generateLUTs();
    std::vector<Module> modules = g.getData(); 
    for (int i = 0; i < LINK_NUMBER; i++) {
        LinkGenerator link_gen;
        LinkFormatter link_formatter(link_gen.run());
        StubFormatter stub_formatter(link_formatter.run(), i);
        CoordinateCorrector coordinate_corrector(stub_formatter.run(modules));
        coordinate_corrector.run();
    }

    

    return 0;
}
