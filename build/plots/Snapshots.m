numOfPart = 1000;
limits = [0 11.5 0 11.5];
scrsz = get(0,'ScreenSize');
for i = 1:10
    figure('Name', ['Snapshot' num2str(i)] , 'Position',[1 scrsz(4) scrsz(3) scrsz(4)]);
    data = importdata( ['T_0.700000_rho_0.700000Snap' num2str((i-1)*10000) '.txt'] );
    subplot(2,2,1)
    DataDensityPlot(data(1:numOfPart,1),data(1:numOfPart,2),...
        50,limits)
    xlabel('x');
    ylabel('y');
    subplot(2,2,2)
    DataDensityPlot(data(1:numOfPart,1),data(1:numOfPart,3),...
        50,limits)
    xlabel('x');
    ylabel('z');
    subplot(2,2,3)
    DataDensityPlot(data(1:numOfPart,2),data(1:numOfPart,3),...
        50,limits)
    xlabel('y');
    ylabel('z');
    M(i)=getframe(gcf);
end