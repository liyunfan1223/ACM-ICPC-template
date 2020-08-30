//任意点(x,y)，绕一个坐标点(rx0,ry0)逆时针旋转a角度后的新的坐标设为(x0, y0)，有公式：
// x0= (x-rx0)*cos(a)-(y-ry0)*sin(a)+rx0 ;
// y0= (x-rx0)*sin(a)+(y-ry0)*cos(a)+ry0 ;

//任意向量(x,y)，绕一个坐标点(rx0,ry0)逆时针旋转a角度后的新的向量设为(x0, y0)，有公式：
// x0= x*cos(a)-y*sin(a);
// y0= x*sin(a)+y*cos(a);
void Rotate(double &x,double &y,double &vx,double &vy,double x0,double y0,double a)
{
	double x_,vx_,y_,vy_;
	x_=(x-x0)*cos(a)-(y-y0)*sin(a)+x0;
	vx_=vx*cos(a)-vy*sin(a);
	y_=(x-x0)*sin(a)+(y-y0)*cos(a)+y0;
	vy_=vx*sin(a)+vy*cos(a);
	x=x_,y=y_,vx=vx_,vy=vy_;
}
