//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//
//
//#define __main main
//class Solution {
//public:
//	bool Find(int target, vector<vector<int> > array) {
//		int row = array.size() - 1;
//		int col = 0;
//		for (; row >= 0 && col < array[0].size();) {
//			if (target == array[row][col]) {
//				return true;
//			}
//			else if (target > array[row][col]) {
//				col++;
//			}
//			else if (target < array[row][col]) {
//				row--;
//			}
//		}
//		return false;
//	}
//};
//
//
//
//
//int __main()
//{
//	int a1[] = { 1, 2 };
//	int a2[] = { 2, 4 };
//	//int a3[] = { 4, 7, 10, 13, };
//	//int a4[] = { 6, 8, 11, 15, };
//	vector<vector<int>> array;
//	array.push_back(vector<int>(a1, a1 + 2));
//	array.push_back(vector<int>(a2, a2 + 2));
//	//array.push_back(vector<int>(a3, a3 + 4));
//	//array.push_back(vector<int>(a4, a4 + 4));
//
//	Solution solu;
//	bool res = solu.Find(2, array);
//	cout << "Hello world" << endl;
//	cout << "res:" << res << endl;
//	return 0;
//}