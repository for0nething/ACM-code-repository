inline void FMT(int *x) {
	for(int i=1;i<lim;i<<=1)
		for(int j=0;j<lim;++j)
			if(j&i)
				addi(x[j],x[j^i]);
}
inline void IFMT(int *x) {
	for(int i=1;i<lim;i<<=1)
		for(int j=0;j<lim;++j)
			if(j&i)
				subi(x[j],x[j^i]);
}
inline void FWTand(int *x) {
	for(int i=1;i<lim;i<<=1)
		for(int j=0;j<lim;j+=(i<<1))
			for(int k=0;k<i;++k)
				addi(x[j+k],x[j+k+i]);
}
inline void IFWTand(int *x) {
	for(int i=1;i<lim;i<<=1)
		for(int j=0;j<lim;j+=(i<<1))
			for(int k=0;k<i;++k)
				subi(x[j+k],x[j+k+i]);
}
inline void FWTxor(int *x) {
	for(int i=1;i<lim;i<<=1)
		for(int j=0;j<lim;j+=(i<<1))
			for(int k=0;k<i;++k) {
				int y=x[j+k],z=x[j+k+i];
				x[j+k]=add(y,z),x[j+k+i]=sub(y,z);
			}
}
inline void IFWTxor(int *x) {
	for(int i=1;i<lim;i<<=1)
		for(int j=0;j<lim;j+=(i<<1))
			for(int k=0;k<i;++k) {
				int y=x[j+k],z=x[j+k+i];
				x[j+k]=half(add(y,z)),x[j+k+i]=half(sub(y,z));
			}
}
