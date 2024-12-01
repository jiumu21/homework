/**
 * @file test.cpp
 * @author zjm 
 * @date 2024-11-30
 * 
 */
#include"HeapSort.h"
#include<random>
#include<chrono>

//check函数：用于检测是否是升序，升序返回true，否则返回false
template<typename Comparable>
bool check(const std::vector<Comparable>&a)
{
	for(int i=1;i<a.size();++i)
	if(a[i]<a[i-1]) return false;
	return true;
}

//构建含有1000000个元素的随机序列
std::vector<int> Random() 
{
    std::vector<int> sequence;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis1(0,2147483647);
    for (int i = 0; i <1000000; ++i) {
        sequence.push_back(dis1(gen));
    }
    return sequence;
}

//构建含有1000000个元素的有序序列
std::vector<int>Ordered()
{
    std::vector<int> sequence(1000000);
    int i=1;
    for(int &x:sequence)
     {
     	x=i;
     	++i;
     }
    return sequence;
 } 
 //构建含有1000000个元素的逆序序列
std::vector<int>ReverseOrdered()
{
    std::vector<int> sequence(1000000);
    int i=1000000;
    for(int &x:sequence)
     {
     	x=i;
     	--i;
	 }
    return sequence;
} 
//构建含有1000000个元素（元素中有重复）的序列
std::vector<int> Repeated() 
{
 std::vector<int> sequence;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis2(0,1000);
    for (int i = 0; i <1000000; ++i) {
        sequence.push_back(dis2(gen));
    }
    return sequence;
}
int main()
{
	std::vector<std::string>type={"随机序列","有序序列","逆序序列","重复序列"};
    //进行不同类型序列的测试
	for(const auto &x:type)
	{
	  std::vector<int>sequence;
	  if(x=="随机序列")
	{
		sequence=Random();
	}else if(x=="有序序列"){
		sequence=Ordered();
	}else if(x=="逆序序列"){
		sequence=ReverseOrdered();
	} else{
	    sequence=Repeated();	
	}
	//复制初始序列，该拷贝序列用来检测sort_heap排序
	std::vector<int>CopySequence=sequence;
	
	//开始第一次计时
	auto start = std::chrono::high_resolution_clock::now();
	//排序
	Heapsort(sequence);
	//第一次计时结束
	auto end = std::chrono::high_resolution_clock::now();

	auto my_duration=std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	//输出排序用时
	std::cout << x <<"通过HeapSort排序用时 : "<<my_duration.count()<< "ms"<<" ";
	//检测排序是否正确
	if(check(sequence))          
	    std::cout <<"排序正确"<<std::endl;
	 else
	    std::cout <<"排序错误"<<std::endl;
	//开始第二次计时
    auto start2 = std::chrono::high_resolution_clock::now();
	if(!std::is_heap(CopySequence.begin(),CopySequence.end()))
	    std::make_heap(CopySequence.begin(),CopySequence.end());//检测初始拷贝序列是否是max堆，如果不是，使其转化成max堆
	std::sort_heap(CopySequence.begin(),CopySequence.end());
	//第二次计时结束
	auto end2 = std::chrono::high_resolution_clock::now(); 
	auto std_duration=std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
	//输出排序用时
	std::cout << x <<"通过sort_heap排序用时 : "<<std_duration.count()<<"ms"<<" ";
	//检测排序是否正确
	if(check(CopySequence)) 
	    std::cout <<"排序正确"<<std::endl;
	 else
	    std::cout <<"排序错误"<<std::endl;

	 std::cout<<std::endl;
}
	return 0;
 } 
