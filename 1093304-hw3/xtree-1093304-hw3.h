// xtree internal header

#ifndef XTREE
#define XTREE

enum class Color { Red, Black }; // colors for link to parent

template< typename Ty >
struct TreeNode
{
	using NodePtr = TreeNode*;
	using value_type = Ty;

	NodePtr left;   // left subtree, or smallest element if head
	NodePtr parent; // parent, or root of tree if head
	NodePtr right;  // right subtree, or largest element if head
	Color color;  // Red or Black, Black if head
	bool isNil;  // true only if head (also nil) node
	value_type myval;  // the stored value, unused if head
};

// CLASS TEMPLATE TreeVal
template< typename Ty >
class TreeVal
{
public:
	using NodePtr = TreeNode< Ty >*;

	using value_type = Ty;
	using size_type = size_t;

	TreeVal()
		: myHead(new TreeNode< value_type >),
		mySize(0)
	{
		myHead->left = myHead;
		myHead->parent = myHead;
		myHead->right = myHead;
		myHead->color = Color::Black;
		myHead->isNil = true;
	}

	~TreeVal()
	{
		clear(myHead->parent);
		delete myHead;
	}

	// Removes all elements from the set object (which are destroyed)
	void clear(TreeNode< value_type >* node)
	{
		if (!node->isNil) // node is not an external node
		{
			clear(node->left);
			clear(node->right);
			delete node;
		}
	}

	// rebalance for insertion
	void reBalance(TreeNode< value_type >* node)
	{  // node->parent cannot be the root
		NodePtr pn = node->parent; //指向node的parent
		NodePtr gn = pn->parent; //指向node的grandparent
		NodePtr spn = (gn->right == pn) ? gn->left : gn->right; //指向pn的sibling
		switch (spn->color) //看spn的顏色是哪一種
		{
		case Color::Red: //若spn顏色為紅
			pn->color = spn->color = Color::Black; //則gn的2個child都設為黑色
			if (gn != myHead->parent) //若gn == root，則gn不改成紅色以滿足RB1(root必為黑色)
			{
				gn->color = Color::Red;
			}

			if (gn->parent->color == Color::Red) //此時若gn的parent也是紅色
			{
				reBalance(gn); //代表調整後又出現連續2個node為紅，則再調整一次
			}

			return;
		case Color::Black: //若spn顏色為黑，則根據當下gn、pn和node的連接狀態來執行相應的rotation
			gn->left == pn ? (pn->left == node ? LLRotation(pn) : LRRotation(node)) : (pn->left == node ? RLRotation(node) : RRRotation(pn));
			return;
		}
	}

	// rotate right at g, where p = g->left and node = p->left
	void LLRotation(TreeNode< value_type >* p) //傳入值為node的parent
	{
		NodePtr pp = p->parent; //指向p的parent
		NodePtr gp = pp->parent; //指向p的grandparent
		Color tempColor = p->color; //p的顏色，將p和pp的顏色交換(不可將pp和p以硬性改成黑和紅的方式來交換，否則在erase的時候會錯)
		if ((pp->left = p->right) != myHead) //pp的左子樹指向p的右子樹，且若指的node不是myHead
		{
			pp->left->parent = pp; //則將該node的parent指向pp(防止將pp誤接成為整棵樹的root)
		}

		//p的parent指向gp，若gp != myHead，則將gp的左或右子樹指向p；否則將myHead->parent指向p。p成為該子樹的root並設成pp的顏色
		(((p->parent = gp) != myHead ? (gp->left == pp ? gp->left : gp->right) : myHead->parent) = p)->color = pp->color;
		((pp->parent = p)->right = pp)->color = tempColor; //pp的parent指向p，p的右子樹指向pp。使pp成為p的child並設成p的顏色
	}

	// LR rotation; p = g->left and node = p->right
	void LRRotation(TreeNode< value_type >* node) //傳入值為node
	{
		NodePtr pn = node->parent; //指向node的parent
		NodePtr gn = pn->parent; //指向node的grandparent
		NodePtr pgn = gn->parent; //指向gn的parent
		if ((pn->right = node->left) != myHead) //pn的右子樹指向node的左子樹，且若子樹不是myHead
		{
			pn->right->parent = pn; //則將子樹的parent指向pn(防止將pn誤接成為整棵樹的root)
		}

		if ((gn->left = node->right) != myHead) //gn的左子樹指向node的右子樹，且若子樹不是myHead
		{
			gn->left->parent = gn; //則將子樹的parent指向gn(防止將gn誤接成為整棵樹的root)
		}

		//node的parent指向pgn，若pgn != myHead，則將pgn的左或右子樹指向node；否則將myHead->parent指向node。node成為該子樹的root並設成黑色
		(((node->parent = pgn) != myHead ? (pgn->left == gn ? pgn->left : pgn->right) : myHead->parent) = node)->color = Color::Black;
		//node的左子樹指向pn，pn和gn的parent都指向node，node的右子樹指向gn，使pn和gn成為node的child並將gn設成紅色
		(((node->left = pn)->parent = gn->parent = node)->right = gn)->color = Color::Red;
	}

	// RL rotation; p = g->right and node = p->left
	void RLRotation(TreeNode< value_type >* node) //傳入值為node
	{
		NodePtr pn = node->parent; //指向node的parent
		NodePtr gn = pn->parent; //指向node的grandparent
		NodePtr pgn = gn->parent; //指向gn的parent
		if ((pn->left = node->right) != myHead) //pn的左子樹指向node的右子樹，且若子樹不是myHead
		{
			pn->left->parent = pn; //則將子樹的parent指向pn(防止將pn誤接成為整棵樹的root)
		}

		if ((gn->right = node->left) != myHead) //gn的右子樹指向node的左子樹，且若子樹不是myHead
		{
			gn->right->parent = gn; //則將子樹的parent指向gn(防止將gn誤接成為整棵樹的root)
		}

		//node的parent指向pgn，若pgn != myHead，則將pgn的左或右子樹指向node；否則將myHead->parent指向node。node成為該子樹的root並設成黑色
		(((node->parent = pgn) != myHead ? (pgn->left == gn ? pgn->left : pgn->right) : myHead->parent) = node)->color = Color::Black;
		//node的右子樹指向pn，pn和gn的parent都指向node，node的左子樹指向gn，使pn和gn成為node的child並將gn設成紅色
		(((node->right = pn)->parent = gn->parent = node)->left = gn)->color = Color::Red;
	}

	// rotate left at g, where p = g->right and node = p->right
	void RRRotation(TreeNode< value_type >* p) //傳入值為node的parent
	{
		NodePtr pp = p->parent; //指向p的parent
		NodePtr gp = pp->parent; //指向p的grandparent
		Color tempColor = p->color; //p的顏色，將p和pp的顏色交換(不可將pp和p以硬性改成黑和紅的方式來交換，否則在erase的時候會錯)
		if ((pp->right = p->left) != myHead) //pp的右子樹指向p的左子樹，且若指的node不是myHead
		{
			pp->right->parent = pp; //則將該node的parent指向pp(防止將pp誤接成為整棵樹的root)
		}

		//p的parent指向gp，若gp != myHead，則將gp的左或右子樹指向p；否則將myHead->parent指向p。p成為該子樹的root並設成pp的顏色
		(((p->parent = gp) != myHead ? (gp->left == pp ? gp->left : gp->right) : myHead->parent) = p)->color = pp->color;
		((pp->parent = p)->left = pp)->color = tempColor; //pp的parent指向p，p的左子樹指向pp。使pp成為p的child並設成p的顏色
	}

	// erase node provided that the degree of node is at most one
	void eraseDegreeOne(TreeNode< value_type >* node)
	{
		NodePtr child = (node->left != myHead) ? node->left : node->right; //若左子節點 != myHead，則child設為左子節點，否則設為右子節點
		(node == node->parent->left ? node->parent->left : node->parent->right) = child; //node的parent指向child
		if (child != myHead) //若child != myHead
		{
			child->parent = node->parent; //將child的parent指向node的parent
		}

		if (node == myHead->left || node == myHead->right) //若刪除的node是整棵樹中的最小或最大值
		{
			(node == myHead->left ? myHead->left : myHead->right) = node->parent; //則myHead->left或myHead->right重新指向node的parent
		}

		if (node->color == Color::Black)
			fixUp(child, node->parent);

		delete node;
		mySize--;
	}

	// rebalance for deletion
	void fixUp(TreeNode< value_type >* N, TreeNode< value_type >* P) //N == node的child，P == node的parent，此時N路徑上少1黑
	{
		if (N->color == Color::Red) //若N為紅
		{
			N->color = Color::Black; //則把N染黑即可
		}
		else //反之若N為黑
		{
			NodePtr S = (P->right == N) ? P->left : P->right; //N的sibling == P的另一個child
			NodePtr on = (S == P->left) ? S->left : S->right; //S的2個child中靠外側的node(outside node)
			NodePtr in = (S == P->left) ? S->right : S->left; //S的2個child中靠內側的node(inside node)
			if (S->color == Color::Red) //若S的顏色為紅，代表P、on、in皆黑(case 1)
			{
				(S == P->left) ? LLRotation(S) : RRRotation(S); //根據S是P的左或右子節點來執行哪種rotation
				fixUp(N, P); //以rotation後的N和P再調整一次
			}
			else //若S的顏色為黑
			{
				if (on->color == Color::Red) //若靠外側的child node為紅(此時P和in的顏色不固定)(case 2)
				{
					on->color = Color::Black; //將on塗黑
					(S == P->left) ? LLRotation(S) : RRRotation(S); //根據S是P的左或右子節點來執行哪種rotation
				}
				else //若靠外側的child node為黑
				{
					if (in->color == Color::Red) //若靠內側的child node為紅(此時P顏色不固定)(case 3)
					{
						(S == P->left) ? (RRRotation(in), LLRotation(in)) : (LLRotation(in), RRRotation(in)); //根據in是P的左或右子節點來執行哪種rotation
						S->color = Color::Black; //第1次rotation使S染紅，第2次rotation是執行case 2，故將S塗黑
					}
					else //若靠內側的child node為黑
					{
						S->color = Color::Red; //執行以下case 4或5都需要將S染紅
						if (P->color == Color::Red) //若P的顏色為紅(此時其他node為黑)(case 4)
						{
							P->color = Color::Black; //則將P塗黑(P和S顏色交換)
						}
						else //若全部的node都為黑(case 5)
						{
							fixUp(P, P->parent); //此時通過P的2個路徑後的黑色數皆比P以外的其他路徑少1，故以P和P的parent作為N與P再調整一次
						}
					}
				}
			}
		}
	}

	NodePtr myHead;   // pointer to head node
	size_type mySize; // number of elements
};

// CLASS TEMPLATE Tree
template< typename Traits >
class Tree // ordered red-black tree for map/multimap/set/multiset
{
public:
	using value_type = typename Traits::value_type;

protected:
	using ScaryVal = TreeVal< value_type >;

public:
	using key_type = typename Traits::key_type;
	using key_compare = typename Traits::key_compare;

	using size_type = size_t;

	Tree(const key_compare& parg)
		: keyCompare(parg),
		scaryVal()
	{
	}

	~Tree()
	{
	}

	// Extends the container by inserting a new element,
	// effectively increasing the container size by one.
	void insert(const value_type& val)
	{
		if (scaryVal.mySize == 0)
		{
			TreeNode< value_type >* root = new TreeNode< value_type >;
			root->myval = val;
			root->left = scaryVal.myHead;
			root->right = scaryVal.myHead;
			root->isNil = false;
			root->parent = scaryVal.myHead;
			root->color = Color::Black;
			scaryVal.myHead->left = root;
			scaryVal.myHead->parent = root;
			scaryVal.myHead->right = root;
			scaryVal.mySize = 1;
		}
		else
		{                           // scaryVal.myHead->parent points to the root
			TreeNode< value_type >* p = scaryVal.myHead->parent;
			TreeNode< value_type >* pp = nullptr;
			while (p != scaryVal.myHead)
			{
				pp = p;
				//              keyCompare.operator()( val, p->myval )
				if (keyCompare(val, p->myval)) // if( val < p->myval )
					p = p->left;
				else if (keyCompare(p->myval, val)) // if( val > p->myval )
					p = p->right;
				else
					return;
			}

			if ((p = new TreeNode< value_type >)->parent = pp) //在p走到external node(即myHead)後建立新的node，p的parent指向pp，且若pp不是nullptr
			{
				p->myval = val;
				p->color = Color::Red; //預設為紅色
				p->isNil = false; //非root一律預設為false			
				p->left = p->right = scaryVal.myHead; //p的左右子樹都設為external node(即myHead)			
				(keyCompare(val, pp->myval) ? pp->left : pp->right) = p; //(以預設的less為例)若val比較小，則pp的左子樹指向p，反之pp的右子樹指向p
				scaryVal.mySize++; //新增一個node，故size + 1
				if (keyCompare(val, scaryVal.myHead->left->myval)) //若val比樹中最小的值還小
				{
					scaryVal.myHead->left = p; //scaryVal.myHead->left指向樹中值最小的node
				}

				if (keyCompare(scaryVal.myHead->right->myval, val)) //若val比樹中最大的值還大
				{
					scaryVal.myHead->right = p; //scaryVal.myHead->right指向樹中值最大的node
				}

				if (pp->color == Color::Red) //若p的parent的顏色是紅
				{
					scaryVal.reBalance(p); //代表連續2個node是紅色，要進行調整
				}
			}
		}
	}

	// Removes from the set container a single element whose value is val
	// This effectively reduces the container size by one, which are destroyed.
	// Returns the number of elements erased.
	size_type erase(const key_type& val)
	{
		TreeNode< key_type >* p = scaryVal.myHead->parent; // p points to the root
		while (p != scaryVal.myHead && val != p->myval)
		{
			//           keyCompare.operator()( val, p->myval )
			if (keyCompare(val, p->myval)) // if( val < p->myval )
				p = p->left;
			else
				p = p->right;
		}

		if (p == scaryVal.myHead) // not found
			return 0;
		else // found
		{  // deletes the node pointed by p
			if (p->right != scaryVal.myHead) //如果p的右子節點 != myHead
			{
				TreeNode<value_type>* eraseNode = p->right; //建立一個pointer指向p的右子節點
				for (; eraseNode->left != scaryVal.myHead; eraseNode = eraseNode->left); //接下來一路向左走到最後一個node

				p->myval = eraseNode->myval; //將eraseNode的值複製給欲刪除的node
				scaryVal.eraseDegreeOne(eraseNode); //將eraseNode刪除
			}
			else //若p沒有右子節點
			{
				scaryVal.eraseDegreeOne(p); //則直接把p節點刪除
			}

			return 1;
		}
	}

private:
	key_compare keyCompare;
	ScaryVal scaryVal;
};

#endif // XTREE