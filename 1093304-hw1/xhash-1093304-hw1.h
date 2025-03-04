// xhash internal header

#ifndef XHASH
#define XHASH

#include <list>
using std::list;

// CLASS TEMPLATE VectorVal
template< typename ValueType >
class VectorVal
{
public:
	using value_type = ValueType;
	using pointer = value_type*;

	VectorVal()
		: myFirst(),
		myLast(),
		myEnd()
	{
	}

	pointer myFirst; // pointer to beginning of array
	pointer myLast;  // pointer to current end of sequence
	pointer myEnd;   // pointer to end of array
};

template< typename Iter >
struct HashVec
{
	using value_type = Iter;
	using size_type = size_t;

	HashVec()
		: myData()
	{
	}

	// set the elements stored here to cells copies of val
	void assignGrow(const size_type cells, const value_type val)
	{
		myData.myFirst = new value_type[cells](); //建立陣列
		for (size_t k = 0; k < cells; k++) //初始化
		{
			myData.myFirst[k] = val;
		}

		myData.myLast = myData.myEnd = myData.myFirst + cells; //vector的初始設定
	}

	~HashVec()
	{
		if (myData.myFirst != nullptr)
			delete[] myData.myFirst;
	}

	VectorVal< value_type > myData;
};

// CLASS TEMPLATE Hash
template< typename Traits >
class Hash // hash table -- list with vector of iterators for quick access
{
protected:
	using MyList = list< typename Traits::value_type >;
	using KeyCompare = typename Traits::key_compare;

public:
	using key_type = typename Traits::key_type;
	using value_type = typename MyList::value_type;
	using size_type = typename MyList::size_type;

	using iterator = typename MyList::const_iterator;
	using const_iterator = typename MyList::const_iterator;

	static const size_type MinBuckets = 8; // must be a positive power of 2

protected:
	Hash(const KeyCompare& parg) // construct empty hash table
		: traitsObj(parg),
		myList(),
		myVec(),
		mask(MinBuckets - 1),
		maxidx(MinBuckets)
	{
		myVec.assignGrow(MinBuckets * 2, myList.end());
	}

public:
	// Returns the number of elements in the unordered_set container.
	size_type size() const
	{
		return myList.size();
	}

	// Returns the number of buckets in the unordered_set container.
	size_type bucket_count() const
	{
		return maxidx;
	}

	// Returns the bucket number where the element with value keyVal is located.
	size_type bucket(const key_type& keyVal) const
	{
		return traitsObj(keyVal) & mask;
		//    return traitsObj.operator()( keyVal ) & mask;
		//    return traitsObj( keyVal ) % maxidx;
	}

	// Returns the number of elements in bucket n.
	size_type bucket_size(size_type n) const
	{
		size_t num = 0; //bucket內的元素個數
		for (iterator numItr = myVec.myData.myFirst[n * 2]; numItr != myList.end(); numItr++) //若該bucket有元素，則從第一個開始計算
		{
			if (num++, numItr == myVec.myData.myFirst[n * 2 + 1]) //每次計算後，若當前為最後一個元素則跳出迴圈並回傳
			{
				break;
			}
		}

		return num;
	}

	// Inserts a new element in the unordered_set.
	// The element is inserted only if it is not equivalent to any other element
	// already in the container ( elements in an unordered_set have unique values ).
	// This effectively increases the container size by one.
	void insert(const value_type& val)
	{
		if (find(val) == myList.end()) //若當前的容器不存在該元素，則將其加入容器中
		{
			if (size() == maxidx) //若當前的元素個數 == bucket總數，則擴大
			{
				MyList tempList = myList; //設立暫存，複製myList的資料
				myList.clear(); //將myList內的資料清除
				maxidx *= (maxidx < 512) ? 8 : 2; //擴充規則，bucket < 512時每次擴充8倍，反之每次擴充2倍
				mask = maxidx - 1; //遮罩的值永遠為bucket - 1
				delete[]myVec.myData.myFirst; //刪除舊陣列
				myVec.assignGrow(maxidx * 2, myList.end()); //以新的bucket數建立新陣列(1個bucket有2格，分別指向該bucket中的第一個和最後一個node)
				for (iterator insertItr = tempList.begin(); insertItr != tempList.end(); putIn(*insertItr++)); //重新計算每個元素insert的位置
			}

			putIn(val); //將值加入容器中
		}
	}

	// Removes from the unordered_set a single element.
	// This effectively reduces the container size by one.
	void erase(const key_type& keyVal)
	{
		iterator eraseItr = find(keyVal); //建立一個iterator指向要刪除的node
		if (eraseItr != myList.end()) //若欲刪除的node存在
		{
			size_t bucket_first = bucket(keyVal) * 2; //算出keyVal所在bucket中第1格的位置
			if (myVec.myData.myFirst[bucket_first] == myVec.myData.myFirst[bucket_first + 1]) //若bucket中的2格皆指向相同node(bucket中只有1個元素)
			{
				myList.erase(eraseItr);
				myVec.myData.myFirst[bucket_first] = myVec.myData.myFirst[bucket_first + 1] = myList.end(); //刪除後，使bucket中的2格都指向myList.end()
			}
			else //反之則代表bucket中有2個node以上
			{
				if (eraseItr == myVec.myData.myFirst[bucket_first]) //若欲刪除的node是bucket中的第一個元素
				{
					myVec.myData.myFirst[bucket_first] = myList.erase(eraseItr); //則在刪除後，bucket中的第1格改指欲刪除的下一個node
				}
				else if (eraseItr == myVec.myData.myFirst[bucket_first + 1]) //若欲刪除的node是bucket中的最後一個元素
				{
					myVec.myData.myFirst[bucket_first + 1] = --myList.erase(eraseItr); //則在刪除後，bucket中的第2格改指欲刪除的上一個node
				}
				else
				{
					myList.erase(eraseItr); //反之則直接刪除
				}
			}
		}
	}

	// Searches the unordered_set for an element with keyVal as value and
	// returns an iterator to it if found, otherwise it returns myList.end()
	iterator find(const key_type& keyVal)
	{
		size_t bucket_first = bucket(keyVal) * 2; //算出keyVal所在bucket中第一格的位置
		for (iterator findItr = myVec.myData.myFirst[bucket_first]; findItr != myList.end(); findItr++) //若該bucket有元素，則從bucket中的第1格開始找
		{
			if (*findItr == keyVal) //若當前iterator所指的node中的值與所求的keyVal相同
			{
				return findItr; //則回傳當前iterator
			}

			if (findItr == myVec.myData.myFirst[bucket_first + 1]) //若此條件成立，代表此bucket中的所有元素皆已被檢查且不合所求
			{
				return myList.end(); //故回傳myList.end()
			}
		}

		return myList.end(); //若執行至此，表示bucket中的第1格為myList.end()，代表此bucket中沒有任何元素(此時第2格也必為myList.end())
	}

private:
	// put a new element in the unordered_set when myVec is large enough
	void putIn(const value_type& val)
	{
		size_t bucket_first = bucket(val) * 2; //算出val所在bucket中第一格的位置
		myVec.myData.myFirst[bucket_first] = myList.insert(myVec.myData.myFirst[bucket_first], val); //每次將bucket中的第1格指向剛insert的node
		if (myVec.myData.myFirst[bucket_first + 1] == myList.end()) //若bucket中的第2格為myList.end()，代表insert的值為此bucket的第1個元素
		{
			myVec.myData.myFirst[bucket_first + 1] = myVec.myData.myFirst[bucket_first]; //使bucket中的2格都指向剛insert的node
		}
	}

protected:
	Traits traitsObj;          // traits to customize behavior
	MyList myList;             // list of elements, must initialize before myVec
	HashVec< iterator > myVec; // "vector" of list iterators for buckets:
							   // each bucket is 2 iterators denoting
							   // the closed range of elements in the bucket,
							   // or both iterators set to end() if the bucket is empty.
	size_type mask;            // the key mask, equals maxidx - 1
	size_type maxidx;          // current maximum key value, must be a power of 2
};

#endif // XHASH