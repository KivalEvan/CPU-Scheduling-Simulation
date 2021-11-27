function p=bisection(a,b,tol)
%Bisection method for solving the non linear equation f(x)=0.

err=tol+1;

if f(a)*f(b)<0
    disp('root exists');
    n=1; %first iteration
    a(n)=a;
    b(n)=b;
    p(n)=(a(n)+b(n))/2;
    while(error>tol)
        if f(a(n))*f(p(n))>0
            a(n+1)=p(n);
            b(n+1)=b(n);
        elseif f(a(n))*f(p(n))<0
            a(n+1)=a(n);
            b(n+1)=p(n);
        end;
        %next iteration:
        p(n+1)=(a(n+1)+b(n+1))/2;
        err=abs(p(n+1)-p(n));
        n=n+1;
    end;
    disp('iteration a b p f(a) f(p) f(a)f(p)');
    for i=1:n
        fprintf('%2.0f %10.6f %10.6f %10.6f %10.6f %10.6f %10.6f\n', [i a(i) b(i) p(i) f(a(i)) f(p(i)) f(a(i))*f(p(i))]); 
    end;
end;