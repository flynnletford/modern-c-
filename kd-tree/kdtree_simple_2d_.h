#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// (c) 2014 Stefan Romberg, sromberg@web.de
//
// License: Proprietary. Not for re-distribution. Neither for commercial nor
//          non-commercial use. Do not use in production code.
//          This piece of code was created for educational purposes only.
//
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
#define _USE_MATH_DEFINES
#include <cassert>
#include <climits>
#include <cfloat>
#include <cstdlib>
#include <vector>
#include <iostream>

#include "kdtree_simple_types.h"

using std::vector;

// =============================================================================
namespace kdtree_example
{

///
/// A kd-tree for efficient 2-D orthogonal range search and nearest neighbor search.
/// This class is optimized for speed and memory size.
/// 
class KdTreeSimple2d_
{
public:
	/// Splitting value
	float             splitVal;

	/// Left child
	KdTreeSimple2d_*  v_left;

	/// Right child
	KdTreeSimple2d_*  v_right;

	/// IdxPtd
	IdxPt2d           pt;

	/// Represents the (sub)-region that this node spans within the partitioned 2D space.
	Region2d          region;
	
	/// Ctor for leaves.
	KdTreeSimple2d_(const IdxPt2d& p) : splitVal(0), v_left(0), v_right(0), pt(p) {}
	
	/// Default Ctor.
	KdTreeSimple2d_() : splitVal(0), v_left(0), v_right(0), pt(-FLT_MAX, -FLT_MAX) {}
	
	/// Dtor.
	~KdTreeSimple2d_();
	
	/// Creates a kd-tree that indexes the given list of Points2d.
	static KdTreeSimple2d_* build(Points2d P /* copy */);
	
	/// Performs a range search and returns all Points2d inside the region *R*.
	/// Points2d on the boundary of *R* are included.
	void rangeSearch(const Region2d& R_query, Points2d& pts /* out */) const;
	
	/// Performs a radius search and returns all Points2d around `(x, y)` within
	/// distance <= *radius*. Points2d on the boundary i.e. circle are included.
	void radiusSearch(float x, float y, float radius, Points2d& found) const;
	
	/// Performs a radius search and returns all Points2d around `(x, y)` with
	/// `minDist <= distance <= maxDist`. Points2d on the boundary i.e. circle are included.
	void radiusSearch(float x, float y, float minDist, float maxDist, Points2d& found) const;
	
	/// Performs a 1-nearest neighbor search and returns the closest point to `(x, y)`. 
	void nnSearch(float x, float y, IdxPt2d& found, float& distance) const;
	
	/// Performs a k-nearest neighbor search and returns the *k* closest Points2d to `(x, y)`. 
	void knnSearch(float x, float y, int knn, Points2d& found, vector<float>& distances) const;
	
	/// Determines if the current sub-tree is a leaf.
	bool isLeaf() const { return (v_left == NULL); }
	
private:
	/// Appends all Points2d within the subtree starting a *this* node to *pts*.
	void reportSubTree(Points2d& pts /* out */) const;
	
	/// Appends indexes of all Points2d within the subtree starting a *this* node to *pts*.
	void reportSubTree(vector<int>& indexes /* out */) const;
	
	/// \internal
	void _nnSearch(float q_x, float q_y, IdxPt2d& best_node, float& min_dist, int depth, int& visitedNodes) const;
	
	/// \internal
	void _knnSearch(float q_x, float q_y, int knn, int depth, int& visitedNodes, Points2d& found, void* pq) const;
	
	/// \internal
	static KdTreeSimple2d_* build(Points2d& P, int depth);
	
	KdTreeSimple2d_(const KdTreeSimple2d_& rhs);              ///< Forbidden
	KdTreeSimple2d_& operator = (const KdTreeSimple2d_& rhs); ///< Forbidden
};

}
