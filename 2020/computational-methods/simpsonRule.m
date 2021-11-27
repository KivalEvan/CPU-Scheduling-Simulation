function output = simpsonRule(a,b,n)
    
    h=(b-a)/n;
    x=a:h:b;
    
    weights=[1, 2*mod(1:n-1,2)+2, 1];
    
    I = (h/3)*f(x)*weights';
    
    output = I;