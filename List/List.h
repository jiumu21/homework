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
        Object data; /**<! �ڵ��ڴ�ŵ�����. */
        Node *prev;  /**<! ָ��ǰһ���ڵ��ָ��. */
        Node *next;  /**<! ָ���һ���ڵ��ָ��. */
        
        Node(const Object &d = Object{}, Node *p = nullptr,
             Node *n = nullptr)
            : data{d}, prev{p}, next{n} {}

        /**
         *�ƶ����캯��. Ψһ�������ǽڵ�������һ����ֵ����. ����� std::move �ķ�ʽ����.
        
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
         * @brief ��������ǰ�����������. ���ڽ�������ָ����һ���ڵ�.
         */
        const_iterator &operator++()
        {
            current = current->next;
            return *this;
        }
        /**
         * @brief �������ĺ������������. ���ڽ�������ָ����һ���ڵ�.
         */
        const_iterator operator++(int)
        {
            const_iterator old = *this;
            ++(*this);
            return old;
        }
        //ǰ���Լ�����������ڽ�������ָ����һ���ڵ� 
        const_iterator &operator--()
        {
            current = current->prev;
            return *this;
        }
         //�����Լ�����������ڽ�������ָ����һ���ڵ� 
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
            /// ����ֱ�ӵ��� == ���㣬����һ�ε��ã�����ȷ��һ����.
            return !(*this == rhs);
        }

    protected:
        /// �ڼ̳��У�protected ���εĳ�Ա�����ͳ�Ա���������Ա�������ʣ������ܱ��ⲿ����.
        /// �����ʵ����Ӧ�ÿ������ڲ��ĺ�˽�е�.

        Node *current; /**<! ��ǰ�ڵ��ָ��. */

        Object &retrieve() const
        {
            return current->data;
        }
        
        const_iterator(Node *p) : current{p}
        {
        }

        friend class List<Object>; /**<! ʹ List ����Է��ʵ���������˽�г�Ա�� protected ��Ա. */

        /// ע�⵽ const_iterator ��û���ṩ������������Ϊ������ҪҲ��Ӧ���ͷ��ڴ�.
    };

    class iterator : public const_iterator
    {
    public:
        /**
         * @brief Ĭ�Ϲ��캯��. ���ڳ�ʼ��������. Ϊ�����ﲻ��Ҫ��ʼ�� current �أ�
         * ��Ϊ���̳��� const_iterator���� const_iterator �Ѿ���ʼ���� current Ϊ nullptr.
         * ����Ĺ��캯������ø���Ĺ��캯�����������ﲻ��Ҫ�ٳ�ʼ�� current ��.
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

        friend class List<Object>;  /**<! ͬ��ʹ List ����Է��ʵ���������˽�г�Ա�� protected ��Ա. */
    };

public:
	//Ĭ�Ϲ��캯�� 
    List() { init( ); }
    //��ʼ���б��캯�� 
    List(std::initializer_list<Object> il) : List()
    {
        for (const auto & x : il)
            push_back(x);
    }
    //�������캯�� 
    List(const List &rhs)
    {
        init( );
        for (auto & x : rhs)
            push_back(x);
    }
    //�������� 
    ~List()
    {
        clear( );
        delete head;
        delete tail;
    }
   //��ֵ��������غ��� 
    List &operator=(List copy)
    {
    //    std::swap( *this, copy );
    /// ����ֱ�� swap ���������Ǵ���ģ���Ϊ List ��δ���� swap ����.
    /// ��������ֵ����ʱ, �ᵼ��һ����������������һ�����󱻸�ֵ.
        std::swap( theSize, copy.theSize );
        std::swap( head, copy.head );
        std::swap( tail, copy.tail );
        return *this;
    }

    /**
     * @brief �ƶ����캯��. ���ڽ�һ����ֵ���õ� List �������ƶ�����һ�� List ��.
     * 
     * @param rhs ������һ����ֵ����. ��˲������Ҳ����������ڵ����������Ҫ����ȱʡ.
     */
    List(List &&rhs) : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
    {
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }
   // ����һ����������ָ��List��һ��Ԫ�� 
    iterator begin()
    {
        return { head->next };
    }
   // ����һ��ֻ���ĵ�������ָ��List��һ��Ԫ�� 
    const_iterator begin() const
    {
        return { head->next };
    }
    // ����һ����������ָ��List���һ��Ԫ��֮�� 
    iterator end()
    {
        return { tail };
    }
    // ����һ��ֻ���ĵ�������ָ��List���һ��Ԫ��֮��
    const_iterator end() const
    {
        return { tail };
    }
    //���ڻ�ȡ��ǰList�����д洢��Ԫ�ظ��� 
    int size() const
    {
        return theSize;
    }
    //�ж��б��Ƿ�Ϊ�� 
    bool empty() const
    {
        return size() == 0;
    }
    //���list�е����� 
    void clear()
    {
        while (!empty())
            pop_front();
    }
    //���ص�һ�����ݽڵ������ 
    Object &front()
    {
        return *begin();
    }
    //ֻ���ĵ�һ�����ݽڵ������ 
    const Object &front() const
    {
        return *begin();
    }
    //�������һ�����ݽڵ������ 
    Object &back()
    {
        return *--end();
    }
    //ֻ�������һ�����ݽڵ������ 
    const Object &back() const
    {
        return *--end();
    }
    //��һ����ֵ���ݽڵ���뵽list��ͷ�� 
    void push_front(const Object &x)
    {
        insert(begin(), x);
    }
     //��һ����ֵ���ݽڵ���뵽list��ͷ��
    void push_front(Object &&x)
    {
        insert(begin(), std::move(x));
    }
    //��һ����ֵ���ݽڵ���뵽list��β��
    void push_back(const Object &x)
    {
        insert(end(), x);
    }
     //��һ����ֵ���ݽڵ���뵽list��β�� 
    void push_back(Object &&x)
    {
        insert(end(), std::move(x));
    }
    //ɾ��list��һ�����ݽڵ� 
    void pop_front()
    {
        erase(begin());
    }
    //ɾ��list���һ�����ݽڵ� 
    void pop_back()
    {
        erase(--end());
    }
    //����һ����ֵ���ݽڵ㵽ָ��λ�� 
    iterator insert(iterator itr, const Object &x)
    {
        Node *p = itr.current;
        theSize++;
        return { p->prev = p->prev->next = new Node{ x, p->prev, p } };
    }
    //����һ����ֵ���ݽڵ㵽ָ��λ�� 
    iterator insert(iterator itr, Object &&x)
    {
        Node *p = itr.current;
        theSize++;
        return { p->prev = p->prev->next = new Node{ std::move( x ), p->prev, p } };
    }
    //ɾ��ָ��λ�õ����ݽڵ� 
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
    //ɾ��ָ����Χ�����ݽڵ� 
    iterator erase(iterator from, iterator to)
    { 
        for( iterator itr = from; itr != to; )
            itr = erase( itr );
        return to;
    }
   //��ӡ�б� 
   void printList() const
    {
    for (const auto &item : *this)
        {
            std::cout << item << " ";
        }
    std::cout << std::endl;
    }

private:
    int theSize;    /**<! ���ݽڵ�����. */
    Node *head;     /**<! ͷָ��. */
    Node *tail;     /**<! βָ��. */
   
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
   
