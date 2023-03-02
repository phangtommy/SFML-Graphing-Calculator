#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;

#include "includes/animate/animate.h"

// // FOR WINDOWS (linker problem on SFML)
// #include "includes/animate/constant.h"
// #include "includes/animate/graph_info.h"
// #include "includes/animate/sidebar.cpp"
// #include "includes/animate/animate.cpp"
// #include "includes/animate/system.cpp"
// #include "includes/animate/graph.cpp"
// #include "includes/animate/plot.cpp"
// #include "includes/animate/coordinate_translator.cpp"
// #include "includes/animate/texthistory.cpp"

// #include "includes/shunting_yard/shunting_yard.cpp"
// #include "includes/rpn/rpn.cpp"
// #include "includes/token/token.cpp"
// #include "includes/token/rightparen.cpp"
// #include "includes/token/operator.cpp"
// #include "includes/token/leftparen.cpp"
// #include "includes/token/integer.cpp"
// #include "includes/token/function.cpp"
// #include "includes/token/constants.h"

int main()
{
    animate calc;
    calc.run();
    return 0;
}
