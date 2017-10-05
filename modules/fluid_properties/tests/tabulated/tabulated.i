# Test thermophysical property calculations using TabulatedFluidProperties.
# Calculations for density, internal energy and enthalpy using bicubic spline
# interpolation of data generated using CO2FluidProperties.

[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 3
  xmax = 3
[]

[Variables]
  [./dummy]
  [../]
[]

[AuxVariables]
  [./pressure]
    initial_condition = 1e6
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./temperature]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./rho]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./mu]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./e]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./h]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./s]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./cv]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./cp]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./c]
    family = MONOMIAL
    order = CONSTANT
  [../]
[]

[Functions]
  [./tic]
    type = ParsedFunction
    value = if(x<1,280,if(x<2,360,500))
  [../]
[]

[ICs]
  [./t_ic]
    type = FunctionIC
    function = tic
    variable = temperature
  [../]
[]

[AuxKernels]
  [./rho]
    type = MaterialRealAux
    variable = rho
    property = density
  [../]
  [./my]
    type = MaterialRealAux
    variable = mu
    property = viscosity
  [../]
  [./internal_energy]
    type = MaterialRealAux
    variable = e
    property = e
  [../]
  [./enthalpy]
    type = MaterialRealAux
    variable = h
    property = h
  [../]
  [./entropy]
    type = MaterialRealAux
    variable = s
    property = s
  [../]
  [./cv]
    type = MaterialRealAux
    variable = cv
    property = cv
  [../]
  [./cp]
    type = MaterialRealAux
    variable = cp
    property = cp
  [../]
  [./c]
    type = MaterialRealAux
    variable = c
    property = c
  [../]
[]

[Modules]
  [./FluidProperties]
    [./co2]
      type = CO2FluidProperties
    [../]
    [./tabulated]
      type = TabulatedFluidProperties
      fp = co2
      fluid_property_file = co2_properties.txt
      temperature_min = 275
      temperature_max = 510
      pressure_min = 2e5
      pressure_max = 2e6
    [../]
  []
[]

[Materials]
  [./fp_mat]
    type = FluidPropertiesMaterialPT
    pressure = pressure
    temperature = temperature
    fp = tabulated
  [../]
[]

[Kernels]
  [./diff]
    type = Diffusion
    variable = dummy
  [../]
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
[]

[Postprocessors]
  [./rho0]
    type = ElementalVariableValue
    elementid = 0
    variable = rho
  [../]
  [./rho1]
    type = ElementalVariableValue
    elementid = 1
    variable = rho
  [../]
  [./rho2]
    type = ElementalVariableValue
    elementid = 2
    variable = rho
  [../]
  [./mu0]
    type = ElementalVariableValue
    elementid = 0
    variable = mu
  [../]
  [./mu1]
    type = ElementalVariableValue
    elementid = 1
    variable = mu
  [../]
  [./mu2]
    type = ElementalVariableValue
    elementid = 2
    variable = mu
  [../]
  [./e0]
    type = ElementalVariableValue
    elementid = 0
    variable = e
  [../]
  [./e1]
    type = ElementalVariableValue
    elementid = 1
    variable = e
  [../]
  [./e2]
    type = ElementalVariableValue
    elementid = 2
    variable = e
  [../]
  [./h0]
    type = ElementalVariableValue
    elementid = 0
    variable = h
  [../]
  [./h1]
    type = ElementalVariableValue
    elementid = 1
    variable = h
  [../]
  [./h2]
    type = ElementalVariableValue
    elementid = 2
    variable = h
  [../]
  [./s0]
    type = ElementalVariableValue
    elementid = 0
    variable = s
  [../]
  [./s1]
    type = ElementalVariableValue
    elementid = 1
    variable = s
  [../]
  [./s2]
    type = ElementalVariableValue
    elementid = 2
    variable = s
  [../]
  [./cv0]
    type = ElementalVariableValue
    elementid = 0
    variable = cv
  [../]
  [./cv1]
    type = ElementalVariableValue
    elementid = 1
    variable = cv
  [../]
  [./cv2]
    type = ElementalVariableValue
    elementid = 2
    variable = cv
  [../]
  [./cp0]
    type = ElementalVariableValue
    elementid = 0
    variable = cp
  [../]
  [./cp1]
    type = ElementalVariableValue
    elementid = 1
    variable = cp
  [../]
  [./cp2]
    type = ElementalVariableValue
    elementid = 2
    variable = cp
  [../]
  [./c0]
    type = ElementalVariableValue
    elementid = 0
    variable = c
  [../]
  [./c1]
    type = ElementalVariableValue
    elementid = 1
    variable = c
  [../]
  [./c2]
    type = ElementalVariableValue
    elementid = 2
    variable = c
  [../]
[]

[Outputs]
  csv = true
  file_base = tabulated_out
  execute_on = 'TIMESTEP_END'
  print_perf_log = true
[]
