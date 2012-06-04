#ifndef _OPTICAL_FLOW_H
#define _OPTICAL_FLOW_H

struct vector_field *compute_optical_flow(struct image *e,
                                          struct vector_field *d,
                                          float lambda, int nsteps);

// inputs: an image, the a vector field containing derivatives (ex, ey, et),
// a parameter lambda, and the previous settings of u and v (in the vector
// field structure "uvprev")
struct vector_field * optical_flow_step(struct image *e, struct vector_field *d, 
                                        float lambda, struct vector_field *uvprev);
 

// the local avg of u and v at point i and j. returned in uavg and vavg.
void local_average(struct vector_field *uv, int i, int j,
                   float *uavg, float *vavg);


#endif
