data = importdata( '0.007000Snapshots.txt' );
energy = importdata( '0.007000EnergySeries.txt' );
numOfPart = 1000;
limits = [0 11.5 0 11.5];
scrsz = get(0,'ScreenSize');
figure('Position',[1 scrsz(4) scrsz(3) scrsz(4)]);
for i = 1:500
    subplot(2,2,1)
    DataDensityPlot(data((i-1)*numOfPart+1:i*numOfPart,1),...
        data((i-1)*numOfPart+1:i*numOfPart,2),...
        50,limits)
    xlabel('x');
    ylabel('y');
    subplot(2,2,2)
    DataDensityPlot(data((i-1)*1000+1:i*1000,1),data((i-1)*1000+1:i*1000,3),...
        50,limits)
    xlabel('x');
    ylabel('z');
    subplot(2,2,3)
    DataDensityPlot(data((i-1)*1000+1:i*1000,2),data((i-1)*1000+1:i*1000,3),...
        50,limits)
    xlabel('y');
    ylabel('z');
    subplot(2,2,4)
    plot( energy(1:i) );
    title( 'Energy' );
    M(i)=getframe(gcf);
end 

% movie2avi(M,'MCMovie.avi');