/*
 * NOTICE
 *
 * This work was produced at the Lawrence Livermore National Laboratory (LLNL)
 * under contract no. DE-AC-52-07NA27344 (Contract 44) between the U.S.
 * Department of Energy (DOE) and Lawrence Livermore National Security, LLC
 * (LLNS) for the operation of LLNL. The rights of the Federal Government are
 * reserved under Contract 44.
 *
 * DISCLAIMER
 *
 * This work was prepared as an account of work sponsored by an agency of the
 * United States Government. Neither the United States Government nor Lawrence
 * Livermore National Security, LLC nor any of their employees, makes any
 * warranty, express or implied, or assumes any liability or responsibility
 * for the accuracy, completeness, or usefulness of any information, apparatus,
 * product, or process disclosed, or represents that its use would not infringe
 * privately-owned rights. Reference herein to any specific commercial products,
 * process, or service by trade name, trademark, manufacturer or otherwise does
 * not necessarily constitute or imply its endorsement, recommendation, or
 * favoring by the United States Government or Lawrence Livermore National
 * Security, LLC. The views and opinions of authors expressed herein do not
 * necessarily state or reflect those of the United States Government or
 * Lawrence Livermore National Security, LLC, and shall not be used for
 * advertising or product endorsement purposes.
 *
 * NOTIFICATION OF COMMERCIAL USE
 *
 * Commercialization of this product is prohibited without notifying the
 * Department of Energy (DOE) or Lawrence Livermore National Security.
 */

#ifndef KERNEL_LTIMES_POLICY_H__
#define KERNEL_LTIMES_POLICY_H__

#include<Kripke.h>
#include<Domain/Layout.h>
#include<Domain/Forall.h>


template<typename T>
struct LTimesPolicy{}; // nm, d, g, z

template<>
struct LTimesPolicy<NEST_DGZ_T> : //Forall4_OMP_Parallel<
                                  //  Forall4_Tile<tile_none, tile_none, tile_fixed<16>, tile_fixed<512>,
                                      Forall4_Execute<PERM_IJKL, seq_pol, seq_pol, omp_nowait, seq_pol>
                                  //  >
                                  //>
{};

template<>
struct LTimesPolicy<NEST_DZG_T> : //Forall4_OMP_Parallel<
                                    Forall4_Execute<PERM_LIJK, seq_pol, seq_pol, seq_pol, omp_nowait>
                                  //>
{};

template<>
struct LTimesPolicy<NEST_GDZ_T> : Forall4_Execute<PERM_KIJL, seq_pol, seq_pol, omp_pol, seq_pol>
{};

template<>
struct LTimesPolicy<NEST_GZD_T> : Forall4_Execute<PERM_KLIJ, seq_pol, seq_pol, omp_pol, omp_pol>
{};

template<>
struct LTimesPolicy<NEST_ZDG_T> : Forall4_Execute<PERM_LIJK, omp_pol, seq_pol, seq_pol, omp_pol>
{}; 

template<>
struct LTimesPolicy<NEST_ZGD_T> : Forall4_Execute<PERM_LKIJ, seq_pol, seq_pol, omp_pol, omp_pol>
{};


#endif
