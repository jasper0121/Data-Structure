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
		myData.myFirst = new value_type[cells](); //�إ߰}�C
		for (size_t k = 0; k < cells; k++) //��l��
		{
			myData.myFirst[k] = val;
		}

		myData.myLast = myData.myEnd = myData.myFirst + cells; //vector����l�]�w
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
		size_t num = 0; //bucket���������Ӽ�
		for (iterator numItr = myVec.myData.myFirst[n * 2]; numItr != myList.end(); numItr++) //�Y��bucket�������A�h�q�Ĥ@�Ӷ}�l�p��
		{
			if (num++, numItr == myVec.myData.myFirst[n * 2 + 1]) //�C���p���A�Y��e���̫�@�Ӥ����h���X�j��æ^��
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
		if (find(val) == myList.end()) //�Y��e���e�����s�b�Ӥ����A�h�N��[�J�e����
		{
			if (size() == maxidx) //�Y��e�������Ӽ� == bucket�`�ơA�h�X�j
			{
				MyList tempList = myList; //�]�߼Ȧs�A�ƻsmyList�����
				myList.clear(); //�NmyList������ƲM��
				maxidx *= (maxidx < 512) ? 8 : 2; //�X�R�W�h�Abucket < 512�ɨC���X�R8���A�Ϥ��C���X�R2��
				mask = maxidx - 1; //�B�n���ȥû���bucket - 1
				delete[]myVec.myData.myFirst; //�R���°}�C
				myVec.assignGrow(maxidx * 2, myList.end()); //�H�s��bucket�ƫإ߷s�}�C(1��bucket��2��A���O���V��bucket�����Ĥ@�өM�̫�@��node)
				for (iterator insertItr = tempList.begin(); insertItr != tempList.end(); putIn(*insertItr++)); //���s�p��C�Ӥ���insert����m
			}

			putIn(val); //�N�ȥ[�J�e����
		}
	}

	// Removes from the unordered_set a single element.
	// This effectively reduces the container size by one.
	void erase(const key_type& keyVal)
	{
		iterator eraseItr = find(keyVal); //�إߤ@��iterator���V�n�R����node
		if (eraseItr != myList.end()) //�Y���R����node�s�b
		{
			size_t bucket_first = bucket(keyVal) * 2; //��XkeyVal�Ҧbbucket����1�檺��m
			if (myVec.myData.myFirst[bucket_first] == myVec.myData.myFirst[bucket_first + 1]) //�Ybucket����2��ҫ��V�ۦPnode(bucket���u��1�Ӥ���)
			{
				myList.erase(eraseItr);
				myVec.myData.myFirst[bucket_first] = myVec.myData.myFirst[bucket_first + 1] = myList.end(); //�R����A��bucket����2�泣���VmyList.end()
			}
			else //�Ϥ��h�N��bucket����2��node�H�W
			{
				if (eraseItr == myVec.myData.myFirst[bucket_first]) //�Y���R����node�Obucket�����Ĥ@�Ӥ���
				{
					myVec.myData.myFirst[bucket_first] = myList.erase(eraseItr); //�h�b�R����Abucket������1�������R�����U�@��node
				}
				else if (eraseItr == myVec.myData.myFirst[bucket_first + 1]) //�Y���R����node�Obucket�����̫�@�Ӥ���
				{
					myVec.myData.myFirst[bucket_first + 1] = --myList.erase(eraseItr); //�h�b�R����Abucket������2�������R�����W�@��node
				}
				else
				{
					myList.erase(eraseItr); //�Ϥ��h�����R��
				}
			}
		}
	}

	// Searches the unordered_set for an element with keyVal as value and
	// returns an iterator to it if found, otherwise it returns myList.end()
	iterator find(const key_type& keyVal)
	{
		size_t bucket_first = bucket(keyVal) * 2; //��XkeyVal�Ҧbbucket���Ĥ@�檺��m
		for (iterator findItr = myVec.myData.myFirst[bucket_first]; findItr != myList.end(); findItr++) //�Y��bucket�������A�h�qbucket������1��}�l��
		{
			if (*findItr == keyVal) //�Y��eiterator�ҫ���node�����ȻP�ҨD��keyVal�ۦP
			{
				return findItr; //�h�^�Ƿ�eiterator
			}

			if (findItr == myVec.myData.myFirst[bucket_first + 1]) //�Y�����󦨥ߡA�N��bucket�����Ҧ������Ҥw�Q�ˬd�B���X�ҨD
			{
				return myList.end(); //�G�^��myList.end()
			}
		}

		return myList.end(); //�Y����ܦ��A���bucket������1�欰myList.end()�A�N��bucket���S�����󤸯�(���ɲ�2��]����myList.end())
	}

private:
	// put a new element in the unordered_set when myVec is large enough
	void putIn(const value_type& val)
	{
		size_t bucket_first = bucket(val) * 2; //��Xval�Ҧbbucket���Ĥ@�檺��m
		myVec.myData.myFirst[bucket_first] = myList.insert(myVec.myData.myFirst[bucket_first], val); //�C���Nbucket������1����V��insert��node
		if (myVec.myData.myFirst[bucket_first + 1] == myList.end()) //�Ybucket������2�欰myList.end()�A�N��insert���Ȭ���bucket����1�Ӥ���
		{
			myVec.myData.myFirst[bucket_first + 1] = myVec.myData.myFirst[bucket_first]; //��bucket����2�泣���V��insert��node
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