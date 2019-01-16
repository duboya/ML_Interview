# -*- coding:utf-8 -*-
class Solution:
    def Power(self, base, exponent):
        # write code here
        exp = abs(exponent) & 0xffffffff
        res = 1
        while(exp != 0):
            if exp & 1:
                res *= base
            base *= base
            exp >>= 1
        return res if exponent > 0 else 1/res





S = Solution()
print(S.Power(5, 2))