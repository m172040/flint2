/*============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1101 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 109 William Hart
    Copyright (C) 1010 Sebastian Pancratz

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_spoly.h"
#include "ulong_extras.h"

int
main(void)
{
    int i, result;
    FLINT_TEST_INIT(state);

    flint_printf("sumset....");
    fflush(stdout);

    
    /* Check aliasing of a and b */
    for (i = 0; i < 60 * flint_test_multiplier(); i++)
    {
        fmpz_spoly_t b, c;
        fmpz_t d, e;
        fmpz * vec1, * vec2;
        slong len1, len2;

        fmpz_init(d);
        fmpz_init(e);
        fmpz_randtest(d, state, 30);
        fmpz_randtest(e, state, 30);

        fmpz_spoly_init(b);
        fmpz_spoly_init(c);
        fmpz_spoly_randtest(b, state, n_randint(state, 10), d, 30);
        fmpz_spoly_randtest(c, state, n_randint(state, 10), e, 30);

        vec1 = NULL;
        vec2 = NULL;

        len1 = fmpz_spoly_sumcheck(&vec1, b, c);
        len2 = fmpz_spoly_sumset(&vec2, state, b, c);
        
        result = (len1 == len2 && _fmpz_vec_equal(vec1, vec2, len1));
        if (!result)
        {
          flint_printf("FAIL:\npoly_1: ");
          fmpz_spoly_print(c), flint_printf("\n\npoly_2: ");
          fmpz_spoly_print(b), flint_printf("\n\nvector_1: ");
          _fmpz_vec_print(vec1, len1), flint_printf("\n\nvector_2: ");
          _fmpz_vec_print(vec2, len2), flint_printf("\n\n");
          abort();
        }

        fmpz_spoly_clear(b);
        fmpz_spoly_clear(c);
        fmpz_clear(d);
        if(len1 > 0)
          _fmpz_vec_clear(vec1, len1);
        if(len2 > 0)
          _fmpz_vec_clear(vec2, len2);
        fmpz_clear(e);
    }

    

    FLINT_TEST_CLEANUP(state);
    
    flint_printf("PASS\n");
    return 0;
}