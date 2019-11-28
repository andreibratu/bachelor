function [vu,VectRelFr]=Fr_rel(v)

vu=unique(v);
lu=length(vu);


fr=zeros(1,lu);
for j=1:lu
  fr(j)=sum(v==vu(j));
end

VectRelFr=fr/length(v);