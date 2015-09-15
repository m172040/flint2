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

    Copyright (C) 2009 William Hart

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_sparse.h"
#include "ulong_extras.h"

int
main(void)
{
    int i, result;
    FLINT_TEST_INIT(state);

    flint_printf("sub....");
    fflush(stdout);

    

    /* Check a - b = a + neg(b) */
    for (i = 0; i < 1000 * flint_test_multiplier(); i++)
    {
        fmpz_sparse_t a, b, c, d;
        fmpz_t e, f;

        fmpz_init(e);
        fmpz_init(f);
        fmpz_randtest_not_zero(e, state, 100);
        fmpz_randtest_not_zero(f, state, 100);

        fmpz_sparse_init(a);
        fmpz_sparse_init(b);
        fmpz_sparse_init(c);
        fmpz_sparse_init(d);
        fmpz_sparse_randtest(a, state, n_randint(state, 100), e, 200);
        fmpz_sparse_randtest(b, state, n_randint(state, 100), f, 200);

        fmpz_sparse_sub(c, a, b);
        fmpz_sparse_neg(b, b);
        fmpz_sparse_add(d, a, b);

        result = (fmpz_sparse_equal(c, d));
        if (!result)
        {
            flint_printf("FAIL:\n");
            fmpz_sparse_print(a), flint_printf("\n\n");
            fmpz_sparse_print(b), flint_printf("\n\n");
            fmpz_sparse_print(c), flint_printf("\n\n");
            fmpz_sparse_print(d), flint_printf("\n\n");
            abort();
        }

        fmpz_sparse_clear(a);
        fmpz_sparse_clear(b);
        fmpz_sparse_clear(c);
        fmpz_sparse_clear(d);
        fmpz_clear(e);
        fmpz_clear(f);
    }

    /* Check aliasing of a and c */
    for (i = 0; i < 1000 * flint_test_multiplier(); i++)
    {
        fmpz_sparse_t a, b, c;
        fmpz_t e, f;

        fmpz_init(e);
        fmpz_init(f);
        fmpz_randtest_not_zero(e, state, 100);
        fmpz_randtest_not_zero(f, state, 100);

        fmpz_sparse_init(a);
        fmpz_sparse_init(b);
        fmpz_sparse_init(c);
        fmpz_sparse_randtest(a, state, n_randint(state, 100), e, 200);
        fmpz_sparse_randtest(b, state, n_randint(state, 100), f, 200);

        fmpz_sparse_sub(c, a, b);
        fmpz_sparse_sub(a, a, b);

        result = (fmpz_sparse_equal(a, c));
        if (!result)
        {
            flint_printf("FAIL:\n");
            fmpz_sparse_print(a), flint_printf("\n\n");
            fmpz_sparse_print(b), flint_printf("\n\n");
            fmpz_sparse_print(c), flint_printf("\n\n");
            abort();
        }

        fmpz_sparse_clear(a);
        fmpz_sparse_clear(b);
        fmpz_sparse_clear(c);
        fmpz_clear(e);
        fmpz_clear(f);
    }

    /* Check aliasing of b and c */
    for (i = 0; i < 1000 * flint_test_multiplier(); i++)
    {
        fmpz_sparse_t a, b, c;
        fmpz_t e, f;

        fmpz_init(e);
        fmpz_init(f);
        fmpz_randtest_not_zero(e, state, 100);
        fmpz_randtest_not_zero(f, state, 100);
        
        fmpz_sparse_init(a);
        fmpz_sparse_init(b);
        fmpz_sparse_init(c);
        fmpz_sparse_randtest(a, state, n_randint(state, 100), e, 200);
        fmpz_sparse_randtest(b, state, n_randint(state, 100), f, 200);

        fmpz_sparse_sub(c, a, b);
        fmpz_sparse_sub(b, a, b);

        result = (fmpz_sparse_equal(b, c));
        if (!result)
        {
            flint_printf("FAIL:\n");
            fmpz_sparse_print(a), flint_printf("\n\n");
            fmpz_sparse_print(b), flint_printf("\n\n");
            fmpz_sparse_print(c), flint_printf("\n\n");
            abort();
        }

        fmpz_sparse_clear(a);
        fmpz_sparse_clear(b);
        fmpz_sparse_clear(c);
        fmpz_clear(e);
        fmpz_clear(f);
    }

    FLINT_TEST_CLEANUP(state);
    
    flint_printf("PASS\n");
    return 0;
}
