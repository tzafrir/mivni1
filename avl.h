#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <cassert>

template <typename T,bool FreeItems>
class AVL{
public:

	enum AVLReturnCodes
	{	
		Success,
		Item_already_exist,
		Item_doesnt_exist
	};

	// A unary predicate class - used to preform operations on the items in the tree
	// while traversal the tree
    // return true to stop the tree-traversal 
	class Predicate{
	public:
		virtual bool DoWork(T* item) = 0;
	};

	AVL() : root(NULL) {};

	~AVL() 
	{
		free(root);
	}

	// returns the number of items in the tree
	int NumberOfItems() const
	{
		CountNodes c;
		inorder(&c);
		return c.Nodes;
	}

	// returns the Height of the tree
	int Height() const
	{
		int Height = -1;
		node* ptr = root;
		while (ptr != NULL)
		{
			ptr = ptr->bf > 0 ? ptr->Children[Left] :  ptr->Children[Right];
			Height++;
		}
		return Height;
	}


	//travers the tree in order until p->dowork return true
	//calls p->DoWork on each item in the tree
	// notice: if you want to change an item in a way that effects how
	// it compares to other items, you should remove it from the tree
	// make the change and reinsert it.
	void inorder(Predicate *p) const
	{
		inorder(root,p);
	}

	// inserts the item to the tree. The item is added AS-IS - 
    // no copy of the pointed item is created
	// notice: if you want to change an item in a way that effects how
	// it compares to other items, you should remove it from the tree
	// make the change and reinsert it.
	AVLReturnCodes insert(T *item)
	{
		return insert(root, item) != Error ?  Success : Item_already_exist;
	}

	// removes an item from the tree, the argument
	// should be an item which is equal to the item
	// to remove according to the <= function
	AVLReturnCodes remove(T *item)
	{
		return remove(root, item) != Error ?  Success : Item_doesnt_exist;
	}

	// retrives an item from the tree, the argument
	// should be an item which is equal to the item
	// to remove according to the <= function
	T* Find(T *item) const
	{
		node* ptr = root;
		while  (ptr != NULL)
		{
			CmpResult res= Cmp(ptr->data,item);
			if (res == Equal)
			{
				return root->data; //item found
			}
			//else
			directions dir = (directions) res; //bellow -> left, above -> right
			ptr = ptr->Children[dir];
		}
		return NULL; //if we arrive here item wasnt found
	}

	//return the minimal item in the tree according to <=,
	//or null if the tree is empty
	T* GetMin() const
	{
		node* ptr = root;
		T* item;
		while (ptr != NULL)
		{
			item = ptr->data;
			ptr = ptr->Children[Left];
		}
		return item;
	}

	//basic tree printing function, only usefull when the tree is small
	void print_tree() const
	{
		int height = Height();
		if (height == -1)
		{
			std::cout << "Tree is Empty";
		}
		else
		{
			height+= 2;// 1 for the formula in the next line, and another one for the null leafs
			int Maxnodes = (1 << (height)) -1; //2^ (height) -1

			node** Array = new node*[Maxnodes];
			node** ptr= Array;

			for (int i=0; i< Maxnodes; i++)
			{
				*(ptr++) = NULL; //init array
			}

			ptr= Array;

			print_tree(root,0,Array); //fill array with tree nodes

			//print array
			height--; //no need to print all the none in last line
			for (int i=0; i<height; i++)
			{
				for (int j = 0; j < 1 << i; j++)
				{
					if (i != height-1)
					{
						for (int k = 0; k < (1 << (height-2-i)) ; k++)
						{
							std::cout << "     ";
						}
						//std::cout << char(8) << char(8); //backspace
					}

					if (*ptr == NULL)
					{
						std::cout << "none ";
					}
					else
					{
						std::cout << *(*ptr)->data <<  '('  << (*ptr)->bf <<  ')';
					}
					std::cout <<  ',';
					ptr++;
				}
				std::cout << char(8); //backspace
				std::cout << ' ' << std::endl;
			}
			delete[] Array;
		}
		std::cout <<  std::endl;
	}

private:
	#define NumberOfChildren 2

	 // internal class - not needed for usage of Tree
	class node
	{
	public:
		node(T *newdata) : data(newdata), bf(0)
		{
			Children[0]=Children[1] = NULL;
		}
		T *data;
		node* Children[NumberOfChildren];
		int bf;
	};

	 // internal class - not needed for usage of Tree
	class CountNodes : public Predicate{
	public:
		CountNodes() : Nodes(0) {}
		virtual bool DoWork(T* item)
		{
			Nodes++;
			return false;
		}
		int Nodes;
	};

	//direction, or the indexes of the children of a node
	enum directions
	{
		Left=0,
		Right=1
	};

	//return values of various recursive function
	//tells the caller if the height changed or not
	//and if there was an error
	enum HeightChange
	{
		NoHeightChange,
		HeightChanged,
		Error //problem in insert, remove, etc..
	};

	//recives a direction and returns the opposite direction
	static inline directions OtherDirection(directions dir)
	{
		return  (directions) (1 - dir);
	}

	//results of the compare function
	//number so it will be easy to convert compare result and direction
	//to continue search
	enum CmpResult
	{
		Bellow=Left,
		Above=Right,
		Equal
	};
	
	//calc the bfchange if a balanced tree grow  by 1 in dir direction
	//if dir = left we need to add 1 to bf, if 
	//dir == right we need to add -1 to bf
	static inline int CalcBfChange(directions Dir)
	{
		return (1 - 2 * Dir);
	}

	//cmpares two items using <= and returns result
	static CmpResult Cmp(const T* x,const T* y)
	{
		if (*y <= *x)
		{
			if (*x <= *y)
			{
				//*x == *y
				return Equal;
			}
			//*x < *y
			return Bellow;
		}
		else
		{
			//*x > *y
			return Above;
		}
	}


	//recives the root and the change in bf, updates Bf and
	//preforms roll if nessasry and returns wheter a roll occored
	static bool UpdateBalance(node* &root,int BfChange)
	{
		root->bf += BfChange;
		if (root->bf == 2*BfChange)
		{
			directions RollDirection = root->bf == 2 ? Right : Left; //if we arrive here bf is either 2 or -2
			//if its two need to roll to the right otherwise to the left
			directions OppositeDirection = OtherDirection(RollDirection); 
				
			if (root->Children[OppositeDirection]->bf == CalcBfChange(RollDirection))
			{	//if direction is Right(=0), we need
				//to check if the left subtree's bf is -1 and if is is do LR roll
				//if direction is Left(=1), we need
				//to check if the Right subtree's bf is 1 and if it is do Rl roll

				//LR or RL roll
				Roll(root->Children[OppositeDirection],OppositeDirection,RollDirection);
				Roll(root,RollDirection,OppositeDirection);
			}
			else
			{
				//LL or RR roll
				Roll(root,RollDirection,OppositeDirection);
			}
			return true;
		}
		return false;
	}

	//preforms a roll in RollDirection to the subtree whose root is root
	static void Roll(node* &root, directions RollDirection, directions OppositeDirection)
	{
		node* ptr = root->Children[OppositeDirection];
		root->Children[OppositeDirection] = ptr->Children[RollDirection];
		ptr->Children[RollDirection] = root;
		

		int BfValue = CalcBfChange(RollDirection); //1 for left -1 for right

		//balance updates
		//description for left roll (other side is symetric)
		//old root:
		//we lose the right child, and the childs right child
		//so first we decrese one for child
		//second we check if the right child's right subtree is bigger
		//the right child's left sub tree if it is we also gain the diffrence between the subtrees
		root->bf +=  BfValue;
		if (ptr->bf * BfValue < 0)
		{
			root->bf -=  ptr->bf;
		}

		//description for left roll (other side is symetric)
		//new root:
		//in the new root we gain the old root as the left child,
		//now we have to check if our old left subtree is smaller then
		//the oldroot left subtree, if it his we also gain this diffrence
		//we can preform this check according to the old root new bfvalue
		ptr->bf  +=  BfValue;
		if (root->bf * BfValue > 0)
		{
			ptr->bf +=  root->bf;
		}

		root = ptr; //update root
	}

	//internal insert function
	static HeightChange insert(node* &root,T *item)
	{
		if (root == NULL)
		{
			root = new node(item);
			return HeightChanged;
		}	
		//else
		CmpResult res= Cmp(root->data,item);
		if (res == Equal)
		{
			//we arrive here if the item already exist
			return Error;
		}
		else
		{
			directions dir = (directions) res; //bellow -> left, above -> right
			HeightChange height = insert(root->Children[dir],item);
			if (height == HeightChanged)
			{
				if (UpdateBalance(root,CalcBfChange(dir)) || root->bf == 0)
				{
					//if the tree is balanced now it was imblanced we didnt change the hight,
					//if its -1 or 1 it means that one of the sides grow
					height = NoHeightChange;
				}
			}
			assert(root->bf >=-1 && root->bf <= 1);
			return height;
		}
	}

	//internal remove function
	static HeightChange remove(node* &root,T *item)
	{
		if (root == NULL)
		{
			return Error; //item wasnt found
		}

		//else
		int BfChange;
		HeightChange height;
		CmpResult res= Cmp(root->data,item);
		if (res == Equal)
		{
			if (FreeItems)
			{
				delete(root->data); //free data
			}
			//found item need to delete it
			if (root->Children[Right] == NULL) //we dont have right child
			{
				node* ptr = root; //save pointer to root to free it
			    root = root->Children[Left]; //make the left child (or null) the name child of parent
				delete ptr; //free node;
				return HeightChanged; //we changed the height
			}
			else //we have a right child
			{
				//extranct the minimum of the sub tree and put it in root
				height = ExtractMin(root->Children[Right],root->data);
				BfChange = 1;
			}
		}
		else
		{
			directions dir = (directions) res; //bellow -> left, above -> right
			BfChange = -CalcBfChange(dir);
			height = remove(root->Children[dir],item); 
		}

		if (height == HeightChanged)
		{
			if ((UpdateBalance(root,BfChange) && root->bf != 0)
				|| root->bf != 0)
			{
				height = NoHeightChange; //if we preformed a roll and the tree still isnt balanced
				//or if we didnt, the tree was balanced but now it isnt then the height didnt change
			}
		}
		assert(root->bf >=-1 && root->bf <= 1);
		return height;	
	}

	//Extract the minumum from the tree and put it in Min
	//could be done with getmin + remove, but then we would travel
	//the tree twice and do unnesesary compares
	static HeightChange ExtractMin(node* &root,T* &Min)
	{
		if (root->Children[Left] == NULL)
		{
			node* ptr = root->Children[Right];
			Min = root->data;
			delete(root); //free node
			root = ptr; //update the child of the parent to point to the right child
			return HeightChanged; //we deleted a node so the height changed
		}
		//else
		HeightChange height = ExtractMin(root->Children[Left],Min);
		if (height == HeightChanged)
		{
			if ((UpdateBalance(root,-1) && root->bf != 0)
					|| root->bf != 0)
			{
				height = NoHeightChange; //if we preformed a roll and now the tree is balanced,
				//or if we didnt, the tree was balanced but now it isnt then the height didnt change
			}
		}
		assert(root->bf >=-1 && root->bf <= 1);
		return height;
	}

	//internal function for print_tree, puts the tree in Array
	static void print_tree(node* root,int index, node* Array[])
	{
		Array[index] = root;
		if (root != NULL)
		{
			print_tree(root->Children[Left],(index +1) * 2 -1,Array);
			print_tree(root->Children[Right],(index +1) * 2,Array);
		}
	}

	//internal inorder function
	static bool inorder(node* root,Predicate *p)
	{
		if (root != NULL)
		{
			return inorder(root->Children[Left],p)
				|| p->DoWork(root->data)
				|| inorder(root->Children[Right],p);
		}
		return false;
	}

	//internal free function
	static void free(node* root)
	{
		if (root != NULL)
		{
			free(root->Children[Left]);
			free(root->Children[Right]);
			if (FreeItems)
			{
				delete root->data;
			}
			delete root;
		}
	}

	node* root;
};

#endif

