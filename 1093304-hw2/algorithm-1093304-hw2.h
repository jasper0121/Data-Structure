// algorithm standard header

#ifndef ALGORITHM
#define ALGORITHM

namespace MyNamespace
{

	template< typename RanIt, typename Ty, typename Pr >
	inline void pushHeapByIndex(RanIt first, ptrdiff_t hole, ptrdiff_t top, Ty& val, Pr pred) //從底開始找val介於以上哪2數之間並插入
	{
		for (; top != hole && pred(first[(hole - 1) / 2], val); (--hole) /= 2) //(以max heap為例)若hole還沒到頂且parent < val、每次將hole改為parent的index
		{
			first[hole] = first[(hole - 1) / 2]; //則將parent的值推下來
		}

		first[hole] = val; //確定好位置後把值插入
	}

	// push *(last - 1) onto heap at [first, last - 1), using pred
	template< typename RanIt, typename Pr >
	inline void push_heap(RanIt first, RanIt last, Pr pred)
	{
		ptrdiff_t count = last - first;
		if (count >= 2)
		{
			--last;
			typename RanIt::value_type val = *last;
			--count;
			pushHeapByIndex(first, count, 0, val, pred);
		}
	}

	template< typename RanIt, typename Ty, typename Pr >
	inline void popHeapHoleByIndex(RanIt first, ptrdiff_t hole, ptrdiff_t bottom, Ty& val, Pr pred) //盡可能把底部的值推上去 且將hole推到最底
	{
		ptrdiff_t top = hole; //將當前hole所在的節點視為子樹頂點
		for (ptrdiff_t newHole; hole * 2 + 1 < bottom; hole = newHole) //若當前hole的子節點存在(bottom == 最後一個元素的下一個index)、每次更新hole的值
		{
			//(以max heap為例)若hole只有左子節點或左子節點比較大，則先記錄新hole後，再將左子節點的值推上去；反之則將右子節點推上去
			first[hole] = (hole * 2 + 2 == bottom || pred(first[hole * 2 + 2], first[hole * 2 + 1])) ? first[newHole = hole * 2 + 1] : first[newHole = hole * 2 + 2];
		}

		pushHeapByIndex(first, hole, top, val, pred); //插值
	}

	// pop *first to *(last - 1) and reheap, using pred
	template< typename RanIt, typename Pr >
	inline void pop_heap(RanIt first, RanIt last, Pr pred)
	{
		if (last - first >= 2)
		{
			--last;
			typename RanIt::value_type val = *last;

			// pop *first to *(last - 1) and reheap, using pred
			// precondition: first != last
			*last = *first;
			popHeapHoleByIndex(first, 0, last - first, val, pred);
		}
	}

	// make [first, last) into a heap, using pred
	template< typename RanIt, typename Pr >
	inline void make_heap(RanIt first, RanIt last, Pr pred)
	{
		ptrdiff_t bottom = last - first;
		ptrdiff_t hole = bottom / 2;
		while (hole > 0)
		{
			// reheap top half, bottom to top
			--hole;
			typename RanIt::value_type val = *(first + hole);
			popHeapHoleByIndex(first, hole, bottom, val, pred);
		}
	}
}

#endif // ALGORITHM