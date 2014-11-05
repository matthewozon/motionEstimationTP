clc
clear all
close all


IM1 = double(imread ('movie_train00000001.tif'));
IM2 = double(imread ('movie_train00000002.tif'));
IM3 = double(imread ('movie_train00000003.tif'));


IMdt = 0.5*(IM3-IM1);

IMdx = zeros(size(IM2,1),size(IM2,2));
IMdx(:,2:end-1) = 0.5*(IM2(:,3:end)-IM2(:,1:end-2));

IMdx(:,end) = IMdx(:,end-1);
IMdx(:,1) = IMdx(:,2);

IMdy = zeros(size(IM2,1),size(IM2,2));
IMdy(2:end-1,:) = 0.5*(IM2(1:end-2,:)-IM2(3:end,:));
IMdy(end,:) = IMdy(end-1,:);
IMdy(1,:) = IMdy(2,:);

IMgradNorm = sqrt(IMdx.^2 + IMdy.^2);

figure(1)
imagesc(IMgradNorm)
colormap gray
title('spatial gradient norm')

figure(2)
imagesc(abs(IMdt))
colormap gray
title('temporal gradient norm')


%for each pixel fully inside the image (5*5 neighborhood)
A = zeros(25,2);
B = zeros(25,1);
V = zeros(size(IM2,1),size(IM2,2),2);
for i=3:5:(size(IM2,1)-2) %y in reverse order
    for j=3:5:(size(IM2,2)-2) %x straight
        %fill in the matrix system
	n=1;
        for di=-2:2
            for dj=-2:2
                A(n,1) = IMdx(i+di,j+dj);
                A(n,2) = IMdy(i+di,j+dj);
                B(n) = -IMdt(i+di,j+dj);
		n = n+1;
            end
        end
	dV = inv(A'*A)*(A'*B);
	V(i,j,:) = dV;
    end
end

V = V(3:5:end,3:5:end,:);

l = 3:5:size(IM2,1);
L = repmat(l',[1, size(V,2)]);
c = 3:5:size(IM2,2);
C = repmat(c,[size(V,1),1]);


figure(3)
imagesc(IM2)
colormap gray
hold on
quiver(C,L,V(:,:,1), V(:,:,2))
hold off
