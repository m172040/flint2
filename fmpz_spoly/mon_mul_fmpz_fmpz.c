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

    Authored 2016 by A. Whitman Groves; US Government work in the public domain. 

******************************************************************************/

#include <gmp.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_vec.h"
#include "fmpz_spoly.h"

void
fmpz_spoly_mon_mul_fmpz_fmpz(fmpz_spoly_t res, const fmpz_spoly_t poly,
                          const fmpz_t c, const fmpz_t e)
{
    /* Either scalar or input poly is zero */
    if ((fmpz_is_zero(c)) || (poly->length == 0))
    {
        fmpz_spoly_zero(res);
    }
    else if (fmpz_is_one(c) && fmpz_is_zero(e))
    {
        fmpz_spoly_set(res, poly);
    }
    else
    {
        slong t2 = fmpz_spoly_terms(poly);
        slong i = 0;

        if (res != poly)
        {
            _fmpz_spoly_reserve(res, t2);
            
            for(i = 0; i < t2; i++)
            {
                fmpz_init(res->expons + i);
            }
        }
            
        for(i = 0; i < t2; i++)
        {
            fmpz_add(res->expons + i, poly->expons + i, e);
        }

        _fmpz_vec_scalar_mul_fmpz(res->coeffs, poly->coeffs, t2, c);

        _fmpz_spoly_set_length(res, t2);
    }
}