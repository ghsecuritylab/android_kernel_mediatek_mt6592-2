// Copyright (C) 2012 Désiré Nuentsa-Wakam <desire.nuentsa_wakam@inria.fr>
// Public License v. 2.0. If a copy of the MPL was not distributed

#ifndef EIGEN_INCOMPLETE_CHOlESKY_H
#define EIGEN_INCOMPLETE_CHOlESKY_H
#include "Eigen/src/IterativeLinearSolvers/IncompleteLUT.h" 
#include <Eigen/OrderingMethods>
#include <list>

namespace Eigen {  

template <typename Scalar, int _UpLo = Lower, typename _OrderingType = NaturalOrdering<int> >
class IncompleteCholesky : internal::noncopyable
{
  public:
    typedef SparseMatrix<Scalar,ColMajor> MatrixType;
    typedef _OrderingType OrderingType;
    typedef typename MatrixType::RealScalar RealScalar; 
    typedef typename MatrixType::Index Index; 
    typedef PermutationMatrix<Dynamic, Dynamic, Index> PermutationType;
    typedef Matrix<Scalar,Dynamic,1> ScalarType; 
    typedef Matrix<Index,Dynamic, 1> IndexType;
    typedef std::vector<std::list<Index> > VectorList; 
    enum { UpLo = _UpLo };
  public:
    IncompleteCholesky() : m_shift(1),m_factorizationIsOk(false) {}
    IncompleteCholesky(const MatrixType& matrix) : m_shift(1),m_factorizationIsOk(false)
    {
      compute(matrix);
    }
    
    Index rows() const { return m_L.rows(); }
    
    Index cols() const { return m_L.cols(); }
    

    ComputationInfo info() const
    {
      eigen_assert(m_isInitialized && "IncompleteLLT is not initialized.");
      return m_info;
    }
    
    void setShift( Scalar shift) { m_shift = shift; }
    
    template<typename MatrixType>
    void analyzePattern(const MatrixType& mat)
    {
      OrderingType ord; 
      ord(mat.template selfadjointView<UpLo>(), m_perm); 
      m_analysisIsOk = true; 
    }
    
    template<typename MatrixType>
    void factorize(const MatrixType& amat);
    
    template<typename MatrixType>
    void compute (const MatrixType& matrix)
    {
      analyzePattern(matrix); 
      factorize(matrix);
    }
    
    template<typename Rhs, typename Dest>
    void _solve(const Rhs& b, Dest& x) const
    {
      eigen_assert(m_factorizationIsOk && "factorize() should be called first");
      if (m_perm.rows() == b.rows())
        x = m_perm.inverse() * b; 
      else 
        x = b; 
      x = m_scal.asDiagonal() * x;
      x = m_L.template triangularView<UnitLower>().solve(x); 
      x = m_L.adjoint().template triangularView<Upper>().solve(x); 
      if (m_perm.rows() == b.rows())
        x = m_perm * x;
      x = m_scal.asDiagonal() * x;
    }
    template<typename Rhs> inline const internal::solve_retval<IncompleteCholesky, Rhs>
    solve(const MatrixBase<Rhs>& b) const
    {
      eigen_assert(m_factorizationIsOk && "IncompleteLLT did not succeed");
      eigen_assert(m_isInitialized && "IncompleteLLT is not initialized.");
      eigen_assert(cols()==b.rows()
                && "IncompleteLLT::solve(): invalid number of rows of the right hand side matrix b");
      return internal::solve_retval<IncompleteCholesky, Rhs>(*this, b.derived());
    }
  protected:
    SparseMatrix<Scalar,ColMajor> m_L;  
    ScalarType m_scal; 
    Scalar m_shift; 
    bool m_analysisIsOk; 
    bool m_factorizationIsOk; 
    bool m_isInitialized;
    ComputationInfo m_info;
    PermutationType m_perm; 
    
  private:
    template <typename IdxType, typename SclType>
    inline void updateList(const IdxType& colPtr, IdxType& rowIdx, SclType& vals, const Index& col, const Index& jk, IndexType& firstElt, VectorList& listCol); 
}; 

template<typename Scalar, int _UpLo, typename OrderingType>
template<typename _MatrixType>
void IncompleteCholesky<Scalar,_UpLo, OrderingType>::factorize(const _MatrixType& mat)
{
  using std::sqrt;
  using std::min;
  eigen_assert(m_analysisIsOk && "analyzePattern() should be called first"); 
    
  
  
  
  if (m_perm.rows() == mat.rows() ) 
    m_L.template selfadjointView<Lower>() = mat.template selfadjointView<_UpLo>().twistedBy(m_perm);
  else
    m_L.template selfadjointView<Lower>() = mat.template selfadjointView<_UpLo>();
  
  Index n = m_L.cols(); 
  Index nnz = m_L.nonZeros();
  Map<ScalarType> vals(m_L.valuePtr(), nnz); 
  Map<IndexType> rowIdx(m_L.innerIndexPtr(), nnz);  
  Map<IndexType> colPtr( m_L.outerIndexPtr(), n+1); 
  IndexType firstElt(n-1); 
  VectorList listCol(n); 
  ScalarType curCol(n); 
  IndexType irow(n); 
  
  
  
  m_scal.resize(n);
  for (int j = 0; j < n; j++)
  {
    m_scal(j) = m_L.col(j).norm();
    m_scal(j) = sqrt(m_scal(j));
  }
  
  Scalar mindiag = vals[0];
  for (int j = 0; j < n; j++){
    for (int k = colPtr[j]; k < colPtr[j+1]; k++)
     vals[k] /= (m_scal(j) * m_scal(rowIdx[k]));
    mindiag = (min)(vals[colPtr[j]], mindiag);
  }
  
  if(mindiag < Scalar(0.)) m_shift = m_shift - mindiag;
  
  for (int j = 0; j < n; j++)
    vals[colPtr[j]] += m_shift;
  
  for (int j=0; j < n; ++j)
  {  
    
    
    Scalar diag = vals[colPtr[j]];  
    curCol.setZero();
    irow.setLinSpaced(n,0,n-1); 
    for (int i = colPtr[j] + 1; i < colPtr[j+1]; i++)
    {
      curCol(rowIdx[i]) = vals[i]; 
      irow(rowIdx[i]) = rowIdx[i]; 
    }
    std::list<int>::iterator k; 
    
    for(k = listCol[j].begin(); k != listCol[j].end(); k++) 
    {
      int jk = firstElt(*k); 
      jk += 1; 
      for (int i = jk; i < colPtr[*k+1]; i++)
      {
        curCol(rowIdx[i]) -= vals[i] * vals[jk] ;
      }
      updateList(colPtr,rowIdx,vals, *k, jk, firstElt, listCol);
    }
    
    
    if(RealScalar(diag) <= 0) 
    {
      std::cerr << "\nNegative diagonal during Incomplete factorization... "<< j << "\n";
      m_info = NumericalIssue; 
      return; 
    }
    RealScalar rdiag = sqrt(RealScalar(diag));
    vals[colPtr[j]] = rdiag;
    for (int i = j+1; i < n; i++)
    {
      
      curCol(i) /= rdiag;
      
      vals[colPtr[i]] -= curCol(i) * curCol(i);
    }
    
    
    int p = colPtr[j+1] - colPtr[j] - 1 ; 
    internal::QuickSplit(curCol, irow, p); 
    
    int cpt = 0; 
    for (int i = colPtr[j]+1; i < colPtr[j+1]; i++)
    {
      vals[i] = curCol(cpt); 
      rowIdx[i] = irow(cpt); 
      cpt ++; 
    }
    
    Index jk = colPtr(j)+1;
    updateList(colPtr,rowIdx,vals,j,jk,firstElt,listCol); 
  }
  m_factorizationIsOk = true; 
  m_isInitialized = true;
  m_info = Success; 
}

template<typename Scalar, int _UpLo, typename OrderingType>
template <typename IdxType, typename SclType>
inline void IncompleteCholesky<Scalar,_UpLo, OrderingType>::updateList(const IdxType& colPtr, IdxType& rowIdx, SclType& vals, const Index& col, const Index& jk, IndexType& firstElt, VectorList& listCol)
{
  if (jk < colPtr(col+1) )
  {
    Index p = colPtr(col+1) - jk;
    Index minpos; 
    rowIdx.segment(jk,p).minCoeff(&minpos);
    minpos += jk;
    if (rowIdx(minpos) != rowIdx(jk))
    {
      
      std::swap(rowIdx(jk),rowIdx(minpos));
      std::swap(vals(jk),vals(minpos));
    }
    firstElt(col) = jk;
    listCol[rowIdx(jk)].push_back(col);
  }
}
namespace internal {

template<typename _Scalar, int _UpLo, typename OrderingType, typename Rhs>
struct solve_retval<IncompleteCholesky<_Scalar,  _UpLo, OrderingType>, Rhs>
  : solve_retval_base<IncompleteCholesky<_Scalar, _UpLo, OrderingType>, Rhs>
{
  typedef IncompleteCholesky<_Scalar, _UpLo, OrderingType> Dec;
  EIGEN_MAKE_SOLVE_HELPERS(Dec,Rhs)

  template<typename Dest> void evalTo(Dest& dst) const
  {
    dec()._solve(rhs(),dst);
  }
};

} 

} 

#endif
