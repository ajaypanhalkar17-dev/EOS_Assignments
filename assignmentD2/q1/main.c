
#include <stdio.h>
#include "circle.h"
#include "square.h"
#include "rectangle.h"

int main(void)
{
    printf("Circle area: %.2f\n", circle_area(5));
    printf("Square area: %.2f\n", square_area(4));
    printf("Rectangle area: %.2f\n", rectangle_area(5, 3));

    return 0;
}

