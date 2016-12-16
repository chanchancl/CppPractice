#pragma once

#ifndef __PAIR_H__
#define __PAIR_H__

namespace sp
{

	template <typename T1,typename T2>
	struct pair
	{
		typedef T1		first_type;
		typedef T2		second_type;

		first_type  first;
		second_type second;

		pair(const first_type& x1, const second_type& x2) : first(x1),second_type(x2) {}

	};

}



#endif