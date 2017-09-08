###########################################################
# This is a simple test of the CoupledTimeDerivative kernel.
# The expected solution for the variable v is
# v(x) = 1/2 * (x^2 + x)
###########################################################

[Mesh]
  type = GeneratedMesh
  nx = 5
  ny = 5
  dim = 2
[]

[Variables]
  [./u]
  [../]
  [./v]
  [../]
[]

[Kernels]
  [./time_u]
    type = TimeDerivative
    variable = u
  [../]
  [./fn_u]
    type = UserForcingFunction
    variable = u
    function = ffn
  [../]
  [./time_v]
    type = CoupledTimeDerivative
    variable = v
    v = u
  [../]
  [./diff_v]
    type = Diffusion
    variable = v
  [../]
[]

[Functions]
  [./ffn]
    type = ParsedFunction
    value = '1'
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = v
    boundary = 'left'
    value = 0
  [../]
  [./right]
    type = DirichletBC
    variable = v
    boundary = 'right'
    value = 1
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 1
  solve_type = 'NEWTON'
[]

[Outputs]
  exodus = true
[]
