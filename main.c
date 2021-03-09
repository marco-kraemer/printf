#include "ft_printf.h"

int main(void)
{
        char c = 'M';
        char *s  = "SANTOS";
        int     i = 3231321;

        printf("\n");
        ft_printf("FT_PRINTF: %-*s E %p E %-*c E %*x E %X$\n", 10, s , &i, 15, c, 15, i,i);
           printf("   PRINTF: %-*s E %p E %-*c E %*x E %X$\n", 10, s , &i, 15, c, 15, i,i);
        printf("\n");
}