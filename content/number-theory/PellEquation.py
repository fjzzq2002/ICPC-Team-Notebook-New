# Pell equation solver, solves x^2 - n*y^2 = 1
# x[k] + y[k] sqrt(n) = (x[1] + y[1] sqrt(n))^k
def solve(n):
    j=1
    while j*j<n: j+=1
    if j*j==n:
        return (-1,-1)
    p,q,a,g,h=[[0 for _ in range(1001)]for _ in range(5)]
    p[1]=q[0]=h[1]=1
    p[0]=q[1]=g[1]=0
    a[2]=j-1
    i=2
    while 1:
        g[i]=-g[i-1]+a[i]*h[i-1]
        h[i]=(n-g[i]*g[i])//h[i-1]
        a[i+1]=(g[i]+a[2])//h[i]
        p[i]=a[i]*p[i-1]+p[i-2]
        q[i]=a[i]*q[i-1]+q[i-2]
        if(p[i]*p[i]-n*q[i]*q[i]==1):
          return (p[i],q[i])
        i+=1
