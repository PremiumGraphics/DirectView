#ifndef __CRYSTAL_MATH_BAZIER_CURVE_H__
#define __CRYSTAL_MATH_BAZIER_CURVE_H__

namespace Crystal {
	namespace Math {

		/*
class BernsteinBasicFunc{
public:
	float getBinomialCoefficient(const int n, const int k){
		if (n == 0) {
			return 0.0f;
		}
		else if (n == k) {
			return n;
		}
		else {
			return n * getBinomialCoefficient(n - 1, k);
		}
	}

	float get(const int n, const int k, const float x) {
		return getBinomialCoefficient(n, k) * std::pow(x, k) * std::pow(1.0 - x, n - k);
	}
private:
	//float n;
	//float k;

};
*/

class BazierCurve {

};

	}
}

#endif