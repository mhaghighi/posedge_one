im1 = imread('im1.tif');
subplot(1,2,1)
imshow(im1)
im1_vec = double(im1(:)');
tic;
b = afifo3(im1_vec);
tt = toc;
disp(['elapsed time: ', num2str(tt), ' s']);
b1 = uint8(reshape(b, [480, 640]));
subplot(1,2,2)
imshow(b1)