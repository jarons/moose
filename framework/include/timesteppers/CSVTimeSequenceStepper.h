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

#ifndef CSVTIMESEQUENCESTEPPER_H
#define CSVTIMESEQUENCESTEPPER_H

#include "TimeSequenceStepperBase.h"

class CSVTimeSequenceStepper;

template <>
InputParameters validParams<CSVTimeSequenceStepper>();

/**
 * Solves the PDEs at a sequence of time points given as a column in a
 * text table file (such as a *.csv file). This class uses a
 * DelimitedFileReader to read the input file.
 *
 * The column can either be identified by name (if the input file contains
 * an appropriate header) or by its index (1st column corresponds to index 0).
 */
class CSVTimeSequenceStepper : public TimeSequenceStepperBase
{
public:
  CSVTimeSequenceStepper(const InputParameters & parameters);

  virtual void init() override;

protected:
  /// name of the file where the data is read
  const std::string _file_name;
  /// whether the file contains a header with the column names
  bool _header;
  /// string used as a delimiter
  const std::string _delimiter;

  /// name of the column containing the time data
  const std::string _column_name;

  /// index of the column containing the time data
  const int _column_index;
};

#endif // CSVTIMESEQUENCESTEPPER_H
