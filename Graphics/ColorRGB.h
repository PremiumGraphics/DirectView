#ifndef __CRYSTAL_GRAPHICS_COLOR_RGB_H__
#define __CRYSTAL_GRAPHICS_COLOR_RGB_H__

#include <vector>

namespace Crystal {
	namespace Graphics {

template< typename T >
class ColorRGB {
public:
	ColorRGB() :
		red( 0.0f ),
		green( 0.0f ),
		blue( 0.0f )
	{}

	ColorRGB(const T red, const T green, const T blue) :
		red( red ), green( green ), blue( blue )
	{}

	void setRed( const T r ) { this->red = r; }

	void setGreen( const T g ) { this->green = g; }

	void setBlue( const T b ) { this->blue = b; }

	T getRed() const { return red; }

	T getGreen() const { return green; }

	T getBlue() const { return blue; }

	static ColorRGB White() {
		return ColorRGB( 1.0f, 1.0f, 1.0f );
	}

	static ColorRGB Black() {
		return ColorRGB( 0.0f, 0.0f, 0.0f );
	}

	static ColorRGB Red() {
		return ColorRGB( 1.0f, 0.0f, 0.0f );
	}

	static ColorRGB Green() {
		return ColorRGB( 0.0f, 1.0f, 0.0f );
	}

	static ColorRGB Blue() {
		return ColorRGB( 0.0f, 0.0f, 1.0f );
	}

	static ColorRGB Yellow() {
		return ColorRGB( 1.0f, 1.0f, 0.0f );
	}
	
	static ColorRGB Cyan() {
		return ColorRGB( 0.0f, 1.0f, 1.0f );
	}

	static ColorRGB Magenta() {
		return ColorRGB( 1.0f, 0.0f, 1.0f );
	}

	std::vector<T> toArray3() const {
		std::vector<T> results(3);
		results[0] = red;
		results[1] = green;
		results[2] = blue;
		return results;
	}

	std::vector<float> toArray4() const;

	bool equals( const ColorRGB& rhs ) const {
		return 
			(red == rhs.getRed()) &&
			(green == rhs.getGreen()) &&
			(blue == rhs.getBlue());
	}

	bool operator==( const ColorRGB& rhs ) const {
		return equals( rhs );
	}

	bool operator!=(const ColorRGB& rhs) const {
		return !equals( rhs );
	}

	void add( const ColorRGB& rhs ) {
		red += rhs.red;
		green += rhs.green;
		blue += rhs.blue;
	}

	bool isValid() const {
		return
			( 0.0f <= red && red <= 1.0f ) &&
			( 0.0f <= green && green <= 1.0f ) &&
			( 0.0f <= blue && blue <= 1.0f );
	}

private:
	T red;
	T green;
	T blue;
};

//typedef std::vector< ColorRGB > ColorVector;
	}
}

#endif