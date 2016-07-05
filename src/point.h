#ifndef point_
#define point_

class point
{
	double x_ = .0;
	double y_ = .0;
	mutable double length_sq_ = -1;
	mutable double length_ = -1;

public:
	point(const double x, const double y) : x_{x}, y_{y} {}

	point(const point &p1, const point &p2)
		: x_{p2.x_ - p1.x_}, y_{p2.y_ - p1.y_}
	{
	}

	double x() const { return x_; }

	double y() const { return y_; }

	double length_squared() const
	{
		if (length_sq_ < 0) length_sq_ = x_ * x_ + y_ * y_;
		return length_sq_;
	}

	double length() const
	{
		if (length_ < 0) length_ = std::sqrt(length_squared());
		return length_;
	}

	void scale(const double factor)
	{
		x_ *= factor;
		y_ *= factor;
	}

	point scale_by(const double factor) const
	{
		auto ret = *this;
		ret.scale(factor);
		return ret;
	}

	void rotate(const double sine, const double cosine)
	{
		const auto tmp_x = x_;
		const auto tmp_y = y_;
		x_ = tmp_x * cosine - tmp_y * sine;
		y_ = tmp_x * sine + tmp_y * cosine;
	}

	point rotate_by(const double sine, const double cosine)
	{
		auto ret = *this;
		ret.rotate(sine, cosine);
		return ret;
	}

	void normalize() { scale(1 / length()); }

	point unit_vector() const
	{
		auto ret = *this;
		ret.normalize();
		return ret;
	}

	friend bool operator==(const point &lval, const point &rval)
	{
		return lval.x_ == rval.y_;
	}

	/* People tend to write B - A to indicate vector AB */
	friend point operator-(const point &lval, const point &rval)
	{
		return {rval, lval};
	}

	friend point operator+(const point &lval, const point &rval)
	{
		return {lval.x() + rval.x(), lval.y() + rval.y()};
	}

	friend std::ostream &operator<<(std::ostream &str, const point &x)
	{
		str << '(' << x.x_ << ", " << x.y_ << ')';
		return str;
	}
};

#endif
