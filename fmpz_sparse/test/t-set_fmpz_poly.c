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

    Copyright (C) 2010 Sebastian Pancratz

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_poly.h"
#include "fmpz_sparse.h"
#include "ulong_extras.h"

int
main(void)
{
    int i, result;
    FLINT_TEST_INIT(state);

    flint_printf("set_fmpz_poly....");
    fflush(stdout);

    

    /* equal polynomials */
    for (i = 0; i < 1000 * flint_test_multiplier(); i++)
    {
        fmpz_sparse_t a, b;
        fmpz_poly_t n;

        fmpz_sparse_init(a);
        fmpz_sparse_init(b);

        fmpz_poly_init(n);

        fmpz_poly_randtest(n, state, n_randint(state, 100), 200);
        fmpz_sparse_set_fmpz_poly(a, n);
        fmpz_sparse_set(b, a);

        result = (fmpz_sparse_equal(a, b));

        if (!result)
        {
            flint_printf("FAIL:\n");
            flint_printf("n = "), fmpz_poly_print(n), flint_printf("\n\n");
            flint_printf("a = "), fmpz_sparse_print(a), flint_printf("\n\n");
            flint_printf("b = "), fmpz_sparse_print(b), flint_printf("\n\n");
            abort();
        }

        fmpz_sparse_clear(a);
        fmpz_sparse_clear(b);
        fmpz_poly_clear(n);
    }

    for (i = 0; i < 1000 * flint_test_multiplier(); i++)
    {
        fmpz_sparse_t a, b;
        fmpz_poly_t m, n;

        fmpz_poly_init(m);
        fmpz_poly_init(n);

        fmpz_sparse_init(a);
        fmpz_sparse_init(b);

        fmpz_poly_randtest(m, state, n_randint(state, 100), 200);
        fmpz_poly_randtest(n, state, n_randint(state, 100), 200);
        while (fmpz_poly_equal(m, n))
            fmpz_poly_randtest(n, state, n_randint(state, 100), 200);
        fmpz_sparse_set_fmpz_poly(a, m);
        fmpz_sparse_set_fmpz_poly(b, n);

        result = (!fmpz_sparse_equal(a, b));
        if (!result)
        {
            flint_printf("FAIL:\n");
            flint_printf("m = "), fmpz_poly_print(m), flint_printf("\n\n");
            flint_printf("n = "), fmpz_poly_print(n), flint_printf("\n\n");
            flint_printf("a = "), fmpz_sparse_print(a), flint_printf("\n\n");
            flint_printf("b = "), fmpz_sparse_print(b), flint_printf("\n\n");
            abort();
        }

        fmpz_sparse_clear(a);
        fmpz_sparse_clear(b);
        fmpz_poly_clear(m);
        fmpz_poly_clear(n);
    }

    FLINT_TEST_CLEANUP(state);
    
    flint_printf("PASS\n");
    return 0;
}
