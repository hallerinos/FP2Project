figure;

xrange=1000;
yrange = 1;

l=subplot( 4,4,1 );
title( l, 'MC Max Step Size: 0.0025' );
data = importdata( '0_0025CorrelationSeries.txt' );
plot( abs(data(1:xrange)) );
axis([1 xrange 10^(-5) yrange]);
l=subplot( 4,4,2 );
data = importdata( '0_0025EnergySeries.txt' );
plot( data );
axis([1 200000 -700 -500]);
title( l, 'MC Max Step Size: 0.0025' );

l=subplot( 4,4,3 );
title( l, 'MC Max Step Size: 0.005' );
data = importdata( '0_005CorrelationSeries.txt' );
plot( abs(data(1:xrange)) );
axis([1 xrange 10^(-5) yrange]);
l=subplot( 4,4,4 );
data = importdata( '0_005EnergySeries.txt' );
plot( data );
axis([1 200000 -700 -500]);
title( l, 'MC Max Step Size: 0.005' );

l=subplot( 4,4,5 );
title( l, 'MC Max Step Size: 0.025' );
data = importdata( '0_025CorrelationSeries.txt' );
plot( abs(data(1:xrange)) );
axis([1 xrange 10^(-5) yrange]);
l=subplot( 4,4,6 );
data = importdata( '0_025EnergySeries.txt' );
plot( data );
axis([1 200000 -700 -500]);
title( l, 'MC Max Step Size: 0.025' );

l=subplot( 4,4,7 );
title( l, 'MC Max Step Size: 0.05' );
data = importdata( '0_05CorrelationSeries.txt' );
plot( abs(data(1:xrange)) );
axis([1 xrange 10^(-5) yrange]);
l=subplot( 4,4,8 );
data = importdata( '0_05EnergySeries.txt' );
plot( data );
axis([1 200000 -700 -500]);
title( l, 'MC Max Step Size: 0.05' );

l=subplot( 4,4,9 );
title( l, 'MC Max Step Size: 0.075' );
data = importdata( '0_075CorrelationSeries.txt' );
plot( abs(data(1:xrange)) );
axis([1 xrange 10^(-5) yrange]);
l=subplot( 4,4,10 );
data = importdata( '0_075EnergySeries.txt' );
plot( data );
axis([1 200000 -700 -500]);
title( l, 'MC Max Step Size: 0.075' );

l=subplot( 4,4,11 );
title( l, 'MC Max Step Size: 0.25' );
data = importdata( '0_25CorrelationSeries.txt' );
plot( abs(data(1:xrange)) );
axis([1 xrange 10^(-5) yrange]);
l=subplot( 4,4,12 );
data = importdata( '0_25EnergySeries.txt' );
plot( data );
axis([1 200000 -700 -500]);
title( l, 'MC Max Step Size: 0.25' );

l=subplot( 4,4,14 );
title( l, 'MC Max Step Size: 0.5' );
data = importdata( '0_5CorrelationSeries.txt' );
plot( abs(data(1:xrange)) );
axis([1 xrange 10^(-5) yrange]);
l=subplot( 4,4,15 );
data = importdata( '0_5EnergySeries.txt' );
plot( data );
axis([1 200000 -700 -500]);
title( l, 'MC Max Step Size: 0.5' );

figure
subplot( 2,1,1 );
title( l, 'MC Max Step Size: 0.02' );
data = importdata( '0_02CorrelationSeries.txt' );
plot( abs(data(1:xrange)) );
axis([1 xrange 10^(-5) yrange]);
l=subplot( 2,1,2 );
data = importdata( '0_02EnergySeries.txt' );
plot( data );
axis([1 50000 -1000 -500]);
title( l, 'MC Max Step Size: 0.02' );
