#include <iostream>
#include <vector>

using namespace std;

void Merge(vector<int> &input, int left, int mid, int right, vector<int> temp) {
	int i = left;				// i�ǵ�һ�����е��±�
	int j = mid + 1;			// j�ǵڶ������е��±�
	int k = 0;					// k����ʱ��źϲ����е��±�

	// ɨ���һ�κ͵ڶ������У�ֱ����һ��ɨ�����
	while (i <= mid && j <= right) {
		// �жϵ�һ�κ͵ڶ���ȡ�������ĸ���С���������ϲ����У�����������ɨ��
		if (input[i] <= input[j]) {
			temp[k++] = input[i++];
		}
		else {
			temp[k++] = input[j++];
		}
	}
	// ����һ�����л�ûɨ���꣬����ȫ�����Ƶ��ϲ�����
	while (i <= mid) {
		temp[k++] = input[i++];
	}

	// ���ڶ������л�ûɨ���꣬����ȫ�����Ƶ��ϲ�����
	while (j <= right) {
		temp[k++] = input[j++];
	}

	k = 0;
	// ���ϲ����и��Ƶ�ԭʼ������
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
	// ������ǰ���Ƚ���һ�����ȵ���ԭ���鳤�ȵ���ʱ���飬����ݹ���Ƶ�����ٿռ�
	vector<int> temp(input.size());
	MergeSort(input, 0, input.size() - 1, temp);
}

void main() {
	int arr[] = { 6, 4, 8, 9, 2, 3, 1 };
	vector<int> test(arr, arr + sizeof(arr) / sizeof(arr[0]));
	cout << "����ǰ:";
	for (int i = 0; i < test.size(); i++) {
		cout << test[i] << " ";
	}
	cout << endl;

	vector<int> result = test;
	mergesort(result);
	cout << "�����:";
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << " ";
	}
	cout << endl;
	system("pause");
}
