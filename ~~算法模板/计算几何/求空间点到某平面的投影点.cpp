/*
    计算空间点到平面的投影点坐标
    0、p为平面外任意一点；
    1、pp为所求的投影点坐标；
    2、A为平面上任意已知点；
    3、n为平面上的法线；

    n的计算方法：
    一般会已知平面上两个以上的点坐标，例如我是为了求点在任意三角形上的投影点，我当然会
    知道三角形的三个点坐标，通过其中两个点坐标可以求出法向量n。
    假设已知平面为三角形，其三个顶点分别为A（x,y,z）,B(x,y,z), C(x,y,z).
    AB = (Bx-Ax,By-Ay,Bz-Az);AB为向量；
    AC = (Cx-Ax,Cy-Ay,Cz-Az);AC为向量；
    n为法向量
        n = AB X AC
叉积公式：（对应版子中的^运算）
        =>nx = ABy*ACz-ABz*ACy
        ny = ABz*ACx-ABx*ACz
        nz = ABx*ACy-ABy*ACx
注意：以上的Ax是A的x坐标；
ABx指的是AB向量的x分量

*/
point pro(point p)
{
    point pp;
    pp.x = (n.x*n.y*A.y + n.y*n.y*p.x - n.x*n.y*p.y + n.x*n.z*A.z + n.z*n.z*p.x - \
    n.x*n.z*p.z + n.x*n.x*A.x) / (n.x*n.x + n.y*n.y + n.z*n.z);
    pp.y = (n.y*n.z*A.z + n.z*n.z*p.y - n.y*n.z*p.z + n.y*n.x*A.x + n.x*n.x*p.y - \
    n.x*n.y*p.x + n.y*n.y*A.y) / (n.x*n.x + n.y*n.y + n.z*n.z);
    pp.z = (n.x*A.x*n.z + n.x*n.x*p.z - n.x*p.x*n.z + n.y*A.y*n.z + n.y*n.y*p.z - \
    n.y*p.y*n.z + n.z*n.z*A.z) / (n.x*n.x + n.y*n.y + n.z*n.z);
    return pp;
}
