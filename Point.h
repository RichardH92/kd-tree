#ifndef POINT_INCLUDED
#define POINT_INCLUDED

#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

template <size_t N, typename ElemType>
class Point {
public:
	Point(ElemType p_elem);
	size_t num_dimensions() const;
	double &operator[](size_t i);
	ElemType &get_elem();

private:
	double coords[N];
	ElemType elem;
};

template <size_t N, typename ElemType>
Point<N, ElemType>::Point(ElemType p_elem) {
	elem = p_elem;
}

template <size_t N, typename ElemType>
size_t Point<N, ElemType>::num_dimensions() const {
	return N;
}

template <size_t N, typename ElemType>
double &Point<N, ElemType>::operator[](size_t i) {
	return coords[i];
}

template <size_t N, typename ElemType>
ElemType &Point<N, ElemType>::get_elem() {
	return elem;
}

template <size_t N, typename ElemType>
double point_distance(Point<N, ElemType> &a, Point<N, ElemType> &b) {
	double result = 0.0;

	for (size_t i = 0; i < N; i++)
		result += (a[i] - b[i]) * (a[i] - b[i]);

	return sqrt(result);
}

template <size_t N, typename ElemType>
bool operator==(Point<N, ElemType> &a, Point<N, ElemType> &b) {
	for (size_t i = 0; i < N; i++)
		if (a[i] != b[i])
			return false;

	return true;
}

template <size_t N, typename ElemType>
bool operator!=(Point<N, ElemType> &a, Point<N, ElemType> &b) {
	return !(a == b);
}

template <size_t N, typename ElemType>
void sort_points(vector<Point<N, ElemType>> &points, size_t dimension) {
	assert(dimension < N);
	quicksort_points(points, 0, points.size() - 1, dimension);
}

template <size_t N, typename ElemType>
void quicksort_points(vector<Point<N, ElemType>> &points, int low, int high, size_t dimension) {
	if (low < high) {
		size_t pivot = partition_points(points, low, high, dimension);
		quicksort_points(points, low, pivot - 1, dimension);
		quicksort_points(points, pivot + 1, high, dimension);
	}
}

template <size_t N, typename ElemType>
size_t partition_points(vector<Point<N, ElemType>> &points, int low, int high, size_t dimension) {
	assert(dimension < N);

	size_t pivot = choose_pivot(low, high);
	Point<N, ElemType> pivot_value = points[pivot];
	Point<N, ElemType> temp = points[pivot];
	points[pivot] = points[high];
	points[high] = temp;
	size_t store_index = low;

	for (size_t i = low; i < high; i++) {
		if (points[i][dimension] < pivot_value[dimension]) {
			temp = points[i];
			points[i] = points[store_index];
			points[store_index] = temp;
			store_index++;
		}
	}

	temp = points[store_index];
	points[store_index] = points[high];
	points[high] = temp;

	return store_index;
}

size_t choose_pivot(int low, int high) {
	return (high + low) / 2;
}

#endif
