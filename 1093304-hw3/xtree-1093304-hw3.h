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
		NodePtr pn = node->parent; //���Vnode��parent
		NodePtr gn = pn->parent; //���Vnode��grandparent
		NodePtr spn = (gn->right == pn) ? gn->left : gn->right; //���Vpn��sibling
		switch (spn->color) //��spn���C��O���@��
		{
		case Color::Red: //�Yspn�C�⬰��
			pn->color = spn->color = Color::Black; //�hgn��2��child���]���¦�
			if (gn != myHead->parent) //�Ygn == root�A�hgn���令����H����RB1(root�����¦�)
			{
				gn->color = Color::Red;
			}

			if (gn->parent->color == Color::Red) //���ɭYgn��parent�]�O����
			{
				reBalance(gn); //�N��վ��S�X�{�s��2��node�����A�h�A�վ�@��
			}

			return;
		case Color::Black: //�Yspn�C�⬰�¡A�h�ھڷ�Ugn�Bpn�Mnode���s�����A�Ӱ��������rotation
			gn->left == pn ? (pn->left == node ? LLRotation(pn) : LRRotation(node)) : (pn->left == node ? RLRotation(node) : RRRotation(pn));
			return;
		}
	}

	// rotate right at g, where p = g->left and node = p->left
	void LLRotation(TreeNode< value_type >* p) //�ǤJ�Ȭ�node��parent
	{
		NodePtr pp = p->parent; //���Vp��parent
		NodePtr gp = pp->parent; //���Vp��grandparent
		Color tempColor = p->color; //p���C��A�Np�Mpp���C��洫(���i�Npp�Mp�H�w�ʧ令�©M�����覡�ӥ洫�A�_�h�berase���ɭԷ|��)
		if ((pp->left = p->right) != myHead) //pp�����l����Vp���k�l��A�B�Y����node���OmyHead
		{
			pp->left->parent = pp; //�h�N��node��parent���Vpp(����Npp�~��������ʾ�root)
		}

		//p��parent���Vgp�A�Ygp != myHead�A�h�Ngp�����Υk�l����Vp�F�_�h�NmyHead->parent���Vp�Cp�����Ӥl��root�ó]��pp���C��
		(((p->parent = gp) != myHead ? (gp->left == pp ? gp->left : gp->right) : myHead->parent) = p)->color = pp->color;
		((pp->parent = p)->right = pp)->color = tempColor; //pp��parent���Vp�Ap���k�l����Vpp�C��pp����p��child�ó]��p���C��
	}

	// LR rotation; p = g->left and node = p->right
	void LRRotation(TreeNode< value_type >* node) //�ǤJ�Ȭ�node
	{
		NodePtr pn = node->parent; //���Vnode��parent
		NodePtr gn = pn->parent; //���Vnode��grandparent
		NodePtr pgn = gn->parent; //���Vgn��parent
		if ((pn->right = node->left) != myHead) //pn���k�l����Vnode�����l��A�B�Y�l�𤣬OmyHead
		{
			pn->right->parent = pn; //�h�N�l��parent���Vpn(����Npn�~��������ʾ�root)
		}

		if ((gn->left = node->right) != myHead) //gn�����l����Vnode���k�l��A�B�Y�l�𤣬OmyHead
		{
			gn->left->parent = gn; //�h�N�l��parent���Vgn(����Ngn�~��������ʾ�root)
		}

		//node��parent���Vpgn�A�Ypgn != myHead�A�h�Npgn�����Υk�l����Vnode�F�_�h�NmyHead->parent���Vnode�Cnode�����Ӥl��root�ó]���¦�
		(((node->parent = pgn) != myHead ? (pgn->left == gn ? pgn->left : pgn->right) : myHead->parent) = node)->color = Color::Black;
		//node�����l����Vpn�Apn�Mgn��parent�����Vnode�Anode���k�l����Vgn�A��pn�Mgn����node��child�ñNgn�]������
		(((node->left = pn)->parent = gn->parent = node)->right = gn)->color = Color::Red;
	}

	// RL rotation; p = g->right and node = p->left
	void RLRotation(TreeNode< value_type >* node) //�ǤJ�Ȭ�node
	{
		NodePtr pn = node->parent; //���Vnode��parent
		NodePtr gn = pn->parent; //���Vnode��grandparent
		NodePtr pgn = gn->parent; //���Vgn��parent
		if ((pn->left = node->right) != myHead) //pn�����l����Vnode���k�l��A�B�Y�l�𤣬OmyHead
		{
			pn->left->parent = pn; //�h�N�l��parent���Vpn(����Npn�~��������ʾ�root)
		}

		if ((gn->right = node->left) != myHead) //gn���k�l����Vnode�����l��A�B�Y�l�𤣬OmyHead
		{
			gn->right->parent = gn; //�h�N�l��parent���Vgn(����Ngn�~��������ʾ�root)
		}

		//node��parent���Vpgn�A�Ypgn != myHead�A�h�Npgn�����Υk�l����Vnode�F�_�h�NmyHead->parent���Vnode�Cnode�����Ӥl��root�ó]���¦�
		(((node->parent = pgn) != myHead ? (pgn->left == gn ? pgn->left : pgn->right) : myHead->parent) = node)->color = Color::Black;
		//node���k�l����Vpn�Apn�Mgn��parent�����Vnode�Anode�����l����Vgn�A��pn�Mgn����node��child�ñNgn�]������
		(((node->right = pn)->parent = gn->parent = node)->left = gn)->color = Color::Red;
	}

	// rotate left at g, where p = g->right and node = p->right
	void RRRotation(TreeNode< value_type >* p) //�ǤJ�Ȭ�node��parent
	{
		NodePtr pp = p->parent; //���Vp��parent
		NodePtr gp = pp->parent; //���Vp��grandparent
		Color tempColor = p->color; //p���C��A�Np�Mpp���C��洫(���i�Npp�Mp�H�w�ʧ令�©M�����覡�ӥ洫�A�_�h�berase���ɭԷ|��)
		if ((pp->right = p->left) != myHead) //pp���k�l����Vp�����l��A�B�Y����node���OmyHead
		{
			pp->right->parent = pp; //�h�N��node��parent���Vpp(����Npp�~��������ʾ�root)
		}

		//p��parent���Vgp�A�Ygp != myHead�A�h�Ngp�����Υk�l����Vp�F�_�h�NmyHead->parent���Vp�Cp�����Ӥl��root�ó]��pp���C��
		(((p->parent = gp) != myHead ? (gp->left == pp ? gp->left : gp->right) : myHead->parent) = p)->color = pp->color;
		((pp->parent = p)->left = pp)->color = tempColor; //pp��parent���Vp�Ap�����l����Vpp�C��pp����p��child�ó]��p���C��
	}

	// erase node provided that the degree of node is at most one
	void eraseDegreeOne(TreeNode< value_type >* node)
	{
		NodePtr child = (node->left != myHead) ? node->left : node->right; //�Y���l�`�I != myHead�A�hchild�]�����l�`�I�A�_�h�]���k�l�`�I
		(node == node->parent->left ? node->parent->left : node->parent->right) = child; //node��parent���Vchild
		if (child != myHead) //�Ychild != myHead
		{
			child->parent = node->parent; //�Nchild��parent���Vnode��parent
		}

		if (node == myHead->left || node == myHead->right) //�Y�R����node�O��ʾ𤤪��̤p�γ̤j��
		{
			(node == myHead->left ? myHead->left : myHead->right) = node->parent; //�hmyHead->left��myHead->right���s���Vnode��parent
		}

		if (node->color == Color::Black)
			fixUp(child, node->parent);

		delete node;
		mySize--;
	}

	// rebalance for deletion
	void fixUp(TreeNode< value_type >* N, TreeNode< value_type >* P) //N == node��child�AP == node��parent�A����N���|�W��1��
	{
		if (N->color == Color::Red) //�YN����
		{
			N->color = Color::Black; //�h��N�V�§Y�i
		}
		else //�Ϥ��YN����
		{
			NodePtr S = (P->right == N) ? P->left : P->right; //N��sibling == P���t�@��child
			NodePtr on = (S == P->left) ? S->left : S->right; //S��2��child���a�~����node(outside node)
			NodePtr in = (S == P->left) ? S->right : S->left; //S��2��child���a������node(inside node)
			if (S->color == Color::Red) //�YS���C�⬰���A�N��P�Bon�Bin�Ҷ�(case 1)
			{
				(S == P->left) ? LLRotation(S) : RRRotation(S); //�ھ�S�OP�����Υk�l�`�I�Ӱ������rotation
				fixUp(N, P); //�Hrotation�᪺N�MP�A�վ�@��
			}
			else //�YS���C�⬰��
			{
				if (on->color == Color::Red) //�Y�a�~����child node����(����P�Min���C�⤣�T�w)(case 2)
				{
					on->color = Color::Black; //�Non���
					(S == P->left) ? LLRotation(S) : RRRotation(S); //�ھ�S�OP�����Υk�l�`�I�Ӱ������rotation
				}
				else //�Y�a�~����child node����
				{
					if (in->color == Color::Red) //�Y�a������child node����(����P�C�⤣�T�w)(case 3)
					{
						(S == P->left) ? (RRRotation(in), LLRotation(in)) : (LLRotation(in), RRRotation(in)); //�ھ�in�OP�����Υk�l�`�I�Ӱ������rotation
						S->color = Color::Black; //��1��rotation��S�V���A��2��rotation�O����case 2�A�G�NS���
					}
					else //�Y�a������child node����
					{
						S->color = Color::Red; //����H�Ucase 4��5���ݭn�NS�V��
						if (P->color == Color::Red) //�YP���C�⬰��(���ɨ�Lnode����)(case 4)
						{
							P->color = Color::Black; //�h�NP���(P�MS�C��洫)
						}
						else //�Y������node������(case 5)
						{
							fixUp(P, P->parent); //���ɳq�LP��2�Ӹ��|�᪺�¦�ƬҤ�P�H�~����L���|��1�A�G�HP�MP��parent�@��N�PP�A�վ�@��
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

			if ((p = new TreeNode< value_type >)->parent = pp) //�bp����external node(�YmyHead)��إ߷s��node�Ap��parent���Vpp�A�B�Ypp���Onullptr
			{
				p->myval = val;
				p->color = Color::Red; //�w�]������
				p->isNil = false; //�Droot�@�߹w�]��false			
				p->left = p->right = scaryVal.myHead; //p�����k�l�𳣳]��external node(�YmyHead)			
				(keyCompare(val, pp->myval) ? pp->left : pp->right) = p; //(�H�w�]��less����)�Yval����p�A�hpp�����l����Vp�A�Ϥ�pp���k�l����Vp
				scaryVal.mySize++; //�s�W�@��node�A�Gsize + 1
				if (keyCompare(val, scaryVal.myHead->left->myval)) //�Yval��𤤳̤p�����٤p
				{
					scaryVal.myHead->left = p; //scaryVal.myHead->left���V�𤤭ȳ̤p��node
				}

				if (keyCompare(scaryVal.myHead->right->myval, val)) //�Yval��𤤳̤j�����٤j
				{
					scaryVal.myHead->right = p; //scaryVal.myHead->right���V�𤤭ȳ̤j��node
				}

				if (pp->color == Color::Red) //�Yp��parent���C��O��
				{
					scaryVal.reBalance(p); //�N��s��2��node�O����A�n�i��վ�
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
			if (p->right != scaryVal.myHead) //�p�Gp���k�l�`�I != myHead
			{
				TreeNode<value_type>* eraseNode = p->right; //�إߤ@��pointer���Vp���k�l�`�I
				for (; eraseNode->left != scaryVal.myHead; eraseNode = eraseNode->left); //���U�Ӥ@���V������̫�@��node

				p->myval = eraseNode->myval; //�NeraseNode���Ƚƻs�����R����node
				scaryVal.eraseDegreeOne(eraseNode); //�NeraseNode�R��
			}
			else //�Yp�S���k�l�`�I
			{
				scaryVal.eraseDegreeOne(p); //�h������p�`�I�R��
			}

			return 1;
		}
	}

private:
	key_compare keyCompare;
	ScaryVal scaryVal;
};

#endif // XTREE