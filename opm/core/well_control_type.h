/*
  Copyright 2012 SINTEF ICT, Applied Mathematics.

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


#ifndef OPM_WELL_CONTROL_TYPE_H_INCLUDED
#define OPM_WELL_CONTROL_TYPE_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


enum WellControlType  {
    BHP,              /**< Well constrained by BHP target */
    RESERVOIR_RATE,   /**< Well constrained by reservoir volume flow rate */
    SURFACE_RATE      /**< Well constrained by surface volume flow rate */
};


#ifdef __cplusplus
}
#endif

#endif /* OPM_WELL_CONTROL_TYPE_H_INCLUDED */
