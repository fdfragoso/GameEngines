#pragma once

#include "RandomShader.hpp"
using namespace SRE;

//! AlphaChannelShader
/*! Inherits from RandomShader */
/*! Custom alphablend shader for RandomEngine sprites */
class AlphaChannelShader : public RandomShader {
public:
	/*! AlphaChannelShader constructor */
	/*! Uses SRE::createShader() function to create a custom shader */
	AlphaChannelShader();
	/*! AlphaChannelShader destructor */
	~AlphaChannelShader();
};