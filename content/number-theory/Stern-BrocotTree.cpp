P ask(){
	int l0=0,l1=1,r0=1,r1=0,m0,m1;
	while(1){
		m0=l0+r0,m1=l1+r1;
		if(m1>100000)break;
		if(equal(m0/m1))return P(m0,m1);
		if(should_bigger())l0=m0,l1=m1;else r0=m0,r1=m1;
	}
	compare(l0/l1,r0/r1);
}
