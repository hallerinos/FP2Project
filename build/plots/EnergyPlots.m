data = importdata( 'EnergySeries.txt' );

plot(data(:));

corr=zeros(length(data),1);
for n=1:10000
    for i=1:length(data)-n
        corr(n) = corr(n) + data(i)*data(i+n);
    end
    corr(n) = corr(n)/length(data);
end

plot( corr(1:2000) )