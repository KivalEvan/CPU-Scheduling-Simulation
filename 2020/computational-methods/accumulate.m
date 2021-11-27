function y=accumulate(x,range)
y = 0;
for i=1:range
	y = y + x(i);
end