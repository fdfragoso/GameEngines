
#include "RandomInterpolation.hpp"

glm::vec4 RandomInterpolation::interpolate(glm::vec4 x, glm::vec4 y, float t, InterpolationType i) {
    switch (i){
	case InterpolationType::Random:
		return random(x, y);
		break;
	case InterpolationType::Linear:
		return linear(x, y, t);
		break;
	case InterpolationType::Bezier:
		return cubicBezier(x, y, t);
		break;
			/*case InterpolationType::CatmullRom:
            return catmullRom(t);
        case InterpolationType::Hermite:
            return hermite(t);
        case InterpolationType::BSpline:
            return bspline(t);*/
	default:
		return linear(x, y, t);
		break;
    }
}

glm::vec4 RandomInterpolation::linear(glm::vec4 x, glm::vec4 y, float t) {
    return (1-t)* x +  t * y;
}
glm::vec4 RandomInterpolation::random(glm::vec4 x, glm::vec4 y) {
	return glm::linearRand(x,y);
}

//TODO: Improve interpolations to support more than 2 points xD
glm::vec4 RandomInterpolation::cubicBezier(glm::vec4 x, glm::vec4 y, float t) {

    return (float)pow(1-t,3) * x + (float)pow(1-t,2)*t * (y-x) + (1-t)*t*t * 2*(y-x) +(float)pow(t,3) * y;
}
/*
glm::vec2 RandomInterpolation::hermite(float t) {
    std::vector<Point> &points = *(this->points);
    float t2 = t*t;
    float t3 = t2*t;
    float a0 = 1-(3*t2)+(2*t3);
    float a1 = (3*t2)+(-2*t3);
    float b0 = t-(2*t2)+t3;
    float b1 = -t2+t3;
    float tangentWeight = 3;
    return a0 * points[0].position +
            a1* points[1].position +
            b0 * (points[2].position-points[0].position)*tangentWeight +
            b1 * (points[3].position-points[1].position)*tangentWeight;
}

glm::vec2 RandomInterpolation::catmullRom(float t) {
    std::vector<Point> &points = *(this->points);
    float t2 = t*t;
    float t3 = t2*t;
    float a0 = -0.5f*t + t2 - 0.5f*t3;
    float a1 = 1 - 2.5f*t2 + 1.5f*t3;
    float a2 = 0.5f*t + 2*t2 -1.5f*t3;
    float a3 = -0.5f*t2 + 0.5f*t3;
    return a0 * points[0].position +
           a1* points[1].position +
           a2 * points[2].position +
           a3 * points[3].position;
}

glm::vec2 RandomInterpolation::bspline(float t) {
    std::vector<Point> &points = *(this->points);
    float t2 = t*t;
    float t3 = t2*t;
    float a0 = 1 -3*t + 3*t2 - t3;
    float a1 = 4 - 6*t2 + 3*t3;
    float a2 = 1+3*t + 3*t2 -3*t3;
    float a3 = t3;
    return (a0 * points[0].position +
           a1* points[1].position +
           a2 * points[2].position +
           a3 * points[3].position)*(1/6.0f);
}
*/
