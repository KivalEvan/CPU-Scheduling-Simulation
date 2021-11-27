function output= rombergInt(a,b,r)
    %r is no of rows
    R=zeros(r,r)
    R(1,1)=trapezoidalRule(a,b,1);
    
    for n=2:r
        R(n,1)=trapezoidalRule(a,b,2*(n-1));
        for n=2:n
            R(n,m)=R(n,m-1)+(R(n,m-1)-R(n-1,m-1)) / (4^(m-1)-1);
        end
    end
    
    output = R;