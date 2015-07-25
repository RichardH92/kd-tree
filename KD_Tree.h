#ifndef KD_TREE
#define KD_TREE

#include "Node.h"
#include "Point.h"
#include <assert.h>
#include <vector>
#include <cmath>

template <size_t N, typename ElemType>
class KD_Tree {
public:
	KD_Tree(vector<Point<N, ElemType>> &points);
	size_t num_dimensions() const; 
	Node<N, ElemType> *root;
	Point<N, ElemType> &nearest_neighbor(Point<N, ElemType> &test_point);

private:
	Node<N, ElemType> *best_guess = NULL;
	double best_dist = 9999999;

	Node<N, ElemType> *build_tree(size_t depth, vector<Point<N, ElemType>> &points);
	size_t get_median(vector<Point<N, ElemType>> points);
	void sort_list(size_t depth, vector<Point<N, ElemType>> &points);
	void nearest_neighbor_helper(Point<N, ElemType> &test_point, Node<N, ElemType> *curr, size_t depth);

};

template <size_t N, typename ElemType>
KD_Tree<N, ElemType>::KD_Tree(vector<Point<N, ElemType>> &points) {
	root = build_tree(0, points);
}

template <size_t N, typename ElemType>
Node<N, ElemType> *KD_Tree<N, ElemType>::build_tree(size_t depth, vector<Point<N, ElemType>> &points) {
	if (points.empty())
		return NULL;

	if (depth == N)
		depth = 0;

	//Sort points in their depth dimension
	sort_points(points, depth);
	//Get the median location
	size_t median = get_median(points);

	vector<Point<N, ElemType>> list_two;

	//Pop the larger half of points from the original list and add them to list_two
	for (size_t i = points.size() - 1; i > median; i--) {
		list_two.push_back(points.back());
		points.pop_back();
	}

	//Create a node out of the median point
	Node<N, ElemType> *new_node;
	new_node = new Node<N, ElemType>(points.back());
	points.pop_back();

	new_node->left = build_tree(depth + 1, points);
	new_node->right = build_tree(depth + 1, list_two);

	return new_node;
}

template <size_t N, typename ElemType>
size_t KD_Tree<N, ElemType>::get_median(vector<Point<N, ElemType>> points) {
	return points.size() / 2;
}

template <size_t N, typename ElemType>
Point<N, ElemType> &KD_Tree<N, ElemType>::nearest_neighbor(Point<N, ElemType> &test_point) {
	nearest_neighbor_helper(test_point, root, 0);

	return best_guess->get_point(); 
}

template <size_t N, typename ElemType>
void KD_Tree<N, ElemType>::nearest_neighbor_helper(Point<N, ElemType> &test_point, 
	Node<N, ElemType> *curr, size_t depth) {
	if (curr == NULL)
		return;

	if (depth == N)
		depth = 0;

	if (point_distance(curr->get_point(), test_point) < best_dist) {
		best_dist = point_distance(curr->get_point(), test_point);
		best_guess = curr;
	}

	if (test_point[depth] < curr->get_point()[depth]) {
		nearest_neighbor_helper(test_point, curr->left, depth + 1);

		if (	abs(curr->get_point()[depth] - test_point[depth]) < best_dist)
			nearest_neighbor_helper(test_point, curr->right, depth + 1);
	}
	else {
		nearest_neighbor_helper(test_point, curr->right, depth + 1);

		if (abs(curr->get_point()[depth] - test_point[depth]) < best_dist)
			nearest_neighbor_helper(test_point, curr->left, depth + 1);
	}

}

#endif