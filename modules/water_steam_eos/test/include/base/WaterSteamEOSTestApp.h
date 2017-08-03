#ifndef WATERSTEAMEOSTESTAPP_H
#define WATERSTEAMEOSTESTAPP_H

#include "WaterSteamEOSApp.h"

class WaterSteamEOSTestApp;

template <>
InputParameters validParams<WaterSteamEOSTestApp>();

class WaterSteamEOSTestApp : public WaterSteamEOSApp
{
public:
  WaterSteamEOSTestApp(InputParameters parameters);
  virtual ~WaterSteamEOSTestApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* WATERSTEAMEOSTESTAPP_H */
