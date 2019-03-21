#include <iostream>
#include <vector>

using namespace std;

void Merge(vector<int> &input, int left, int mid, int right, vector<int> temp) {
	int i = left;				// i是第一段序列的下标
	int j = mid + 1;			// j是第二段序列的下标
	int k = 0;					// k是临时存放合并序列的下标

	// 扫描第一段和第二段序列，直到有一个扫描结束
	while (i <= mid && j <= right) {
		// 判断第一段和第二段取出的数哪个更小，将其存入合并序列，并继续向下扫描
		if (input[i] <= input[j]) {
			temp[k++] = input[i++];
		}
		else {
			temp[k++] = input[j++];
		}
	}
	// 若第一段序列还没扫描完，将其全部复制到合并序列
	while (i <= mid) {
		temp[k++] = input[i++];
	}

	// 若第二段序列还没扫描完，将其全部复制到合并序列
	while (j <= right) {
		temp[k++] = input[j++];
	}

	k = 0;
	// 将合并序列复制到原始序列中
	while (left <= right) {
		input[left++] = temp[k++];
	}
}

void MergeSort(vector<int> &input, int left, int right, vector<int> temp) {
	if (left < right) {
		int mid = (right + left) >> 1;
		MergeSort(input, left, mid, temp);
		MergeSort(input, mid + 1, right, temp);
		Merge(input, left, mid, right, temp);
	}
}



void mergesort(vector<int> &input) {
	// 在排序前，先建好一个长度等于原数组长度的临时数组，避免递归中频繁开辟空间
	vector<int> temp(input.size());
	MergeSort(input, 0, input.size() - 1, temp);
}

void main() {
	int arr[] = { 6, 4, 8, 9, 2, 3, 1 };
	vector<int> test(arr, arr + sizeof(arr) / sizeof(arr[0]));
	cout << "排序前:";
	for (int i = 0; i < test.size(); i++) {
		cout << test[i] << " ";
	}
	cout << endl;

	vector<int> result = test;
	mergesort(result);
	cout << "排序后:";
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << " ";
	}
	cout << endl;
	system("pause");
}
