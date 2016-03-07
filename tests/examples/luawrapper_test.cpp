#include <iostream>
#include <vector>
#include "Core/luawrapper.h"

using fvec = std::vector<float>;
LUAPP_USERDATA(fvec, "float_array")

fvec eCreateVector(size_t size) {
    return fvec(size);
}

void eDestroyVector(fvec& ref) {
    ref.~vector();
}

void eWriteNumber(fvec& vec, size_t index, float value) {
    vec.at(index) = value;
}

lua::Retval initializeVector(lua::Context& ctx) {
    ctx.mt<fvec>() = lua::Table::records(ctx,
        "__index",      static_cast<float& (fvec::*)(size_t)>(&fvec::at),
        "__newindex",   eWriteNumber,
        "__len",        fvec::size,
        "__gc",         eDestroyVector
    );
    ctx.global["create_float_array"] = eCreateVector;
    return ctx.ret();
}

void interpretLine(lua::State& state, const std::string& line) {
  try {
    state.runString(line);
  } catch(std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}
void interpretStream(lua::State& state, std::istream& in) {
  std::string currentLine;
  while(!in.eof()){
    getline(in, currentLine);
    interpretLine(state, currentLine);
  }
}



int main(int argc, char** argv) {
    lua::State state;

    state.call(lua::mkcf<initializeVector>);
    interpretStream(state, std::cin);

    state.runFile("res/lua_run.lua");

    char exit;
    std::cin >> exit;

    return 0;
}
