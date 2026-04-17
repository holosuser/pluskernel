#include "pinit.hpp"
#include "../../lib.hpp"
#include "../psh/psh.hpp"

extern "C" void init(){
    clearscreen();
    startlogo();
    print("Pluskernel: to learn how to use the system, type help.\n");
    inshell();
    while (1){}
}
