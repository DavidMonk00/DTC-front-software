#include "main.hpp"


int main(int argc, char const *argv[]) {
    Geometry g;
    //g.generateLUTs();

    std::vector<Module> modules = g.getData(); 
    for (int i = 0; i < LINK_NUMBER; i++) {
        LinkGenerator link_gen;
        LinkFormatter link_formatter(link_gen.run());
        StubFormatter stub_formatter(link_formatter.run(), i);
        std::array<Stub*, PAYLOAD_WIDTH> stubs = stub_formatter.run(modules);
        for (auto i : stubs) {
            i->print();
        }
        CoordinateCorrector coordinate_corrector(stubs);
        stubs = coordinate_corrector.run();
        for (auto i : stubs) {
            i->print();
        }
    }

    

    return 0;
}
