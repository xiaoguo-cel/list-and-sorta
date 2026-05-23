#include <stdio.h>
#include <stdlib.h>


typedef int elem_type;  // 声明数据元素(Data Element)类型


// 声明节点类型
typedef struct node
{
	elem_type data;             // 数据域
	struct node* next;          // 指针域
} node;


// 声明链表信息结构体
typedef struct 
{
	node* head;   // 头节点指针，核心属性
	node* tail;   // 尾节点指针
	int   len;    // 长度（数据元素的个数）

} list;


// 初始化链表（有头链表）
void init(list* l)
{
	// 创建一个新节点，该节点将成为新链表的头节点
	node* n = malloc(sizeof(node));

	if(n == NULL)
	{
		perror("malloc fail");
		exit(EXIT_FAILURE);
	}

	n->next = NULL;  // 此时头节点也是尾节点

	l->head = l->tail = n;
	l->len = 0;
}


// 销毁链表
void destroy(list* l)  // 参数 l 表示要销毁的目标链表
{
	// 遍历链表所有节点，将它们都释放掉
	node* p = NULL;

	while(l->head != NULL)
	{
		p = l->head->next;
		free(l->head);
		l->head = p;
	}

	l->tail = NULL;
	l->len  = 0;
}


// 清空（删除所有存放数据元素的节点，对于有头链表，就是释放除头节点之外的其他所有节点）
void clear(list* l)
{
	// 从第 1 个节点开始遍历链表所有节点，将它们都释放掉
	node* p = l->head->next, *q = NULL;

	while(p != NULL)
	{
		q = p->next;
		free(p);
		p = q;
	}

	// 更新链表属性
	l->head->next = NULL;
	l->tail = l->head;
	l->len  = 0;	
}


// 尾插（时间复杂度为 O(1)，空间复杂度为 O(1)）
void push_back(list* l, elem_type data)
{
	// 创建一个新节点
	node* n = malloc(sizeof(node));

	if(n == NULL)
	{
		perror("malloc fail");
	}

	n->data = data;
	n->next = NULL;  // 该节点将成为链表的尾节点

	// 让新节点成为原来尾节点的后继
	l->tail->next = n;
	
	// 更新链表属性
	l->tail = n;
	l->len++;
}


// 头插（时间复杂度为 O(1)，空间复杂度为 O(1)）
void push_front(list* l, elem_type data)
{
	// 创建一个新节点
	node* n = malloc(sizeof(node));

	if(n == NULL)
	{
		perror("malloc fail");
	}

	n->data = data;
	n->next = l->head->next;  // 该节点将成为链表的第 1 个节点，原来的第 1 个节点将成为该节点的后继

	// 让新节点成为链表头节点的后继
	l->head->next = n;
	
	// 更新链表属性
	if(l->len == 0) l->tail = n;  // 如果链表为空就更新尾节点指针
	l->len++;
}


// 中插（在某个指定节点之后插入新节点）
void insert(list* l, node* pos, elem_type data)  // pos 参数表示插入位置（在该指针指向的节点之后插入）
{
	// 创建一个新节点
	node* n = malloc(sizeof(node));

	if(n == NULL)
	{
		perror("malloc fail");
	}

	n->data = data;

	// 将新节点插入到 pos 指向的节点之后
	n->next = pos->next;
	pos->next = n;

	// 更新链表属性
	if(n->next == NULL) l->tail = n;  // 如果是尾插就更新 tail 属性
	l->len++;	
}


// 删除（根据节点指针删除，时间复杂度为 O(1)，空间复杂度为 O(1)）
void erase(list* l, node* pos)  // 删除 pos 指向节点的后继节点
{
	if(pos->next == NULL) return;

	// 先接再杀
	node* p = pos->next;  // 先记录要杀的节点
	pos->next = p->next;  // 前后接上
	free(p);              // 杀掉目标节点

	/*
	// 先杀再接
	node* p = pos->next->next;
	free(pos->next);
	pos->next = p;
	*/

	// 更新链表属性
	if(pos->next == NULL) l->tail = pos;  // 如果删除的是尾节点
	l->len--;
}


// 删除（根据节点的数据域删除）


// 遍历链表，打印链表中的所有数据元素
void show_all(list* l)
{
	node* p = l->head->next;

	while(p != NULL)
	{
		printf("%d ", p->data);
		
		p = p->next;
	}

	printf("\n");
}


// 求长度（时间复杂度为 O(1)，空间复杂度为 O(1)）
int size(list* l)
{
	return l->len;
}


// 判空
int empty(list* l)
{
	return !(l->len);
}


typedef struct
{
	int year;
	int month;
	int day;

} date;


/*
struct student
{
	int sno;
	float sight;
	char* name;
	date* birth;
};
*/


int main()
{
	/*
	student s1;
	s1.sno = 100;
	s1.sight = 4.5;
	s1.name = "zhangsan";
	s1.birth = malloc(sizeof(date));
	s1.birth->year = 2005;

	student* s2 = &s1;
	s2->sno = 101;
	s2->sight = 4.6;
	s2->name = "lisi";
	s2->birth->year = 2006;
	*/

	list l1, l2;

	init(&l1);
	init(&l2);	

	printf("链表 l1 的长度：%d\n", size(&l1));  // 0
	printf("链表 l2 的长度：%d\n", size(&l2));  // 0

	push_front(&l1, 8);
	push_back(&l1, 5);
	push_back(&l1, 3);
	push_front(&l1, 7);
	push_front(&l1, 6);
	push_back(&l1, 4);
	insert(&l1, l1.head, 9);   // 头插
	insert(&l1, l1.tail, 13);  // 尾插
	insert(&l1, l1.head->next->next, 15);
	//insert(&l1, *(*(l1.head).next).next, 15);
	push_back(&l1, 3);

	push_back(&l2, 3);
	push_back(&l2, 4);
	push_front(&l2, 5);
	insert(&l2, l2.head, 1);

	printf("链表 l1 的数据：");
	show_all(&l1);  // 9 6 15 7 8 5 3 4 13 3

	printf("链表 l2 的数据：");
	show_all(&l2);  // 1 5 3 4

	printf("链表 l1 的长度：%d\n", size(&l1));  // 10
	printf("链表 l2 的长度：%d\n", size(&l2));  // 4

	destroy(&l1);
	destroy(&l2);

	return 0;
}
