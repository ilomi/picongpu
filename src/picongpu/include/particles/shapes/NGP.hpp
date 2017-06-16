/* Copyright 2013-2017 Axel Huebl, Heiko Burau, Rene Widera
 *
 * This file is part of PIConGPU.
 *
 * PIConGPU is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PIConGPU is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PIConGPU.
 * If not, see <http://www.gnu.org/licenses/>.
 */


#pragma once

#include "simulation_defines.hpp"

namespace picongpu
{
namespace particles
{
namespace shapes
{

    namespace shared_NGP
    {

        struct NGP
        {
            /**
             * width of the support of this form_factor. This is the area where the function
             * is non-zero.
             */
            static constexpr int support = 1;
        };

    } // namespace shared_NGP

    struct NGP : public shared_NGP::NGP
    {

        struct ChargeAssignment : public shared_NGP::NGP
        {

            HDINLINE float_X operator()(const float_X x)
            {
                /*       -
                 *       |  1               if -1/2<=x<1/2
                 * W(x)=<|
                 *       |  0               otherwise
                 *       -
                 */

                const bool below_half = ( float_X(-0.5) <= x &&
                                                           x < float_X(0.5) );

                return float_X(below_half);
            }
        };

        struct ChargeAssignmentOnSupport : public shared_NGP::NGP
        {

            /** form factor of this particle shape.
             * \param x has to be within [-support/2, support/2)
             */
            HDINLINE float_X operator()(const float_X)
            {
                /*
                 * W(x)=1
                 */
                return float_X(1.0);
            }

        };

    };

} // namespace shapes
} // namespace particles
} // namespace picongpu