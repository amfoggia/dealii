// ---------------------------------------------------------------------
//
// Copyright (C) 1998 - 2018 by the deal.II authors
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

#ifndef dealii_number_cache_h
#define dealii_number_cache_h

#include <deal.II/base/config.h>
#include <deal.II/base/index_set.h>

#include <vector>


DEAL_II_NAMESPACE_OPEN

namespace internal
{
  namespace DoFHandler
  {
    /**
     * A structure used by the DoFHandler classes to store information about
     * the degrees of freedom they deal with.
     */
    struct NumberCache
    {
      /**
       * Default constructor.
       */
      NumberCache ();

      /**
       * Copy constructor. Simply copy all members of the referenced
       * object to the current object.
       */
      NumberCache (const NumberCache &) = default;

      /**
       * Move constructor. Simply move all members of the referenced
       * object to the current object.
       */
      NumberCache (NumberCache &&) = default;

      /**
       * Create a NumberCache object that corresponds to a sequential
       * DoFHandler object in which a single processor stores all
       * degrees of freedom. (Here, "sequential" means that either
       * the whole program does not use MPI, or that it uses MPI
       * but only uses a single MPI process, or that there are multiple MPI
       * processes but the Triangulation on which this DoFHandler builds
       * works only on one MPI process.)
       */
      NumberCache (const types::global_dof_index n_global_dofs);


      /**
       * Create a NumberCache object that corresponds to a parallel
       * DoFHandler object with as many processors as the size of the
       * given argument, in which each processor stores the degrees
       * of freedom indicated in the corresponding element of the
       * vector passed as first argument. The second argument indicates
       * the rank among all participating processors the current
       * processor has, so that we can set the @p locally_owned_dofs
       * and @p n_locally_owned_dofs fields.
       *
       * All other fields stored by the current object can be and are computed
       * from the argument.
       */
      NumberCache (const std::vector<IndexSet> &locally_owned_dofs_per_processor,
                   const unsigned int           my_rank);

      /**
       * Copy operator. Simply copy all members of the referenced
       * object to the current object.
       */
      NumberCache &operator= (const NumberCache &) = default;

      /**
       * Move assignment operator. Simply move all members of the referenced
       * object to the current object.
       */
      NumberCache &operator= (NumberCache &&) = default;

      /**
       * Determine an estimate for the memory consumption (in bytes) of this
       * object.
       */
      std::size_t memory_consumption () const;

      /**
       * This function resets all the stored information.
       */
      void clear ();

      /**
       * Total number of dofs, accumulated over all processors that may
       * participate on this mesh.
       */
      types::global_dof_index n_global_dofs;

      /**
       * Number of dofs owned by this MPI process. If this is a sequential
       * computation, then this equals n_global_dofs. (Here, "sequential" means that either
       * the whole program does not use MPI, or that it uses MPI
       * but only uses a single MPI process, or that there are multiple MPI
       * processes but the Triangulation on which this DoFHandler builds
       * works only on one MPI process.)
       */
      types::global_dof_index n_locally_owned_dofs;

      /**
       * An index set denoting the set of locally owned dofs. If this is a
       * sequential computation, then it contains the entire range
       * [0,n_global_dofs). (Here, "sequential" means that either
       * the whole program does not use MPI, or that it uses MPI
       * but only uses a single MPI process, or that there are multiple MPI
       * processes but the Triangulation on which this DoFHandler builds
       * works only on one MPI process.)
       */
      IndexSet locally_owned_dofs;

      /**
       * The number of dofs owned by each of the various MPI processes. If
       * this is a sequential computation, then the vector contains a single element
       * equal to n_global_dofs. (Here, "sequential" means that either
       * the whole program does not use MPI, or that it uses MPI
       * but only uses a single MPI process, or that there are multiple MPI
       * processes but the Triangulation on which this DoFHandler builds
       * works only on one MPI process.)
       */
      std::vector<types::global_dof_index> n_locally_owned_dofs_per_processor;

      /**
       * The dofs owned by each of the various MPI processes. If this is a
       * sequential DoFHandler, then the vector has a single element equal to
       * locally_owned_dofs. (Here, "sequential" means that either
       * the whole program does not use MPI, or that it uses MPI
       * but only uses a single MPI process, or that there are multiple MPI
       * processes but the Triangulation on which this DoFHandler builds
       * works only on one MPI process.)
       */
      std::vector<IndexSet> locally_owned_dofs_per_processor;

      /**
       * Read or write the data of this object to or from a stream for the
       * purpose of serialization
       */
      template <class Archive>
      void serialize (Archive &ar,
                      const unsigned int version);
    };


    template <class Archive>
    void
    NumberCache::serialize (Archive &ar,
                            const unsigned int /*version*/)
    {
      ar &n_global_dofs &n_locally_owned_dofs;
      ar &locally_owned_dofs;
      ar &n_locally_owned_dofs_per_processor;
      ar &locally_owned_dofs_per_processor;
    }

  }
}


DEAL_II_NAMESPACE_CLOSE

#endif // dealii_dof_iterator_selector_h
