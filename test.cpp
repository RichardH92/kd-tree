#include "Point.h"
#include "Node.h"
#include "KD_Tree.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cstdlib>
#include <time.h>

using namespace std;

static void test_point_equals_1d();
static void test_num_dimensions();
static void test_get_coords();
static void test_point_distance();
static void test_point_equals_6d();
static void test_sort_points();
static void test_kd_tree_1d();
static void test_nearest_neighbor_1d();
static void test_nearest_neighbor_multiple_points();
static void time_comparison_multiple_searches();

int total = 0;
int passed = 0;

int main() {
	test_point_equals_1d();
	test_num_dimensions();
	test_get_coords();
	test_point_distance();
	test_point_equals_6d();
	test_sort_points();
	test_kd_tree_1d();
	test_nearest_neighbor_1d();

	cout << "\r\nPassed tests: " << passed << "/" << total << "\r\n\r\n";

	test_nearest_neighbor_multiple_points();
	time_comparison_multiple_searches();

	//char test;
	//cin >> test;
}

static void test_point_equals_1d() {
	cout << "test_point_equals_1d:\t\t\t";
	total++;

	Point<1, int> a(1);
	Point<1, int> b(1);

	a[0] = 1;
	b[0] = 1;

	if (a == b) {
		cout << "PASS\r\n";
		passed++;
	}
	else
		cout << "FAIL\r\n";
}

static void test_num_dimensions() {
	cout << "test_num_dimensions:\t\t\t";
	total++;

	Point<4, int> a(1);

	if (a.num_dimensions() == 4) {
		cout << "PASS\r\n";
		passed++;
	}
	else
		cout << "FAIL\r\n";
}

static void test_get_coords() {
	cout << "test_get_coords:\t\t\t";
	total++;

	double coords[4];
	coords[0] = 0.22;
	coords[1] = 0.56;
	coords[2] = 0.74;
	coords[3] = 0.53;

	Point<4, int> a(1);
	a[0] = coords[0];
	a[1] = coords[1];
	a[2] = coords[2];
	a[3] = coords[3];

	for (int i = 0; i < 4; i++) {
		if (a[i] != coords[i]) {
			cout << "FAIL\r\n";
			return;
		}
	}

	cout << "PASS\r\n";
	passed++;
}

static void test_point_distance() {
	cout << "test_point_distance:\t\t\t";
	total++;

	Point<3, int> a_x(1);
	a_x[0] = 4.4;
	a_x[1] = 3.5;
	a_x[2] = -7.4;

	Point<3, int> b_x(1);
	b_x[0] = -2.2;
	b_x[1] = 3.6;
	b_x[2] = 4.5;

	double dist = sqrt((a_x[0] - b_x[0]) * (a_x[0] - b_x[0]) + (a_x[1] - b_x[1]) * (a_x[1] - b_x[1]) + (a_x[2] - b_x[2]) * (a_x[2] - b_x[2]));

	double dist_two = point_distance(a_x, b_x);

	if (dist_two != dist)
		cout << "FAIL\r\n";
	else {
		cout << "PASS\r\n";
		passed++;
	}
}

static void test_point_equals_6d() {
	cout << "test_point_equals_6d:\t\t\t";
	total++;

	double a_x[6];
	a_x[0] = 6.6;
	a_x[1] = 4.3;
	a_x[2] = 6.8;
	a_x[3] = -8.8;
	a_x[4] = 2.5;
	a_x[5] = -3.7;

	Point<6, int> a(1);
	Point<6, int> b(1);

	for (size_t i = 0; i < 6; i++) {
		a[i] = a_x[i];
		b[i] = a_x[i];
	}

	if (a == b) {
		cout << "PASS\r\n";
		passed++;
	}
	else
		cout << "FAIL\r\n";
}

static void test_sort_points() {
	cout << "test_sort_points:\t\t\t";
	total++;

	Point<1, int> a(1);
	a[0] = 89;
	Point<1, int> b(1);
	b[0] = 3;
	Point<1, int> c(1);
	c[0] = 32;
	Point<1, int> d(1);
	d[0] = 8;
	Point<1, int> e(1);
	e[0] = 2;
	Point<1, int> f(1);
	f[0] = 26;
	Point<1, int> g(1);
	g[0] = 12;
	Point<1, int> h(1);
	h[0] = 5;

	vector<Point<1, int>> points;
	points.push_back(a);
	points.push_back(b);
	points.push_back(c);
	points.push_back(d);
	points.push_back(e);
	points.push_back(f);
	points.push_back(g);
	points.push_back(h);

	sort_points(points, 0);

	if (points[0] != e || points[1] != b || points[2] != h || points[3] != d || points[4] != g || points[5] != f || points[6] != c || points[7] != a)
		cout << "FAIL\r\n";
	else {
		cout << "PASS\r\n";
		passed++;
	}
}

static void test_kd_tree_1d() {
	cout << "test_kd_tree_1d:\t\t\t";
	total++;

	Point<1, int> a(1);
	a[0] = 89;
	Point<1, int> b(1);
	b[0] = 3;
	Point<1, int> c(1);
	c[0] = 32;
	Point<1, int> d(1);
	d[0] = 8;
	Point<1, int> e(1);
	e[0] = 2;
	Point<1, int> f(1);
	f[0] = 26;
	Point<1, int> g(1);
	g[0] = 12;
	Point<1, int> h(1);
	h[0] = 5;

	vector<Point<1, int>> points;
	points.push_back(a);
	points.push_back(b);
	points.push_back(c);
	points.push_back(d);
	points.push_back(e);
	points.push_back(f);
	points.push_back(g);
	points.push_back(h);

	KD_Tree<1, int> tree(points);

	if (tree.root->get_point()[0] != 12) {
		cout << "FAIL\r\n";
		return;
	}

	if (tree.root->left->get_point()[0] != 5) {
		cout << "FAIL\r\n";
		return;
	}

	if (tree.root->left->left->get_point()[0] != 3) {
		cout << "FAIL\r\n";
		return;
	}

	if (tree.root->left->left->left->get_point()[0] != 2) {
		cout << "FAIL\r\n";
		return;
	}

	if (tree.root->left->right->get_point()[0] != 8) {
		cout << "FAIL\r\n";
		return;
	}

	if (tree.root->right->get_point()[0] != 32) {
		cout << "FAIL\r\n";
		return;
	}

	if (tree.root->right->left->get_point()[0] != 26) {
		cout << "FAIL\r\n";
		return;
	}

	if (tree.root->right->right->get_point()[0] != 89) {
		cout << "FAIL\r\n";
		return;
	}

	passed++;
	cout << "PASS\r\n";
}

static void test_nearest_neighbor_1d() {
	cout << "test_nearest_neighbor_1d:\t\t";
	total++;

	Point<1, int> a(1);
	a[0] = 89;
	Point<1, int> b(1);
	b[0] = 3;
	Point<1, int> c(1);
	c[0] = 32;
	Point<1, int> d(1);
	d[0] = 8;
	Point<1, int> e(1);
	e[0] = 2;
	Point<1, int> f(1);
	f[0] = 26;
	Point<1, int> g(1);
	g[0] = 12;
	Point<1, int> h(1);
	h[0] = 5;

	vector<Point<1, int>> points;
	points.push_back(a);
	points.push_back(b);
	points.push_back(c);
	points.push_back(d);
	points.push_back(e);
	points.push_back(f);
	points.push_back(g);
	points.push_back(h);

	KD_Tree<1, int> tree(points);

	Point<1, int> i(1);
	i[0] = 3.2;

	if(tree.nearest_neighbor(i) == b) {
		cout << "PASS\r\n";
		passed++;
	}
	else
		cout << "FAIL\r\n";
}

static void test_nearest_neighbor_multiple_points() {
	cout << "\r\ntest_nearest_neighbor_multiple_points:\t";

	size_t num_points = 1000;
	size_t num_searches = 1000;

	srand (time(NULL));

	//build the vector
	vector<Point<5, string>> points;
	for (size_t i = 0; i < num_points; i++) {
		Point<5, string> p("Test");

		for (size_t j = 0; j < 3; j++)
			p[j] = rand() % 100 - 100;

		points.push_back(p);
	}

	//Build the tree
	KD_Tree<5, string> *tree = new KD_Tree<5, string>(points);

	for (size_t i = 0; i < num_searches; i++) {

		Point<5, string> test_point("Test");
		for (size_t i = 0; i < 5; i++)
			test_point[i] = rand() % 100 - 100;

		double min_dist = 999999;
		Point<5, string> min_point_linear("Temp");

		for (size_t i = 0; i < num_points; i++) {
			if (point_distance(points[i], test_point) < min_dist) {
				min_dist = point_distance(points[i], test_point);
				min_point_linear = points[i];
			}
		}

		Point<5, string> min_point_knn("Temp");
		min_point_knn = tree->nearest_neighbor(test_point);

		if (min_point_knn != min_point_linear) {
			cout << "\r\n\r\nKD-Tree and linear search did not find the same point.\r\n";
			cout << "KD-Tree point distance: " << point_distance(min_point_knn, test_point);
			cout << "\r\nLinear point distance: " << min_dist;
		}
	}

	delete tree;
	cout << "\r\n";
}

static void time_comparison_multiple_searches() {
	cout << "\r\n\r\ntime_comparison_multiple_searches:\r\n\r\n";

	size_t num_points = 10000;
	size_t num_searches = 10000;

	srand (time(NULL));

	//build the vector
	vector<Point<5, string>> points;
	for (size_t i = 0; i < num_points; i++) {
		Point<5, string> p("Test");

		for (size_t j = 0; j < 3; j++)
			p[j] = rand() % 100 - 100;

		points.push_back(p);
	}

	clock_t linear_begin = clock();

	for (size_t i = 0; i < num_searches; i++) {
		Point<5, string> test_point("Test");
		for (size_t i = 0; i < 5; i++)
			test_point[i] = rand() % 100 - 100;

		double min_dist = 999999;
		Point<5, string> min_point_linear("Temp");

		for (size_t i = 0; i < num_points; i++) {
			if (point_distance(points[i], test_point) < min_dist) {
				min_dist = point_distance(points[i], test_point);
				min_point_linear = points[i];
			}
		}
	}

	clock_t linear_end = clock();
	double linear_time = ((double) (linear_end - linear_begin)) / CLOCKS_PER_SEC;

	cout << "Linear search time: " << linear_time << "\r\n";

	clock_t tree_build_begin = clock();
	KD_Tree<5, string> *tree = new KD_Tree<5, string>(points);
	clock_t tree_build_end = clock();
	double build_time = ((double) (tree_build_end - tree_build_begin)) / CLOCKS_PER_SEC;

	cout << "KD-Tree construction time: " << build_time << "\r\n";

	clock_t knn_begin = clock();
	for (size_t i = 0; i < num_searches; i++) {
		Point<5, string> test_point("Test");
		for (size_t i = 0; i < 5; i++)
			test_point[i] = rand() % 100 - 100;

		tree->nearest_neighbor(test_point);
	}

	clock_t knn_end = clock();
	double knn_time = ((double) (knn_end - knn_begin)) / CLOCKS_PER_SEC;

	cout << "kNN search time: " << knn_time << "\r\n";

	double increase = linear_time / knn_time;
	cout << "kNN search was " << increase << " times faster.\r\n";

	delete tree;
}
