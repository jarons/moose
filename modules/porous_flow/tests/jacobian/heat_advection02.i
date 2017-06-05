# 2phase, unsaturated, heat advection
[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 2
  xmin = 0
  xmax = 1
  ny = 1
  ymin = 0
  ymax = 1
[]

[GlobalParams]
  PorousFlowDictator = dictator
[]

[Variables]
  [./temp]
  [../]
  [./pgas]
  [../]
  [./pwater]
  [../]
[]

[ICs]
  [./pgas]
    type = RandomIC
    variable = pgas
    max = 1.0
    min = 0.0
  [../]
  [./pwater]
    type = RandomIC
    variable = pwater
    max = 0.0
    min = -1.0
  [../]
  [./temp]
    type = RandomIC
    variable = temp
    max = 1.0
    min = 0.0
  [../]
[]

[Kernels]
  [./dummy_pgas]
    type = Diffusion
    variable = pgas
  [../]
  [./dummy_pwater]
    type = Diffusion
    variable = pwater
  [../]
  [./heat_advection]
    type = PorousFlowHeatAdvection
    variable = temp
    gravity = '1 2 3'
  [../]
[]

[UserObjects]
  [./dictator]
    type = PorousFlowDictator
    porous_flow_vars = 'temp pgas pwater'
    number_fluid_phases = 2
    number_fluid_components = 1
  [../]
[]

[Modules]
  [./FluidProperties]
    [./simple_fluid0]
      type = SimpleFluidProperties
      bulk_modulus = 0.5
      density0 = 1
      thermal_expansion = 0
      viscosity = 1
      cv = 1.1
    [../]
    [./simple_fluid1]
      type = SimpleFluidProperties
      bulk_modulus = 0.8
      density0 = 0.7
      thermal_expansion = 0
      viscosity = 1.3
      cv = 1.6
    [../]
  [../]
[]

[Materials]
  [./temperature]
    type = PorousFlowTemperature
    at_nodes = false
    temperature = temp
  [../]
  [./temperature_nodal]
    type = PorousFlowTemperature
    at_nodes = true
    temperature = temp
  [../]
  [./permeability]
    type = PorousFlowPermeabilityConst
    at_nodes = false
    permeability = '1 0 0 0 2 0 0 0 3'
  [../]
  [./relperm0]
    type = PorousFlowRelativePermeabilityCorey
    at_nodes = true
    n = 2
    phase = 0
  [../]
  [./relperm1]
    type = PorousFlowRelativePermeabilityCorey
    at_nodes = true
    n = 3
    phase = 1
  [../]
  [./relperm_all]
    type = PorousFlowJoiner
    at_nodes = true
    material_property = PorousFlow_relative_permeability_nodal
  [../]
  [./ppss]
    type = PorousFlow2PhasePP_VG
    at_nodes = false
    phase0_porepressure = pwater
    phase1_porepressure = pgas
    m = 0.5
    al = 1
  [../]
  [./ppss_nodal]
    type = PorousFlow2PhasePP_VG
    phase0_porepressure = pwater
    phase1_porepressure = pgas
    at_nodes = true
    m = 0.5
    al = 1
  [../]
  [./simple_fluid0]
    type = PorousFlowSingleComponentFluid
    fp = simple_fluid0
    at_nodes = true
    phase = 0
  [../]
  [./simple_fluid0_qp]
    type = PorousFlowSingleComponentFluid
    fp = simple_fluid0
    phase = 0
  [../]
  [./simple_fluid1]
    type = PorousFlowSingleComponentFluid
    fp = simple_fluid1
    at_nodes = true
    phase = 1
  [../]
  [./simple_fluid1_qp]
    type = PorousFlowSingleComponentFluid
    fp = simple_fluid1
    phase = 1
  [../]
  [./dens_all]
    type = PorousFlowJoiner
    at_nodes = true
    material_property = PorousFlow_fluid_phase_density_nodal
  [../]
  [./dens_qp_all]
    type = PorousFlowJoiner
    material_property = PorousFlow_fluid_phase_density_qp
    at_nodes = false
  [../]
  [./visc_all]
    type = PorousFlowJoiner
    at_nodes = true
    material_property = PorousFlow_viscosity_nodal
  [../]
  [./energy_all]
    type = PorousFlowJoiner
    at_nodes = true
    material_property = PorousFlow_fluid_phase_internal_energy_nodal
  [../]
  [./enthalpy_all]
    type = PorousFlowJoiner
    at_nodes = true
    material_property = PorousFlow_fluid_phase_enthalpy_nodal
  [../]
[]

[Preconditioning]
  active = check
  [./andy]
    type = SMP
    full = true
    petsc_options_iname = '-ksp_type -pc_type -snes_atol -snes_rtol -snes_max_it'
    petsc_options_value = 'bcgs bjacobi 1E-15 1E-10 10000'
  [../]
  [./check]
    type = SMP
    full = true
    petsc_options_iname = '-ksp_type -pc_type -snes_atol -snes_rtol -snes_max_it -snes_type'
    petsc_options_value = 'bcgs bjacobi 1E-15 1E-10 10000 test'
  [../]
[]

[Executioner]
  type = Transient
  solve_type = Newton
  dt = 1
  end_time = 1
[]

[Outputs]
  exodus = false
[]