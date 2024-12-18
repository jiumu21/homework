#include<iostream>
#include<stack>
#include<vector>
#include<string>

//给定不同运算符的优先级
int priority( char ch)
{
int result;
	switch(ch)
	{  case '+':case '-':
	   result=1;break;
	   case '*':case '/':
	   result=2;break;
	   case '(':
	   result=0;break;
    }
   return result;
}

//判定字符a是否代表数字
bool check_is_data(const char &a)
{
	if(a>='0'&&a<='9') return true;
	return false;
}
//判定字符a是否代表运算符
bool check_is_mark( char a)
{
	if(a=='+'||a=='-'||a=='*'||a=='/')  return true ;
	return false; 
}
//判定字符a是否合法
bool check_is_( char a)
{
	if(check_is_data(a)) return true;
	if(check_is_mark(a)) return true;
	if(a=='('||a==')'||a=='.') return true;
	return false;
}
//返回a与b四则运算的值
float cal(float a,float b,char ch)
{
float value;
  if(ch=='+') value=b+a;
  if(ch=='-') value=b-a;
  if(ch=='*') value=a*b;
  if(ch=='/') value=b*1.0/a;
return value;
}
//判断中缀表达式是否正确，同时将其转化为后缀表达式
bool check_and_convert(std::string &s,std::stack<char>&pre,std::vector<char>&post)
{
   int length =s.length();
   int point,data,mark;
   mark=point=data=0; 
   //如果是空字符串，返回0
   if(length==0) return false ;
   
   //第一个字符的可能情况
   if(s[0]=='(')
   {
   	pre.push(s[0]);  
   } else if(check_is_data(s[0]))
   {
   	data=1;     
   	post.push_back(s[0]);
   }  else return false;
   
   for(int i=1;i<length;i++){
   
   if(!check_is_(s[i])) return false;
   
   if(s[i]=='(')
        if(check_is_data(s[i-1])||s[i-1]==')') return false; //排除（之前与数字直接连接情况
            else pre.push(s[i]);
            
   if(s[i]==')') {
   if(i<length-1)   //如果 ） 不在末端
        if(check_is_data(s[i+1])) 
		    return false;
   if(pre.empty())  return false;   // ')'不可能第一个出现 
   if(pre.top()=='(')     
        if(s[i-1]=='(')
		    return false; 
   while(pre.top()!='('){
        post.push_back(pre.top());
        pre.pop();
        if(pre.empty()) break;
    }
   if(pre.empty()) return false;
   pre.pop();
   }
   //当检测的字符为 . 时
   if(s[i]=='.')
   {
   	if (point ==1||i==length-1) return false;   //该字符不能出现在末端，以及一个数字至多有一个小数点
     	else if(!check_is_data(s[i+1])) return false;
   	        else point=1;  //此处的point是来表示数字中已经存在小数点
   	post.push_back(s[i]);
   }
   
    if(check_is_mark(s[i])){
   	    if(!mark) mark=1;  //此处的mark用来标识整个输入字符串有无运算符
   	    if(!data) {
   		    return false;
	    }
   	if(i==length-1) return false; //运算符不能出现在末端
   	if(!check_is_data(s[i-1])&&s[i-1]!=')') return false;
	if(!check_is_data(s[i+1])&&s[i+1]!='(') return false;
	if (s[i]=='/'){   //排除除数为0情况
	  if(s[i+1]=='0'){
			if(i==length-2) return false;
			    else if (s[i+2]!='.') return false ;
		int _num=0;
		for(int _temp=i+3;_temp<length;_temp++){
		    if(check_is_data(s[_temp])) if(s[_temp]!='0') 
		    {
			_num=1;break;
		    }
		if(check_is_mark(s[_temp])) break;	
		}
		if(!_num) return false; 
	  }
	}
	point=data=0;
	post.push_back(' ');
        //比较优先级
	while(!pre.empty()){
        if (priority(pre.top())>=priority(s[i])){
	post.push_back(pre.top());
		pre.pop();
	} else break;
	}
	pre.push(s[i]);
}
  if(check_is_data(s[i])){ post.push_back(s[i]);data=1;}
}
    //如果表达式没有运算符，返回0
    if(mark==0) return false;
    //若符号匹配正确，最后的栈中无括号出现
    while(!pre.empty())
    {
    	if(pre.top()!='('){
    	post.push_back(pre.top());
    	pre.pop();
		}else break; 
	}
	if(!pre.empty()) return false;
	return true; 
}

//计算后缀表达式的值
float calculate(std::vector<char>&post)
  {
  std::stack<float>sta;  //建立一个栈用来存放数据
  float value=0;  //初始值为0
  float n=10;
  float m=1;
  //m与n的变化用来标识小数点之前与之后
  
  int data=0;
  float temp1,temp2,result;
  for(auto &x:post){
  if(x=='.')  n=1;  
  if(check_is_data(x)) 
  { if(n==1) m=m*0.1;  //每向后一位，m就变为之前的十分之一
  value=value*n+(x-'0')*m;
    data=1;  
}
  if(x==' '||check_is_mark(x))    //遇见空格或是标识符，代表这一数据读取结束，将value的值压入栈中，同时data变为0 
   if(data)
  {
  	sta.push(value);
  	value=0;
  	n=10;
  	m=1;
  	data=0;
  }
  //遇见运算符，将栈弹出两次的数据进行运算
  if(check_is_mark(x)){
   temp1=sta.top();
   sta.pop();
   temp2=sta.top();
   sta.pop();
   result=cal(temp1,temp2,x);
   sta.push(result);
  }}
  return result;
}

