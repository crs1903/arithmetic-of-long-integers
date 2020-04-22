#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
typedef struct
{
	uint64_t word[64];
}
uint4096;


const uint4096 ZERO = {{0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL}};
const uint4096 ONE  = {{0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,1UL}};

uint4096 get_int(const char * );
void printuint(uint4096 );
void printint(uint4096 );
void init(uint4096 * ,char *);
int compare(uint4096 ,uint4096 );
uint4096 lshift(uint4096 ,int );
uint4096 rshift(uint4096 ,int );
unsigned int bits(uint4096 );
uint4096 mp_sum(uint4096 ,uint4096 ,unsigned int );
uint4096 multi(uint4096 , uint4096 );
uint4096 mp_div(uint4096 , uint4096 ,uint4096 *);
uint4096 mod(uint4096 ,uint4096 );
uint4096 square_multiple(uint4096 ,uint4096 ,uint4096 );
uint4096 AND(uint4096 , uint4096 );
uint4096 OR(uint4096 ,uint4096 );
uint4096 NOT(uint4096 );
uint4096 GCD(uint4096 ,uint4096 );
uint4096 INV(uint4096 ,uint4096 );

int main()
{
	int i;
	uint4096 a,b,c,s,m,d,r,x,y,g,inv;
	int n;

	a = get_int("Enter the first integer in hex :\n");
	b = get_int("Enter the second integer in hex :\n");
	c= get_int("Enter the third integer in hex :\n");

	printf("\n\na\t: ");
	printint(a);
	printf("\n\nb\t: ");
	printint(b);
	printf("\n\nc\t: ");
	printint(c);
	printf("\n\nmult\t: ");
	m = multi(a,b);
	printint(m);
	printf("\n\nadd a b\t: ");
	s = mp_sum(a,b,0);
	printint(s);
	printf("\n\ndiv a b\t: ");
	d = mp_div(a,b,NULL);
	printint(d);
	printf("\n\nsubs a b\t: ");
	x = mp_sum(a,b,1);
	printint(x);
	printf("\n\nmod a b\t: ");
	r = mod(a,b);
	printint(r);
	printf("\n\ngcd a b\t: ");
	g = GCD(a,b);
	printint(g);
	printf("\n\n(a^b)%%c\t: ");
	y = square_multiple(a,b,c);
	printint(y);
	if(compare(GCD(a,b),ONE) == 0)
	{
		printf("\n\na^-1 b\t: ");
		inv = INV(a,b);
		printint(inv);
	}
	printf("\n\n");
}


uint4096 get_int(const char *s)
{
	char *str = (char*)malloc(1024);
	uint4096 a;
	if(s!=NULL)
		printf("%s",s);
	scanf("%1024s",str);
	init(&a,str);
	free(str);
	return a;
}
void printuint(uint4096 a)
{
	int i;
	int flag = 0;
	for(i=0;i<64;i++)
	{
		if(flag == 0 && a.word[i] == 0UL)
		{
			continue;
		}
		else if(flag == 0)
		{
			flag = 1;
			printf("%lx",a.word[i]);
		}
		else	
		printf("%.16lx",a.word[i]);
	}
	if(flag == 0)
		printf("%x",0);
}

void printint(uint4096 a)
{
	int i;
	if(a.word[0]>>63 == 1UL)
	{
		for(i=0;i<64;i++)
			a.word[i] = ~(a.word[i]);
		a = mp_sum(a,ONE,0);
		printf("-");
	}
	int flag = 0;
	for(i=0;i<64;i++)
	{
		if(flag == 0 && a.word[i] == 0UL)
		{
			continue;
		}
		else if(flag == 0)
		{
			flag = 1;
			printf("%lx",a.word[i]);
		}
		else	
		printf("%.16lx",a.word[i]);
	}
	if(flag == 0)
		printf("%x",0);
}

void init(uint4096 *n,char *str)
{
	int i,flag = 0;
	*n = ZERO;
	if(str!=NULL)	
	{
		if(str[0] == '-')
		{	
			flag = 1;
			str++;
		}
		int len = strlen(str),w,j,k;
		char ch;
		for(i=0,j=64,k=0;i<len;i++)
		{	
			ch = str[len-i-1];
			if(ch<='9' && ch>='0')
				ch-='0';
			else if(ch<='f' && ch>='a')
				ch-='a'-10;
			else if(ch<='F' && ch>='A')
				ch-='A'-10;
			else
			{
				printf("\n\nError : %s :Invalid input of INTEGER type\n",str);
				exit(1);
			}
		
			uint64_t c = (uint64_t)ch;
			if((i&15) == 0)
				j--;
			n->word[j]|=c<<k;
			k=(k+4)&63;
		}
	}
	if(flag == 1)
	{
		for(i=0;i<64;i++)
			n->word[i] = ~(n->word[i]);
		*n = mp_sum(*n,ONE,0);
	}
}
unsigned int bits(uint4096 n)
{
	unsigned int b=0,k = 0;
	while(n.word[b] == 0UL)
		b++;
	if(b>64)
		return 0;
	while(n.word[b] != 0)
	{
		n.word[b]>>=1;
		k++;
	}
	return ((63-b)<<6)+k;
}
int compare(uint4096 m,uint4096 n)
{
	int i;
	uint4096 c = mp_sum(m,n,1);
	if(c.word[0]>>63 == 1UL)
		return -1;
	else
	{
		for(i=0;i<64;i++)
			if(c.word[i] != 0UL)
				return 1;
			return 0;
	}
}



uint4096 lshift(uint4096 n,int c)
{
	if(c == 0)
		return n;
	int i,offset = c>>6;
	c = c&0x3f;
	uint4096 m = ZERO;
	uint64_t s = 0;
	if(c==0)
	{
		for(i=63;i>=offset;i--)
		{
			s = n.word[i];
			m.word[i-offset] |= s;
		}
	}
	else
		for(i=63;i>=offset;i--)
		{
			s = n.word[i]>>(64-c);
			if(i-offset-1 >= 0)
			m.word[i-offset-1] |= s;
			s = (n.word[i]^(s<<(64-c)))<<c;
			m.word[i-offset] |= s;
		}
	return m;
}
uint4096 rshift(uint4096 n,int c)
{	
	if(c == 0)
		return n;
	int i,offset = c>>6;
	c = c&0x3f;
	uint4096 m = ZERO;
	uint64_t s = 0UL;
	if(c==0)
	{
		for(i=0;i<64-offset;i++)
		{
			s = n.word[i];
			m.word[i+offset] |= s;
		}
	}
	else
		for(i=0;i<64-offset;i++)
		{
			s = n.word[i]>>c;
			m.word[i+offset] |= s;
			s = (n.word[i]^(s<<c))<<(64-c);
			if(i+offset+1 < 64)
			m.word[i+offset+1] |= s;
		}
	return m;
}
uint4096 mp_sum(uint4096 m,uint4096 n,unsigned int c)
{
	int i,j;
	unsigned int ic=c==1?1:0;
	uint64_t a,b,s,sum;
	uint4096 sum_long;
	for(i=63;i>=0;i--)
	{
		sum = 0UL;
		for(j=0;j<8*sizeof(uint64_t);j++)
		{	
			a=(m.word[i]>>j)&1UL;
			b=((n.word[i]>>j)&1UL)^(uint64_t)ic;
		
			s=a^b^(uint64_t)c;
			c=(unsigned int)(a&b)|((a^b)&(uint64_t)c);
			
			sum=sum|(s<<j);
		}
		sum_long.word[i] = sum;
	}
	return sum_long; 
}
uint4096 multi(uint4096 m, uint4096 n)
{
	int i,j,k,t;
	uint4096 mult = ZERO;
	
	for(j=63,k=0,t=0;j>=0;)
	{	
		if((m.word[j]>>k)&1UL == 1UL)
			mult = mp_sum(mult,n,0);
		n = lshift(n,1);
		k = (k+1)&63;
		if(k == 0)
			j--;
	}
	return mult;
}

uint4096 mp_div(uint4096 m, uint4096 n,uint4096 *remainder)
{
	int flag =0,t;
	
	uint4096 q,r,x,i;
	
	if(compare(m,ZERO)<0)
	{
		for(t=0;t<64;t++)
			m.word[t] = ~(m.word[t]);
		m = mp_sum(m,ONE,0);
		flag |= 1;
	}
	if(compare(n,ZERO)<0)
	{
		for(t=0;t<64;t++)
			n.word[t] = ~(n.word[t]);
		n = mp_sum(n,ONE,0);
		flag |= 2;
	}
	unsigned int k,a=bits(m),b=bits(n);
	if(compare(n,ZERO) == 0)
	{
		printf("\n\nError: cannot divide by ZERO\n");
		exit(1);
	}	
	if(compare(m,n)<0)
	{
		if(flag == 1)
		{
			for(t=0;t<64;t++)
				m.word[t] = ~(m.word[t]);
			m = mp_sum(m,ONE,0);	
			
		}
		if(remainder != NULL)
			*remainder = m;
		return ZERO;
	}
	q=ZERO;
	r=m;
	while(compare(r,n)>=0)
	{
		x=n;
		
		a=bits(x);
		b=bits(r);
		k=b-a;
		
		x = lshift(x,k);
		if(compare(r,x)<0)
		{
			x=rshift(x,1);
			k--;
		}
		
		i = lshift(ONE,k);
		
		for(k=0;k<64;k++)
		{
			q.word[k]|=i.word[k];
		}	
		r=mp_sum(r,x,1);	
	}
	if(flag == 1 || flag == 2)
	{
		for(t=0;t<64;t++)
			q.word[t] = ~(q.word[t]);
		q = mp_sum(q,ONE,0);	
	}
	if(flag == 1 || flag == 3)
	{
		for(t=0;t<64;t++)
			r.word[t] = ~(r.word[t]);
		r = mp_sum(r,ONE,0);	
	}
	if(remainder!=NULL)
		*remainder=r;
	return q;
}
uint4096 mod(uint4096 m,uint4096 n)
{
	int flag =0,t;
	
	uint4096 q,r,x,i;
	
	if(compare(m,ZERO)<0)
	{
		for(t=0;t<64;t++)
			m.word[t] = ~(m.word[t]);
		m = mp_sum(m,ONE,0);
		flag |= 1;
	}
	if(compare(n,ZERO)<0)
	{
		for(t=0;t<64;t++)
			n.word[t] = ~(n.word[t]);
		n = mp_sum(n,ONE,0);
		flag |= 2;
	}
	unsigned int k,a=bits(m),b=bits(n);
	if(compare(n,ZERO) == 0)
	{
		printf("\n\nError: cannot divide by ZERO :\n");
		exit(1);
	}	
	if(compare(m,n)<0)
	{
		if(flag == 1)
		{
			for(t=0;t<64;t++)
				m.word[t] = ~(m.word[t]);
			m = mp_sum(m,ONE,0);	
			
		}
		return m;
	}
	q=ZERO;
	r=m;
	while(compare(r,n)>=0)
	{
		x=n;
		
		a=bits(x);
		b=bits(r);
		k=b-a;
		
		x = lshift(x,k);
		if(compare(r,x)<0)
		{
			x=rshift(x,1);
			k--;
		}
		
		i = lshift(ONE,k);
		
		for(k=0;k<64;k++)
		{
			q.word[k]|=i.word[k];
		}	
		r=mp_sum(r,x,1);	
	}
	if(flag == 1 || flag == 2)
	{
		for(t=0;t<64;t++)
			q.word[t] = ~(q.word[t]);
		q = mp_sum(q,ONE,0);	
	}
	if(flag == 1 || flag == 3)
	{
		for(t=0;t<64;t++)
			r.word[t] = ~(r.word[t]);
		r = mp_sum(r,ONE,0);	
	}
	return r;
}
uint4096 square_multiple(uint4096 a,uint4096 b,uint4096 n)
{
	int flag =0;
	if(compare(b,ZERO)<0)
	{
		printf("\n\nError : Power should be non negative\n");
		exit(1);
	}
	uint4096 s=ONE,m,c;
	int i,j;
	unsigned int k = bits(b),offset,t;
	for(i = k-1; i>=0 ; i--)
	{
		offset = 63 - (i>>6);
		t = i&0x3f;
		
		m = multi(s,s);
		s = mod(m,n);
		if((b.word[offset]>>t)&1UL == 1UL)
		{
			m = multi(s,a);
			s = mod(m,n);
		}
	}
	return s;
}
uint4096 AND(uint4096 a, uint4096 b)
{
	int i;
	uint4096 c = ZERO;
	for(i=0;i<64;i++)
		c.word[i] = a.word[i]&b.word[i];
	return c;
} 
uint4096 OR(uint4096 a,uint4096 b)
{
	int i;
	uint4096 c = ZERO;
	for(i=0;i<64;i++)
		c.word[i] = a.word[i]|b.word[i];
	return c;
}
uint4096 NOT(uint4096 a)
{
	int i;
	for(i=0;i<64;i++)
		a.word[i] = ~(a.word[i]);
	return a;
}
uint4096 GCD(uint4096 a,uint4096 b)
{
	if(compare(a,ZERO)<0)
	{
		for(int i=0;i<64;i++)
			a.word[i] = ~(a.word[i]);
		a = mp_sum(a,ONE,0);
	}
	if(compare(b,ZERO)<0)
	{
		for(int i=0;i<64;i++)
			b.word[i] = ~(b.word[i]);
		b = mp_sum(b,ONE,0);
	}
	uint4096 q = ZERO,r = a,x;
	while(compare(r,ZERO) != 0)
	{
		q = mp_div(a,b,&r);
		a = b;
		b = r;
	}
	return a;
}
uint4096 INV(uint4096 a,uint4096 p)
{
	if(compare(a,ZERO) == 0)
	{
		printf("\n\nError : Inverse of ZERO does not exist\n");
		exit(1);
	}
	if(compare(GCD(a,p),ONE) != 0)
	{
		printf("\n\nError : Finding Inverse of a non-coprime number is not possible\n");
		exit(1);	
	}
	a = mod(a,p);
	if(compare(a,p)<0)
		a=mp_sum(a,p,0);
	uint4096 x=a,y=p,t,m,q,r,u[2] = {ONE,ZERO},v[2] = {ZERO,ONE};
	while(compare(y,ZERO) != 0)
	{
		q = mp_div(x,y,&r);
		
		m = multi(q,u[1]);
		t = mp_sum(u[0],m,1);
		u[0] = u[1];
		u[1] = t; 
		
		m = multi(q,v[1]);
		t = mp_sum(v[0],m,1);
		v[0] = v[1];
		v[1] = t;
			
		x=y;
		y=r;
	}
	if(compare(u[0],ZERO)<0)
		u[0] = mod(mp_sum(u[0],p,0),p);
	
	return u[0];
}
