#ifndef __CRYSTAL_GRAPHICS_COLOR_H__
#define __CRYSTAL_GRAPHICS_COLOR_H__

#include <vector>

namespace Crystal {
	namespace Graphics {

template< typename T >
class ColorRGBA {
public:
	ColorRGBA() :
		red( 0 ),
		green( 0 ),
		blue( 0 ),
		alpha( 0 )
	{}

	/*
	ColorRGBA( const ColorRGB& rgb ) :
		ColorRGB( rgb ),
		alpha( 1.0f )
	{}
	*/

	ColorRGBA(const T red, const T green, const T blue, const T alpha = 0.0) :
		red( red ),
		green( green ),
		blue( blue ),
		alpha( alpha )
	{}

	void setRed( const T r ) { red = r; }

	T getRed() const { return red; }

	void setGreen( const T g ) { green = g; }

	T getGreen() const { return green; }

	void setBlue( const T b ) { blue = b; }

	T getBlue() const { return blue; }

	void setAlpha(const T a) { this->alpha = a;  }

	T getAlpha() const { return alpha; }

	static ColorRGBA White() {
		return ColorRGBA( 1.0f, 1.0f, 1.0f );
	}

	static ColorRGBA Black() {
		return ColorRGBA( 0.0f, 0.0f, 0.0f );
	}

	static ColorRGBA Red() {
		return ColorRGBA( 1.0f, 0.0f, 0.0f );
	}

	static ColorRGBA Green() {
		return ColorRGBA( 0.0f, 1.0f, 0.0f );
	}

	static ColorRGBA Blue() {
		return ColorRGBA( 0.0f, 0.0f, 1.0f );
	}

	static ColorRGBA Yellow() {
		return ColorRGBA( 1.0f, 1.0f, 0.0f );
	}
	
	static ColorRGBA Cyan() {
		return ColorRGBA( 0.0f, 1.0f, 1.0f );
	}

	static ColorRGBA Magenta() {
		return ColorRGBA( 1.0f, 0.0f, 1.0f );
	}

	std::vector<T> toArray3() const {
		std::vector<T> results(3);
		results[0] = red;
		results[1] = green;
		results[2] = blue;
		return results;
	}

	std::vector<T> toArray4() const {
		std::vector<T> results(4);
		results[0] = getRed();
		results[1] = getGreen();
		results[2] = getBlue();
		results[3] = getAlpha();
		return results;
	}

	bool equals( const ColorRGBA& rhs ) const {
		return 
			(getRed() == rhs.getRed()) &&
			(getGreen() == rhs.getGreen()) &&
			(getBlue() == rhs.getBlue()) &&
			(alpha == rhs.getAlpha());
	}

	bool operator==( const ColorRGBA& rhs ) const {
		return equals( rhs );
	}

	bool operator!=(const ColorRGBA& rhs) const {
		return !equals( rhs );
	}

	ColorRGBA<T> getScaled( const T f ) const {
		return ColorRGBA<T>( red * f, green * f, blue * f, alpha * f );
	}

	void add( const ColorRGBA& rhs ) {
		this->red += rhs.red;
		this->green += rhs.green;
		this->blue += rhs.blue;
		this->alpha+= rhs.alpha;
	}

	ColorRGBA<T> getAdded( const ColorRGBA& rhs ) const {
		return ColorRGBA<T>( red + rhs.red, green + rhs.green, blue + rhs.blue, alpha + rhs.alpha );
	}

	void operator+=( const ColorRGBA& rhs ) {
		add( rhs );
	}

	ColorRGBA<T> operator+( const ColorRGBA& rhs ) const {
		return getAdded( rhs );
	}

private:
	T red;
	T green;
	T blue;
	T alpha;
};

template< typename T >
using ColorVector = std::vector< ColorRGBA< T > >;

static std::vector<float> toArray4( const ColorVector<float>& colors ) {
	std::vector< float > result;
	for( size_t i = 0; i < colors.size(); ++i ) {
		const std::vector<float>& color = colors[i].toArray4();
		result.insert( result.end(), color.begin(), color.end() );
	}
	return result;
}

	}
}

#endif