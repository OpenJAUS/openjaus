#include <math.h>
#include "proj.h"

#ifndef PI
#define PI 	3.141592653589793238
#endif

#define HALF_PI (PI*0.5)

#ifndef TWO_PI
#define TWO_PI 	(PI*2.0)
#endif

#define EPSLN	1.0e-10

#ifndef R2D
#define R2D     57.2957795131
#endif

#ifndef D2R
#define D2R 1.745329251994328e-2
#endif

#define S2R	4.848136811095359e-6

#ifndef OK
#define OK	0
#endif

#define ERROR  -1
#define IN_BREAK -2

/* Misc macros
  -----------*/
#define SQUARE(x)       x * x   /* x**2 */
#define CUBE(x)     x * x * x   /* x**3 */
#define QUAD(x) x * x * x * x   /* x**4 */

#define GMAX(A, B)      ((A) > (B) ? (A) : (B)) /* assign maximum of a and b */
#define GMIN(A, B)      ((A) < (B) ? (A) : (B)) /* assign minimum of a and b */

#define IMOD(A, B)      (A) - (((A) / (B)) * (B)) /* Integer mod function */

