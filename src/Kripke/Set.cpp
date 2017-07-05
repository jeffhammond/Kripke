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

#include<Kripke/Set.h>


using namespace Kripke;



/*****************************************************************************
 *
 *  Kripke::Set
 *
 *****************************************************************************/


Set::Set() :
    m_global_size(0)
{

}


size_t Set::getNumDimensions() const{
  return 1;
}



size_t Set::dimSize(size_t dim, Kripke::SdomId sdom_id) const{
  return size(sdom_id);
}


/*****************************************************************************
 *
 *  Kripke::RangeSet
 *
 *****************************************************************************/

RangeSet::RangeSet(Kripke::PartitionSpace &pspace, Kripke::SPACE space,
            std::vector<size_t> const &local_sizes) :
    m_pspace(&pspace),
    m_space(space)
{
  setup_setupByLocalSize(local_sizes);
}


void RangeSet::setup_setupByLocalSize(std::vector<size_t> const &local_sizes){

  Comm const &comm = m_pspace->getComm(m_space);

  // Figure out number of subdomains and chunks
  setup_initChunks(*m_pspace, m_space);
  size_t num_chunks = m_chunk_to_subdomain.size();

  KRIPKE_ASSERT(local_sizes.size() == num_chunks,
    "Space %d has %lu subdomains, but provided %lu subdomains",
    (int)m_space,
    (unsigned long)m_chunk_to_subdomain.size(),
    (unsigned long)local_sizes.size());



  // Compute global size
  long total_local = 0;
  for(size_t s : local_sizes){
    total_local += s;
  }
  m_global_size = comm.allReduceSumLong(total_local);


  // Copy in local subdomain sizes
  m_chunk_to_size = local_sizes;


  // Compute global offsets for each chunk
  m_chunk_to_lower.resize(num_chunks);
  m_chunk_to_lower[0] = comm.scanSumLong(total_local) - total_local;
  for(size_t i = 1;i < num_chunks;++ i){
    m_chunk_to_lower[i] = m_chunk_to_lower[i-1] + m_chunk_to_size[i-1];
  }

}

/*****************************************************************************
 *
 *  Kripke::GlobalRangeSet
 *
 *****************************************************************************/
GlobalRangeSet::GlobalRangeSet(Kripke::PartitionSpace &pspace,
    size_t global_size)
{
  setup_setGlobalSize(pspace.getNumSubdomains(), global_size);
}


GlobalRangeSet::GlobalRangeSet(Kripke::Set &parent_set)
{
  setup_setGlobalSize(parent_set.getNumSubdomains(), parent_set.globalSize());
}


void GlobalRangeSet::setup_setGlobalSize(size_t num_subdomains,
    size_t global_size)
{
  // Kripke::DomainVar
  m_subdomain_to_chunk.resize(num_subdomains, 0);
  m_chunk_to_subdomain.resize(1, 0);

  // Kripke::Set
  m_chunk_to_size.resize(1, global_size);
  m_chunk_to_lower.resize(1, 0);
  m_global_size = global_size;
}


/*****************************************************************************
 *
 *  Kripke::ProductSet
 *
 *****************************************************************************/
