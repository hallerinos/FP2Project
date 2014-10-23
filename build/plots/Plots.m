% Creates a 2D Mesh to plot surface
x=linspace(0,1,100);
[X,Y] = meshgrid(x,x);

N=100; % Number of frames
for i = 1:N
    % Example of plot 
    Z = sin(2*pi*(X-i/N)).*sin(2*pi*(Y-i/N));
    surf(X,Y,Z)
    
    % Store the frame   
    M(i)=getframe(gcf); % leaving gcf out crops the frame in the movie. 
end 

% Output the movie as an avi file
movie2avi(M,'WaveMovie.avi');