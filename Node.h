#ifndef NODE_H
#define NODE_H

#include "Point.h"

template <size_t N, typename ElemType>
class Node {
public:
	Node(Point<N, ElemType> &point);

	Node *left = NULL;
	Node *right = NULL;

	size_t num_dimensions() const;
	Point<N, ElemType> &get_point();
	bool equals(Node<N, ElemType> *b);

private:
	Point<N, ElemType> p;
};

template <size_t N, typename ElemType>
Node<N, ElemType>::Node(Point<N, ElemType> &point) : p(point.get_elem()){
	for (size_t i = 0; i < N; i++)
		p[i] = point[i];
}

template <size_t N, typename ElemType>
size_t Node<N, ElemType>::num_dimensions() const {
	return N;
}

template <size_t N, typename ElemType>
Point<N, ElemType> &Node<N, ElemType>::get_point() {
	return p;
}

template <size_t N, typename ElemType>
bool Node<N, ElemType>::equals(Node<N, ElemType> *b) {
	if (p == b->get_point())
		return true;

	return false;
}

#endif