/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef INTERACTIONINTEGRALSM_H
#define INTERACTIONINTEGRALSM_H

#include "ElementIntegralPostprocessor.h"
#include "CrackFrontDefinition.h"
#include "SymmTensor.h"

// Forward Declarations
class InteractionIntegralSM;
class RankTwoTensor;

template <>
InputParameters validParams<InteractionIntegralSM>();

/**
 * This postprocessor computes the Interaction Integral
 *
 */
class InteractionIntegralSM : public ElementIntegralPostprocessor
{
public:
  InteractionIntegralSM(const InputParameters & parameters);

  virtual Real getValue();

protected:
  virtual void initialSetup();
  virtual Real computeQpIntegral();
  virtual Real computeIntegral();
  const CrackFrontDefinition * const _crack_front_definition;
  bool _has_crack_front_point_index;
  const unsigned int _crack_front_point_index;
  bool _treat_as_2d;
  const MaterialProperty<SymmTensor> & _stress;
  const MaterialProperty<SymmTensor> & _strain;
  const VariableGradient & _grad_disp_x;
  const VariableGradient & _grad_disp_y;
  const VariableGradient & _grad_disp_z;
  const bool _has_temp;
  const VariableGradient & _grad_temp;
  std::string _aux_stress_name;
  const MaterialProperty<RankTwoTensor> & _aux_stress;
  std::string _aux_grad_disp_name;
  const MaterialProperty<RankTwoTensor> & _aux_grad_disp;
  const MaterialProperty<Real> * _current_instantaneous_thermal_expansion_coef;
  Real _K_factor;
  bool _has_symmetry_plane;
  bool _t_stress;
  Real _poissons_ratio;
  unsigned int _ring_index;
  unsigned int _ring_first;
  MooseEnum _q_function_type;
  std::vector<Real> _q_curr_elem;
  const std::vector<std::vector<Real>> * _phi_curr_elem;
  const std::vector<std::vector<RealGradient>> * _dphi_curr_elem;
};

#endif // INTERACTIONINTEGRALSM_H
