#include "PorousFlowApp.h"
#include "Moose.h"
#include "TensorMechanicsApp.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "FluidPropertiesApp.h"
#include "ChemicalReactionsApp.h"

// Actions
#include "PorousFlowUnsaturated.h"
#include "PorousFlowFullySaturated.h"
#include "PorousFlowBasicTHM.h"

// UserObjects
#include "PorousFlowDictator.h"
#include "PorousFlowSumQuantity.h"

// DiracKernels
#include "PorousFlowSquarePulsePointSource.h"
#include "PorousFlowPeacemanBorehole.h"
#include "PorousFlowPolyLineSink.h"

// Postprocessors
#include "PorousFlowFluidMass.h"
#include "PorousFlowHeatEnergy.h"
#include "PorousFlowPlotQuantity.h"

// Materials
#include "PorousFlow1PhaseMD_Gaussian.h"
#include "PorousFlow2PhasePP.h"
#include "PorousFlow2PhasePS_VG.h"
#include "PorousFlow1PhaseP.h"
#include "PorousFlow2PhasePP_VG.h"
#include "PorousFlow2PhasePP_RSC.h"
#include "PorousFlowMassFraction.h"
#include "PorousFlow1PhaseP_VG.h"
#include "PorousFlow1PhaseP_BW.h"
#include "PorousFlow2PhasePS.h"
#include "PorousFlowVariableBase.h"
#include "PorousFlowBrine.h"
#include "PorousFlowDensityConstBulk.h"
#include "PorousFlowEffectiveFluidPressure.h"
#include "PorousFlowFluidPropertiesBase.h"
#include "PorousFlowIdealGas.h"
#include "PorousFlowPermeabilityConst.h"
#include "PorousFlowPermeabilityConstFromVar.h"
#include "PorousFlowPermeabilityKozenyCarman.h"
#include "PorousFlowPermeabilityExponential.h"
#include "PorousFlowPorosityConst.h"
#include "PorousFlowPorosityHM.h"
#include "PorousFlowPorosityHMBiotModulus.h"
#include "PorousFlowPorosityTM.h"
#include "PorousFlowPorosityTHM.h"
#include "PorousFlowRelativePermeabilityCorey.h"
#include "PorousFlowRelativePermeabilityConst.h"
#include "PorousFlowRelativePermeabilityVG.h"
#include "PorousFlowRelativePermeabilityBW.h"
#include "PorousFlowRelativePermeabilityFLAC.h"
#include "PorousFlowTotalGravitationalDensityFullySaturatedFromPorosity.h"
#include "PorousFlowViscosityConst.h"
#include "PorousFlowVolumetricStrain.h"
#include "PorousFlowJoiner.h"
#include "PorousFlowTemperature.h"
#include "PorousFlowThermalConductivityIdeal.h"
#include "PorousFlowThermalConductivityFromPorosity.h"
#include "PorousFlowMatrixInternalEnergy.h"
#include "PorousFlowInternalEnergyIdeal.h"
#include "PorousFlowEnthalpy.h"
#include "PorousFlowDiffusivityConst.h"
#include "PorousFlowDiffusivityMillingtonQuirk.h"
#include "PorousFlowSingleComponentFluid.h"
#include "PorousFlowNearestQp.h"
#include "PorousFlowConstantBiotModulus.h"
#include "PorousFlowConstantThermalExpansionCoefficient.h"
#include "PorousFlowFluidStateWaterNCG.h"

// Kernels
#include "PorousFlowAdvectiveFlux.h"
#include "PorousFlowMassTimeDerivative.h"
#include "PorousFlowEffectiveStressCoupling.h"
#include "PorousFlowMassVolumetricExpansion.h"
#include "PorousFlowEnergyTimeDerivative.h"
#include "PorousFlowHeatConduction.h"
#include "PorousFlowHeatAdvection.h"
#include "PorousFlowDispersiveFlux.h"
#include "PorousFlowHeatVolumetricExpansion.h"
#include "PorousFlowPlasticHeatEnergy.h"
#include "PorousFlowDesorpedMassTimeDerivative.h"
#include "PorousFlowDesorpedMassVolumetricExpansion.h"
#include "PorousFlowMassRadioactiveDecay.h"
#include "PorousFlowFullySaturatedDarcyBase.h"
#include "PorousFlowFullySaturatedDarcyFlow.h"
#include "PorousFlowFullySaturatedHeatAdvection.h"
#include "PorousFlowFullySaturatedMassTimeDerivative.h"

// BoundaryConditions
#include "PorousFlowSink.h"
#include "PorousFlowPiecewiseLinearSink.h"
#include "PorousFlowHalfGaussianSink.h"
#include "PorousFlowHalfCubicSink.h"

// AuxKernels
#include "PorousFlowDarcyVelocityComponent.h"
#include "PorousFlowPropertyAux.h"

// Functions
#include "MovingPlanarFront.h"

template <>
InputParameters
validParams<PorousFlowApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

PorousFlowApp::PorousFlowApp(const InputParameters & parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  TensorMechanicsApp::registerObjects(_factory);
  FluidPropertiesApp::registerObjects(_factory);
  ChemicalReactionsApp::registerObjects(_factory);
  PorousFlowApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  TensorMechanicsApp::associateSyntax(_syntax, _action_factory);
  FluidPropertiesApp::associateSyntax(_syntax, _action_factory);
  ChemicalReactionsApp::associateSyntax(_syntax, _action_factory);
  PorousFlowApp::associateSyntax(_syntax, _action_factory);
}

PorousFlowApp::~PorousFlowApp() {}

// External entry point for dynamic application loading
extern "C" void
PorousFlowApp__registerApps()
{
  PorousFlowApp::registerApps();
}
void
PorousFlowApp::registerApps()
{
  registerApp(PorousFlowApp);
}

// External entry point for dynamic object registration
extern "C" void
PorousFlowApp__registerObjects(Factory & factory)
{
  PorousFlowApp::registerObjects(factory);
}
void
PorousFlowApp::registerObjects(Factory & factory)
{
  // UserObjects
  registerUserObject(PorousFlowDictator);
  registerUserObject(PorousFlowSumQuantity);

  // DiracKernels
  registerDiracKernel(PorousFlowSquarePulsePointSource);
  registerDiracKernel(PorousFlowPeacemanBorehole);
  registerDiracKernel(PorousFlowPolyLineSink);

  // Postprocessors
  registerPostprocessor(PorousFlowFluidMass);
  registerPostprocessor(PorousFlowHeatEnergy);
  registerPostprocessor(PorousFlowPlotQuantity);

  // Materials
  registerMaterial(PorousFlow1PhaseMD_Gaussian);
  registerMaterial(PorousFlow2PhasePP);
  registerMaterial(PorousFlow2PhasePS_VG);
  registerMaterial(PorousFlow1PhaseP);
  registerMaterial(PorousFlow2PhasePP_VG);
  registerMaterial(PorousFlow2PhasePP_RSC);
  registerMaterial(PorousFlowMassFraction);
  registerMaterial(PorousFlow1PhaseP_VG);
  registerMaterial(PorousFlow1PhaseP_BW);
  registerMaterial(PorousFlow2PhasePS);
  registerMaterial(PorousFlowVariableBase);
  registerMaterial(PorousFlowBrine);
  registerMaterial(PorousFlowDensityConstBulk);
  registerMaterial(PorousFlowEffectiveFluidPressure);
  registerMaterial(PorousFlowFluidPropertiesBase);
  registerMaterial(PorousFlowIdealGas);
  registerMaterial(PorousFlowPermeabilityConst);
  registerMaterial(PorousFlowPermeabilityConstFromVar);
  registerMaterial(PorousFlowPermeabilityKozenyCarman);
  registerMaterial(PorousFlowPermeabilityExponential);
  registerMaterial(PorousFlowPorosityConst);
  registerMaterial(PorousFlowPorosityHM);
  registerMaterial(PorousFlowPorosityHMBiotModulus);
  registerMaterial(PorousFlowPorosityTM);
  registerMaterial(PorousFlowPorosityTHM);
  registerMaterial(PorousFlowRelativePermeabilityCorey);
  registerMaterial(PorousFlowRelativePermeabilityConst);
  registerMaterial(PorousFlowRelativePermeabilityVG);
  registerMaterial(PorousFlowRelativePermeabilityBW);
  registerMaterial(PorousFlowRelativePermeabilityFLAC);
  registerMaterial(PorousFlowTotalGravitationalDensityFullySaturatedFromPorosity);
  registerMaterial(PorousFlowViscosityConst);
  registerMaterial(PorousFlowVolumetricStrain);
  registerMaterial(PorousFlowJoiner);
  registerMaterial(PorousFlowTemperature);
  registerMaterial(PorousFlowThermalConductivityIdeal);
  registerMaterial(PorousFlowThermalConductivityFromPorosity);
  registerMaterial(PorousFlowMatrixInternalEnergy);
  registerMaterial(PorousFlowInternalEnergyIdeal);
  registerMaterial(PorousFlowEnthalpy);
  registerMaterial(PorousFlowDiffusivityConst);
  registerMaterial(PorousFlowDiffusivityMillingtonQuirk);
  registerMaterial(PorousFlowSingleComponentFluid);
  registerMaterial(PorousFlowNearestQp);
  registerMaterial(PorousFlowConstantBiotModulus);
  registerMaterial(PorousFlowConstantThermalExpansionCoefficient);
  registerMaterial(PorousFlowFluidStateWaterNCG);

  // Kernels
  registerKernel(PorousFlowAdvectiveFlux);
  registerKernel(PorousFlowMassTimeDerivative);
  registerKernel(PorousFlowEffectiveStressCoupling);
  registerKernel(PorousFlowMassVolumetricExpansion);
  registerKernel(PorousFlowEnergyTimeDerivative);
  registerKernel(PorousFlowHeatConduction);
  registerKernel(PorousFlowHeatAdvection);
  registerKernel(PorousFlowDispersiveFlux);
  registerKernel(PorousFlowHeatVolumetricExpansion);
  registerKernel(PorousFlowPlasticHeatEnergy);
  registerKernel(PorousFlowDesorpedMassTimeDerivative);
  registerKernel(PorousFlowDesorpedMassVolumetricExpansion);
  registerKernel(PorousFlowMassRadioactiveDecay);
  registerKernel(PorousFlowFullySaturatedDarcyBase);
  registerKernel(PorousFlowFullySaturatedDarcyFlow);
  registerKernel(PorousFlowFullySaturatedHeatAdvection);
  registerKernel(PorousFlowFullySaturatedMassTimeDerivative);

  // BoundaryConditions
  registerBoundaryCondition(PorousFlowSink);
  registerBoundaryCondition(PorousFlowPiecewiseLinearSink);
  registerBoundaryCondition(PorousFlowHalfGaussianSink);
  registerBoundaryCondition(PorousFlowHalfCubicSink);

  // AuxKernels
  registerAuxKernel(PorousFlowDarcyVelocityComponent);
  registerAuxKernel(PorousFlowPropertyAux);

  // Functions
  registerFunction(MovingPlanarFront);
}

// External entry point for dynamic syntax association
extern "C" void
PorousFlowApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  PorousFlowApp::associateSyntax(syntax, action_factory);
}
void
PorousFlowApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  syntax.registerActionSyntax("PorousFlowUnsaturated", "PorousFlowUnsaturated", "add_user_object");
  syntax.registerActionSyntax("PorousFlowUnsaturated", "PorousFlowUnsaturated", "add_kernel");
  syntax.registerActionSyntax("PorousFlowUnsaturated", "PorousFlowUnsaturated", "add_material");
  syntax.registerActionSyntax("PorousFlowUnsaturated", "PorousFlowUnsaturated", "add_aux_variable");
  syntax.registerActionSyntax("PorousFlowUnsaturated", "PorousFlowUnsaturated", "add_aux_kernel");
  registerAction(PorousFlowUnsaturated, "add_user_object");
  registerAction(PorousFlowUnsaturated, "add_kernel");
  registerAction(PorousFlowUnsaturated, "add_material");
  registerAction(PorousFlowUnsaturated, "add_aux_variable");
  registerAction(PorousFlowUnsaturated, "add_aux_kernel");

  syntax.registerActionSyntax(
      "PorousFlowFullySaturated", "PorousFlowFullySaturated", "add_user_object");
  syntax.registerActionSyntax("PorousFlowFullySaturated", "PorousFlowFullySaturated", "add_kernel");
  syntax.registerActionSyntax(
      "PorousFlowFullySaturated", "PorousFlowFullySaturated", "add_material");
  syntax.registerActionSyntax(
      "PorousFlowFullySaturated", "PorousFlowFullySaturated", "add_aux_variable");
  syntax.registerActionSyntax(
      "PorousFlowFullySaturated", "PorousFlowFullySaturated", "add_aux_kernel");
  registerAction(PorousFlowFullySaturated, "add_user_object");
  registerAction(PorousFlowFullySaturated, "add_kernel");
  registerAction(PorousFlowFullySaturated, "add_material");
  registerAction(PorousFlowFullySaturated, "add_aux_variable");
  registerAction(PorousFlowFullySaturated, "add_aux_kernel");

  syntax.registerActionSyntax("PorousFlowBasicTHM", "PorousFlowBasicTHM", "add_user_object");
  syntax.registerActionSyntax("PorousFlowBasicTHM", "PorousFlowBasicTHM", "add_kernel");
  syntax.registerActionSyntax("PorousFlowBasicTHM", "PorousFlowBasicTHM", "add_material");
  syntax.registerActionSyntax("PorousFlowBasicTHM", "PorousFlowBasicTHM", "add_aux_variable");
  syntax.registerActionSyntax("PorousFlowBasicTHM", "PorousFlowBasicTHM", "add_aux_kernel");
  registerAction(PorousFlowBasicTHM, "add_user_object");
  registerAction(PorousFlowBasicTHM, "add_kernel");
  registerAction(PorousFlowBasicTHM, "add_material");
  registerAction(PorousFlowBasicTHM, "add_aux_variable");
  registerAction(PorousFlowBasicTHM, "add_aux_kernel");
}
