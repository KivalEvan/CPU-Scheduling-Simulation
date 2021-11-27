function output = trapezoidalRule(a,b,n)
    
    h=(b-a)/n;
    x=a:h:b;
    
    weights=[1, 2*ones(1,n-1), 1];
    
    I = (h/2)*f(x)*weights';
    
    output=I;