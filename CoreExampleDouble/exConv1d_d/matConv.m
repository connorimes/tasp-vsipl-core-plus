c=conv(h,x);
cF = c(1:decimation:end);
first  = 1 + floor(kernel_len/2);
length = floor((data_len-1)/decimation) + 1;
last = first + (length - 1) * decimation;
cS = c(first:decimation:last);
first = kernel_len;
length = floor((data_len-1)/decimation) - floor((kernel_len-1)/decimation) + 1;
last = first + (length -1) * decimation;
cM = c(first:decimation:last);