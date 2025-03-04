// algorithm standard header

#ifndef ALGORITHM
#define ALGORITHM

namespace MyNamespace
{

	template< typename RanIt, typename Ty, typename Pr >
	inline void pushHeapByIndex(RanIt first, ptrdiff_t hole, ptrdiff_t top, Ty& val, Pr pred) //�q���}�l��val����H�W��2�Ƥ����ô��J
	{
		for (; top != hole && pred(first[(hole - 1) / 2], val); (--hole) /= 2) //(�Hmax heap����)�Yhole�٨S�쳻�Bparent < val�B�C���Nhole�אּparent��index
		{
			first[hole] = first[(hole - 1) / 2]; //�h�Nparent���ȱ��U��
		}

		first[hole] = val; //�T�w�n��m���ȴ��J
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
	inline void popHeapHoleByIndex(RanIt first, ptrdiff_t hole, ptrdiff_t bottom, Ty& val, Pr pred) //�ɥi��⩳�����ȱ��W�h �B�Nhole����̩�
	{
		ptrdiff_t top = hole; //�N��ehole�Ҧb���`�I�����l���I
		for (ptrdiff_t newHole; hole * 2 + 1 < bottom; hole = newHole) //�Y��ehole���l�`�I�s�b(bottom == �̫�@�Ӥ������U�@��index)�B�C����shole����
		{
			//(�Hmax heap����)�Yhole�u�����l�`�I�Υ��l�`�I����j�A�h���O���shole��A�A�N���l�`�I���ȱ��W�h�F�Ϥ��h�N�k�l�`�I���W�h
			first[hole] = (hole * 2 + 2 == bottom || pred(first[hole * 2 + 2], first[hole * 2 + 1])) ? first[newHole = hole * 2 + 1] : first[newHole = hole * 2 + 2];
		}

		pushHeapByIndex(first, hole, top, val, pred); //����
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