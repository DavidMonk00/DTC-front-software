#include "main.hpp"

void recordStubs(std::vector<std::array<Stub*, PAYLOAD_WIDTH> > all_stubs) {
    std::ofstream ofs(path + "output.csv");
    // std::ofstream f(path + "output.stubs", std::ofstream::binary);
    ofs << "r" << "," << "phi" << "," << "z" << std::endl;
    for (auto link : all_stubs) {
        StubWriter sw(path + "output.stubs");
        sw.writeStubs(link);
        for (auto stub : link) {
            ofs << stub->getPayload().r << "," << stub->getPayload().phi << "," << stub->getPayload().z << std::endl;
            // stub->writeRaw(f);
        }
    }
    ofs.close();
    // f.close();
}

std::vector<Stub> readStubFile(std::string filename) {
    std::vector<Stub> stubs;
    Stub s;
    std::ifstream file(filename, std::ifstream::binary);
    while (file.read((char*)&s, sizeof(s))) {
        stubs.push_back(s);
    }
    file.close();
    return stubs;
}


int main(int argc, char const *argv[]) {
    Geometry g;
    g.generateModuleLUTs();
    g.generateCorrectionLUTs();
    std::vector<std::array<Stub*, PAYLOAD_WIDTH> > all_stubs;
    std::vector<Module> modules = g.getData(); 
    for (int i = 0; i < LINK_NUMBER; i++) {
        LinkGenerator link_gen;
        LinkFormatter link_formatter(link_gen.run());
        StubFormatter stub_formatter(link_formatter.run(), i);
        std::array<Stub*, PAYLOAD_WIDTH> stubs = stub_formatter.run(modules);
        CoordinateCorrector coordinate_corrector(stubs);
        all_stubs.push_back(coordinate_corrector.run());
    }
    recordStubs(all_stubs);
    for (auto i : StubReader(path + "output.stubs")) {
       i.print(); 
    }
    return 0;
}
