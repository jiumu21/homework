/**
 * @file HeapSort.h
 * @author zjm
 * @brief 
 * @version 0.1
 * @date 2024-11-30
 */
#include<iostream>
#include<vector>
#include<algorithm>


template<typename Comparable>
void Heapsort(std::vector<Comparable>&a)
{
  //将a转化成一个max堆,此时序列中最大的元素位于第一个位置
  std::make_heap(a.begin(),a.end()) ;
  
  for(int j=0;j<a.size();++j)
  {
     //在每一次循环中，将最大的元素移动至序列尾端，同时循环范围逐次缩小，实现有序排列
  	  std::pop_heap(a.begin(),a.end()-j);
     
  }
}

