#include<iostream>
#include<iomanip>
#include<cstring>
using namespace std;

class uint4096
{
	protected:
	uint64_t word[64];
	public:
	
	uint4096(uint64_t p)
	{
		int i;
		for(i = 0;i<64;i++)
			this->word[i] = 0UL;
		if(p != 0)
			this->word[63] = p;
	}
	uint4096(const char *str)
	{
		int i,w,j,k,len,flag = 0;
		char ch;
		uint64_t c;
		if(str!=NULL)	
		{
			if(str[0] == '-')
			{	
				flag = 1;
				str++;
			}
			len = strlen(str);
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
					cout << "\n\nError :"<< str << ":Invalid input of INTEGER type" << endl;
					exit(1);
				}
			
				c = (uint64_t)ch;
				if((i&15) == 0)
				{	
					j--;
					this->word[j] = 0UL;
				}
				this->word[j]|=c<<k;
				k=(k+4)&63;
			}
			while(j-->0)
			{
				this->word[j] = 0UL;
			}
		}
		if(flag == 1)
		{
			for(i=0;i<64;i++)
				word[i] = ~(word[i]);
			*this = *this + 1;
		}
	}
	void init(char *str)
	{
		int i,flag = 0,w,j,k,len;
		uint64_t c;
		*this = 0;
		if(str!=NULL)	
		{
			if(str[0] == '-')
			{	
				flag = 1;
				str++;
			}
			len = strlen(str);
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
					cout << "\n\nError :" << str << ":Invalid input of INTEGER type" << endl;
					exit(1);
				}
			
				c = (uint64_t)ch;
				if((i&15) == 0)
					j--;
				word[j]|=c<<k;
				k=(k+4)&63;
			}
		}
		if(flag == 1)
		{
			for(i=0;i<64;i++)
				word[i] = ~(word[i]);
			*this = *this+1;
		}
	}
	void printuint() const
	{
		int i;
		int flag = 0;
		for(i=0;i<64;i++)
		{
			if(flag == 0 && word[i] == 0UL)
			{
				continue;
			}
			else if(flag == 0)
			{
				flag = 1;
				cout << hex << word[i];
			}
			else	
			cout << std::setfill('0') << std::setw(16) << hex << word[i];
		}
		if(flag == 0)
			cout << 0;
	}

	void printint() const
	{
		int i;
		uint4096 m = *this;
		if((word[0]>>63) == 1UL)
		{
			for(i=0;i<64;i++)
				m.word[i] = ~(m.word[i]);
			m = m + 1;
			cout << "-";
		}
		int flag = 0;
		for(i=0;i<64;i++)
		{
			if(flag == 0 && m.word[i] == 0UL)
			{
				continue;
			}
			else if(flag == 0)
			{
				flag = 1;
				cout << hex << m.word[i];
			}
			else	
			cout << std::setfill('0') << std::setw(16) << hex << m.word[i];
		}
		if(flag == 0)
			cout << 0;
	}
	void operator= (uint64_t p)
	{
		int i;
		for(i = 0;i<64;i++)
			this->word[i] = 0UL;
		if(p != 0)
			this->word[63] = p;
	}
	
	uint4096 operator + (uint4096 const &n) const
	{
		int i,j;
		if(n==0)
			return *this;
		unsigned int c=0;
		uint64_t a,b,s,sum;
		uint4096 sum_long(0UL);
		for(i=63;i>=0;i--)
		{
			sum = 0UL;
			for(j=0;j<8*sizeof(uint64_t);j++)
			{	
				a=(this->word[i]>>j)&1UL;
				b=(n.word[i]>>j)&1UL;
			
				s=a^b^(uint64_t)c;
				c=(unsigned int)(a&b)|((a^b)&(uint64_t)c);
				
				sum=sum|(s<<j);
			}
			sum_long.word[i] = sum;
		}
		return sum_long; 
	}
	void operator += (uint4096 const &n)
	{
		int i,j;
		if(n==0)
			return;
		unsigned int c=0;
		uint64_t a,b,s,sum;
		
		for(i=63;i>=0;i--)
		{
			sum = 0UL;
			for(j=0;j<8*sizeof(uint64_t);j++)
			{	
				a=(word[i]>>j)&1UL;
				b=(n.word[i]>>j)&1UL;
			
				s=a^b^(uint64_t)c;
				c=(unsigned int)(a&b)|((a^b)&(uint64_t)c);
				
				sum=sum|(s<<j);
			}
			word[i] = sum;
		}
	}
	uint4096 operator + (uint64_t const &m) const
	{
		if(m==0)
			return *this;
		uint4096 n = m;
		return *this+n;
	}
	void operator += (uint64_t const &m)
	{
		if(m==0)
			return;
		uint4096 n = m;
		*this += n;
	}
	uint4096 operator -() const
	{	
		int i;
		if(*this == 0)
			return *this;
		uint4096 b=0UL;
		for(i=0;i<64;i++)
			b.word[i] = ~word[i];
		b+=1;
		return b;	
	}
	uint4096 operator - (uint4096 const &n) const
	{
		int i,j;
		if(n==0)
			return *this;
		unsigned int c=1;
		uint64_t a,b,s,sum;
		uint4096 sum_long(0UL);
		for(i=63;i>=0;i--)
		{
			sum = 0UL;
			for(j=0;j<8*sizeof(uint64_t);j++)
			{	
				a=(this->word[i]>>j)&1UL;
				b=((n.word[i]>>j)&1UL)^1UL;
			
				s=a^b^(uint64_t)c;
				c=(unsigned int)(a&b)|((a^b)&(uint64_t)c);
				
				sum=sum|(s<<j);
			}
			sum_long.word[i] = sum;
		}
		return sum_long; 
	}
	void operator -= (uint4096 const &n)
	{
		int i,j;
		if(n==0)
			return;
		unsigned int c=0;
		uint64_t a,b,s,sum;
		
		for(i=63;i>=0;i--)
		{
			sum = 0UL;
			for(j=0;j<8*sizeof(uint64_t);j++)
			{	
				a=(word[i]>>j)&1UL;
				b=((n.word[i]>>j)&1UL)^1UL;
			
				s=a^b^(uint64_t)c;
				c=(unsigned int)(a&b)|((a^b)&(uint64_t)c);
				
				sum=sum|(s<<j);
			}
			word[i] = sum;
		}
	}
	uint4096 operator - (uint64_t const &m) const 
	{
		if(m==0)
			return *this;
		uint4096 n = m;
		return *this - n; 
	}
	void operator -= (uint64_t const &m)
	{
		if(m==0)
			return;
		uint4096 n = m;		
		*this-=n;
	}
	int operator < (uint4096 const &n) const
	{
		uint4096 c = *this - n;
		if((c.word[0]>>63) == 1UL)
			return 1;
		else
			return 0;
	}
	
	int operator == (uint4096 const &n) const
	{
		int i;
		uint4096 c = *this - n;
		if((c.word[0]>>63) == 1UL)
			return 0;
		
		else
		{
			for(i=0;i<64;i++)
				if(c.word[i] != 0UL)
					return 0;
				return 1;
		}
	}
	int operator != (uint4096 const &n) const
	{
		if(*this == n)
			return 0;
		return 1;
	}
	int operator > (uint4096 const &n) const
	{
		int i;
		uint4096 c = *this - n;
		if((c.word[0]>>63) == 1UL)
			return 0;
		else
		{
			for(i=0;i<64;i++)
				if(c.word[i] != 0UL)
					return 1;
				return 0;
		}
	}
	int operator <= (uint4096 const &n) const
	{
		int i;
		uint4096 c = *this - n;
		if((c.word[0]>>63) == 1UL)
			return 1;
		else
		{
			for(i=0;i<64;i++)
				if(c.word[i] != 0UL)
					return 0;
				return 1;
		}
	}
	int operator >= (uint4096 const &n) const
	{
		int i;
		uint4096 c = *this - n;
		if((c.word[0]>>63) == 1UL)
			return 0;
		return 1;
	}


	int operator < (uint64_t const &n) const
	{
		uint4096 c = *this - n;
		if((c.word[0]>>63) == 1UL)
			return 1;
		else
			return 0;
	}
	int operator == (uint64_t const &n) const
	{
		int i;
		uint4096 t = ((*this)-n);
		if((t.word[0]>>63) == 1UL)
			return 0;
		
		else
		{
			for(i=0;i<64;i++)
				if(t.word[i] != 0UL)
					return 0;
				return 1;
		}
	}
	int operator != (uint64_t const &n) const
	{
		if(*this == n)
			return 0;
		else 
			return 1;
	}
	int operator > (uint64_t const &n) const
	{
		int i;
		uint4096 c = *this - n;
		if((c.word[0]>>63) == 1UL)
			return 0;
		else
		{
			for(i=0;i<64;i++)
				if(c.word[i] != 0UL)
					return 1;
				return 0;
		}
	}
	int operator <= (uint64_t const &n) const
	{
		int i;
		uint4096 c = *this - n;
		if((c.word[0]>>63) == 1UL)
			return 1;
		else
		{
			for(i=0;i<64;i++)
				if(c.word[i] != 0UL)
					return 0;
				return 1;
		}
	}
	int operator >= (uint64_t const &n) const
	{
		int i;
		uint4096 c = *this - n;
		if((c.word[0]>>63) == 1UL)
			return 0;
		else
			return 1;
	}
	unsigned int bits() const
	{
		uint4096 m = *this;
		unsigned int b=0,k = 0;
		while(m.word[b] == 0UL)
			b++;
		if(b>64)
			return 0;
		while(m.word[b] != 0)
		{
			m.word[b]>>=1;
			k++;
		}
		return ((63-b)<<6)+k;
	}
	uint4096 operator << (unsigned int const &cl) const
	{
		unsigned int c=cl;
		if(c == 0)
			return *this;
		int i,offset = c>>6;
		c = c&0x3f;
		uint4096 m(0UL);
		uint64_t s = 0;
		if(c==0)
		{
			for(i=63;i>=offset;i--)
			{
				s = word[i];
				m.word[i-offset] |= s;
			}
		}
		else
			for(i=63;i>=offset;i--)
			{
				s = word[i]>>(64-c);
				if(i-offset-1 >= 0)
				m.word[i-offset-1] |= s;
				s = (word[i]^(s<<(64-c)))<<c;
				m.word[i-offset] |= s;
			}
		return m;
	}
	void operator <<= (unsigned int const &cl)
	{
		unsigned int c=cl;
		if(c == 0)
			return;
		int i,offset = c>>6;
		c = c&0x3f;
		uint4096 m(0UL);
		uint64_t s = 0;
		if(c==0)
		{
			for(i=63;i>=offset;i--)
			{
				s = word[i];
				m.word[i-offset] |= s;
			}
		}
		else
			for(i=63;i>=offset;i--)
			{
				s = word[i]>>(64-c);
				if(i-offset-1 >= 0)
				m.word[i-offset-1] |= s;
				s = (word[i]^(s<<(64-c)))<<c;
				m.word[i-offset] |= s;
			}
		for(i=0;i<64;i++)
			word[i] = m.word[i];
	}
	uint4096 operator >> (unsigned int const &cl) const
	{	
		unsigned int c=cl;
		if(c == 0)
			return *this;
		int i,offset = c>>6;
		c = c&0x3f;
		uint4096 m(0UL);
		uint64_t s = 0UL;
		if(c==0)
		{
			for(i=0;i<64-offset;i++)
			{
				s = word[i];
				m.word[i+offset] |= s;
			}
		}
		else
			for(i=0;i<64-offset;i++)
			{
				s = word[i]>>c;
				m.word[i+offset] |= s;
				s = (word[i]^(s<<c))<<(64-c);
				if(i+offset+1 < 64)
				m.word[i+offset+1] |= s;
			}
		return m;
	}
	void operator >>= (unsigned int const &cl)
	{	
		unsigned int c=cl;
		if(c == 0)
			return;
		int i,offset = c>>6;
		c = c&0x3f;
		uint4096 m(0UL);
		uint64_t s = 0UL;
		if(c==0)
		{
			for(i=0;i<64-offset;i++)
			{
				s = word[i];
				m.word[i+offset] |= s;
			}
		}
		else
			for(i=0;i<64-offset;i++)
			{
				s = word[i]>>c;
				m.word[i+offset] |= s;
				s = (word[i]^(s<<c))<<(64-c);
				if(i+offset+1 < 64)
				m.word[i+offset+1] |= s;
			}
		for(i=0;i<64;i++)
			word[i] = m.word[i];
	}
	uint4096 operator * (uint4096 const &m) const
	{
		int i,j,k,t;
		uint4096 mult(0UL),n=m;
		
		for(j=63,k=0,t=0;j>=0;)
		{	
			if(((word[j]>>k)&1UL) == 1UL)
				mult = mult+n;
			n = (n<<1);
			k = (k+1)&63;
			if(k == 0)
				j--;
		}
		return mult;
	}
	uint4096 operator * (uint64_t const &m) const
	{
		if(m==1)
			return *this;
		uint4096 n = m;
		return *this*n;	
	}
	uint4096 operator *= (uint4096 const &m)
	{
		int i,j,k,t;
		uint4096 mult(0UL),n=m;
		
		for(j=63,k=0,t=0;j>=0;)
		{	
			if((word[j]>>k)&1UL == 1UL)
				mult = mult+n;
			n = (n<<1);
			k = (k+1)&63;
			if(k == 0)
				j--;
		}
		return mult;
		*this = mult;
	}
	void operator *= (uint64_t const &m)
	{
		if(m==1)
			return;
		uint4096 n = m;
		*this*=n;	
	}
	uint4096 operator / (uint4096 const &y) const
	{
		int flag =0,t;
		uint4096 ZERO(0UL),ONE(1UL);
		uint4096 m = *this,n = y,q(0UL),r(0UL),x(0UL),i(0UL);
		unsigned int k,a,b;
		if(m<0)
		{
			for(t=0;t<64;t++)
				m.word[t] = ~(m.word[t]);
			m = m+1;
			flag |= 1;
		}
		if(n<0)
		{
			for(t=0;t<64;t++)
				n.word[t] = ~(n.word[t]);
			n = n+1;
			flag |= 2;
		}
		a = m.bits();
		b = n.bits();
		if(n == 0)
		{
			cout << "\n\nError: cannot divide by ZERO" << endl;
			exit(1);
		}	
		if(m<n)
			return ZERO;

		q=ZERO;
		r=m;
		while(r>=n)
		{
			x=n;
			
			a=x.bits();
			b=r.bits();
			k=b-a;
			
			x = x<<k;
			if(r<x)
			{
				x>>=1;
				k--;
			}
			
			i = ONE<<k;
			
			for(k=0;k<64;k++)
			{
				q.word[k]|=i.word[k];
			}	
			r-=x;	
		}
		if(flag == 1 || flag == 2)
		{
			for(t=0;t<64;t++)
				q.word[t] = ~(q.word[t]);
			q = q+1;	
		}
		if(flag == 1 || flag == 3)
		{
			for(t=0;t<64;t++)
				r.word[t] = ~(r.word[t]);
			r = r+1;	
		}
		return q;
	}
	uint4096 operator / (uint64_t const &m) const
	{
		if(m==1)
			return *this;
		uint4096 n = m;
		return *this/n;	
	}
	void operator /= (uint4096 const &y)
	{
		int flag =0,t;
		uint4096 ZERO(0UL),ONE(1UL);
		uint4096 m = *this,n = y,q(0UL),r(0UL),x(0UL),i(0UL);
		unsigned int k,a,b;
		if(m<0)
		{
			for(t=0;t<64;t++)
				m.word[t] = ~(m.word[t]);
			m = m+1;
			flag |= 1;
		}
		if(n<0)
		{
			for(t=0;t<64;t++)
				n.word[t] = ~(n.word[t]);
			n = n+1;
			flag |= 2;
		}
		a = m.bits();
		b = n.bits();
		if(n == 0)
		{
			cout << "\n\nError: cannot divide by ZERO" <<endl;
			exit(1);
		}	
		if(m<n)
			*this = ZERO;

		q=ZERO;
		r=m;
		while(r>=n)
		{
			x=n;
			
			a=x.bits();
			b=r.bits();
			k=b-a;
			
			x = x<<k;
			if(r<x)
			{
				x>>=1;
				k--;
			}
			
			i = ONE<<k;
			
			for(k=0;k<64;k++)
			{
				q.word[k]|=i.word[k];
			}	
			r-=x;	
		}
		if(flag == 1 || flag == 2)
		{
			for(t=0;t<64;t++)
				q.word[t] = ~(q.word[t]);
			q = q+1;	
		}
		if(flag == 1 || flag == 3)
		{
			for(t=0;t<64;t++)
				r.word[t] = ~(r.word[t]);
			r = r+1;	
		}
		*this = q;
	}
	void operator /= (uint64_t const &m)
	{
		if(m==1)
			return;
		uint4096 n = m;
		*this/=n;	
	}
	uint4096 operator % (const uint4096 &y) const
	{
		int flag =0,t;
		unsigned int k,a,b;
		uint4096 ZERO(0UL),ONE(1UL),m=*this,n=y,q=0UL,r = 0UL,x = 0UL,i = 0UL;
		
		if(m<0)
		{
			for(t=0;t<64;t++)
				m.word[t] = ~(m.word[t]);
			m = m+1;
			flag |= 1;
		}
		if(n<0)
		{
			for(t=0;t<64;t++)
				n.word[t] = ~(n.word[t]);
			n = n+1;
			flag |= 2;
		}
		a=m.bits();
		b=n.bits();
		if(n==0)
		{
			cout << "\n\nError: cannot divide by ZERO :" << endl;
			exit(1);
		}	
		if(m<n)
		{
			if(flag == 1)
			{
				for(t=0;t<64;t++)
					m.word[t] = ~(m.word[t]);
				m = m+1;	
				
			}
			return m;
		}
		q=ZERO;
		r=m;
		while(r>=n)
		{
			x=n;
			
			a=x.bits();
			b=r.bits();
			k=b-a;
			
			x <<=k;
			if(r<x)
			{
				x=x>>1;
				k--;
			}
			
			i = ONE<<k;
			
			for(k=0;k<64;k++)
			{
				q.word[k]|=i.word[k];
			}	
			r=r-x;	
		}
		if(flag == 1 || flag == 2)
		{
			for(t=0;t<64;t++)
				q.word[t] = ~(q.word[t]);
			q = q+1;	
		}
		if(flag == 1 || flag == 3)
		{
			for(t=0;t<64;t++)
				r.word[t] = ~(r.word[t]);
			r = r+1;	
		}
		return r;
	}
	uint4096 operator % (uint64_t const &m) const
	{
		uint4096 n = m;
		return *this%n;	
	}
	void operator %= (uint4096 const &y)
	{
		int flag =0,t;
		unsigned int k,a,b;
		uint4096 ZERO(0UL),ONE(1UL),m=*this,n=y,q(0UL),r(0UL),x(0UL),i(0UL);
		
		if(m<0)
		{
			for(t=0;t<64;t++)
				m.word[t] = ~(m.word[t]);
			m = m+1;
			flag |= 1;
		}
		if(n<0)
		{
			for(t=0;t<64;t++)
				n.word[t] = ~(n.word[t]);
			n = n+1;
			flag |= 2;
		}
		a=m.bits();
		b=n.bits();
		if(n==0)
		{
			cout << "\n\nError: cannot divide by ZERO :" << endl;
			exit(1);
		}	
		if(m<n)
		{
			if(flag == 1)
			{
				for(t=0;t<64;t++)
					m.word[t] = ~(m.word[t]);
				m = m+1;	
				
			}
			*this=m;
		}
		q=ZERO;
		r=m;
		while(r>=n)
		{
			x=n;
			
			a=x.bits();
			b=r.bits();
			k=b-a;
			
			x <<=k;
			if(r<x)
			{
				x=x>>1;
				k--;
			}
			
			i = ONE<<k;
			
			for(k=0;k<64;k++)
			{
				q.word[k]|=i.word[k];
			}	
			r=r-x;	
		}
		if(flag == 1 || flag == 2)
		{
			for(t=0;t<64;t++)
				q.word[t] = ~(q.word[t]);
			q = q+1;	
		}
		if(flag == 1 || flag == 3)
		{
			for(t=0;t<64;t++)
				r.word[t] = ~(r.word[t]);
			r = r+1;	
		}
		*this=r;
	}
	void operator %= (uint64_t const &m)
	{
		uint4096 n = m;
		*this%=n;	
	}
	uint4096 operator &(uint4096 const &b) const
	{
		int i;
		uint4096 c = 0UL;
		for(i=0;i<64;i++)
			c.word[i] = word[i]&b.word[i];
		return c;
	} 
	uint4096 operator &(uint64_t const &b) const
	{
		int i;
		uint4096 c = 0UL,d = b;
		for(i=0;i<64;i++)
			c.word[i] = word[i]&d.word[i];
		return c;
	} 
	uint4096 operator |(uint4096 const &b) const
	{
		int i;
		uint4096 c = 0UL;
		for(i=0;i<64;i++)
			c.word[i] = word[i]|b.word[i];
		return c;
	}
	uint4096 operator |(uint64_t const &b) const
	{
		int i;
		uint4096 c = 0UL,d=b;
		for(i=0;i<64;i++)
			c.word[i] = word[i]|d.word[i];
		return c;
	}
	uint4096 operator ^(uint4096 const &b) const
	{
		int i;
		uint4096 c = 0UL;
		for(i=0;i<64;i++)
			c.word[i] = word[i]^b.word[i];
		return c;
	}
	uint4096 operator ^(uint64_t const &b) const
	{
		int i;
		uint4096 c = 0UL,d=b;
		for(i=0;i<64;i++)
			c.word[i] = word[i]^d.word[i];
		return c;
	}
	uint4096 operator ~() const
	{
		int i;
		uint4096 a = 0UL;
		for(i=0;i<64;i++)
			a.word[i] = ~(word[i]);
		return a;
	}
	void operator &=(uint4096 const &b)
	{
		int i;
		for(i=0;i<64;i++)
			word[i] = word[i]&b.word[i];
	} 
	void operator &=(uint64_t const &b)
	{
		int i;
		uint4096 d=b;
		for(i=0;i<64;i++)
			word[i] = word[i]&d.word[i];
	} 
	void operator |=(uint4096 const &b)
	{
		int i;
		for(i=0;i<64;i++)
			word[i] = word[i]|b.word[i];
	}
	void operator |=(uint64_t const &b)
	{
		int i;
		uint4096 d=b;
		for(i=0;i<64;i++)
			word[i] = word[i]|d.word[i];
	} 
	void operator ^=(uint4096 const &b)
	{
		int i;
		for(i=0;i<64;i++)
			word[i] = word[i]^b.word[i];
	}
	void operator ^=(uint64_t const &b)
	{
		int i;
		uint4096 d=b;
		for(i=0;i<64;i++)
			word[i] = word[i]^d.word[i];
	} 
		
};
uint4096 get_int(const char *);
uint4096 square_multiple(const uint4096 ,const uint4096 ,const uint4096 );
uint4096 GCD(uint4096 ,uint4096 );
uint4096 INV(uint4096 ,uint4096 );

int main()
{
	int i;
	uint4096 a=0UL,b=0UL,c=0UL,s(0UL);
	int n;
	a = get_int("Enter the first integer in hex :\n");
	b = get_int("Enter the second integer in hex :\n");
	c= get_int("Enter the third integer in hex :\n");

	cout << "\n\na\t: ";
	a.printint();
	cout << "\n\n-a\t: ";
	s=-a;
	s.printint();
	cout << "\n\nb\t: ";
	b.printint();
	cout << "\n\nc\t: ";
	c.printint();
	
	cout << "\n\nadd\t: ";
	s = a+b;
	s.printint();
	cout << "\n\nmult\t: ";
	s = a*b;
	s.printint();
	cout << "\n\ndiv\t: ";
	s = a/b;
	s.printint();
	cout << "\n\nsubs\t: ";
	s = a-b;
	s.printint();
	cout << "\n\nmod\t: ";
	s = a%b;
	s.printint();
	cout << "\n\n(a^b)%c\t: ";
	s = square_multiple(a,b,c);
	s.printint();
	cout << "\n\ngcd\t: ";
	s = GCD(a,b);
	s.printint();
	cout << "\n\n";
	if(s == 1)
	{
		cout << "\n\ninv\t: ";
		s = INV(a,b);
		s.printint();
		cout << "\n\n";
	}
}

uint4096 get_int(const char *s)
{
	char *str = (char*)malloc(1025);
	uint4096 a = 0UL;
	if(s!=NULL)
		cout << s;
	cin >> str;
	str[1024] = '\0';
	a.init(str);
	free(str);
	return a;
}
uint4096 square_multiple(const uint4096 a,const uint4096 b,const uint4096 n)
{
	if(b<0)
	{
		printf("\n\nError: Power must be positive\n");
		exit(1);
	}
	uint4096 s=1UL,c=0UL;
	int i,j;
	unsigned int k = b.bits();
	for(i = k-1; i>=0 ; i--)
	{
		
		s = (s*s)%n;
		if(((b>>i)&1UL)==1UL)
			s=(s*a)%n;
	}
	return s;
}
uint4096 GCD(uint4096 a,uint4096 b)
{
	if(a<0)
		a=-a;
	if(b<0)
		b=-b;
	uint4096 r = b;
	while(b != 0)
	{
		r = a%b;
		a = b;
		b = r;
	}
	return a;
}
uint4096 INV(uint4096 a,uint4096 p)
{
	if(a == 0)
	{
		cout << "\n\nError : Inverse of ZERO does not exist" << endl;
		exit(1);
	}
	if(GCD(a,p) != 1)
	{
		cout << "\n\nError : Finding Inverse of a non-coprime number is not possible\n" << endl;
		exit(1);	
	}
	uint4096 x=a,y=p,t=0UL,m=0UL,q=0UL,r=0UL,u[2] = {1UL,0UL},v[2] = {0UL,1UL};
	while(y != 0)
	{
		q = x/y;
		
		m = q*u[1];
		t = u[0]-m;
		u[0] = u[1];
		u[1] = t; 
		
		m = q*v[1];
		t = v[0]-m;
		v[0] = v[1];
		v[1] = t;

		r = x%y;	
		x=y;
		y=r;
	}
	if(u[0]<0)
		u[0] = (u[0]+p)%p;
	
	return u[0];
}
