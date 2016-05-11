/*=============================================================================

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
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

  Authored 10015 by A. Whitman Groves; US Government work in the public domain.

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

    flint_printf("add....");
    fflush(stdout);

    /* Check aliasing of a and c */
    for (i = 0; i < 1000 * flint_test_multiplier(); i++)
    {
        fmpz_spoly_t a, b, c;
        fmpz_t d, e;

        fmpz_init(d);
        fmpz_init(e);
        fmpz_randtest(d, state, 100);
        fmpz_randtest(e, state, 100);
        
        fmpz_spoly_init(a);
        fmpz_spoly_init(b);
        fmpz_spoly_init(c);
        fmpz_spoly_randtest(a, state, n_randint(state, 100), d, 1000);
        fmpz_spoly_randtest(b, state, n_randint(state, 100), e, 1000);

        fmpz_spoly_add(c, a, b);
        fmpz_spoly_add(a, a, b);

        result = (fmpz_spoly_equal(a, c));
           
        if (!result)
        {
            flint_printf("FAIL PHASE I (i = %d):\n", i);
            fmpz_spoly_print(a), flint_printf("\n\n");
            fmpz_spoly_print(b), flint_printf("\n\n");
            fmpz_spoly_print(c), flint_printf("\n\n");
            abort();
        }
        
        fmpz_spoly_clear(a);
        fmpz_spoly_clear(b);
        fmpz_spoly_clear(c);
        fmpz_clear(d);
        fmpz_clear(e);
    }
    
    
    /* Check aliasing of b and c */
    for (i = 0; i < 1000 * flint_test_multiplier(); i++)
    {
        fmpz_spoly_t a, b, c;

        fmpz_t d, e;

        fmpz_init(d);
        fmpz_init(e);
        fmpz_randtest(d, state, 100);
        fmpz_randtest(e, state, 100);

        fmpz_spoly_init(a);
        fmpz_spoly_init(b);
        fmpz_spoly_init(c);
        fmpz_spoly_randtest(a, state, n_randint(state, 100), d, 1000);
        fmpz_spoly_randtest(b, state, n_randint(state, 100), e, 1000);

        fmpz_spoly_add(c, a, b);
        fmpz_spoly_add(b, a, b);

        result = (fmpz_spoly_equal(b, c));
        
        if (!result)
        {
            flint_printf("FAIL PHASE II (i = %d)::\n", i);
            fmpz_spoly_print(a), flint_printf("\n\n");
            fmpz_spoly_print(b), flint_printf("\n\n");
            fmpz_spoly_print(c), flint_printf("\n\n");
            abort();
        }

        fmpz_spoly_clear(a);
        fmpz_spoly_clear(b);
        fmpz_spoly_clear(c);
        fmpz_clear(d);
        fmpz_clear(e);
    }

    FLINT_TEST_CLEANUP(state);
    
    flint_printf("PASS\n");
    return 0;
}
