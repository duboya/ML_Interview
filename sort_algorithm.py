def quick_sort(nums):
    if len(nums) <= 1:
        return nums
    less = []
    greater = []
    base = nums.pop()
    for count in nums:
        if count > base:
            greater.append(count)
        else:
            less.append(count)

    return quick_sort(less) + [base] + quick_sort(greater)


def q_sort(nums):
    res = q_sort_core(nums, 0, len(nums) - 1)
    return res


def q_sort_core(nums, left, right):
    if left > right:
        return nums
    begin = left
    end = right
    key = nums[left]
    while begin < end:
        while (begin < end && nums[end] )





if __name__ == "__main__":
    nums = [5, 1, 3, 2, 6]
    res = quick_sort(nums)
    print(res)