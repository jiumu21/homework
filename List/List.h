#ifndef __LIST_MARK__
#define __LIST_MARK__

#include <utility>
#include <initializer_list>
#include<iostream>
template <typename Object>
class List
{
private:
    
    struct Node
    {
        Object data; /**<! 节点内存放的数据. */
        Node *prev;  /**<! 指向前一个节点的指针. */
        Node *next;  /**<! 指向后一个节点的指针. */
        
        Node(const Object &d = Object{}, Node *p = nullptr,
             Node *n = nullptr)
            : data{d}, prev{p}, next{n} {}

        /**
         *移动构造函数. 唯一的区别是节点数据是一个右值引用. 因此以 std::move 的方式传递.
        
         */
        Node(Object &&d, Node *p = nullptr, Node *n = nullptr)
            : data{std::move(d)}, prev{p}, next{n} {}
    };

public:
    class const_iterator
    {
    public:
        const_iterator() : current{nullptr}
        {
        }
        const Object &operator*() const
        {
            return retrieve();
        }
        /**
         * @brief 迭代器的前置自增运算符. 用于将迭代器指向下一个节点.
         */
        const_iterator &operator++()
        {
            current = current->next;
            return *this;
        }
        /**
         * @brief 迭代器的后置自增运算符. 用于将迭代器指向下一个节点.
         */
        const_iterator operator++(int)
        {
            const_iterator old = *this;
            ++(*this);
            return old;
        }
        //前置自减运算符，用于将迭代器指向上一个节点 
        const_iterator &operator--()
        {
            current = current->prev;
            return *this;
        }
         //后置自减运算符，用于将迭代器指向上一个节点 
        const_iterator operator--(int)
        {
            const_iterator old = *this;
            --(*this);
            return old;
        }
        
        bool operator==(const const_iterator &rhs) const
        {
            return current == rhs.current;
        }
        
        bool operator!=(const const_iterator &rhs) const
        {
            /// 这里直接调用 == 运算，多了一次调用，但能确保一致性.
            return !(*this == rhs);
        }

    protected:
        /// 在继承中，protected 修饰的成员变量和成员函数，可以被子类访问，但不能被外部访问.
        /// 因此它实际上应该看作是内部的和私有的.

        Node *current; /**<! 当前节点的指针. */

        Object &retrieve() const
        {
            return current->data;
        }
        
        const_iterator(Node *p) : current{p}
        {
        }

        friend class List<Object>; /**<! 使 List 类可以访问到迭代器的私有成员和 protected 成员. */

        /// 注意到 const_iterator 并没有提供析构函数，因为它不需要也不应该释放内存.
    };

    class iterator : public const_iterator
    {
    public:
        /**
         * @brief 默认构造函数. 用于初始化迭代器. 为何这里不需要初始化 current 呢？
         * 因为它继承自 const_iterator，而 const_iterator 已经初始化了 current 为 nullptr.
         * 子类的构造函数会调用父类的构造函数，所以这里不需要再初始化 current 了.
         *
         */
        iterator()
        {
        }
        Object &operator*()
        {
            return const_iterator::retrieve();
        }

        const Object &operator*() const
        {
            return const_iterator::operator*();
        }

        iterator &operator++()
        {
            this->current = this->current->next;
            return *this;
        }

        iterator operator++(int)
        {
            iterator old = *this;
            ++(*this);
            return old;
        }
         iterator &operator--()
        {
            this->current = this->current->prev;
            return *this;
        }
        iterator operator--(int)
        {
            iterator old = *this;
           --(*this);
            return old;
        }
    protected:
        iterator(Node *p) : const_iterator{p}
        {
        }

        friend class List<Object>;  /**<! 同样使 List 类可以访问到迭代器的私有成员和 protected 成员. */
    };

public:
	//默认构造函数 
    List() { init( ); }
    //初始化列表构造函数 
    List(std::initializer_list<Object> il) : List()
    {
        for (const auto & x : il)
            push_back(x);
    }
    //拷贝构造函数 
    List(const List &rhs)
    {
        init( );
        for (auto & x : rhs)
            push_back(x);
    }
    //析构函数 
    ~List()
    {
        clear( );
        delete head;
        delete tail;
    }
   //赋值运算符重载函数 
    List &operator=(List copy)
    {
    //    std::swap( *this, copy );
    /// 这里直接 swap 两个对象是错误的，因为 List 并未定义 swap 操作.
    /// 当发生右值引用时, 会导致一个对象被析构，而另一个对象被赋值.
        std::swap( theSize, copy.theSize );
        std::swap( head, copy.head );
        std::swap( tail, copy.tail );
        return *this;
    }

    /**
     * @brief 移动构造函数. 用于将一个右值引用的 List 的数据移动到另一个 List 中.
     * 
     * @param rhs 必须是一个右值引用. 因此不存在右操作数不存在的情况，不需要考虑缺省.
     */
    List(List &&rhs) : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
    {
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }
   // 返回一个迭代器，指向List第一个元素 
    iterator begin()
    {
        return { head->next };
    }
   // 返回一个只读的迭代器，指向List第一个元素 
    const_iterator begin() const
    {
        return { head->next };
    }
    // 返回一个迭代器，指向List最后一个元素之后 
    iterator end()
    {
        return { tail };
    }
    // 返回一个只读的迭代器，指向List最后一个元素之后
    const_iterator end() const
    {
        return { tail };
    }
    //用于获取当前List对象中存储的元素个数 
    int size() const
    {
        return theSize;
    }
    //判断列表是否为空 
    bool empty() const
    {
        return size() == 0;
    }
    //清除list中的数据 
    void clear()
    {
        while (!empty())
            pop_front();
    }
    //返回第一节数据节点的数据 
    Object &front()
    {
        return *begin();
    }
    //只读的第一节数据节点的数据 
    const Object &front() const
    {
        return *begin();
    }
    //返回最后一个数据节点的数据 
    Object &back()
    {
        return *--end();
    }
    //只读的最后一个数据节点的数据 
    const Object &back() const
    {
        return *--end();
    }
    //将一个左值数据节点插入到list的头部 
    void push_front(const Object &x)
    {
        insert(begin(), x);
    }
     //将一个右值数据节点插入到list的头部
    void push_front(Object &&x)
    {
        insert(begin(), std::move(x));
    }
    //将一个左值数据节点插入到list的尾部
    void push_back(const Object &x)
    {
        insert(end(), x);
    }
     //将一个右值数据节点插入到list的尾部 
    void push_back(Object &&x)
    {
        insert(end(), std::move(x));
    }
    //删除list第一个数据节点 
    void pop_front()
    {
        erase(begin());
    }
    //删除list最后一个数据节点 
    void pop_back()
    {
        erase(--end());
    }
    //插入一个左值数据节点到指定位置 
    iterator insert(iterator itr, const Object &x)
    {
        Node *p = itr.current;
        theSize++;
        return { p->prev = p->prev->next = new Node{ x, p->prev, p } };
    }
    //插入一个右值数据节点到指定位置 
    iterator insert(iterator itr, Object &&x)
    {
        Node *p = itr.current;
        theSize++;
        return { p->prev = p->prev->next = new Node{ std::move( x ), p->prev, p } };
    }
    //删除指定位置的数据节点 
    iterator erase(iterator itr)
    {
        Node *p = itr.current;
        iterator retVal{ p->next };
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        theSize--;
        return retVal;
    }
    //删除指定范围的数据节点 
    iterator erase(iterator from, iterator to)
    { 
        for( iterator itr = from; itr != to; )
            itr = erase( itr );
        return to;
    }
   //打印列表 
   void printList() const
    {
    for (const auto &item : *this)
        {
            std::cout << item << " ";
        }
    std::cout << std::endl;
    }

private:
    int theSize;    /**<! 数据节点总数. */
    Node *head;     /**<! 头指针. */
    Node *tail;     /**<! 尾指针. */
   
    void init()
    {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
};
#else
// DO NOTHING.
#endif
   
