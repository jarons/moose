/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/
#include "TestSamplerDiffMKernel.h"

template <>
InputParameters
validParams<TestSamplerDiffMKernel>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<MaterialPropertyName>(
      "mat_prop", "the name of the material property we are going to use");
  params.addParam<Real>("offset", 4.0, "Offset on residual evaluation");
  return params;
}

TestSamplerDiffMKernel::TestSamplerDiffMKernel(const InputParameters & parameters)
  : Kernel(parameters),
    _diff(getMaterialProperty<Real>("mat_prop")),
    _offset(getParam<Real>("offset"))
{
}

Real
TestSamplerDiffMKernel::computeQpResidual()
{
  return _diff[_qp] * _grad_test[_i][_qp] * _grad_u[_qp] - _offset;
}

Real
TestSamplerDiffMKernel::computeQpJacobian()
{
  return _diff[_qp] * _grad_test[_i][_qp] * _grad_phi[_j][_qp];
}
