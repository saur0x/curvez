#ifndef BEZIER_H
#define BEZIER_H

#ifdef BEZIER_DECASTELJAU
	#include "decasteljau.hpp"
#else
	#include "bernstein.hpp"
#endif

namespace bezier {


#ifdef BEZIER_DECASTELJAU
	using decasteljau::linear;
	using decasteljau::quadratic;
	using decasteljau::cubic;
	using decasteljau::npoint;
#else
	using bernstein::linear;
	using bernstein::quadratic;
	using bernstein::cubic;
	using bernstein::npoint;
#endif


}

#endif // BEZIER_H