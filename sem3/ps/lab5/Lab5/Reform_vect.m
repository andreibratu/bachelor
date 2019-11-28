function [vnew]=Reform_vect(v)
lv=max(size(v)); % or lv=length(v);
lvnew=sum(v(2,:));
vnew=zeros(1,lvnew);
ji=1;
for i=1:lv
    jf=ji+v(2,i)-1;
    vnew(ji:jf)=v(1,i);
    ji=jf+1;    
end