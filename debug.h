#ifndef DEBUG_H
	#define DEBUG_H

	#ifdef DEBUG
		#define DEBUG_IF(x) if(x)
	#else
		#define DEBUG_IF(x) if(false)
	#endif /*DEBUG*/

#endif /*DEBUG_H*/
