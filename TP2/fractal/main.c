#include <stdlib.h>
#include "fractal.h"
#include "sg.h"

#define SIZE_DEFAULT 640

int main(void) {
    sg_open(SIZE_DEFAULT, SIZE_DEFAULT, BLACK, WHITE, "Recursive graphs");

    if (fitted_squares("Fitted squares", SIZE_DEFAULT, 24) == 0
        && koch_curve("Koch curve", SIZE_DEFAULT, 9) == 0
        && sierpinski_triangle("Sierpinski triangle", SIZE_DEFAULT, 10) == 0
        && pythagoras_tree("Pythagoras tree", SIZE_DEFAULT, 10) == 0){
    }

    sg_close();
    return EXIT_SUCCESS;
}
