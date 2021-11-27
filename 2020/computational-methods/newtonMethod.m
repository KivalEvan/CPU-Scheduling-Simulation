function p = newtonMethod(a,tol)
    
    err = tol + 1;
    
    % first iteration
    n = 2;
    
    p(1) = a;
    
    while(err > tol)
        p(n) = p(n-1) - f(p(n-1)) / df(p(n-1));
        
        err = abs(p(n) - p(n-1));
        
        n = n + 1;
    end
    
    output = p;