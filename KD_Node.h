#ifndef KD_NODE_H
#define KD_NODE_H

#include "Point.h"

template <size_t N, typename ElemType>
class KD_Node {
public:
	KD_Node(Point<N, ElemType> &point);
	~KD_Node();

	KD_Node *left = NULL;
	KD_Node *right = NULL;

	size_t num_dimensions() const;
	Point<N, ElemType> &get_point();
	bool equals(KD_Node<N, ElemType> *b);

private:
	Point<N, ElemType> p;
};

template <size_t N, typename ElemType>
KD_Node<N, ElemType>::KD_Node(Point<N, ElemType> &point) : p(point.get_elem()){
	for (size_t i = 0; i < N; i++)
		p[i] = point[i];
}

template <size_t N, typename ElemType>
KD_Node<N, ElemType>::~KD_Node() {
	if (left != NULL)
		delete left;
	if (right != NULL)
		delete right;
}

template <size_t N, typename ElemType>
size_t KD_Node<N, ElemType>::num_dimensions() const {
	return N;
}

template <size_t N, typename ElemType>
Point<N, ElemType> &KD_Node<N, ElemType>::get_point() {
	return p;
}

template <size_t N, typename ElemType>
bool KD_Node<N, ElemType>::equals(KD_Node<N, ElemType> *b) {
	if (p == b->get_point())
		return true;

	return false;
}

#endif