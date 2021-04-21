function [H]=HermitePol(t,d,v,x)
  % t = node interpolation vector
  % d = the value of the function calc in t vector
  % v = the value of the derivative of the function calc in t vector
  % x = the vector of the elements in witch we want to aproxx the function

  l=length(t);
   
  z=zeros(1,2*l);  z(1:2:end)=t; z(2:2:end)=t; % sau z=reshape([t;t], 1, []);
  f=zeros(1,2*l);  f(1:2:end)=d; f(2:2:end)=d; % sau f=reshape([d;d], 1, []);

  m=zeros(2*l,2*l); % m = matrix of divided diff table
  m(:,1)=f';
  m(1:2:end,2)=v';
  m(2:2:2*l-1,2)=(d(2:l)-d(1:l-1))./(t(2:l)-t(1:l-1));
  for k=3:2*l
      for i=1:2*l-k+1
          m(i,k)=(m(i+1,k-1)-m(i,k-1))/(z(i+k-1)-z(i));
      end
  end

  lx=length(x);   # the Hermite interpolation
  p=ones(lx,1);
  s=m(1,1)*ones(lx,1);   % --> f(z0) = m(1,1)
  for j=1:lx
    for i=1:2*l-1
      p(j)=p(j)*(x(j)-z(i));
      s(j)=s(j)+p(j)*m(1,i+1);
    end
  end

  H=s';
 endfunction