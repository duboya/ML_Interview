#include <iostream>
#include <vector>
#include <stack>

using namespace std;


struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x = 0) :
			val(x), next(NULL) {
	}
};

//struct ListNode
//{
//	int val;
//	struct ListNode *next;
//	ListNode(int x = 0)
//		:
//		val(x), next(NULL) {
//	}
//};


class Solution {
public:
	ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
		if (k <= 0) {
			return NULL;
		}
		ListNode* head = pListHead;
		ListNode* node = pListHead;
		int first = -k;
		int length = 0;
		while (head) {
			if (first >= 0) {
				node = head;
			}
			first += 1;
			length += 1;
			head = head->next;
		}
		return first < 0 || first > length ? NULL : node;
	}
};


/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution_two {
public:
	ListNode* ReverseList(ListNode* pHead) {
		if (pHead == nullptr) {
			return nullptr;
		}
		ListNode* node;
		ListNode* end = pHead->next;
		while (end) {
			node = end;
			end = end->next;
			node->next = pHead;
			pHead = node;
		}
		return pHead;
	}
};
/*
int main()
{
	ListNode list[7];

	list[0].val = 1;
	list[0].next = &list[1];

	list[1].val = 2;
	list[1].next = &list[2];

	list[2].val = 3;
	list[2].next = &list[3];

	list[3].val = 3;
	list[3].next = &list[4];

	list[4].val = 4;
	list[4].next = &list[5];

	list[5].val = 5;
	list[5].next = &list[6];

	list[6].val = 6;
	list[6].next = NULL;



	ListNode *node;

	Solution_two solu;
	node = solu.ReverseList(list);
	cout << node->val << endl;

	return 0;
}
*/