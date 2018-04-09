/*
 *  @name: Solution.cpp
 *  @author: EA
 */

#include <stack>
#include <queue>
#include <map>
#include <unordered_map>
#include "Solution.h"
#include <math.h>
#include <climits>

#define SUCCESS 8
#define NOT_FOUND -1
#define ONE 1

/**
 * description : INORDER TREE WALK can be explained as first visit the left node,
 * then,
 * go through the its root node
 * then, goto right node
 */
// This function traverses a binary tree using INORDER
void Solution::inorder_tree_walk (Node2 *root)
{
	if (root != NULL)
	{
		inorder_tree_walk (root->left);
		printf ("%d\t", root->key);
		inorder_tree_walk (root->right);
	}
	// base case i) 'do nothing'
}

/**
 * description : LEVELORDER TREE WALK is a breadth first traversal for the tree
 */
// This function traverses a binary tree using LEVELORDER
void Solution::levelorder_tree_walk (Node2 *root)
{
	// base case i) 'do nothing'
	if (root == NULL) return;

	// Use auxiliary data structure, in this case queue chosen
	std::queue<Node2 *> q;

	q.push(root);

	while (!q.empty())
	{
		Node2 *first = q.front();

		// job done
		printf ("%d\t", first->key);

		// continue to iterate over
		q.pop();

		if (first->left != NULL)
			q.push(first->left);

		if (first->right != NULL)
			q.push(first->right);
	}

	printf ("\n");
}

// This function removes the N-TH node from the end of given a linked list and returns its head
// Assumption : n will be valid
Node* Solution::remove_nth_from_end (Node *head, int n)
{
	if (head == NULL) return head;

	// local data
	Node *current = head, *prev = NULL;
	int l = length (head, 0);

	// Find (LENGTH - N)-TH node from head
	for (int j = 0; j < (l - n); j++)
	{
		prev = current;
		current = current->next;
	}

	if (prev != NULL)
		prev->next = current->next;
	else
	{
		head = current->next; // move head to rest
		current->next = NULL; // unlink between current and rest
	}

	delete current;
	current = NULL;

	return head;
}

// This function flattens given a binary tree to a linked list in place, based on selected direction as LEFT|RIGHT
void Solution::flatten (Node2 *root, DIRECTION d)
{
	// base case i) 'return with empty hands'
	if (root == NULL)
		return;

	// flatten (it) from (it ? of course the given binary tree) from left
	if (CCW == d)
		flatten_l (root);
	else
		flatten_r (root); // RIGHT
}

// These functions are helper functions for flatten function
void Solution::flatten_r (Node2 *root)
{
	// defensive check
	if (root == NULL)
		return;

	// base case ii.i) 'left subtree not empty'
	if (root->left != NULL)
	{
		// local data
		Node2 *remember = root->left;
		root->left = NULL; // unlink
		Node2 *temp = root->right; // do not forget

		// move left subtree to right subtree at first
		root->right = remember;
		// remember->right = temp; // articulate from right this line is wrong, you must find end of its leaf

		while (remember->right != NULL)
			remember = remember->right;

		// now articulate from right
		remember->right = temp;
	}

	// recursive_part
	flatten_r (root->left);
	flatten_r (root->right);
}

void Solution::flatten_l (Node2 *root)
{
	// defensive check
	if (root == NULL)
		return;

	// yazmaya usendim (AYNI SAGIN SOLU)!

	/**
	 * @note: why not use inverse of binary tree function
	 * since the result of the function of FLATTEN LEFT is in fact INVERSE of the result of the function of flattened RIGHT version of binary function
	 */

	flatten_r (root);
	inverse (root); // TESTED in LEETCODE, it worked
}

// This function constructs the binary tree at maximum possible height from vector
Node2* Solution::construct_maximum_binary_tree(const std::vector<int>& A)
{
	// TODO
}

// This function checks whether given binary tree is an actually binary search tree or not
bool Solution::check_BST (Node2 *root)
{
	// base case i) called just after leaf node
	if (root == NULL)	return true;

	// local data
	Node2 *right = min (root->right); // find the minimum value of right subtree and use it to compare with root
	Node2 *left = max (root->left); // find the maximum value of left subtree and use it to compare with root

	// breaks the binary search tree rule
	if (right != NULL && right->key <= root->key)	return false;

	// breaks the binary search tree rule
	if (left != NULL && left->key > root->key)	return false;

	return (check_BST (root->right) && check_BST (root->left)); // check both subtrees
}

/*
 * rule : If the height of any nodes' RIGHT subtree differs from the height of the nodes' LEFT subtree by no more than ONE,
 * then, it is a balanced BT
 */
// This function checks whether given binary tree is an actually balanced binary tree or not
bool Solution::check_balanced (Node2 *root)
{
	// base case i)
	if (root == NULL)	return true;

	// base case ii)
	if (root->right == NULL)
	{
		// check the height of LEFT subtree
		int l = height (root->left);
		return (l <= ONE);
	}

	// base case iii)
	if (root->left == NULL)
	{
		// check the height of RIGHT subtree
		int r = height (root->right);
		return (r <= ONE);
	}

	// local data
	int l = height (root->left);
	int r = height (root->right);

	// continue to check both LEFT and RIGHT subtrees
	return ( check_balanced (root->left) && check_balanced (root->right) && (abs (l - r) <= ONE) );
}

/*
 * description : following functions use breadth first search (BFS) strategy, in other words, LEVELORDER TREE WALK
 */

// This function inverses the given binary tree and returns it in iterative way
Node2* Solution::inverse (Node2 *root)
{
	// base case i)
	if (root == NULL) return NULL;

	// use auxiliary data structure, in this case queue chosen
	std::queue<Node2 *> q;

	q.push(root);

	while (!q.empty())
	{
		// fetch current queue size
		int size = q.size();

		// current level of the binary tree contains at least one node or more
		while (size > 0)
		{
			Node2 *first = q.front();

			// swap OP.
			// local data O(1) In Place
			Node2 *temp = first->left; // remember
			first->left = first->right;
			first->right = temp;

			q.pop();

			if (first->left != NULL)
				q.push(first->left);

			if (first->right != NULL)
				q.push(first->right);

			// one pop, one decrement
			size = size - 1;
		}
		// level by level
	}

	return root;
}

// This function calculates the average value of the nodes on each level in the form of vector*
std::vector<double> Solution::av_of_levels (Node2 *root)
{
	// local data
	std::vector<double> v;

	// base case i) 'return empty vector'
	if (root == NULL) return v;

	// Use auxiliary data structure, in this case queue chosen
	std::queue<Node2 *> q;

	q.push(root);

	while (!q.empty())
	{
		// fetch current count size & define counter
		int size = q.size();
		int c = 0;

		/*
		 * @note : It is VERY important to define SUM as long rather than signed integer
		 * since SUM, in fact addition may overflow, please be careful ! (because of that you failed some of TEST CASES, remember)
		 */
		long sum = 0;


		// current level of the binary tree contains at least one node or more
		while (size > 0)
		{
			Node2 *first = q.front();

			// job done is here, once you can understand this is the place where print out the nodes' key in LEVELORDER TREE WALK,
			// in this case, fetch the nodes' key and sum up
			sum += first->key;
			q.pop();

			if (first->left != NULL)
				q.push(first->left);

			if (first->right != NULL)
				q.push(first->right);

			size = size - 1;
			c++;
		}
		// level by level

		double av = (double) (sum) / (double) (c);
		v.push_back(av);
	}

	return v;
}

// This function calculates the largest value of the nodes on each level in the form of vector*
std::vector<int> Solution::largest_value_of_levels (Node2 *root)
{
	// local data
	std::vector<int> v;

	// base case i) 'return empty vector'
	if (root == NULL) return v;

	// use auxiliary data structure, in this case queue chosen
	std::queue<Node2 *> q;

	q.push(root);

	while (!q.empty())
	{
		// fetch current count size & define counter
		int size = q.size();
		int c = 0;
		std::vector<int> inner_v;

		// current level of the binary tree contains at least one node or more
		while (size > 0)
		{
			Node2 *first = q.front();

			// job done is here, once you can understand this is the place where print out the nodes' key in LEVELORDER TREE WALK,
			// in this case, fetch the nodes' key and pushes into vector
			inner_v.push_back(first->key); // O(1)
			q.pop();

			if (first->left != NULL)
				q.push(first->left);

			if (first->right != NULL)
				q.push(first->right);

			size = size - 1;
			c++;
		}
		// level by level

		int m = max (inner_v, c);
		v.push_back(m);
	}

	return v;
}

/*
 * This function returns with the node containing the key, otherwise search miss (returning NULL)
 * Note: this function searches the key in given BST
 */
Node2* Solution::search (Node2 *root, int key)
{
	// base case i)
	if ( (root == NULL) || (key == root->key)) return root;

	if (key > root->key)	// seek RIGHT subtree
		return search (root->right, key);
	else	// seek LEFT subtree
		return search (root->left, key);
}

// This function searches the key provided as @param.
// Assumption is root is a BST,
Node2* Solution::iterative_tree_search (Node2 *root, int key)
{
	// local data
	Node2 *current = root;

	while ( (current != NULL) && (key != current->key) )
	{
		// This is the rule set from definition of Binary Search Tree (BST)
		if (key < current->key) // seek LEFT subtree
			current = current->left;
		else // seek RIGHT subtree
			current = current->right;
	}
	// What if we construct binary tree instead of BST ?
	// Check out exist function not using any auxiliary data structure

	return current; // either key found or current left as NULL
}
// This function searches the key provided as @param.
// Assumption is root can be BT, which is a larger set of BST
Node2* Solution::iterative_randomized_tree_search (Node2 *root, int key)
{
	// base case i)
	if (root == NULL)
		return NULL;

	// Use auxiliary data structure, in this case stack chosen
	std::stack<Node2 *> s1;
	s1.push(root);

	// eger boyle bir kontrol koyuyorsan bir yerlerde mutlaka pop yapmalisin.
	// ki iterasyondan cikabilesin.
	while (!s1.empty())
	{
		// We need ,first and foremost, to compare key
		// in stack the way is looking top element at a time
		// fetch top element of current stack
		Node2 *tp = s1.top();

		if (tp->key == key)
			return tp;

		// continue to iterate over
		s1.pop();

		if (tp->left != NULL)
			s1.push(tp->left);

		if (tp->right != NULL)
			s1.push(tp->right);
	}
	// If the execution reaches this points, it is meant not to be found (key)

	return NULL;
}

// This function searches & returns minimum node
// Assumption: root is a binary search tree
Node2* Solution::min (Node2 *root)
{
	if (root == NULL) return root;

	// seek always LEFT
	while (root->left != NULL)
		root = root->left;

	return root;
}

// This function searches & returns maximum node
// Assumption: root is a binary search tree
Node2* Solution::max (Node2 *root)
{
	if (root == NULL) return root;

	// seek always RIGHT
	while (root->right != NULL)
		root = root->right;

	return root;
}

/**
 * definition : "lowest common ancestor is defined between two nodes v and w as the lowest node in T
 * which has both v and w as descendants (a node to be a descendant to itself)
 */
// This function finds and returns the node which is the lowest common ancestor of given two nodes
Node2* Solution::lca (Node2 *root, Node2 *v, Node2 *w)
{
	// base case null)
	if (root == NULL) return NULL;

	// base case i) 'current root is already either node v or node w' then return current root, directly'
	if (root == w || root == v)
		return root;

	// recursive part 'continue to seek both left & right subtrees'
	Node2 *left = lca (root->left, v, w);
	Node2 *right = lca (root->right, v, w);

	// base case ii.i) 'the one is in roots left subtree, the other one is in roots right subtree'
	if (left != NULL && right != NULL) return root;

	// base case ii.ii) 'the one is not in its right subtree'
	else if (left != NULL)
		return left;

	// base case ii.iii) 'the one is not in its left subtree'
	else if (right != NULL)
		return right;

	else
		return NULL;
}

// This function returns predecessor node of asked node as in parameter
// Assumption : root is a binary search tree
Node2* Solution::predecessor (Node2 *root, Node2 *v)
{
	// base case null)
	if (root == NULL || v == NULL) return NULL;

	// Actually, this problem has two base cases
	// base case i) 'node v has left subtree, then problem turns into seeking maximum node in this left subtree'
	if (v->left != NULL)
		return max (v->left);

	// base case ii) 'node v has NOT left subtree, then problems into searching node with the biggest key smaller than node v.key starting from ROOT'
	else
	{
		// local data
		bool found = false;
		Node2 *current = root, *remember = NULL;

		while (!found && current != NULL)
		{
			// base case ii) 'current is v'
			/*
			if (current == v)
				return remember; // return successor or successor miss if there is no successor node
			*/

			// base case iii.i 'current is not v'
			if (current->key > v->key) // which means look up in LEFT subtree
				current = current->left;

			// base case iii.ii) 'current is not v'
			else if (current->key < v->key) // which means look up in RIGHT subtree
			{
				remember = current; // remember turning point
				current = current->right;
			}

			else
				found = true;
		}

		// return predecessor or predecessor miss if there is no predecessor node, the case of remember stayed NULL
		return remember;
	}
}

// This function returns successor node of asked node as in parameter
// Assumption : root is a binary search tree
Node2* Solution::successor (Node2 *root, Node2 *v)
{
	// base case null)
	if (root == NULL || v == NULL) return NULL;

	// Actually, this problem has two base cases
	// base case i) 'node v has right subtree, then problem turns into seeking minimum node in this right subtree'
	if (v->right != NULL)
		return min (v->right);

	// base case ii) 'node v has NOT right subtree, then problems into searching node with smallest key bigger than v.key starting from ROOT'
	else
	{
		// local data
		bool found = false;
		Node2 *current = root, *remember = NULL;

		while (!found && current != NULL)
		{
			// base case ii) 'current is v'
			/*
			if (current == v)
				return remember; // return successor or successor miss if there is no successor node
			*/

			// base case iii.i 'current is not v'
			if (current->key > v->key) // which means look up in LEFT subtree
			{
				remember = current; // remember turning point
				current = current->left;
			}

			// base case iii.ii) 'current is not v'
			else if (current->key < v->key) // which means look up in RIGHT subtree
				current = current->right;

			else
				found = true;
		}

		// return successor or successor miss if there is no successor node, the case of remember stayed NULL
		return remember;
	}
}

/**
 * definition : the minimum depth is # of nodes along the shortest path from root down to the nearest leaf node
 */
// This function calculates the minimum depth of a binary tree in recursive way
int Solution::min_depth (Node2 *root)
{
	// base case i)
	if (root == NULL)
		return 0;

	// base case ii) leaf node
	if (root->left == NULL && root->right == NULL)
		return ONE;

	// seek in RIGHT subtree
	if (root->left == NULL)
		return 1 + min_depth (root->right);

	// seek in LEFT subtree
	if (root->right == NULL)
		return 1 + min_depth (root->left);

	// local data
	int depth_left = min_depth (root->left);
	int depth_right = min_depth (root->right);

	return 1 + std::min ( depth_right, depth_left );
}

/**
 * definition : the height of a tree is # of nodes along the longest path from root to leaf
 */
// This function calculates the height of a binary tree using iteration
int Solution::height_iterative (Node2 *root)
{
	// Note: use similar logic as in LEVELORDER TREE WALK

	// base case i)
	if (root == NULL) return 0;

	// local data
	int H = 0;

	// Use auxiliary data structure, in this case queue chosen
	std::queue<Node2 *> q;

	q.push(root);

	while (!q.empty())
	{
		// Re-update node count as current queue size
		int node_count = q.size();

		// increment height
		H++;

		// current level of the binary tree contains nodes
		while (node_count > 0)
		{
			Node2 *first = q.front();
			q.pop();

			if (first->left != NULL)
				q.push(first->left);

			if (first->right != NULL)
				q.push(first->right);

			node_count--;
		}
		// level by level
	}

	return H;
}

// This function calculates the height of a binary tree by using recursion
int Solution::height (Node2 *root)
{
	// base case i)
	if (root == NULL)
		return 0;

	int left_height = height (root->left);
	int right_height = height (root->right);

	return 1 + std::max( right_height, left_height );
}

// This function returns true when key be existed in a binary tree, otherwise returns false
bool Solution::exist (Node2 *root, int key)
{
	// base case i)
	if (root == NULL)
		return false;

	// base case ii)
	if (key == root->key)
		return true;

	// local data
	bool left = exist (root->left, key);
	bool right = exist (root->right, key);

	return (right || left);
}

// This function returns the length of linked list given as parameter,
// pointed by HEAD, recursive solution
int Solution::length (Node* head)
{
	// base case is NULLITY of given linked list
	if (head == NULL)
		return 0;

	// Spans of multiple calls of this function
	return 1 + length(head->next);

	// In a recursive way, goto end of linked list,
	// count from tail ... one by one, understand
}

/*
 * This function calculates the length of the given linked list by using tail recursion
 */
int Solution::length (Node* head, int l) // use second argument as the counter in this case
{
	// base case i) head NULL then return length, itself
	if (head == NULL) return l;

	return length (head->next, (l+1));
}

// This function reverses the linked list given as parameter,
// pointed by HEAD, iterative solution
Node* Solution::reverse (Node *head)
{
	if (head == NULL)
		return NULL;

	// local data
	Node *curr = head;
	Node *prev = NULL, *next;

	while (curr != NULL)
	{
		next = curr->next;
		curr->next = prev; // ilk adimda previous NULL bu noktaya dikkat et
		prev = curr; // simdi previous current noda point ediyor.

		// iterasyona devam et
		curr = next;
	}

	return prev; // now it points the tail of original list another word, reverse list.
}

// This function reverses the given linked list from position m to n
// Given m, n satisfy the following condition
// 1 <= m <= n <= length of the list
Node* Solution::reverse (Node *head, int m, int n)
{
	if (head == NULL) return NULL;
	// if ( (n - m) == 0) return head; // No modification required in the case of [1,1] or [3,3]

	// local data
	Node *curr = head, *aux = NULL, *prev = NULL, *next, *start;

	// move current by (m-1) at the begin if possible
	for (int j = 0; j < (m - 1); j++)
	{
		aux = curr;
		curr = curr->next;
	}

	// remember current
	start = curr;

	for (int i = 0; i < (n - m + 1); i++)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;

		// continue to iterate
		curr = next;
	}

	// The case of NOT movement of current, therefore auxiliary remained NULL,
	// THEN, link head.next to next and return with previous
	if (aux == NULL)
	{
		head->next = next;
		return prev;
	}
	// The case of movement of current means auxiliary points at least first node
	// THEN, link auxiliary.next to previous, (first location of current).next (start.next) to next
	// and return with previous
	else
	{
		aux->next = prev;
		start->next = next;
		return head;
	}
}

/*
 * This function rotates the given list right by k places where k non-negative
 */
Node* Solution::rotate_r (Node *head, int k)
{
	// local data
	int n = length (head, 0);

	if (n == 0 || n == 1) return head; // if head is null or contains one element

	for (int i = 0; i < (k % n); i++)
		head = rotate_r_one (head);

	return head;
}

/*
 * This function rotates the given list right by one place
 * Assumption : the list pointed by head contains at least two or more elements
 */
Node* Solution::rotate_r_one (Node *head)
{
	// defensive check
	if (head == NULL || head->next == NULL) return head;

	// local data
	Node *current = head, *prev = NULL;

	while (current->next != NULL)
	{
		prev = current;
		current = current->next;
	}

	prev->next = NULL;
	current->next = head;

	return current;
}
// This function prints the given string in reverse order without altering the string
void Solution::print_r (char *str)
{
	if (*str)
	{
		print_r(str+1);

		// job done
		printf("%c", *str);
	}
	// base case i) 'do nothing'
}

// This function prints the singly-linked list in reverse order
void Solution::print_r (Node *head)
{
	if (head != NULL)
	{
		print_r (head->next);
		printf ("%d\t", head->key);
	}
	// base case i) do nothing
}

// This function pushes the node from back for singly-linked list
// Note : use as push_back (&head, key)
void Solution::push_back (Node **head, int key)
{
	// local data
	Node *temp = new Node (key);

	if (*head == NULL)
	{
		*head = temp;
	}
	else
	{
		temp->next = *head;
		*head = temp;
	}
}

// This function gets the middle element of the linked list given as parameter,
// pointed by HEAD
Node* Solution::get_middle_node (Node *head)
{
	Node *first = head, *second = head;

	// The idea to put two pointer and one to move by one step while the second one to move by two step
	// When fast one reaches the end, slow one points the middle node of list
	while (second != NULL && second->next != NULL)
	{
		first = first->next; // slow pointer
		second = second->next->next; // fast pointer
	}
	// at the end of iteration, think about...
	return first;
}

// This function detects whether cycle or not in the linked list given as parameter
// pointed by HEAD
bool Solution::detect_cycle (Node *head)
{
	// construct similar logic as getting middle node of linked list
	Node *first = head, *second = head;

	while (first != NULL && second != NULL && second->next != NULL)
	{
		first = first->next; // slow pointer
		second = second->next->next; // fast pointer

		// first and second points the same node, then cycle detected
		if (first == second)
			return true;

		// else continue the iteration
	}
	// If we reaches this point then there is no cycle in the list since iteration already terminated with NULL

	return false;
}

// This function returns the node where cycle begins, if given list contains cycle, if NOT, then, returns miss cycle (NULL)
Node* Solution::detect_cycle_node (Node *head)
{
	// use similar logic as in detect cycle which returns 1/0 decisions
	Node *first = head, *second = head;
	bool cycle = false;

	while (!cycle && first != NULL && second != NULL && second->next != NULL)
	{
		first = first->next; // slow pointer
		second = second->next->next; // fast pointer

		// first and second points the same node, then cycle detected
		if (first == second)
			cycle = true;

		// else continue the iteration
	}
	// If we reaches this point then there is no cycle in the list since iteration already terminated with NULL

	// it is clear there is a cycle and seek the node where the cycle detected
	if (cycle)
	{
		// there is no need to NULL check since given list contains a cycle

		// restart from head;
		first = head;

		while (first != second)
		{
			first = first->next;
			second = second->next;
		}

		return first;
	}
	// cycle remains false, which means there is no cycle in given list
	else
		return NULL;
}

// This function checks whether linked list is palindrome or not given as a parameter
// pointed by HEAD
int Solution::check_palindrome(Node *head)
{
	// base case
	if (head == NULL)
		return SUCCESS;

	// local data
	std::vector<int> v;
	push_r (head, v);

	unsigned int i = 0;

	while (i < v.size())
	{
		if (v[i] != head->key)
			return -1;

		// traverse vector & list
		i = i + 1;
		head = head->next;
	}

	// If we reach at this point, the list is a palindrome
	return SUCCESS;
}

// This function pushes the key from the given singly-linked list in reverse order
// It is similar to print key in reverse order
void Solution::push_r (Node *head, std::vector<int>& A)
{
	if (head != NULL)
	{
		push_r (head->next, A);
		A.push_back(head->key);
	}
	// base case i) do nothing
}

// This function implements the reversal algorithm for array rotation
std::vector<int> Solution::rotate_rl(std::vector<int>& A, int k, DIRECTION d)
{
	// local data
	int n = A.size();

	if (n == 0) return A; // defensive check

	// LEETCODE test update
	k = k % n;

	// this means direction CCW, left rotate by k
	if (CCW == d)
	{
		// split the array properly
		reverse (A, 0, k-1);
		reverse (A, k, n-1);
	}
	// this means direction CW, right rotate by k
	else
	{
		// split the array properly
		reverse (A, 0, n-k-1);
		reverse (A, n-k, n-1);
	}

	// reverse of reverse
	return reverse (A, 0, n-1);
}

// This function reverses the given vector, i as started index and j as last index at the beginning
std::vector<int> Solution::reverse(std::vector<int>& A, int i, int j)
{
	// WHILE I-TH index smaller than J-TH index, then
	// SWAP the elements and move the indices towards each other
	while (i < j)
	{
		swap(&A[i], &A[j]);

		// Increment start index and decrement last index by 1 for each iteration
		i++;
		j--;
	}

	return A;
}

// This function searches the target in the given sorted array
int Solution::search(const std::vector<int>& A, int first, int last, int target)
{
	// base case i)
	if (first > last)
	{
		return NOT_FOUND;
	}
	else
	{
		int mid = first + (last - first) / 2; // avoid overflow a negative value

		// base case ii)
		if (target == A[mid])
			return mid;
		else if (target > A[mid]) // continue to search in array::RIGHT
			return search(A, mid+1, last, target);
		else // continue to search in array::LEFT
			return search(A, first, mid-1, target);
	}
}

/** This function returns K-TH smallest value in a binary search tree
 *	Assume k in in valid range
 */
int Solution::k_small (Node2 *root, int k)
{
	if (root != NULL)
	{
		std::vector<int> v;
		construct_vector(root, v);
		return v[k-1];
	}
	else
		return INT_MAX;
}

// This function solves K-TH small problem in recursive way without using any additional data structure
int Solution::k_small(int k, Node2 *root)
{
	if (root != NULL)
	{
		// TODO
	}
	else
		return INT_MAX;
}

/*
 * This function constructs a vector from a binary tree based on INORDER traversal algorithm
 * @Warning : Note that this vector is sorted if given binary tree is actually binary search tree
 */
void Solution::construct_vector(Node2 *root, std::vector<int>& A)
{
	// TODO : Solve in iteration
	if (root != NULL)
	{
		construct_vector(root->left, A);

		// Instead of print out the current value, just push it to vector
		A.push_back (root->key);

		construct_vector(root->right, A);
	}
	// base case i) do nothing
}

// This function searches the maximum value in the given unsorted array
int Solution::max(const std::vector<int>& A, int first, int last)
{
	// base case
	if (first >= last) // array SZE of 1
		return A[last]; // remember at the end, you can think as leaf node, this function returns from here
	else
	{
		int mid = first + (last - first) / 2;
		return std::max ( max (A, first, mid), max (A, mid+1, last)  );
	}
}

// This function searches the maximum value in the given unsorted array (alternative)
int Solution::max(const std::vector<int>& A, int size)
{
	// base case
	if (size  == 1) // array SZE of 1
		return A[0]; // remember at the end, you can think as leaf node, this function returns from here
	else
	{
		// approach last & rest
		return std::max ( A[size-1], max (A, size-1)  );
	}
}

// This function returns the K-TH largest value in the given array
int Solution::k_largest (std::vector<int>& A, int k)
{
	// local data
	int size = A.size();

	// Actually, K-TH largest means (SIZE-K)-TH smallest, then the problem turns finding (SIZE-K) smallest value in the given array
	return k_small ( (size-k + 1), A, 0, size-1);
}

// This function returns the K-TH smallest value in the given array
int Solution::k_small (int k, std::vector<int>& A, int first, int last)
{
	if (k > (last - first +1) || k < 0)
		return INT_MAX;

	// select pivot index based on lomuto's partition
	int pivotIdx = l_partition(A, first, last);

	if (k < (pivotIdx - first + 1) )
		return k_small (k, A, first, pivotIdx-1);
	else if (k == (pivotIdx - first + 1) )
		return A[pivotIdx]; // base case
	else
		return k_small (k - (pivotIdx - first + 1), A, pivotIdx+1, last);
}

// This function implements the Lomuto's partition
int Solution::l_partition(std::vector<int>& A, int p, int r)
{
	int pivot = A[r]; // select pivot as last element
	int i = p - 1;

	for (int j = p; j <= r - 1; j++)
	{
		if (A[j] <= pivot)
		{
			i = i+1;
			swap (&A[i], &A[j]);
		}
	}

	swap (&A[i+1], &A[r]);
	return (i+1);
}

// This function implements the hoare's partition
int Solution::h_partition(std::vector<int>& A, int p, int q)
{
	// TODO
}

void Solution::swap (int *x, int *y)
{
	// local data O(1) In Place
	int temp = *x;
	*x = *y;
	*y = temp;
}

/*
 * This function finds the maximum # of occurrence any number given in the list
 */

int Solution::find_maximum_occurrence (std::vector<const char *>& A)
{
	// Note : Use map in order to catch O(N) solution P.S. you will remember this line
	int size = A.size();
	std::map<const char *, int> temp; // define map onto stack

	for (int j = 0; j < size; j++)
	{
		if (temp.find(A[j]) == temp.end()) // not contain
			temp.insert(std::pair<const char *, int> (A[j], 1) );
		else // already contain
			temp.find(A[j])->second = temp.find(A[j])->second + 1; // simply increment the occurrence
	}

	// you know map already sorted, reach out with the iterator begin
	return temp.begin()->second;
}

/*
 * This function prints pair from given array whose sum is equal the the given sum
 */
void Solution::print_pair_sum (std::vector<int>& A, int sum)
{
	// Note: similar logic as in the function finding maximum occurrence problem expected solution complexity : O (N)
	int size = A.size();
	std::unordered_map<int, int> temp; // define map onto stack

	// construct pairs by making key as vector value and value as vector index, <key, value>
	for (int i = 0; i < size; i++)
		temp.insert(std::pair<int, int> (A[i], i) );

	for (int j = 0; j < size; j++)
	{
		int diff = (sum - A[j]); // now the problem turns into seeking DIFF in map

		// OK, key,value pair in fact a,b where a+b = sum in order words, sum-a = b
		if (temp.find(diff) != temp.end()) // contain
			printf ("pair as sum %d, (<%d, %d>) \n", sum, diff, A[j]);
	}
}

// This function compares two given string (in recursive way) and returns an integer value
int Solution::compare (std::string s1, std::string s2)
{
	// base case null) both string inputs are NULL character at the same time
	if (s1.size() == 0 && s2.size() == 0)
		return 0;

	// base case null.i) first is null or reached null before second
	if (s1.size() == 0)
		return -1;

	// base case null.ii) second is null or reached null before first
	if (s2.size() == 0)
		return 1;

	// compare first characters, always
	// base case i.i) not equality
	if (s1.at(0) < s2.at(0) )
		return -1;
	// base case i.ii) not equality
	else if (s1.at(0) > s2.at(0) )
		return 1;
	// recursive part
	else
	{
		// continue to seek with string except first character, always
		return compare (s1.substr(1), s2.substr(1));
	}
}
