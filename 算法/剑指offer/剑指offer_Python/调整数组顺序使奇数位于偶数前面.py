# -*- coding:utf-8 -*-
class Solution:
    def reOrderArray(self, array):
        # write code here
        return sorted(array, key=lambda c: c % 2, reverse=True)


array = [4, 1, 7, 2, 5, 8]
test = Solution()
print(test.reOrderArray(array))
