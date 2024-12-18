#include<iostream>
#include<stack>
#include<vector>
#include<string>

//������ͬ����������ȼ�
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

//�ж��ַ�a�Ƿ��������
bool check_is_data(const char &a)
{
	if(a>='0'&&a<='9') return true;
	return false;
}
//�ж��ַ�a�Ƿ���������
bool check_is_mark( char a)
{
	if(a=='+'||a=='-'||a=='*'||a=='/')  return true ;
	return false; 
}
//�ж��ַ�a�Ƿ�Ϸ�
bool check_is_( char a)
{
	if(check_is_data(a)) return true;
	if(check_is_mark(a)) return true;
	if(a=='('||a==')'||a=='.') return true;
	return false;
}
//����a��b���������ֵ
float cal(float a,float b,char ch)
{
float value;
  if(ch=='+') value=b+a;
  if(ch=='-') value=b-a;
  if(ch=='*') value=a*b;
  if(ch=='/') value=b*1.0/a;
return value;
}
//�ж���׺���ʽ�Ƿ���ȷ��ͬʱ����ת��Ϊ��׺���ʽ
bool check_and_convert(std::string &s,std::stack<char>&pre,std::vector<char>&post)
{
   int length =s.length();
   int point,data,mark;
   mark=point=data=0; 
   //����ǿ��ַ���������0
   if(length==0) return false ;
   
   //��һ���ַ��Ŀ������
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
        if(check_is_data(s[i-1])||s[i-1]==')') return false; //�ų���֮ǰ������ֱ���������
            else pre.push(s[i]);
            
   if(s[i]==')') {
   if(i<length-1)   //��� �� ����ĩ��
        if(check_is_data(s[i+1])) 
		    return false;
   if(pre.empty())  return false;   // ')'�����ܵ�һ������ 
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
   //�������ַ�Ϊ . ʱ
   if(s[i]=='.')
   {
   	if (point ==1||i==length-1) return false;   //���ַ����ܳ�����ĩ�ˣ��Լ�һ������������һ��С����
     	else if(!check_is_data(s[i+1])) return false;
   	        else point=1;  //�˴���point������ʾ�������Ѿ�����С����
   	post.push_back(s[i]);
   }
   
    if(check_is_mark(s[i])){
   	    if(!mark) mark=1;  //�˴���mark������ʶ���������ַ������������
   	    if(!data) {
   		    return false;
	    }
   	if(i==length-1) return false; //��������ܳ�����ĩ��
   	if(!check_is_data(s[i-1])&&s[i-1]!=')') return false;
	if(!check_is_data(s[i+1])&&s[i+1]!='(') return false;
	if (s[i]=='/'){   //�ų�����Ϊ0���
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
        //�Ƚ����ȼ�
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
    //������ʽû�������������0
    if(mark==0) return false;
    //������ƥ����ȷ������ջ�������ų���
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

//�����׺���ʽ��ֵ
float calculate(std::vector<char>&post)
  {
  std::stack<float>sta;  //����һ��ջ�����������
  float value=0;  //��ʼֵΪ0
  float n=10;
  float m=1;
  //m��n�ı仯������ʶС����֮ǰ��֮��
  
  int data=0;
  float temp1,temp2,result;
  for(auto &x:post){
  if(x=='.')  n=1;  
  if(check_is_data(x)) 
  { if(n==1) m=m*0.1;  //ÿ���һλ��m�ͱ�Ϊ֮ǰ��ʮ��֮һ
  value=value*n+(x-'0')*m;
    data=1;  
}
  if(x==' '||check_is_mark(x))    //�����ո���Ǳ�ʶ����������һ���ݶ�ȡ��������value��ֵѹ��ջ�У�ͬʱdata��Ϊ0 
   if(data)
  {
  	sta.push(value);
  	value=0;
  	n=10;
  	m=1;
  	data=0;
  }
  //�������������ջ�������ε����ݽ�������
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

