# Tests the Jacobian when no secondary species are present

[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 2
  ny = 2
[]

[Variables]
  [./a]
    order = FIRST
    family = LAGRANGE
  [../]
  [./b]
    order = FIRST
    family = LAGRANGE
  [../]
  [./pressure]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[ICs]
  [./pressure]
    type = RandomIC
    variable = pressure
    max = 10
    min = 1
  [../]
  [./a]
    type = RandomIC
    variable = a
    max = 1
    min = 0
  [../]
  [./b]
    type = RandomIC
    variable = b
    max = 1
    min = 0
  [../]
[]

[Kernels]
  [./a_ie]
    type = PrimaryTimeDerivative
    variable = a
  [../]
  [./a_diff]
    type = PrimaryDiffusion
    variable = a
  [../]
  [./a_conv]
    type = PrimaryConvection
    variable = a
    p = pressure
  [../]
  [./b_ie]
    type = PrimaryTimeDerivative
    variable = b
  [../]
  [./b_diff]
    type = PrimaryDiffusion
    variable = b
  [../]
  [./b_conv]
    type = PrimaryConvection
    variable = b
    p = pressure
  [../]
  [./pressure]
    type = Diffusion
    variable = pressure
  [../]
[]

[Materials]
  [./porous]
    type = GenericConstantMaterial
    prop_names = 'diffusivity conductivity porosity'
    prop_values = '1e-4 1e-4 0.2'
  [../]
[]

[Executioner]
  type = Transient
  solve_type = NEWTON
  end_time = 1
[]

[Outputs]
  print_perf_log = true
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]
