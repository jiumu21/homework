#include "List.h"
#include <iostream>
int main()
{
	List<int> a;//测试默认构造函数 
	std::cout<<"a是否为空（1代表空，0代表非空）:"<<a.empty()<<std::endl;

	List<int> b={1,2,3,4,5};	//测试初始化列表构造函数 
	std::cout<<"b is ";
	b.printList();
	 
	List<int> c=b;	         //测试拷贝构造函数
	std::cout<<"c is ";      
	c.printList();

	a=b;         //测试赋值运算符重载函数
	std::cout<<"a is ";
	a.printList();

	List<int>d(std::move(c)); 	//测试移动构造函数
	std::cout<<"d is ";
	d.printList();  
	std::cout<<"c是否为空（1代表空，0代表非空）:"<<c.empty()<<std::endl; //测试列表是否为空 

	c=std::move(d);   	//测试移动赋值运算符
	std::cout<<"c is ";
	c.printList();
	std::cout<<"d是否为空（1代表空，0代表非空）:"<<d.empty()<<std::endl;  
	
	for(int i=6;i<=15;i++)
	{
	   c.push_back(i); //测试右值push_back 
    } 
	c.push_back(c.back());//测试左值push_back  //测试back
	c.back()++;
	std::cout<<"c is ";
	c.printList();
	
	for(int i=0;i<=5;i++) 
	{
	  c.pop_back();     //测试pop_back 
	} 
	std::cout<<"c is ";
	c.printList();
	
	for(int i=0;i<=4;i++) 
	{
	  c.pop_front();         //测试pop_front 
	} 
	std::cout<<"c is ";
	c.printList();
   
    c.clear();  //清空列表 
    
    for(int i=10;i>0;i-=2)
     {
     	c.push_front(i); //测试右值push_front 
	 }
	std::cout<<"c is ";
	c.printList();
 
    c.push_front(c.front());  //测试左值push_front
	c.front()--;
    auto it=++c.begin();  //测试自增运算符 //测试begin 
	for(;it!=c.end();++it)  //测试end 
	{ 
	   c.insert(it,*it);  //测试insert左值 
	   (*it)++;
	}
	c.insert(c.begin(),0);  //测试insert右值 
	std::cout<<"c is ";
	c.printList();
	
	c.pop_back(); 
	for(it=--c.end();(*it)>5;--it);
	c.erase(c.begin(),it); 
	std::cout<<"c is ";
	c.printList();
	
	std::cout<<"c是否为空（1代表空，0代表非空）:"<<c.empty()<<std::endl;
	std::cout<<"size of c is "<<c.size()<<std::endl;//测试size 
    return 0;
}
