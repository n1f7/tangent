#ifndef line_
#define line_

class line
{
	point a_;
	point b_;

public:
	line(const point &a, const point &b) : a_{a}, b_{b} {}

	const point &begin() const { return a_; }
	const point &end() const { return b_; }

	friend std::ostream &operator<<(std::ostream &str, const line &x)
	{
		str << '(' << x.a_ << ", " << x.b_ << ')';
		return str;
	}
};

#endif
