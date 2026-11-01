#include "workbench.hpp"
#include <cmath>
#include <algorithm>

namespace wb {
static double loss(double w,double b,double v,double c) {
    const double h=std::tanh(w*1.0+b), pred=v*h+c, e=pred-2.0;
    return 0.5*e*e;
}
NNResult train_one_neuron(int steps,double lr) {
    double w=.5,b=0,v=1,c=0;
    NNResult out{};
    for(int s=0;s<=steps;++s) {
        const double x=1,y=2,h=std::tanh(w*x+b), pred=v*h+c, e=pred-y;
        const double dJ_dyhat=e, dyhat_dv=h, dyhat_dc=1, dyhat_dh=v;
        const double dh_da=1-h*h;
        const double dw=dJ_dyhat*dyhat_dh*dh_da*x;
        const double db=dJ_dyhat*dyhat_dh*dh_da;
        const double dv=dJ_dyhat*dyhat_dv, dc=dJ_dyhat*dyhat_dc;
        if(s==0) { out.prediction=pred; out.loss=.5*e*e; out.dw=dw; out.db=db; out.dv=dv; out.dc=dc; }
        out.loss_history.push_back(.5*e*e);
        if(s==steps) break;
        // Simultaneous update: every gradient above uses the same old parameters.
        w-=lr*dw; b-=lr*db; v-=lr*dv; c-=lr*dc;
    }
    out.w=w; out.b=b; out.v=v; out.c=c;
    const double eps=1e-6;
    auto fd=[&](int p) {
        double a=w,bb=b,vv=v,cc=c;
        double *ptr[4]={&a,&bb,&vv,&cc};
        *ptr[p]+=eps; double plus=loss(a,bb,vv,cc);
        *ptr[p]-=2*eps; double minus=loss(a,bb,vv,cc);
        return (plus-minus)/(2*eps);
    };
    // Validate analytical gradients at the initial parameter point.
    double iw=.5, ib=0, iv=1, ic=0, ih=std::tanh(iw+ib), ie=iv*ih+ic-2;
    double ag[4]={ie*iv*(1-ih*ih),ie*iv*(1-ih*ih),ie*ih,ie};
    double maxerr=0;
    for(int p=0;p<4;++p) {
        double a=iw,bb=ib,vv=iv,cc=ic; double* ptr[4]={&a,&bb,&vv,&cc};
        *ptr[p]+=eps; double plus=loss(a,bb,vv,cc);
        *ptr[p]-=2*eps; double minus=loss(a,bb,vv,cc);
        maxerr=std::max(maxerr,std::abs(ag[p]-(plus-minus)/(2*eps)));
    }
    out.finite_difference_max_error=maxerr;
    return out;
}
}
