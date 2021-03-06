#pragma once

#include "../../types.hpp"
#include "../../utilities/evaluations.hpp"

#include "../bases.hpp"


namespace waveblocks
{
  namespace potentials
  {
    namespace modules
    {
      namespace hessian
      {
        /**
       * \brief Abstract class for potential evaluation
       *
       * A matrix potential inheriting an implementation of this module
       * can evaluate its hessian in one or multiple points
       *
       * This makes use of the CRTPattern
       *
       * \tparam Subtype The type extending this interface (used for static polymorphism)
       * \tparam Basis
       * Which basis (bases::Eigen or bases::Canonical) the potential is given in
       */
        template <class Subtype, class Basis>
        struct Abstract {
          using Self = Abstract<Subtype, Basis>;
          IMPORT_TYPES_FROM( Basis)


          hessian_evaluation_type evaluate_hessian_at( const argument_type &arg ) const {
            return static_cast<const Subtype*>(this)->evaluate_hessian_at_implementation( arg );
          }

          template < template <typename...> class grid_in = std::vector,
                   template <typename...> class grid_out = grid_in >
          grid_out<hessian_evaluation_type> evaluate_hessian(
            const grid_in<argument_type > &args ) const {
            return utilities::evaluate_function_in_grid < argument_type,
                   hessian_evaluation_type,
                   grid_in,
                   grid_out,
                   function_t > (
                     std::bind( &Self::evaluate_hessian_at, this, std::placeholders::_1 ),
                     args );
          }

        };

        /**
         * \brief Helper class for easier template specialization
         *
         * This wraps concrete implementations of the Abstract base class
         *
         * \tparam Basis
         * Which basis (bases::Eigen or bases::Canonical) the potential is given in
         */
        template <class Basis>
        struct Standard : Abstract<Standard<Basis>, Basis> {

                IMPORT_TYPES_FROM( Basis)

              private:
                hessian_type hessian;

              public:
                Standard(
                           hessian_type hessian )
                  :  hessian( hessian ){}

              public:


                hessian_evaluation_type evaluate_hessian_at_implementation(
                  const argument_type &arg ) const {
                  return utilities::FunctionMatrixEvaluator< Basis::number_of_levels,
                    Basis::number_of_columns,
                         GMatrix,
                         argument_type,
                         hessian_return_type,
                         function_t >::apply( hessian, arg );
                }
            };



      }

      template <class Basis>
      using Hessian = hessian::Standard<Basis>;
    }
  }
}
