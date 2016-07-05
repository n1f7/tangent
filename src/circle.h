#ifndef circle_
#define circle_

class circle
{
	point centre_;
	double radius_;

public:
	circle(const point &c, const double r) : centre_{c}, radius_{r} {}

	const point &centre() const { return centre_; }
	double radius() const { return radius_; }

	friend bool operator==(const circle &lval, const circle &rval)
	{
		return (lval.radius_ == rval.radius_) && (lval.centre_ == rval.centre_);
	}

	friend std::ostream &operator<<(std::ostream &str, const circle &x)
	{
		str << '(' << x.centre_ << ", " << x.radius_ << ')';
		return str;
	}
};

inline bool operator!=(const circle &lval, const circle &rval)
{
	return !(lval == rval);
}

inline constexpr auto sign(const double x) { return x >= 0 ? 1 : -1; }

constexpr auto positive = sign(0);
constexpr auto negative = sign(-1);

template <class Iter>
inline Iter tangent_lines(const circle &c1, const circle &c2, Iter d_first)
{
	auto c1c2 = c2.centre() - c1.centre();
	const auto delta_r = c2.radius() - c1.radius();
	/* Bail out if either of given circles is inside another */
	if (c1c2.length_squared() <= (delta_r * delta_r)) return d_first;
	c1c2.normalize();
	/* Now that both vectors are normalized find n by rotating c1c2 */
	for (auto i = positive; i >= negative; i -= 2) {
		const auto cosine = (c1.radius() - i * c2.radius()) / c1c2.length();
		if (cosine * cosine > 1.) continue;
		const auto sine = std::sqrt(1. - cosine * cosine);
		for (auto j = positive; j >= negative; j -= 2) {
			auto n = c1c2.rotate_by(sine * j, cosine);
			*d_first++ = line{c1.centre() + n.scale_by(c1.radius()),
							  c2.centre() + n.scale_by(c2.radius() * i)};
		}
	}
	return d_first;
}

#endif
