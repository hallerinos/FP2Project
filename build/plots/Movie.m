data = importdata( '0.020000Snapshots.txt' );
energy = importdata( '0.020000EnergySeries.txt' );
numOfPart = 250;
scrsz = get(0,'ScreenSize');
figure('Name','Simulation Plot Window','NumberTitle','off','Position',[1 scrsz(4) scrsz(3) scrsz(4)]);
for i = 1:2
    subplot(2,2,1)
    DataDensityPlot(data((i-1)*numOfPart+1:i*numOfPart,1), data((i-1)*numOfPart+1:i*numOfPart,2), 50);
    xlabel('x');
    ylabel('y');
    subplot(2,2,2)
    DataDensityPlot(data((i-1)*numOfPart+1:i*numOfPart,1), data((i-1)*numOfPart+1:i*numOfPart,3), 50);
    xlabel('x');
    ylabel('z');
    subplot(2,2,3)
    DataDensityPlot(data((i-1)*numOfPart+1:i*numOfPart,2), data((i-1)*numOfPart+1:i*numOfPart,3), 50);
    xlabel('y');
    ylabel('z');
    subplot(2,2,4)
    plot( energy(1:i) );
    title( 'Energy' );
    M(i)=getframe(gcf);
end 

movie2avi(M,'MCMovie.avi');