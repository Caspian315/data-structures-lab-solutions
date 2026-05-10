# Caspian315的算法学习笔记



## 双链表基本原理



双链表及其创建函数的实现

```cpp
class DoublyListNode {
public:
    int val;
    DoublyListNode *next, *prev;
    DoublyListNode(int x) : val(x), next(NULL), prev(NULL) {}
};

DoublyListNode* createDoublyLinkedList(const vector<int>& arr) {
    if (arr.empty()) {
        return NULL;
    }
    DoublyListNode* head = new DoublyListNode(arr[0]);
    DoublyListNode* cur = head;
    // for 循环迭代创建双链表
    for (int i = 1; i < arr.size(); i++) {
        DoublyListNode* newNode = new DoublyListNode(arr[i]);
        cur->next = newNode;
        newNode->prev = cur;
        cur = cur->next;
    }
    return head;
}

```



接下来实现双链表的四大基本功能---增删改查

### 查/改

从头结点或尾节点开始，根据需要向前或向后遍历

```cpp
DoublyListNode* head = createDoublyLinkedList({1,2,3,4,5});
DoublyListNode* tail;

//从头向后
for(DoublyListNode* p = head; p != nullptr; p = p ->next){
//查或改 
    std::cout <<p -> val <<std::endl;
    tail = p;
}

//从尾向前
for(DoublyListNode* p = tail ; p != nullptr;p = p ->prev){
	std::cout<<p -> val <<std::end;
}
```

根据索引靠近头部还是尾部选择其中一种方式



### 增



头部插入一个元素

```cpp
DoublyListNode* head = createDoublyLinkedList({1,2,3,4,5});

DoublyListNode* newHead = new DoublyListNode(0);
newHead -> next = head;
head -> prev = newHead;
head = newHead;
// 现在链表变成了 0 -> 1 -> 2 -> 3 -> 4 -> 5
```



尾部插入一个元素

```cpp
DoublyListNode* head = createDoublyLinkedList({1, 2, 3, 4, 5});

DoublyListNode* tail = head;
//先走到链表最后一个节点
while(tail -> next != nullptr){
	tail = tail -> next;
}

DoublyListNode* newTail = DoublyListNode(6);
newTail -> prev = tail;
tail -> next = newTail;
tail = newTail;
// 现在链表变成了 1 -> 2 -> 3 -> 4 -> 5 -> 6
```



中间插入一个元素

```cpp
DoublyListNode* head = createDoublyLinkedList({1, 2, 3, 4, 5});

// 想要把元素 66 插入到索引 3（第 4 个节点）
// 需要操作索引 2（第 3 个节点）的指针

DoublyListNode* p = head;
for(int i = 0;i < 2; ++i){
p = p -> next;
}
// 组装新节点// 插入新节点
DoublyListNode* newNode = DoublyListNode(66);
newNode -> prev = p;
newNode -> next = p -> next;
// 插入新节点
p -> next ->prev = newNode;
p -> next = newNode;
// 现在链表变成了 1 -> 2 -> 3 -> 66 -> 4 -> 5
```



### 删

```cpp
// 创建一个双链表
DoublyListNode* head = createDoublyLinkedList({1, 2, 3, 4, 5});

//删除第4个节点
DoublyListNode* p = head;
for(int i = 0; i < 2 ;++ i){
p = p -> next;
}

DoublyListNode* toDelete = p -> next;

p -> next = toDelete -> next;
toDelete -> next -> prev = p;

//好习惯
toDelete -> next = nullptr;
toDelete -> prev = nullptr;

// 现在链表变成了 1 -> 2 -> 3 -> 5
```

删除头部

```cpp
DoublyListNode* head = createDoublyLinkedList({1, 2, 3, 4, 5});

DoublyListNode* toDelete = head;
head = head -> next;
head->prev = nullptr;

//好习惯
toDelete -> next = nullptr;
// 现在链表变成了 2 -> 3 -> 4 -> 5
```

删除尾部

```cpp
DoublyListNode* head = createDoublyLinkedList({1, 2, 3, 4, 5});

//先找到尾结点
DoublyListNode* p = head;
while(p -> next != nullptr){
	p = p -> next;
}

p -> prev -> next = nullptr;
p -> prev = nullptr;
// 现在链表变成了 1 -> 2 -> 3 -> 4
```



## 单/双链表代码实现



### 细节一

> 在力扣做题时，一般题目给我们传入的就是单链表的头指针。但是在实际开发中，用的都是双链表，而双链表一般会同时持有头尾节点的引用。
>
> 因为在软件开发中，在容器尾部添加元素是个非常高频的操作，双链表持有尾部节点的引用，就可以在 O(1)*O*(1) 的时间复杂度内完成尾部添加元素的操作。
>
> 对于单链表来说，持有尾部节点的引用也有优化效果。比如你要在单链表尾部添加元素，如果没有尾部节点的引用，你就需要遍历整个链表找到尾部节点，时间复杂度是 O(n)；如果有尾部节点的引用，就可以在 O(1) 的时间复杂度内完成尾部添加元素的操作。
>
> 然而，如果删除一次单链表的尾结点，那么之前尾结点的引用就失效了，还是需要遍历一遍链表找到尾结点。
>
> 进一步思考，删除单链表尾结点的时候，是不是也得遍历到倒数第二个节点（尾结点的前驱），才能通过指针操作把尾结点删掉？那么这个时候，不就可以顺便把尾结点的引用给更新了吗？



### 细节二 虚拟头尾节点

> 它的原理很简单，就是在创建双链表时就创建一个虚拟头节点和一个虚拟尾节点，无论双链表是否为空，这两个节点都存在。这样就不会出现空指针的问题，可以避免很多边界情况的处理。

举例来说，假设虚拟头尾节点分别是 `dummyHead` 和 `dummyTail`，那么一条空的双链表长这样：

```
dummyHead <-> dummyTail
```

如果你添加 `1,2,3` 几个元素，那么链表长这样：

```
dummyHead <-> 1 <-> 2 <-> 3 <-> dummyTail
```

以前要把在头部插入元素、在尾部插入元素和在中间插入元素几种情况分开讨论，现在有了头尾虚拟节点，无论链表是否为空，都只需要考虑在中间插入元素的情况就可以了，这样代码会简洁很多。

当然，虚拟头结点会多占用一点内存空间，但是比起给你解决的麻烦，这点空间消耗是划算的。

对于单链表，虚拟头结点有一定的简化作用，但虚拟尾节点没有太大作用。

> [!WARNING]
>
> 虚拟节点是内部实现数据结构的技巧，对外是不可见的。比如按照索引获取元素的 `get(index)` 方法，都是从真实节点开始计算索引，而不是从虚拟节点开始计算。



### 细节三 内存泄漏

在链表中，删除元素会不会也有内存泄露的问题呢？

尤其是这样的写法：

```java
// 假设单链表头结点 head = 1 -> 2 -> 3 -> 4 -> 5

// 删除单链表头结点
head = head.next;

// 此时 head = 2 -> 3 -> 4 -> 5
```

细心的读者可能认为这样写会有内存泄露的问题，因为原来的那个头结点 `1` 的 `next` 指针没有断开，依然指向着节点 `2`。

但实际上这样写是 OK 的，因为 Java 的垃圾回收的判断机制是看这个对象是否被别人引用，而并不会 care 这个对象是否还引用着别人。

那个节点 `1` 的 `next` 指针确实还指向着节点 `2`，但是并没有别的指针引用节点 `1` 了，所以节点 `1` 最终会被垃圾回收器回收释放。所以说这个场景和数组中删除元素的场景是不一样的，你可以再仔细思考一下。

不过呢，删除节点时，最好还是把被删除节点的指针都置为 null，这是个好习惯，不会有什么代价，还可能避免一些潜在的问题。所以在下面的实现中，无论是否有必要，我都会把被删除节点上的指针置为 null。



## 双链表代码实现

```cpp
#include<iostream>
#include<stdexcept>

template<typename E>
class MyLinkedList {
//虚拟头尾节点
    struct Node {
        E val;
        Node* prev;
        Node* next;

        Node(E value) : val(value), next(nullptr), prev(nullptr){}
    };

    Node* head;
    Node* tail;
    int size;

public:
    MyLinkedList() {
        head = new Node(E());
        tail = new Node(E());
        head->next = tail;
        tail->prev = head;
        size = 0;
    }

    ~MylinkedList() {

    }

    //增
    void addLast(E e) {
        Node* x = new Node(e);
        Node* temp = tail->prev;

        temp->next = x;
        x->prev = temp;

        x->next = tail;
        tail->prev = x;

        size++;
    }

    void addFirst(E e) {
        Node* x = new Node(e);
        Node* temp = head->next;
        temp->prev = x;
        x->next = temp;

        head->next = x;
        x->prev = head;

        size++;
    }
    void add(int index, E element) {
        checkPositionIndex(index);
        if (index == size) {
            addLast(element);
            return;
        }

        Node* p = getNode(index);
        Node* temp = p->prev;

        Node* x = new Node(element);
        p->prev = x;
        temp->next = x;
        
        x->prev = temp;
        x->next = p;

        size++;
    }

    //删
    E removeFirst(){
        if (size < 1) {
            throw std::out_of_range("No element to remove!");
        }
        Node* x = head->next;
        Node* temp = x->next;

        head->next = temp;
        temp->prev = head;

        E val = x->val;
        delete x;

        size--;
        return val;
    }

    E removeLast() {
        if (size < 1) {
            throw std::out_of_range("No element to remove!");
        }
        Node* x = tail->prev;
        Node* temp = x->prev;

        tail->prev = temp;
        temp->next = tail;

        E val = x->val;
        x->prev = nullptr;
        x->next = nullptr;

        size--;
        return val;
    }

    E remove(int index) {
        checkElementIndex(index);

        Node* x = getNode(index);
        Node* prev = x->prev;
        Node* next = x->next;

        prev->next = next;
        next->prev = prev;

        E val = x->val;
        x->prev = nullptr;
        x->next = nullptr;
        delete x;

        size--;
        return val;
    }

    //查
    E get(int index) {
        checkElementindex(index);
        Node* p = getNode(index);

        return p->val;
    }

    E getFirst() {
        if (isEmpty()) {
            throw std::out_of_range("No element in the list!");
        }

        return head->next->val;
    }

    E getLast() {
        if (isEmpty()) {
            throw std::out_of_range("No element in the list!");
        }

        return tail->prev->val;
    }

    //改
    E set(int index, E val) {
        checkElementIndex(index);
        Node* p = getNode(index);

        E oldVal = p->val;
        p->val = val;

        return oldVal;
    }

    int getSize() const{
        return size;
    }

    bool isEmpty() {
        return size == 0;
    }
    
    void display() {
        std::cout << "size = " << size << std::endl;
        for (Node* p = head->next; p != tail; p = p->next) {
            std::cout << p->val << " <-> ";
        }
        std::cout << "nullptr" << std::endl;
        std::cout << std::endl;
    }

private:
    Node* getNode* (int index) {
        checkElementIndex(index);
        //根据index判断是从head开始还是从tail开始
        if (index <= size / 2) {
            Node* p = head->next;
            for (int i = 0; i < index; ++i) {
                p = p->next;
                return p;
            }
        }
        else {
            Node* p = tail->prev;
            for (int i = 0; i < size - index - 1; ++i) {
                p = p->prev;
                return p;
            }
        }
    }

    bool isElementIndex(int index) const {
        return index >= 0 && index < size;
    }

    bool isPositionIndex(int index) const {
        return index >= 0 && index <= size;
    }

    // 检查 index 索引位置是否可以存在元素
    void checkElementIndex(int index) const {
        if (!isElementIndex(index))
            throw std::out_of_range("Index: " + std::to_string(index) + ", Size: " + std::to_string(size));
    }

    // 检查 index 索引位置是否可以添加元素
    void checkPositionIndex(int index) const {
        if (!isPositionIndex(index))
            throw std::out_of_range("Index: " + std::to_string(index) + ", Size: " + std::to_string(size));
    }

};

```



### 环形数组(双端队列deque)代码实现

核心在于**取模运算**

```c++
#include<iostream>
#include<stdexcept>
#include<vector>
#include<ostream>

template<typename T>
class CycleArray {
	std::vector<T> arr;
	int start;
	int end;
	int count;

	//自动扩缩容辅助函数
	void resize(int newSize) {
		std::vector<T> newArr(newSize);
		for (int i = 0; i < count; ++i) {
			newArr[i] = arr[(start + i) % arr.size()];
		}
		arr = std::move(newArr);
		//重置start和end指针
		start = 0;
		end = count;//左闭右开
	}

public:
	CycleArray() : CycleArray(1) {}//委托构造

	explicit CycleArray(int size)
		: arr(size), start(0), end(0), count(0){}
	//注意以下操作时间复杂度均为O(1)
	void addFirst(const T &val) {
		if (isFull()) {
			resize(arr.size() * 2);
		}
		start = (start - 1 + arr.size()) % arr.size();
		arr[start] = val;
		count++;
	}

	void removeFirst() {
		if (isEmpty()) {
			throw std::runtime_error("Array is empty!");
		}
		arr[start] = T();
		start = (start + 1) % arr.size();
		count--;
		if (count > 0 && count == arr.size() / 4) {
			resize(arr.size() / 2);
		}
	}

	void addLast(const T& val) {
		if(isFull()) {
			resize(arr.size() * 2);
		}
		arr[end] = val;
		end = (end + 1) % arr.size();
		count++;
	}

	void removeLast() {
		if (isEmpty()) {
			throw std::runtime_error("Array is empty!");
		}
		end = (end - 1 + arr.size()) % arr.size();
		arr[end] = T() :
			count--;
		if (count > 0 && count == arr.size() / 4) {
			resize(arr.size() / 2);
		}
	}

	T getFirst()const {
		if (isEmpty()) {
			throw std::runtime_error("Array is empty!");
		}
		return arr[start];
	}

	T getLast()const {
		if (isEmpty()) {
			throw std::runtime_error("Array is empty!");
		}
		return arr[(end - 1 + arr.size()) % arr.size()];
	}
	//几个工具函数
	bool isFull()const {
		return count == arr.size();
	}

	int size() const{
		return count;
	}

	bool isEmpty() const{
		return count == 0;
	}
};

```



## 跳表

目的：降低链表查询操作的时间复杂度

跳能使增删改查的时间复杂度降低到 **O(log⁡N)**

### 核心原理（空间换时间）

这是一个普通单链表：

```
index  0  1  2  3  4  5  6  7  8  9
node   a->b->c->d->e->f->g->h->i->j
```

这是一个跳表：

```
indexLevel   0-----------------------8-----10
indexLevel   0-----------4-----------8-----10
indexLevel   0-----2-----4-----6-----8-----10
indexLevel   0--1--2--3--4--5--6--7--8--9--10
nodeLevel    a->b->c->d->e->f->g->h->i->j->k
```

跳表相当于在原链表的基础上，增加了多层索引，每向上一层，索引节点的数量减少一半，索引的间隔变为 2 倍，所以索引的高度是 log⁡Nlog*N*，N*N* 代表链表中元素的个数。

此时，如果我们想查询索引为 7 的元素，可以从最高层索引开始一层一层地往下找：

首先最高层的第一个索引区间是 `[0, 8]`，可以确定索引 7 在这个区间内，所以从下一层的节点 0 开始搜索；

第二层从节点 0 开始，索引区间 `[0, 4]` 不包含索引 7，继续往右移动到节点 4，索引区间 `[4, 8]` 包含索引 7，所以从下一层的节点 4 开始搜索；

第三层从节点 4 开始，索引区间 `[4, 6]` 不包含索引 7，继续往右移动到节点 6，索引区间 `[6, 8]` 包含索引 7，所以从下一层的节点 6 开始搜索；

第四层从节点 6 开始，索引区间 `[6, 7]` 包含索引 7，最终找到目标节点 `h`。

这个搜索过程中，会经过 log⁡N 层索引，在每层索引中移动的次数不会超过 **2** 次（因为上层索引区间在下一层被分为两半），所以跳表的查询时间复杂度是 O(log⁡N)。



## 位图BitMap

位图（BitMap）是一种非常节省**空间**的数据结构，它用一个比特位（bit）的 0 和 1 来标记某个元素是否存在。



在做算法题时，我们经常会用到类似bool visited[]这样的布尔数组，来记录数组中哪些元素已经被访问过。

```cpp
int nums[] = {...};
bool visited[] = new bool[nums.size()];
visited[10] = true;
```
