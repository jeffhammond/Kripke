//AUTOGENERATED BY genForallN.py
  
#ifndef __DOMAIN_FORALL4_H__
#define __DOMAIN_FORALL4_H__

#include<RAJA/RAJA.hxx>
#include<Domain/Tile.h>



/******************************************************************
 *  Policy base class, forall4()
 ******************************************************************/

    // Interchange-loops and Execute (Base-case for all policies)
    struct Forall4_Execute_Tag {};
    template<typename LOOP_ORDER, typename POL_I, typename POL_J, typename POL_K, typename POL_L>
    struct Forall4_Execute {
      typedef Forall4_Execute_Tag PolicyTag;
      typedef LOOP_ORDER LoopOrder;
      typedef POL_I PolicyI;
      typedef POL_J PolicyJ;
      typedef POL_K PolicyK;
      typedef POL_L PolicyL;
    };

    // Begin OpenMP Parallel Block
    struct Forall4_OMP_Parallel_Tag {};
    template<typename NEXT>
    struct Forall4_OMP_Parallel {
      typedef Forall4_OMP_Parallel_Tag PolicyTag;
      typedef NEXT NextPolicy;
    };

    // Tiling Policy
    struct Forall4_Tile_Tag {};
    template<typename TILE_I, typename TILE_J, typename TILE_K, typename TILE_L, typename NEXT>
    struct Forall4_Tile {
      typedef Forall4_Tile_Tag PolicyTag;
      typedef NEXT NextPolicy;
      typedef TILE_I TileI;
      typedef TILE_J TileJ;
      typedef TILE_K TileK;
      typedef TILE_L TileL;
    };


/******************************************************************
 *  Default Executor for forall4()
 ******************************************************************/

    template<typename POLICY_I, typename POLICY_J, typename POLICY_K, typename POLICY_L, typename TI, typename TJ, typename TK, typename TL>
    class Forall4Executor {
      public:  
        template<typename BODY>
        inline void operator()(TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body) const {
          RAJA::forall<POLICY_I>(is_i, RAJA_LAMBDA(int i){
            exec(is_j, is_k, is_l, RAJA_LAMBDA(int j, int k, int l){
              body(i, j, k, l);
            });
          });
        }

      private:
        Forall3Executor<POLICY_J, POLICY_K, POLICY_L, TJ, TK, TL> exec;
    };


/******************************************************************
 *  OpenMP Auto-Collapsing Executors for forall4()
 ******************************************************************/

#ifdef _OPENMP

    // OpenMP Executor with collapse(2) for omp_parallel_for_exec
    template<typename POLICY_K, typename POLICY_L, typename TK, typename TL>
    class Forall4Executor<RAJA::omp_parallel_for_exec, RAJA::omp_parallel_for_exec, POLICY_K, POLICY_L, RAJA::RangeSegment, RAJA::RangeSegment, TK, TL> {
      public:  
        template<typename BODY>
        inline void operator()(RAJA::RangeSegment const &is_i, RAJA::RangeSegment const &is_j, TK const &is_k, TL const &is_l, BODY const &body) const {
          int const i_start = is_i.getBegin();
          int const i_end   = is_i.getEnd();

          int const j_start = is_j.getBegin();
          int const j_end   = is_j.getEnd();

#pragma omp parallel for schedule(static) collapse(2)
          for(int i = i_start;i < i_end;++ i){
            for(int j = j_start;j < j_end;++ j){
              exec(is_k, is_l, RAJA_LAMBDA(int k, int l){
                body(i, j, k, l);
              });
          } } 
        }

      private:
        Forall2Executor<POLICY_K, POLICY_L, TK, TL> exec;
    };

    // OpenMP Executor with collapse(3) for omp_parallel_for_exec
    template<typename POLICY_L, typename TL>
    class Forall4Executor<RAJA::omp_parallel_for_exec, RAJA::omp_parallel_for_exec, RAJA::omp_parallel_for_exec, POLICY_L, RAJA::RangeSegment, RAJA::RangeSegment, RAJA::RangeSegment, TL> {
      public:  
        template<typename BODY>
        inline void operator()(RAJA::RangeSegment const &is_i, RAJA::RangeSegment const &is_j, RAJA::RangeSegment const &is_k, TL const &is_l, BODY const &body) const {
          int const i_start = is_i.getBegin();
          int const i_end   = is_i.getEnd();

          int const j_start = is_j.getBegin();
          int const j_end   = is_j.getEnd();

          int const k_start = is_k.getBegin();
          int const k_end   = is_k.getEnd();

#pragma omp parallel for schedule(static) collapse(3)
          for(int i = i_start;i < i_end;++ i){
            for(int j = j_start;j < j_end;++ j){
              for(int k = k_start;k < k_end;++ k){
                RAJA::forall<POLICY_L>(is_l, RAJA_LAMBDA(int l){
                  body(i, j, k, l);
                });
          } } } 
        }
    };

    // OpenMP Executor with collapse(4) for omp_parallel_for_exec
    template<>
    class Forall4Executor<RAJA::omp_parallel_for_exec, RAJA::omp_parallel_for_exec, RAJA::omp_parallel_for_exec, RAJA::omp_parallel_for_exec, RAJA::RangeSegment, RAJA::RangeSegment, RAJA::RangeSegment, RAJA::RangeSegment> {
      public:  
        template<typename BODY>
        inline void operator()(RAJA::RangeSegment const &is_i, RAJA::RangeSegment const &is_j, RAJA::RangeSegment const &is_k, RAJA::RangeSegment const &is_l, BODY const &body) const {
          int const i_start = is_i.getBegin();
          int const i_end   = is_i.getEnd();

          int const j_start = is_j.getBegin();
          int const j_end   = is_j.getEnd();

          int const k_start = is_k.getBegin();
          int const k_end   = is_k.getEnd();

          int const l_start = is_l.getBegin();
          int const l_end   = is_l.getEnd();

#pragma omp parallel for schedule(static) collapse(4)
          for(int i = i_start;i < i_end;++ i){
            for(int j = j_start;j < j_end;++ j){
              for(int k = k_start;k < k_end;++ k){
                for(int l = l_start;l < l_end;++ l){
                  body(i, j, k, l);
          } } } } 
        }
    };

    // OpenMP Executor with collapse(2) for omp_for_nowait_exec
    template<typename POLICY_K, typename POLICY_L, typename TK, typename TL>
    class Forall4Executor<RAJA::omp_for_nowait_exec, RAJA::omp_for_nowait_exec, POLICY_K, POLICY_L, RAJA::RangeSegment, RAJA::RangeSegment, TK, TL> {
      public:  
        template<typename BODY>
        inline void operator()(RAJA::RangeSegment const &is_i, RAJA::RangeSegment const &is_j, TK const &is_k, TL const &is_l, BODY const &body) const {
          int const i_start = is_i.getBegin();
          int const i_end   = is_i.getEnd();

          int const j_start = is_j.getBegin();
          int const j_end   = is_j.getEnd();

#pragma omp for schedule(static) collapse(2) nowait
          for(int i = i_start;i < i_end;++ i){
            for(int j = j_start;j < j_end;++ j){
              exec(is_k, is_l, RAJA_LAMBDA(int k, int l){
                body(i, j, k, l);
              });
          } } 
        }

      private:
        Forall2Executor<POLICY_K, POLICY_L, TK, TL> exec;
    };

    // OpenMP Executor with collapse(3) for omp_for_nowait_exec
    template<typename POLICY_L, typename TL>
    class Forall4Executor<RAJA::omp_for_nowait_exec, RAJA::omp_for_nowait_exec, RAJA::omp_for_nowait_exec, POLICY_L, RAJA::RangeSegment, RAJA::RangeSegment, RAJA::RangeSegment, TL> {
      public:  
        template<typename BODY>
        inline void operator()(RAJA::RangeSegment const &is_i, RAJA::RangeSegment const &is_j, RAJA::RangeSegment const &is_k, TL const &is_l, BODY const &body) const {
          int const i_start = is_i.getBegin();
          int const i_end   = is_i.getEnd();

          int const j_start = is_j.getBegin();
          int const j_end   = is_j.getEnd();

          int const k_start = is_k.getBegin();
          int const k_end   = is_k.getEnd();

#pragma omp for schedule(static) collapse(3) nowait
          for(int i = i_start;i < i_end;++ i){
            for(int j = j_start;j < j_end;++ j){
              for(int k = k_start;k < k_end;++ k){
                RAJA::forall<POLICY_L>(is_l, RAJA_LAMBDA(int l){
                  body(i, j, k, l);
                });
          } } } 
        }
    };

    // OpenMP Executor with collapse(4) for omp_for_nowait_exec
    template<>
    class Forall4Executor<RAJA::omp_for_nowait_exec, RAJA::omp_for_nowait_exec, RAJA::omp_for_nowait_exec, RAJA::omp_for_nowait_exec, RAJA::RangeSegment, RAJA::RangeSegment, RAJA::RangeSegment, RAJA::RangeSegment> {
      public:  
        template<typename BODY>
        inline void operator()(RAJA::RangeSegment const &is_i, RAJA::RangeSegment const &is_j, RAJA::RangeSegment const &is_k, RAJA::RangeSegment const &is_l, BODY const &body) const {
          int const i_start = is_i.getBegin();
          int const i_end   = is_i.getEnd();

          int const j_start = is_j.getBegin();
          int const j_end   = is_j.getEnd();

          int const k_start = is_k.getBegin();
          int const k_end   = is_k.getEnd();

          int const l_start = is_l.getBegin();
          int const l_end   = is_l.getEnd();

#pragma omp for schedule(static) collapse(4) nowait
          for(int i = i_start;i < i_end;++ i){
            for(int j = j_start;j < j_end;++ j){
              for(int k = k_start;k < k_end;++ k){
                for(int l = l_start;l < l_end;++ l){
                  body(i, j, k, l);
          } } } } 
        }
    };


#endif // _OPENMP


/******************************************************************
 *  Permutations layer for forall4()
 ******************************************************************/

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_IJKL, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyI, typename POLICY::PolicyJ, typename POLICY::PolicyK, typename POLICY::PolicyL, TI, TJ, TK, TL> exec;
        exec(is_i, is_j, is_k, is_l, RAJA_LAMBDA(int i, int j, int k, int l){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_IJLK, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyI, typename POLICY::PolicyJ, typename POLICY::PolicyL, typename POLICY::PolicyK, TI, TJ, TL, TK> exec;
        exec(is_i, is_j, is_l, is_k, RAJA_LAMBDA(int i, int j, int l, int k){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_IKJL, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyI, typename POLICY::PolicyK, typename POLICY::PolicyJ, typename POLICY::PolicyL, TI, TK, TJ, TL> exec;
        exec(is_i, is_k, is_j, is_l, RAJA_LAMBDA(int i, int k, int j, int l){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_IKLJ, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyI, typename POLICY::PolicyK, typename POLICY::PolicyL, typename POLICY::PolicyJ, TI, TK, TL, TJ> exec;
        exec(is_i, is_k, is_l, is_j, RAJA_LAMBDA(int i, int k, int l, int j){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_ILJK, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyI, typename POLICY::PolicyL, typename POLICY::PolicyJ, typename POLICY::PolicyK, TI, TL, TJ, TK> exec;
        exec(is_i, is_l, is_j, is_k, RAJA_LAMBDA(int i, int l, int j, int k){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_ILKJ, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyI, typename POLICY::PolicyL, typename POLICY::PolicyK, typename POLICY::PolicyJ, TI, TL, TK, TJ> exec;
        exec(is_i, is_l, is_k, is_j, RAJA_LAMBDA(int i, int l, int k, int j){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_JIKL, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyJ, typename POLICY::PolicyI, typename POLICY::PolicyK, typename POLICY::PolicyL, TJ, TI, TK, TL> exec;
        exec(is_j, is_i, is_k, is_l, RAJA_LAMBDA(int j, int i, int k, int l){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_JILK, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyJ, typename POLICY::PolicyI, typename POLICY::PolicyL, typename POLICY::PolicyK, TJ, TI, TL, TK> exec;
        exec(is_j, is_i, is_l, is_k, RAJA_LAMBDA(int j, int i, int l, int k){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_JKIL, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyJ, typename POLICY::PolicyK, typename POLICY::PolicyI, typename POLICY::PolicyL, TJ, TK, TI, TL> exec;
        exec(is_j, is_k, is_i, is_l, RAJA_LAMBDA(int j, int k, int i, int l){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_JKLI, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyJ, typename POLICY::PolicyK, typename POLICY::PolicyL, typename POLICY::PolicyI, TJ, TK, TL, TI> exec;
        exec(is_j, is_k, is_l, is_i, RAJA_LAMBDA(int j, int k, int l, int i){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_JLIK, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyJ, typename POLICY::PolicyL, typename POLICY::PolicyI, typename POLICY::PolicyK, TJ, TL, TI, TK> exec;
        exec(is_j, is_l, is_i, is_k, RAJA_LAMBDA(int j, int l, int i, int k){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_JLKI, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyJ, typename POLICY::PolicyL, typename POLICY::PolicyK, typename POLICY::PolicyI, TJ, TL, TK, TI> exec;
        exec(is_j, is_l, is_k, is_i, RAJA_LAMBDA(int j, int l, int k, int i){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_KIJL, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyK, typename POLICY::PolicyI, typename POLICY::PolicyJ, typename POLICY::PolicyL, TK, TI, TJ, TL> exec;
        exec(is_k, is_i, is_j, is_l, RAJA_LAMBDA(int k, int i, int j, int l){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_KILJ, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyK, typename POLICY::PolicyI, typename POLICY::PolicyL, typename POLICY::PolicyJ, TK, TI, TL, TJ> exec;
        exec(is_k, is_i, is_l, is_j, RAJA_LAMBDA(int k, int i, int l, int j){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_KJIL, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyK, typename POLICY::PolicyJ, typename POLICY::PolicyI, typename POLICY::PolicyL, TK, TJ, TI, TL> exec;
        exec(is_k, is_j, is_i, is_l, RAJA_LAMBDA(int k, int j, int i, int l){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_KJLI, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyK, typename POLICY::PolicyJ, typename POLICY::PolicyL, typename POLICY::PolicyI, TK, TJ, TL, TI> exec;
        exec(is_k, is_j, is_l, is_i, RAJA_LAMBDA(int k, int j, int l, int i){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_KLIJ, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyK, typename POLICY::PolicyL, typename POLICY::PolicyI, typename POLICY::PolicyJ, TK, TL, TI, TJ> exec;
        exec(is_k, is_l, is_i, is_j, RAJA_LAMBDA(int k, int l, int i, int j){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_KLJI, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyK, typename POLICY::PolicyL, typename POLICY::PolicyJ, typename POLICY::PolicyI, TK, TL, TJ, TI> exec;
        exec(is_k, is_l, is_j, is_i, RAJA_LAMBDA(int k, int l, int j, int i){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_LIJK, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyL, typename POLICY::PolicyI, typename POLICY::PolicyJ, typename POLICY::PolicyK, TL, TI, TJ, TK> exec;
        exec(is_l, is_i, is_j, is_k, RAJA_LAMBDA(int l, int i, int j, int k){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_LIKJ, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyL, typename POLICY::PolicyI, typename POLICY::PolicyK, typename POLICY::PolicyJ, TL, TI, TK, TJ> exec;
        exec(is_l, is_i, is_k, is_j, RAJA_LAMBDA(int l, int i, int k, int j){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_LJIK, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyL, typename POLICY::PolicyJ, typename POLICY::PolicyI, typename POLICY::PolicyK, TL, TJ, TI, TK> exec;
        exec(is_l, is_j, is_i, is_k, RAJA_LAMBDA(int l, int j, int i, int k){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_LJKI, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyL, typename POLICY::PolicyJ, typename POLICY::PolicyK, typename POLICY::PolicyI, TL, TJ, TK, TI> exec;
        exec(is_l, is_j, is_k, is_i, RAJA_LAMBDA(int l, int j, int k, int i){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_LKIJ, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyL, typename POLICY::PolicyK, typename POLICY::PolicyI, typename POLICY::PolicyJ, TL, TK, TI, TJ> exec;
        exec(is_l, is_k, is_i, is_j, RAJA_LAMBDA(int l, int k, int i, int j){
          body(i, j, k, l);
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
      RAJA_INLINE void forall4_permute(PERM_LKJI, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
        Forall4Executor<typename POLICY::PolicyL, typename POLICY::PolicyK, typename POLICY::PolicyJ, typename POLICY::PolicyI, TL, TK, TJ, TI> exec;
        exec(is_l, is_k, is_j, is_i, RAJA_LAMBDA(int l, int k, int j, int i){
          body(i, j, k, l);
        });
      }


/******************************************************************
 *  OpenMP Parallel Region forall4()
 ******************************************************************/

#ifdef _OPENMP

    template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
    RAJA_INLINE void forall4(Forall4_OMP_Parallel_Tag, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
      typedef typename POLICY::NextPolicy NextPolicy;
      typedef typename POLICY::NextPolicy::PolicyTag NextPolicyTag;
      // create OpenMP Parallel Region
#pragma omp parallel
      {
        // execute the next policy
        forall4<NextPolicy, TI, TJ, TK, TL, BODY>(NextPolicyTag(), is_i, is_j, is_k, is_l, body);
      }
    }

#endif


/******************************************************************
 *  Tiling Policy for forall4()
 ******************************************************************/

    template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
    RAJA_INLINE void forall4(Forall4_Tile_Tag, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
      typedef typename POLICY::NextPolicy NextPolicy;
      typedef typename POLICY::NextPolicy::PolicyTag NextPolicyTag;
      typedef typename POLICY::TileI TileI;
      typedef typename POLICY::TileJ TileJ;
      typedef typename POLICY::TileK TileK;
      typedef typename POLICY::TileL TileL;

      // execute the next policy
      forall_tile(TileI(), is_i, [=](auto is_ii){
        forall_tile(TileJ(), is_j, [=](auto is_jj){
          forall_tile(TileK(), is_k, [=](auto is_kk){
            forall_tile(TileL(), is_l, [=](auto is_ll){
              forall4<NextPolicy>(NextPolicyTag(), is_ii, is_jj, is_kk, is_ll, body);
            });
          });
        });
      });
    }



/******************************************************************
 *  Execute policy, forall4()
 ******************************************************************/

    template<typename POLICY, typename TI, typename TJ, typename TK, typename TL, typename BODY>
    RAJA_INLINE void forall4(Forall4_Execute_Tag, TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
      typedef typename POLICY::LoopOrder L;
      forall4_permute<POLICY, TI, TJ, TK, TL, BODY>(L(), is_i, is_j, is_k, is_l, body);
    }


/******************************************************************
 *  User interface, forall4()
 ******************************************************************/

    template<typename POLICY, typename IdxI=int, typename IdxJ=int, typename IdxK=int, typename IdxL=int, typename TI, typename TJ, typename TK, typename TL, typename BODY>
    RAJA_INLINE void forall4(TI const &is_i, TJ const &is_j, TK const &is_k, TL const &is_l, BODY const &body){
      typedef typename POLICY::PolicyTag PolicyTag;
      forall4<POLICY, TI, TJ, TK, TL>(PolicyTag(), is_i, is_j, is_k, is_l, 
        [=](int i, int j, int k, int l){
          body(IdxI(i), IdxJ(j), IdxK(k), IdxL(l));
        }
      );
    }


  
#endif

