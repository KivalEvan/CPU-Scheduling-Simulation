function p = secantMethod(a,b,tol)
    
    err = tol + 1;
    
    % first iteration
    n = 2;
    
    p(1) = a;
    p(2) = b;
    
    while(err > tol)
        p(n+1) = p(n) - (f(p(n)) * (p(n) - p(n-1))) / (f(p(n)) - f(p(n-1)));
        err = abs(p(n+1) - p(n))
        
        n = n + 1;
    end
    
    output = p;
    end