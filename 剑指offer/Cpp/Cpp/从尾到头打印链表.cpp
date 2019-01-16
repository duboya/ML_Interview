//#include <iostream>
//#include <vector>
//#include <stack>
//
//using namespace std;
//
//
//
//struct ListNode {
//	int val;
//	struct ListNode *next;
//	//ListNode(int x) :
//	//	val(x), next(NULL) {
//	//}
//};
//
//class Solution {
//public:
//	vector<int> printListFromTailToHead(ListNode* head) {
//		stack<int> nodes;
//		vector<int> res;
//		ListNode* node = head;
//		while (node != NULL) {
//			nodes.push(node->val);
//			node = node->next;
//		}
//		while (!nodes.empty()) {
//			res.push_back(nodes.top());
//			nodes.pop();
//		}
//		return res;
//
//	}
//};
//
//
//int main()
//{
//	ListNode list[4];
//	list[0].val = 1;
//	list[0].next = &list[1];
//	list[1].val = 2;
//	list[1].next = &list[2];
//	list[2].val = 3;
//	list[2].next = &list[3];
//	list[3].val = 4;
//	list[3].next = NULL;
//
//
//
//	Solution solu;
//	vector<int> res = solu.printListFromTailToHead(list);
//
//	cout << "there are " << res.size() << "datas in vector" << endl;
//	for (int i = 0; i < res.size(); i++)
//	{
//		cout << res[i] << endl;
//	}
//	return 0;
//}