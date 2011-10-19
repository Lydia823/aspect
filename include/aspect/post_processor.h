//-------------------------------------------------------------
//    $Id$
//
//    Copyright (C) 2011 by the authors of the ASPECT code
//
//-------------------------------------------------------------
#ifndef __aspect__post_processor_h
#define __aspect__post_processor_h


#include <deal.II/lac/trilinos_vector.h>
#include <deal.II/lac/trilinos_block_vector.h>
#include <deal.II/dofs/dof_handler.h>


namespace aspect
{
  template <int dim> class Simulator;


  /**
   * A namespace for everything to do with postprocessing solutions every time step
   * or every few time steps.
   *
   * @ingroup Postprocessing
   **/
  namespace Postprocess
  {

    /**
     * Base class for postprocessors. Basically, this class provides access to
     * the various variables of the main class that postprocessors may want to use
     * in their evaluations, such as solution vectors, the current time, time step
     * sizes, or the triangulations and DoFHandlers that correspond to solutions.
     *
     * This class is the interface between postprocessors and the main simulator
     * class. Using this insulation layer, postprocessors need not know anything
     * about the internal details of the simulation class.
     *
     * Since the functions providing access to details of the simulator class
     * are meant to be used only by derived classes of this base class, these
     * functions are made @p protected.
     *
     * @ingroup Postprocessing
     */
    template <int dim>
    class Base
    {
      public:
	/**
	 * Constructor.
	 *
	 * @param simulator A reference to the main simulator object to which the
	 * postprocessor implemented in the derived class should be applied.
	 **/
	Base (const Simulator<dim> &simulator);
	
      protected:
        /** @name Accessing variables that identify overall properties of the simulator */
        /** @{ */

        /**
         * Return the current simulation time.
         */
        double get_time () const;

        /**
         * Return the current number of a time step.
         */
        double get_timestep_number () const;
        /** @} */


        /** @name Accessing variables that identify the solution of the Stokes problem */
        /** @{ */


        /**
         * Return a reference to the vector that has the current solution
         * of the Stokes system, i.e. the velocity and pressure variables.
         * This vector is associated with the DoFHandler object returned by
         * get_stokes_dof_handler().
         *
         * @note In general the vector is a distributed vector; however, it
         * contains ghost elements for all locally relevant degrees of freedom.
         */
        const TrilinosWrappers::Vector &
        get_stokes_solution () const;

        /**
         * Return a reference to the vector that has the solution
         * of the Stokes system at the previous time step.
         * This vector is associated with the DoFHandler object returned by
         * get_stokes_dof_handler().
         *
         * @note In general the vector is a distributed vector; however, it
         * contains ghost elements for all locally relevant degrees of freedom.
         */
        const TrilinosWrappers::Vector &
        get_old_stokes_solution () const;

        /**
         * Return a reference to the DoFHandler that is used to discretize
         * the Stokes system of velocity and pressure.
         */
        const parallel::distributed::DoFhandler<dim> &
        get_stokes_dof_handler () const;
        /** @} */


        /** @name Accessing variables that identify the solution of the temperature problem */
        /** @{ */


        /**
         * Return a reference to the vector that has the current solution
         * of the temperature system.
         * This vector is associated with the DoFHandler object returned by
         * get_temperature_dof_handler().
         *
         * @note In general the vector is a distributed vector; however, it
         * contains ghost elements for all locally relevant degrees of freedom.
         */
        const TrilinosWrappers::Vector &
        get_temperature_solution () const;

        /**
         * Return a reference to the vector that has the solution
         * of the temperature system at the previous time step.
         * This vector is associated with the DoFHandler object returned by
         * get_temperature_dof_handler().
         *
         * @note In general the vector is a distributed vector; however, it
         * contains ghost elements for all locally relevant degrees of freedom.
         */
        const TrilinosWrappers::Vector &
        get_old_temperature_solution () const;

        /**
         * Return a reference to the DoFHandler that is used to discretize
         * the temperature equation.
         */
        const parallel::distributed::DoFhandler<dim> &
        get_temperature_dof_handler () const;
        /** @} */
    };
  }
}


#endif
