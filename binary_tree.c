#include <stdio.h>
#include <stdlib.h>
#include "queue.h"



// 创建二叉树
node* create(void)  // 返回值为新二叉树的根节点指针
{
	// 采用先序遍历顺序创建各个节点并将它们连接起来
	
	char c;

	c = getchar();

	if(c == ' ') return NULL;

	node* root = (node*)malloc(sizeof(node));

	root->data  = c;

	root->left  = create();
	root->right = create();

	return root;
}


// 销毁二叉树
void destroy(node* bt)
{
	if(bt == NULL) return;  // 如果为空树，直接返回

	// 采用后序遍历顺序释放所有节点
	destroy(bt->left);
	destroy(bt->right);
	free(bt);

	/*
	// 采用先序遍历顺序释放所有节点
	node* left = bt->left, *right = bt->right;
	free(bt);
	destroy(left);
	destroy(right);
	*/
}



// 先序遍历（打印数据元素）
void preorder(node* bt)
{
	if(bt == NULL) return;

	printf("%c", bt->data);
	preorder(bt->left);
	preorder(bt->right);
}



// 中序遍历（打印数据元素）
void inorder(node* bt)
{
	if(bt == NULL) return;

	inorder(bt->left);
	printf("%c", bt->data);
	inorder(bt->right);
}



// 后序遍历（打印数据元素）
void lastorder(node* bt)
{
	if(bt == NULL) return;

	lastorder(bt->left);
	lastorder(bt->right);
	printf("%c", bt->data);
}


// 层序遍历
void level_order(node* bt)
{
	// 创建队列
	queue* q = create_queue(100);

	// 将根节点指针入队
	if(bt != NULL) push_back(q, bt);

	// 反复进行如下操作，直到队列为空
	node* p = NULL;

	while(!empty(q))
	{
		// 访问队头元素，然后出队
		p = *front(q);
		printf("%c", p->data);
		pop_front(q);

		// 如果左孩子和右孩子不为空，就将它们依次入队
		if(p->left != NULL) push_back(q, p->left);
		if(p->right != NULL) push_back(q, p->right);
	}
	
	destroy_queue(q);
}



int main()
{
	node* bt1 = create();

	printf("\n先序遍历序列为：");
	preorder(bt1);
	printf("\n");

	printf("\n中序遍历序列为：");
	inorder(bt1);
	printf("\n");

	printf("\n后序遍历序列为：");
	lastorder(bt1);
	printf("\n");

	printf("\n层序遍历序列为：");
	level_order(bt1);
	printf("\n");

	destroy(bt1);	

	return 0;
}
