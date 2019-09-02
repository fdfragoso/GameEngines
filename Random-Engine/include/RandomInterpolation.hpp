#pragma once

#include <vector>
#include "glm/glm.hpp"
#include <glm/gtc/random.hpp>

//! InterpolationType
/**
* Enum class for the type of interpolation used by RandomInterpolation
*/
enum class InterpolationType{
	Random,
    Linear,
    Bezier,
    Hermite,
    CatmullRom,
    BSpline
};


//! RandomInterpolation
/**
* Class that implements different types of interpolation
*/
class RandomInterpolation{
public:
	/**
	* Calls other functions based on the InterpolationType parameter
	* @param {glm::vec4} x - first value for interpolation
	* @param {glm::vec4} y - second value for interpolation
	* @param {float} t - 0 to 1 value of how much we want to interpolate between the two
	* @param {RandomInterpolation::InterpolationType} i - type of interpolation to use
	* @return {glm::vec4}
	*/
    static glm::vec4 interpolate(glm::vec4 x, glm::vec4 y, float t, InterpolationType i);
private:
	/**
	* Linear interpolation between two values
	* @param {glm::vec4} x - first value for interpolation
	* @param {glm::vec4} y - second value for interpolation
	* @param {float} t - 0 to 1 value of how much we want to interpolate between the two
	* @return {glm::vec4}
	*/
    static glm::vec4 linear(glm::vec4 x, glm::vec4 y, float t);
	/**
	* Random "interpolation" between two values (glm::linearRand(x,y))
	* @param {glm::vec4} x - first value for interpolation
	* @param {glm::vec4} y - second value for interpolation
	* @return {glm::vec4}
	*/
	static glm::vec4 random(glm::vec4 x, glm::vec4 y);
	/**
	* Bezier interpolation between two values
	* @param {glm::vec4} x - first value for interpolation
	* @param {glm::vec4} y - second value for interpolation
	* @param {float} t - 0 to 1 value of how much we want to interpolate between the two
	* @return {glm::vec4}
	*/
    static glm::vec4 cubicBezier(glm::vec4 x, glm::vec4 y, float t);
	//glm::vec2 hermite(float t);
    // glm::vec2 catmullRom(float t);
    // glm::vec2 bspline(float t);
};