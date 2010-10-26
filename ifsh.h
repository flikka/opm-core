/*
  Copyright 2010 SINTEF ICT, Applied Mathematics.

  This file is part of the Open Porous Media project (OPM).

  OPM is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OPM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OPM.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPM_IFSH_HEADER_INCLUDED
#define OPM_IFHS_HEADER_INCLUDED

#include "grid.h"
#include "well.h"
#include "flow_bc.h"
#include "fsh_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @file Incompressible flow solver, using hybridization.
 *
 *  These functions implements assembly of a hybridized linear
 *  system for face-pressures in incompressible two-phase flow.
 *  A routine for back-substitution that computes cell pressures
 *  and face fluxes is also included.
 */

struct fsh_data;

/** Constructs incompressible hybrid flow-solver data object for a
 *  given grid and well pattern.
 *
 *  @param G The grid
 *  @param W The wells
 */
struct fsh_data *
ifsh_construct(grid_t *G, well_t *W);



/** Assembles the hybridized linear system for face pressures.
 *
 * This routine produces no output, other than changing the linear
 * system embedded in the ifsh_data object.
 * @param bc Boundary conditions.
 * @param src Per-cell source terms (volume per second). Positive
 *            values flow are sources, negative values are sinks.
 * @param Binv The cell-wise inner products to employ in
 *             assembly. This should be an array of length equal to
 *             sum_ngconn2 of the ifsh_data object. For each cell i,
 *             there are \f$n_i^2\f$ entries, giving the inner product for
 *             that cell. The inner products may for example be
 *             computed by the functions of mimetic.h.
 * @param gpress Gravity terms. This should be an array of length
 *               \f$\sum_i n_i\f$. For each cell, the \f$n_i\f$ elements
 *               corresponding to cell \f$i\f$ should be given by
 *               \f$g \cdot (f_c - c_c)\f$ where the symbols represent
 *               the gravity vector, face centroid and cell centroid.
 * @param wctrl \TODO
 * @param WI \TODO
 * @param wdp \TODO
 * @param totmob Cell-wise total mobilities to use for this assembly.
 * @param omega Cell-wise phase densities weighted by fractional flow.
 * @param h The fsh_data object to use (and whose linear system will
 *          be modified). Must already be constructed.
 */
void
ifsh_assemble(flowbc_t        *bc,
              const double    *src,
              const double    *Binv,
              const double    *gpress,
              well_control_t  *wctrl,
              const double    *WI,
              const double    *wdp,
              struct fsh_data *h);

/** Computes cell pressures, face fluxes, well pressures and well
 * fluxes from face pressures.
 *
 * @param G The grid.
 * @param h The fsh_data object. You must have called ifsh_assemble()
 *          prior to this, and solved the embedded linear system of
 *          this object before you call ifsh_press_flux().
 * @param cpress[out] Cell pressures.
 * @param fflux[out] Oriented face fluxes.
 * @param wpress[out] \TODO
 * @param wflux[out] \TODO
 */
void
ifsh_press_flux(grid_t *G,
                const double *Binv, const double *gpress,
                struct fsh_data *h,
                double *cpress, double *fflux,
                double *wpress, double *wflux);


#ifdef __cplusplus
}
#endif


#endif  /* OPM_IFSH_HEADER_INCLUDED */
