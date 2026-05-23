#include <stdio.h>
#include <stdlib.h>


typedef int elem_type;  // 声明数据元素(Data Element)类型


// 声明节点类型
typedef struct node
{
	elem_type data;             // 数据域
	struct node* next;          // 指针域
} node;


// 声明栈信息结构体
typedef struct 
{
	node* top;    // 栈顶指针，即头节点指针，核心属性
	int   len;    // 长度（数据元素的个数）

} stack;


// 初始化栈（基于无头单向链表实现）
stack* create(void)
{
	stack* s = malloc(sizeof(stack));

	if(s == NULL)
	{
		perror("malloc fail");
	}

	s->top = NULL;
	s->len = 0;

	return s;
}



// 清空（删除所有存放数据元素的节点）
void clear(stack* s)
{
	// 遍历栈所有节点，将它们都释放掉
	node* p = NULL;

	while(s->top != NULL)
	{
		p = s->top->next;
		free(s->top);
		s->top = p;
	}

	s->len = 0;
}



// 销毁栈
void destroy(stack* s)  // 参数 s 表示要销毁的目标栈
{
	clear(s);
	free(s);
}




// 求长度（时间复杂度为 O(1)，空间复杂度为 O(1)）
int size(stack* s)
{
	return s->len;
}



// 判空
int empty(stack* s)
{
	return !(s->len);
}



// 入栈（就是头插，时间复杂度为 O(1)，空间复杂度为 O(1)）
void push(stack* s, elem_type data)
{
	// 创建一个新节点
	node* n = malloc(sizeof(node));

	if(n == NULL)
	{
		perror("malloc fail");
	}

	n->data = data;
	n->next = s->top;  // 该节点将成为栈的第 0 个节点，原来的第 0 个节点将成为该节点的后继
	// 让新节点成为栈头节点的后继
	s->top = n;
	
	// 更新栈属性
	s->len++;
}



// 出栈（就是头删，时间复杂度为 O(1)，空间复杂度为 O(1)）
void pop(stack* s)  // 删除头节点
{
	// 必须保证栈非空，否则结果不可预知
	node* p = s->top->next;  
	free(s->top);  
	s->top = p;
	s->len--;
}



// 访问栈顶元素（就是访问头节点的数据域，时间复杂度为 O(1)，空间复杂度为 O(1)）
elem_type* top(stack* s)
{
	return &(s->top->data);
}



int main()
{
	stack* s1, *s2;

	s1 = create();

	push(s1, 5);
	push(s1, 3);
	push(s1, 4);
	pop(s1);
	pop(s1);
	push(s1, 1);
	push(s1, 7);
	pop(s1);
	push(s1, 6);
	push(s1, 2);

	printf("栈 s1 的长度：%d\n", size(s1));  // 4

	// 出栈
	while(!empty(s1))
	{
		// 2 6 1 5
		printf("%d\n", *top(s1));
		
		pop(s1);
	}

	destroy(s1);

	return 0;
}

