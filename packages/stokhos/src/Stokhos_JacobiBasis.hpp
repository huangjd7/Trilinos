// @HEADER
// *****************************************************************************
//                           Stokhos Package
//
// Copyright 2009 NTESS and the Stokhos contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

#ifndef STOKHOS_JACOBIBASIS_HPP
#define STOKHOS_JACOBIBASIS_HPP

#include "Stokhos_RecurrenceBasis.hpp"

namespace Stokhos {

  //! Jacobi polynomial basis
  /*!
   * Jacobi polynomials are defined by the recurrence relationship
   * \f[
   *   A_k \psi_{k+1}(x) = \left(B_k-x C_k\right)
   * \psi_k(x) - D_k \psi_{k-1}(x)
   * \f]
   * with \f$\psi_{-1}(x) = 0\f$ and \f$\psi_{0}(x) = 1\f$
   * where
   * \f[
   * A_n = 2 (n+1)(n+\alpha+\beta+1)(2 n + \alpha+\beta)
   * \f]
   * \f[
   * B_n = -(2n+\alpha+\beta+1)(\alpha^2 - \beta^2)
   * \f]
   * \f[
   * C_n = (2n+\alpha+\beta)_3
   * \f]
   * \f[
   * D_n = 2(n+\alpha)(n+\beta)(2n+\alpha+\beta+2).
   * \f]
   * In Stokhos notation we have
   * \f[ \gamma_{k+1}=1/A_{k} \f]
   * \f[ \alpha_k = B_k \f]
   * \f[ \delta_k = C_k \f]
   * \f[ \beta_k = D_k. \f]
   *
   * The corresponding 
   * density function is 
   * \f[
   *   \rho(x) = w_{\alpha_,\beta}(1-x)^\alpha (1+x)^\beta, \quad x\in[-1,1]
   * \f]
   * with 
   * \f[
   * w_{\alpha,\beta}^{-1}=\frac{2^{\alpha+\beta+1}}{\alpha+\beta+1}
   * \frac{\Gamma(\alpha+1)\Gamma(\beta+1)}{\Gamma(\alpha+\beta+1)}.
   * \f]
   * This class implements computeRecurrenceCoefficients() using the
   * above formula.
   *
   * \author Kevin Long (kevin.long@ttu.edu)
   */
  template <typename ordinal_type, typename value_type>
  class JacobiBasis : 
    public RecurrenceBasis<ordinal_type, value_type> {
  public:

    //! Constructor
    /*!
     * \param p order of the basis
     * \param normalize whether polynomials should be given unit norm
     */
    JacobiBasis(ordinal_type p, 
		value_type alphaIndex, 
		value_type betaIndex, bool normalize = false, 
		GrowthPolicy growth = SLOW_GROWTH);

    //! Destructor
    ~JacobiBasis();

    //! \name Implementation of Stokhos::OneDOrthogPolyBasis methods
    //@{ 

    /*! 
     * \brief Clone this object with the option of building a higher order
     * basis.
     */
    /*!
     * This method is following the Prototype pattern (see Design Pattern's textbook).
     * The slight variation is that it allows the order of the polynomial to be modified,
     * otherwise an exact copy is formed. The use case for this is creating basis functions
     * for column indices in a spatially varying adaptive refinement context.
     */
    virtual Teuchos::RCP<OneDOrthogPolyBasis<ordinal_type,value_type> > cloneWithOrder(ordinal_type p) const;

    //@}

  protected:

    //! \name Implementation of Stokhos::RecurrenceBasis methods
    //@{ 

    //! Compute recurrence coefficients
    virtual bool
    computeRecurrenceCoefficients(ordinal_type n,
				  Teuchos::Array<value_type>& alpha,
				  Teuchos::Array<value_type>& beta,
				  Teuchos::Array<value_type>& delta,
				  Teuchos::Array<value_type>& gamma) const;

    //@}

    //! Copy constructor with specified order
    JacobiBasis(ordinal_type p, const JacobiBasis& basis);

  private:

    value_type getA(int n) const ;
    value_type getB(int n) const ;
    value_type getC(int n) const ;
    value_type getD(int n) const ;
    value_type poch3(value_type x) const ;

    // Prohibit copying
    JacobiBasis(const JacobiBasis&);

    // Prohibit Assignment
    JacobiBasis& operator=(const JacobiBasis& b);

    value_type alphaIndex_;
    value_type betaIndex_;

  }; // class JacobiBasis

} // Namespace Stokhos

// Include template definitions
#include "Stokhos_JacobiBasisImp.hpp"

#endif
