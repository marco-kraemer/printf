#include "ft_printf.h"

int main(void)
{
        char c = 'M';
        char *s  = "SANTOS";
        int     i = 6524;

        printf("\n");
        ft_printf("FT_PRINTF: %-*s E %.*d E %-*c E %*X E %0*X$\n", 10, s , 10, i, 15, c, 15, i, 10,i);
           printf("   PRINTF: %-*s E %.*d E %-*c E %*X E %0*X$\n", 10, s , 10, i, 15, c, 15, i, 10,i);
        printf("\n");
}