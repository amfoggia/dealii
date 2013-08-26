// ---------------------------------------------------------------------
// $Id$
//
// Copyright (C) 2003 - 2013 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE at
// the top level of the deal.II distribution.
//
// ---------------------------------------------------------------------


// test that the grid generated by GridGenerator::cylinder_shell<3> works as
// expected


#include "../tests.h"
#include <deal.II/base/logstream.h>
#include <deal.II/grid/tria.h>
#include <deal.II/grid/tria_iterator.h>
#include <deal.II/grid/tria_accessor.h>
#include <deal.II/grid/grid_generator.h>
#include <fstream>
#include <iomanip>



int main ()
{
  std::ofstream logfile("output");
  deallog.attach(logfile);
  deallog.depth_console(0);
  deallog.threshold_double(1.e-10);
  deallog << std::setprecision (2);

  // generate a hyperball in 3d
  Triangulation<3> tria;
  GridGenerator::cylinder_shell (tria, 1, .8, 1);

  // make sure that all cells have positive
  // volume
  for (Triangulation<3>::active_cell_iterator cell=tria.begin_active();
       cell!=tria.end(); ++cell)
    deallog << cell << ' ' << cell->measure () << std::endl;
}
